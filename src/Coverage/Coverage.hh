<?hh //strict

/**
 * This file is part of hhpack\typechecker package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\TypeChecker\Coverage;

final class Coverage
{

    public function __construct(
        private int $checked,
        private int $partial,
        private int $unchecked
    )
    {
    }

    public function checked() : int
    {
        return $this->checked;
    }

    public function partial() : int
    {
        return $this->partial;
    }

    public function unchecked() : int
    {
        return $this->unchecked;
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
