<?hh // partial

namespace hhpack\typechecker;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\typechecker\Visitor;
use hhpack\typechecker\TypeCheckerClient;
use hhpack\typechecker\coverage\CoverageNode;

async function coverage_main(string $cwd) : Awaitable<void>
{
    $client = new TypeCheckerClient($cwd);
    await $client->restart();

    $result = await $client->coverage();

    await async {
      $visitor = new ReportVisitor();
      $visitor->visit($result);
    };
}

final class ReportVisitor implements Visitor<CoverageNode>
{

    private int $indent = 0;

    public function visit(CoverageNode $node) : void
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
