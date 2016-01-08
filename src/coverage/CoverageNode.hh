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

interface CoverageNode
{
    public function name() : string;
    public function parsentage() : float;
    public function checked() : int;
    public function partial() : int;
    public function unchecked() : int;
    public function total() : int;
    public function hasChildren() : bool;
    public function children() : ImmMap<string, CoverageNode>;
    public function accept(Visitor<CoverageNode> $visitor) : void;
}
