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
use HHPack\TypeChecker\Coverage\ResultNode;

interface ClientBehavior
{
    public function version() : Awaitable<version>;
    public function init() : Awaitable<configurationPath>;
    public function start() : Awaitable<void>;
    public function stop() : Awaitable<void>;
    public function restart() : Awaitable<void>;
    public function check() : Awaitable<Result>;
    public function coverage() : Awaitable<ResultNode>;
}
