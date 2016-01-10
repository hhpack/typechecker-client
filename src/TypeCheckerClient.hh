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
use hhpack\typechecker\coverage\ResultNode;
use hhpack\typechecker\coverage\CoverageReportDecoder;
use hhpack\process;
use hhpack\process\ExecOptions;
use RuntimeException;


final class TypeCheckerClient implements ClientBehavior
{

    const PROGRAM = 'hh_client';

    public function __construct(
        private string $cwd = (string) getcwd()
    )
    {
    }

    public async function version() : Awaitable<Version>
    {
        $options = new ExecOptions($this->cwd);

        $result = await process\exec( $this->command('', [ '--version' ]), $options );
        $version = (string) $result->stdout();

        return trim($version);
    }

    public async function init() : Awaitable<ConfigurationPath>
    {
        $path = realpath($this->cwd) . '/.hhconfig';

        if (touch($path) === false) {
            throw new RuntimeException('Failed to generate .hhconfig');
        }

        return $path;
    }

    public async function start() : Awaitable<void>
    {
        $options = new ExecOptions($this->cwd);
        await process\exec( $this->command('start'), $options );
    }

    public async function stop() : Awaitable<void>
    {
        $options = new ExecOptions($this->cwd);
        await process\exec( $this->command('stop'), $options );
    }

    public async function restart() : Awaitable<void>
    {
        $options = new ExecOptions($this->cwd);
        await process\exec( $this->command('restart'), $options );
    }

    public async function check() : Awaitable<Result>
    {
        $options = new ExecOptions($this->cwd);

        $result = await process\exec( $this->command('check', [ '--json' ]), $options);
        return Result::fromString((string) $result->stderr());
    }

    public async function coverage() : Awaitable<ResultNode>
    {
        $options = new ExecOptions($this->cwd);
        $cmd = $this->command('check', [ '--json', '--coverage', $this->cwd ]);

        $result = await process\exec($cmd, $options);

        $decoder = new CoverageReportDecoder($this->cwd);
        return $decoder->decode((string) $result->stdout());
    }

    private function command(string $command, Traversable<string> $args = []) : string
    {
        $builder = Set {};
        $builder->add('%s %s %s');
        $builder->addAll([ static::PROGRAM, $command, implode(' ', $args) ]);

        return call_user_func_array('sprintf', $builder->toValuesArray());
    }

}
