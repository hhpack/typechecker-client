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

final class File
{

    public function __construct
    (
        private string $path,
        private FilePosition $position
    )
    {
    }

    public function path() : string
    {
        return $this->path;
    }

    public function lineNumber() : int
    {
        return $this->position->lineNumber();
    }

    public function startColumnNumber() : int
    {
        return $this->position->startColumnNumber();
    }

    public function endColumnNumber() : int
    {
        return $this->position->endColumnNumber();
    }

    public function lineCodeAt(int $lineAt) : string
    {
        return $this->readContent()->lineCodeAt($lineAt);
    }

    public function lineCodes() : KeyedIterator<int, string>
    {
        return $this->readContent()->lineCodes();
    }

    public function lineCodesByRange(LineRange $range) : KeyedIterator<int, string>
    {
        return $this->readContent()->lineCodesByRange($range);
    }

    public function totalLineCount() : int
    {
        return $this->readContent()->totalLineCount();
    }

    <<__Memoize>>
    private function readContent() : FileContent
    {
        $content = file_get_contents($this->path());
        return new FileContent($content);
    }

}
