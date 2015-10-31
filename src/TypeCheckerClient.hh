<?hh //strict

namespace hhpack\typechecker;

use hhpack\process\Process;

final class TypeCheckerClient implements Client
{

    public async function restart(?string $cwd = (string) getcwd()) : Awaitable<void>
    {
        await Process::exec('hh_client restart');
    }

    public async function check(?string $cwd = (string) getcwd()) : Awaitable<Result>
    {
        $result = await Process::exec('hh_client check --json');
        return Result::fromString((string) $result->getStderr());
    }

}
