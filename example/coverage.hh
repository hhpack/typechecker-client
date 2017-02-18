<?hh // partial

namespace HHPack\TypeChecker;

require_once __DIR__ . '/../vendor/autoload.php';

use HHPack\TypeChecker\Visitor;
use HHPack\TypeChecker\TypeCheckerClient;
use HHPack\TypeChecker\Coverage\ResultNode;

async function coverage_main(string $cwd) : Awaitable<void>
{
    $client = new TypeCheckerClient($cwd);
    await $client->restart();

    $result = await $client->coverage();

    $reporter = new Reporter();
    await $reporter->report($result);
}

final class Reporter
{

    private Visitor<ResultNode> $visitor;

    public function __construct()
    {
        $this->visitor = new ReportVisitor();
    }

    public async function report(ResultNode $node) : Awaitable<void>
    {
        await async {
          $this->visitor->visit($node);
        };
    }

}

final class ReportVisitor implements Visitor<ResultNode>
{

    private int $indent = 0;

    public function visit(ResultNode $node) : void
    {
        echo str_pad(" ", $this->indent * 2), $node->name(), " - ", $node->parsentage(), PHP_EOL;

        if (!$node->hasChildren()) {
            return;
        }

        $this->indent++;
        foreach ($node->children()->lazy() as $name => $childNode) {
            $this->visit($childNode);
        }
        $this->indent--;
    }

}

coverage_main(realpath(__DIR__ . '/../'));
