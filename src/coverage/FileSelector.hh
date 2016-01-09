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
use hhpack\typechecker\Selector;
use hhpack\typechecker\FromOptions;

final class FileSelector implements Selector<ResultNode>
{

    public function select(ResultNode $node) : Iterator<File>
    {
        if ($node instanceof File) {
            yield $node;
        }

        $files = $this->selectFromCurrentDirectory($node);

        foreach ($files as $file) {
            yield $file;
        }

        $files = $this->selectFromSubDirectory($node);

        foreach ($files as $file) {
            yield $file;
        }
    }

    private function selectFromCurrentDirectory(ResultNode $node) : Iterator<File>
    {
        foreach ($node->children()->values() as $node) {
            if (!($node instanceof File)) {
                continue;
            }
            yield $node;
        }
    }

    private function selectFromSubDirectory(ResultNode $node) : Iterator<File>
    {
        foreach ($node->children()->values() as $node) {
            if ($node instanceof File) {
                continue;
            }
            $files = $this->select($node);

            foreach ($files as $file) {
                yield $file;
            }
        }
    }

}
