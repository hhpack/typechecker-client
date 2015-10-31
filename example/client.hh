<?hh // partial

namespace hhpack\typesafety;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\typechecker\TypeCheckerClient;

async function main(string $cwd) : Awaitable<void>
{
    $client = new TypeCheckerClient();
    await $client->restart($cwd);
    $result = await $client->check($cwd);

    if ($result->isPassed()) {
        echo 'Type check Passed', PHP_EOL;
        return;
    }

    echo 'Type check Failed', PHP_EOL;
}

main(realpath(__DIR__ . '/../'));
