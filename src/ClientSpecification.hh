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
    public function clientVersion() : Awaitable<Version>;
    public function generateConfiguration() : Awaitable<ConfigurationPath>;
    public function startServer() : Awaitable<void>;
    public function stopServer() : Awaitable<void>;
    public function restartServer() : Awaitable<void>;
    public function check() : Awaitable<Result>;
}
