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

trait CoverageCalculatable
{

    require implements ResultNode;

    private int $checked = 0;
    private int $partial = 0;
    private int $unchecked = 0;
    private int $total = 0;

    private function calculate(KeyedTraversable<string, Coverage> $result) : void
    {
        foreach ($result as $_ => $coverage) {
            $this->checked += $coverage->checked();
            $this->partial += $coverage->partial();
            $this->unchecked += $coverage->unchecked();
            $this->total += $coverage->total();
        }
    }

    public function parsentage() : float
    {
        if ($this->total <= 0) {
            return 0.0;
        }

        return (float) $this->checked / $this->total;
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

    public function total() : int
    {
        return $this->total;
    }

}
