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

final class ColumnRange
{

    use IntegerRange;

    public function __construct(
        ColumnNumber $first,
        ColumnNumber $last
    )
    {
        $this->first = $first;
        $this->last = $last;
        $this->validate();
    }

    public function getStartColumnNumber() : ColumnNumber
    {
        return $this->first;
    }

    public function getEndColumnNumber() : ColumnNumber
    {
        return $this->last;
    }

}
