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

use HHPack\TypeChecker\Visitor;
use HHPack\TypeChecker\VisitorAcceptable;
use HHPack\TypeChecker\Selectable;

interface ResultNode extends VisitorAcceptable<ResultNode>, Selectable<ResultNode>
{
    public function name() : string;
    public function result() : ImmMap<string, Coverage>;
    public function checked() : int;
    public function partial() : int;
    public function unchecked() : int;
    public function total() : int;
    public function parsentage() : float;
    public function hasChildren() : bool;
    public function children() : ImmMap<string, ResultNode>;
    public function items() : Iterator<ResultNode>;
}
