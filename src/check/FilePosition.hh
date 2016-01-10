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
        private int $lineNumber,
        private IntegerRange $columnRange
    )
    {
    }

    public function getLineNumber() : int
    {
        return $this->lineNumber;
    }

    public function getStartColumnNumber() : int
    {
        return $this->columnRange->first();
    }

    public function getEndColumnNumber() : int
    {
        return $this->columnRange->last();
    }

}
