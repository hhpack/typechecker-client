<?hh //partial

namespace hhpack\typechecker\check;

use hhpack\typechecker\Node;
use \stdClass;

final class Message implements Node<Message>
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

    public static function fromObject(stdClass $message) : Message
    {
        $columnRange = new ColumnRange($message->start, $message->end);
        $filePosition = new FilePosition($message->line, $columnRange);
        $file = new File($message->path, $filePosition);

        return new Message($message->code, $message->descr, $file);
    }

}
