<?hh // partial

namespace hhpack\typesafety;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\typechecker\TypeCheckerClient;

async function main(string $cwd) : Awaitable<void>
{
    $client = new TypeCheckerClient($cwd);

    $version = await $client->version();
    echo $version, PHP_EOL;

    await $client->restart();
    $result = await $client->check();

    if ($result->isPassed()) {
        echo 'Type check Passed', PHP_EOL;
        return;
    }

    echo 'Type check Failed', PHP_EOL;
}

main(realpath(__DIR__ . '/../'));
