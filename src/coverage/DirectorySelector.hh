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

final class DirectorySelector implements Selector<ResultNode>
{

    public function select(ResultNode $node) : Iterator<Directory>
    {
        if (!($node instanceof Directory)) {
            return;
        }
        yield $node;

        $directories = $this->selectFromCurrentDirectory($node);

        foreach ($directories as $directory) {
            yield $directory;
        }
    }

    private function selectFromCurrentDirectory(ResultNode $node) : Iterator<Directory>
    {
        foreach ($node->children()->values() as $node) {
            if ($node instanceof File) {
                continue;
            }
            $directories = $this->select($node);

            foreach ($directories as $directory) {
                yield $directory;
            }
        }
    }

}
