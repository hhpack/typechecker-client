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

use hhpack\typechecker\Node;
use \stdClass;

final class Message implements Node<MessageOptions>
{

    public function __construct(
        private int $code,
        private string $description,
        private File $file
    )
    {
    }

    public function getCode() : int
    {
        return $this->code;
    }

    public function getDescription() : string
    {
        return $this->description;
    }

    public function getPath() : Path
    {
        return $this->file->getPath();
    }

    public function getLineNumber() : LineNumber
    {
        return $this->file->getLineNumber();
    }

    public function getStartColumnNumber() : ColumnNumber
    {
        return $this->file->getStartColumnNumber();
    }

    public function getEndColumnNumber() : ColumnNumber
    {
        return $this->file->getEndColumnNumber();
    }

    public function getLineCodesByRange(LineRange $range) : KeyedIterator<LineNumber, string>
    {
        return $this->file->getLineCodesByRange($range);
    }

    public static function fromOptions(MessageOptions $options) : this
    {
        $columnRange = new ColumnRange($options['start'], $options['end']);
        $filePosition = new FilePosition($options['line'], $columnRange);
        $file = new File($options['path'], $filePosition);

        return new static($options['code'], $options['descr'], $file);
    }

}
