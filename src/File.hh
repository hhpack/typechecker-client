<?hh //strict

namespace hhpack\typechecker;


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

}
