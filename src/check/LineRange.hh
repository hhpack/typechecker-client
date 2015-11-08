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

final class LineRange
{

    public function __construct
    (
        private int $startAt,
        private int $endAt
    )
    {
    }

    public function getStartLineNumber() : LineNumber
    {
        return $this->startAt;
    }

    public function getEndLineNumber() : LineNumber
    {
        return $this->endAt;
    }

}
