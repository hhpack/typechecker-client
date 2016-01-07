<?hh //strict

/**
 * This file is part of hhpack\typechecker package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\typechecker\coverage;

final class Coverage
{

    public function __construct(
        private int $checked,
        private int $partial,
        private int $unchecked
    )
    {
    }

    public function parsentage() : float
    {
        return (float) $this->checked / $this->total();
    }

    public function total() : int
    {
        return $this->checked + $this->partial + $this->unchecked;
    }

}
