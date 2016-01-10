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

use hhpack\typechecker\range\IntegerRange;
use hhpack\typechecker\FromOptions;

final class Message implements ResultNode, FromOptions<MessageOptions>
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

    public function getPath() : string
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

    public function getLineCode() : string
    {
        return $this->file->getLineCode( $this->getLineNumber() );
    }

    public function getDetailCodes() : KeyedIterator<LineNumber, string>
    {
        $lineAt = $this->getLineNumber();

        $startLineAt = $lineAt - 2;
        $startLineAt = ($startLineAt <= 0) ? 1 : $startLineAt;

        $endLineAt = $lineAt + 2;
        $endLineAt = ($this->file->getTotalLineCount() <= $endLineAt)
            ? $this->file->getTotalLineCount() : $endLineAt;

        $range = IntegerRange::between(
            $startLineAt,
            $endLineAt
        );

        return $this->file->getLineCodesByRange($range);
    }

    public static function fromOptions(MessageOptions $options) : this
    {
        $columnRange = new IntegerRange($options['start'], $options['end']);
        $filePosition = new FilePosition($options['line'], $columnRange);
        $file = new File($options['path'], $filePosition);

        return new static($options['code'], $options['descr'], $file);
    }

}
