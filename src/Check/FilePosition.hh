<?hh //strict

/**
 * This file is part of hhpack\typechecker package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\TypeChecker\Check;

use HHPack\TypeChecker\Range\IntegerRange;

final class FilePosition
{

    public function __construct(
        private int $lineNumber,
        private IntegerRange $columnRange
    )
    {
    }

    public function lineNumber() : int
    {
        return $this->lineNumber;
    }

    public function startColumnNumber() : int
    {
        return $this->columnRange->first();
    }

    public function endColumnNumber() : int
    {
        return $this->columnRange->last();
    }

}
