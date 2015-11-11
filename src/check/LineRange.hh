<?hh //strict

/**
 * This file is part of hhpack\typechecker package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\typechecker\check;

use hhpack\typechecker\range\IntegerRange;

final class LineRange
{

    use IntegerRange;

    public function __construct
    (
        int $first,
        int $last
    )
    {
        $this->first = $first;
        $this->last = $last;
        $this->validate();
    }

    public function getStartLineNumber() : LineNumber
    {
        return $this->first;
    }

    public function getEndLineNumber() : LineNumber
    {
        return $this->last;
    }

    public static function onlyAt(LineNumber $lineAt) : this
    {
        return new static($lineAt, $lineAt);
    }

    public static function between(LineNumber $first, LineNumber $last) : this
    {
        return new static($first, $last);
    }

}
