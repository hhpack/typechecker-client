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
    $files = $result->filter(($item) ==> {
        return $item instanceof File;
    });

    foreach ($files as $file) {
        $formattedParsentage = sprintf('%6.2f%%', (float) $file->parsentage() * 100); 
        echo $formattedParsentage, ' ', $file->name(), PHP_EOL;
    }

    $directories = $result->filter(($item) ==> {
        return $item instanceof Directory;
    });

    foreach ($directories as $directory) {
        $formattedParsentage = sprintf('%6.2f%%', (float) $directory->parsentage() * 100); 
        echo $formattedParsentage, ' ', $directory->name(), PHP_EOL;
    }
}

coverage_select_main(realpath(__DIR__ . '/../'));
