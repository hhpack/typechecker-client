<?hh //strict

/**
 * This file is part of hhpack\typechecker package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\typechecker\check;

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

    public function getStartLineNumber() : LineNumber
    {
        return 1;
    }

    public function getEndLineNumber() : LineNumber
    {
        return $this->lines->count();
    }

    public function getLineCode(LineNumber $lineAt) : string
    {
        return $this->lines->at($lineAt - 1);
    }

    public function getLineCodes() : KeyedIterator<LineNumber, string>
    {
        foreach ($this->lines->lazy() as $lineAt => $line) {
            yield $lineAt + 1 => $line;
        }
    }

    public function getTotalLineCount() : int
    {
        return $this->lines->count();
    }

    public function getLineCodesByRange(LineRange $range) : KeyedIterator<LineNumber, string>
    {
        $endAt = $range->last();

        for ($lineAt = $range->first(); $lineAt <= $endAt; $lineAt++) {
            yield $lineAt => $this->lines->at($lineAt - 1);
        }
    }

}
