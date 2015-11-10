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
        private Path $path,
        private FilePosition $position
    )
    {
    }

    public function getPath() : Path
    {
        return $this->path;
    }

    public function getLineNumber() : LineNumber
    {
        return $this->position->getLineNumber();
    }

    public function getStartColumnNumber() : ColumnNumber
    {
        return $this->position->getStartColumnNumber();
    }

    public function getEndColumnNumber() : ColumnNumber
    {
        return $this->position->getEndColumnNumber();
    }

    public function getLineCodes() : KeyedIterator<LineNumber, string>
    {
        return $this->readContent()->getLineCodes();
    }

    public function getLineCodesByRange(LineRange $range) : KeyedIterator<LineNumber, string>
    {
        return $this->readContent()->getLineCodesByRange($range);
    }

    <<__Memoize>>
    private function readContent() : FileContent
    {
        $content = file_get_contents($this->getPath());
        return new FileContent($content);
    }

}
