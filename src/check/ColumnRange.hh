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


final class ColumnRange
{

    public function __construct
    (
        private ColumnNumber $startColumnNumber,
        private ColumnNumber $endColumnNumber
    )
    {
    }

    public function getStartColumnNumber() : ColumnNumber
    {
        return $this->startColumnNumber;
    }

    public function getEndColumnNumber() : ColumnNumber
    {
        return $this->endColumnNumber;
    }

}
