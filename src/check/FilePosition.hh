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

final class FilePosition
{

    public function __construct(
        private LineNumber $lineNumber,
        private IntegerRange $columnRange
    )
    {
    }

    public function getLineNumber() : LineNumber
    {
        return $this->lineNumber;
    }

    public function getStartColumnNumber() : ColumnNumber
    {
        return $this->columnRange->first();
    }

    public function getEndColumnNumber() : ColumnNumber
    {
        return $this->columnRange->last();
    }

}
