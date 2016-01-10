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

    public function code() : int
    {
        return $this->code;
    }

    public function description() : string
    {
        return $this->description;
    }

    public function path() : string
    {
        return $this->file->path();
    }

    public function lineNumber() : int
    {
        return $this->file->lineNumber();
    }

    public function startColumnNumber() : int
    {
        return $this->file->startColumnNumber();
    }

    public function endColumnNumber() : int
    {
        return $this->file->endColumnNumber();
    }

    public function lineCode() : string
    {
        return $this->file->lineCodeAt( $this->lineNumber() );
    }

    public function detailCodes() : KeyedIterator<int, string>
    {
        $lineAt = $this->lineNumber();

        $startLineAt = $lineAt - 2;
        $startLineAt = ($startLineAt <= 0) ? 1 : $startLineAt;

        $endLineAt = $lineAt + 2;
        $endLineAt = ($this->file->totalLineCount() <= $endLineAt)
            ? $this->file->totalLineCount() : $endLineAt;

        $range = IntegerRange::between(
            $startLineAt,
            $endLineAt
        );

        return $this->file->lineCodesByRange($range);
    }

    public static function fromOptions(MessageOptions $options) : this
    {
        $columnRange = new IntegerRange($options['start'], $options['end']);
        $filePosition = new FilePosition($options['line'], $columnRange);
        $file = new File($options['path'], $filePosition);

        return new static($options['code'], $options['descr'], $file);
    }

}
