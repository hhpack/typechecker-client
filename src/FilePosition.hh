<?hh //strict

namespace hhpack\typechecker;

final class FilePosition
{

    public function __construct(
        private LineNumber $lineNumber,
        private ColumnRange $columnRange
    )
    {
    }

    public function getLineNumber() : LineNumber
    {
        return $this->lineNumber;
    }

    public function getStartColumnNumber() : ColumnNumber
    {
        return $this->columnRange->getStartColumnNumber();
    }

    public function getEndColumnNumber() : ColumnNumber
    {
        return $this->columnRange->getEndColumnNumber();
    }

}
