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

final class TypeCheckerClient implements ClientSpecification
{

    const PROGRAM = 'hh_client';

    public async function restart(?string $cwd = (string) getcwd()) : Awaitable<void>
    {
        await Process::exec( $this->command('restart') );
    }

    public async function check(?string $cwd = (string) getcwd()) : Awaitable<Result>
    {
        $result = await Process::exec( $this->command('check', [ '--json' ]));
        return Result::fromString((string) $result->getStderr());
    }

    private function command(string $command, Traversable<string> $args = []) : string
    {
        $builder = Set {};
        $builder->add('%s %s %s');
        $builder->addAll([ static::PROGRAM, $command, implode(' ', $args) ]);

        return call_user_func_array('sprintf', $builder->toValuesArray());
    }

}
