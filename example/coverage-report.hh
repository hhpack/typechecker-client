<?hh // partial

namespace hhpack\typechecker;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\typechecker\Visitor;
use hhpack\typechecker\TypeCheckerClient;
use hhpack\typechecker\coverage\File;
use hhpack\typechecker\coverage\Directory;
use hhpack\typechecker\coverage\ResultNode;

async function coverage_select_main(string $cwd) : Awaitable<void>
{
    $client = new TypeCheckerClient($cwd);
    await $client->restart();

    $result = await $client->coverage();
    $files = $result->select(fun('hhpack\typechecker\file_selector'));

    foreach ($files as $file) {
        $formattedParsentage = sprintf('%6.2f%%', (float) $file->parsentage() * 100); 
        echo $formattedParsentage, ' ', $file->name(), PHP_EOL;
    }
}

function file_selector(ResultNode $node) : Iterator<ResultNode>
{
    if ($node instanceof File) {
        yield $node;
    } else {
        $files = $node->children()->filter(($childNode) ==> {
            return $childNode instanceof File;
        })->toImmVector();

        foreach ($files as $file) {
            yield $file;
        }

        $directories = $node->children()->filter(($childNode) ==> {
            return $childNode instanceof Directory;
        })->toImmVector();

        foreach ($directories as $directory) {
            $files = file_selector($directory);

            foreach ($files as $file) {
                yield $file;
            }
        }
    }
}

coverage_select_main(realpath(__DIR__ . '/../'));
