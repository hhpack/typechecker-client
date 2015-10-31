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

interface Client
{
    public function restart(?string $cwd = (string) getcwd()) : Awaitable<void>;
    public function check(?string $cwd = (string) getcwd()) : Awaitable<Result>;
}
