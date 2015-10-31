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
    public function getVersion() : Awaitable<Version>;
    public function generateConfiguration() : Awaitable<ConfigurationPath>;
    public function restartServer() : Awaitable<void>;
    public function verifyType() : Awaitable<Result>;
}
