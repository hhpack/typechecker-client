<?hh // partial

namespace HHPack\TypeChecker;

require_once __DIR__ . '/../vendor/autoload.php';

use HHPack\TypeChecker\Visitor;
use HHPack\TypeChecker\TypeCheckerClient;
use HHPack\TypeChecker\Coverage\File;
use HHPack\TypeChecker\Coverage\Directory;
use HHPack\TypeChecker\Coverage\ResultNode;

async function coverage_select_main(string $cwd) : Awaitable<void>
{
    $client = new TypeCheckerClient($cwd);
    await $client->restart();

    $result = await $client->coverage();
    $files = $result->filter(($file) ==> $file instanceof File)
        ->filter(($file) ==> preg_match('/typechecker-client\/src/', $file->name()) === 1);

    echo 'Files:', PHP_EOL;

    foreach ($files as $file) {
        $formattedParsentage = sprintf('%6.2f%%', (float) $file->parsentage() * 100);
        echo $formattedParsentage, ' ', $file->name(), PHP_EOL;
    }
    echo PHP_EOL;

    $directories = $result->filter(($directory) ==> $directory instanceof Directory)
        ->filter(($directory) ==> preg_match('/typechecker-client\/src/', $directory->name()) === 1);

    echo 'Directories:', PHP_EOL;

    foreach ($directories as $directory) {
        $formattedParsentage = sprintf('%6.2f%%', (float) $directory->parsentage() * 100);
        echo $formattedParsentage, ' ', $directory->name(), PHP_EOL;
    }
}

coverage_select_main(realpath(__DIR__ . '/../'));
