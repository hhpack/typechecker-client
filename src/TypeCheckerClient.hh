<?hh //strict

/**
 * This file is part of hhpack\typechecker package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\TypeChecker;

use HHPack\TypeChecker\Check\Result;
use HHPack\TypeChecker\Check\TypeCheckReportDecoder;
use HHPack\TypeChecker\Coverage\ResultNode;
use HHPack\TypeChecker\Coverage\CoverageReportDecoder;
use HHPack\Process;
use HHPack\Process\ExecOptions;
use RuntimeException;


final class TypeCheckerClient implements ClientBehavior
{

    const PROGRAM = 'hh_client';

    public function __construct(
        private string $cwd = (string) getcwd()
    )
    {
    }

    public async function version() : Awaitable<version>
    {
        $options = new ExecOptions($this->cwd);

        $result = await Process\exec( $this->command('', [ '--version' ]), $options );
        $version = (string) $result->stdout();

        return trim($version);
    }

    public async function init() : Awaitable<configurationPath>
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
        await Process\exec( $this->command('start'), $options );
    }

    public async function stop() : Awaitable<void>
    {
        $options = new ExecOptions($this->cwd);
        await Process\exec( $this->command('stop'), $options );
    }

    public async function restart() : Awaitable<void>
    {
        $options = new ExecOptions($this->cwd);
        await Process\exec( $this->command('restart'), $options );
    }

    public async function check() : Awaitable<Result>
    {
        $options = new ExecOptions($this->cwd);
        $result = await Process\exec( $this->command('check', [ '--json' ]), $options);

        $decoder = new TypeCheckReportDecoder();
        return $decoder->decode((string) $result->stderr());
    }

    public async function coverage() : Awaitable<ResultNode>
    {
        $options = new ExecOptions($this->cwd);
        $cmd = $this->command('check', [ '--json', '--coverage', $this->cwd ]);

        $result = await Process\exec($cmd, $options);

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
