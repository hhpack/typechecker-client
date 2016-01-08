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

trait VisitorAcceptable
{
    require implements CoverageNode;

    public function accept(Visitor<CoverageNode> $visitor) : void
    {
        $visitor->visit($this);
    }
}
