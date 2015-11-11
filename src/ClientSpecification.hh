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

interface ClientSpecification
{
    public function version() : Awaitable<Version>;
    public function init() : Awaitable<ConfigurationPath>;
    public function start() : Awaitable<void>;
    public function stop() : Awaitable<void>;
    public function restart() : Awaitable<void>;
    public function check() : Awaitable<Result>;
}
