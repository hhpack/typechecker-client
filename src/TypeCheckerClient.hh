<?hh //strict

/**
 * This file is part of hhpack\typechecker package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\typechecker;

use hhpack\typechecker\check\Result;
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
