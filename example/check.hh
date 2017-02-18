<?hh // partial

namespace HHPack\TypeChecker;

require_once __DIR__ . '/../vendor/autoload.php';

use HHPack\TypeChecker\TypeCheckerClient;

async function check_main(string $cwd) : Awaitable<void>
{
    $client = new TypeCheckerClient($cwd);

    $version = await $client->version();
    echo $version, PHP_EOL;

    await $client->restart();
    $result = await $client->check();

    if ($result->isOk()) {
        echo 'Type check Passed', PHP_EOL;
        return;
    }

    echo 'Type check Failed', PHP_EOL;
}

check_main(realpath(__DIR__ . '/../'));
