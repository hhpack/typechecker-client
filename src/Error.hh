<?hh //partial

namespace hhpack\typechecker;

use \stdClass;


final class Error implements Node<Error>
{

    private ImmutableMessages $messages;

    public function __construct(Messages $messages)
    {
        $this->messages = new ImmVector($messages);
    }

    public function getMessages() : Iterator<Message>
    {
        return $this->messages->getIterator();
    }

    public function hasMessages() : bool
    {
        return $this->messages->isEmpty() === false;
    }

    public static function fromObject(stdClass $errorObject) : Error
    {
        $messages = Vector {};

        foreach ($errorObject->message as $messageObject) {
            $message = Message::fromObject($messageObject);
            $messages->add($message);
        }

        return new Error($messages->getIterator());
    }

}
