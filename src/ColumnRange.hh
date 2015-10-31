<?hh //strict

namespace hhpack\typechecker;

final class ColumnRange
{

    public function __construct
    (
        private ColumnNumber $startColumnNumber,
        private ColumnNumber $endColumnNumber
    )
    {
    }

    public function getStartColumnNumber() : ColumnNumber
    {
        return $this->startColumnNumber;
    }

    public function getEndColumnNumber() : ColumnNumber
    {
        return $this->endColumnNumber;
    }

}
