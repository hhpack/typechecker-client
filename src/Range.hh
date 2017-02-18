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

interface Range<T>
{
    public function first() : T;
    public function last() : T;
    public function contains(T $value) : bool;
    public static function only(T $value) : this;
    public static function between(T $first, T $last) : this;
}
