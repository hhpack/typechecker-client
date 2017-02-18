<?hh //strict

/**
 * This file is part of hhpack\typechecker package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\TypeChecker\Check;

final class FileContent
{

    private ImmVector<string> $lines;

    public function __construct
    (
        string $content
    )
    {
        $this->lines = ImmVector::fromItems(explode(PHP_EOL, rtrim($content)));
    }

    public function startLineNumber() : int
    {
        return 1;
    }

    public function endLineNumber() : int
    {
        return $this->lines->count();
    }

    public function lineCodeAt(int $lineAt) : string
    {
        return $this->lines->at($lineAt - 1);
    }

    public function lineCodes() : KeyedIterator<int, string>
    {
        foreach ($this->lines->lazy() as $lineAt => $line) {
            yield $lineAt + 1 => $line;
        }
    }

    public function totalLineCount() : int
    {
        return $this->lines->count();
    }

    public function lineCodesByRange(LineRange $range) : KeyedIterator<int, string>
    {
        $endAt = $range->last();

        for ($lineAt = $range->first(); $lineAt <= $endAt; $lineAt++) {
            yield $lineAt => $this->lines->at($lineAt - 1);
        }
    }

}
