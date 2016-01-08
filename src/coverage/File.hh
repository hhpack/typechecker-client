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

final class File extends CoverageNode implements ResultNode, FromOptions<FileOptions>
{

    public function __construct(
        string $name,
        ImmMap<string, Coverage> $result
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
        return false;
    }

    public function children() : ImmMap<string, ResultNode>
    {
        return ImmMap {};
    }

    public static function fromOptions(FileOptions $options) : this
    {
        return new static(
            $options['name'],
            $options['result']
        );
    }

}
