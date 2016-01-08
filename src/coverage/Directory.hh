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

final class Directory implements CoverageNode, FromOptions<DirectoryOptions>
{

    use CoverageCalculatable;

    public function __construct(
        private string $name,
        private ImmMap<string, Coverage> $result,
        private ImmMap<string, CoverageNode> $children
    )
    {
        $this->calculate($result);
    }

    public function name() : string
    {
        return $this->name;
    }

    public function hasChildren() : bool
    {
        return $this->children->isEmpty() === false;
    }

    public function children() : ImmMap<string, CoverageNode>
    {
        return $this->children;
    }

    public function accept(Visitor<CoverageNode> $visitor) : void
    {
        $visitor->visit($this);
    }

    public static function fromOptions(DirectoryOptions $options) : this
    {
        return new static(
            $options['name'],
            $options['result'],
            $options['children']
        );
    }

}
