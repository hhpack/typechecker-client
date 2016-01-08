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

use hhpack\typechecker\Visitor;
use hhpack\typechecker\VisitorAcceptable;
use hhpack\typechecker\Selectable;

abstract class CoverageNode implements ResultNode, VisitorAcceptable<ResultNode>, Selectable<ResultNode>
{

    protected string $name;
    protected ImmMap<string, Coverage> $result;
    private int $checked = 0;
    private int $partial = 0;
    private int $unchecked = 0;
    private int $total = 0;

    public function name() : string
    {
        return $this->name;
    }

    public function result() : ImmMap<string, Coverage>
    {
        return $this->result;
    }

    protected function calculate(KeyedTraversable<string, Coverage> $result) : void
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

    public function accept(Visitor<ResultNode> $visitor) : void
    {
        $visitor->visit($this);
    }

    public function select((function(ResultNode) : Iterator<ResultNode>) $selector) : Iterator<ResultNode>
    {
        return $selector($this);
    }

}
