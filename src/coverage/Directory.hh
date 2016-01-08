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

final class Directory extends CoverageNode implements ResultNode, FromOptions<DirectoryOptions>
{

    public function __construct(
        string $name,
        ImmMap<string, Coverage> $result,
        private ImmMap<string, ResultNode> $children
    )
    {
        $this->name = $name;
        $this->result = $result;
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

    public function children() : ImmMap<string, ResultNode>
    {
        return $this->children;
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
