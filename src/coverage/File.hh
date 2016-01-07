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
use hhpack\typechecker\FromOptions;

final class File implements CoverageNode, FromOptions<FileOptions>
{

    public function __construct(
        private string $name,
        private ImmMap<string, Coverage> $result
    )
    {
    }

    public function name() : string
    {
        return $this->name;
    }

    public function parsentage() : float
    {
        $checked = 0;

        foreach ($this->result->lazy() as $_ => $coverage) {
            $checked += $coverage->checked();
        }

        if ($this->total() <= 0) {
            return 0.0;
        }

        return (float) $checked / $this->total();
    }

    public function total() : int
    {
        $total = 0;

        foreach ($this->result->lazy() as $_ => $coverage) {
            $total += $coverage->total();
        }

        return $total;
    }

    public function hasChildren() : bool
    {
        return false;
    }

    public function children() : ImmMap<string, CoverageNode>
    {
        return ImmMap {};
    }

    public function accept(Visitor<CoverageNode> $visitor) : void
    {
        $visitor->visit($this);
    }

    public static function fromOptions(FileOptions $options) : this
    {
        return new static(
            $options['name'],
            $options['result']
        );
    }

}
