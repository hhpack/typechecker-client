<?hh //partial

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

    public static function fromObject(stdClass $errorObject) : this
    {
        $messages = Vector {};

        foreach ($errorObject->message as $messageObject) {
            $message = Message::fromObject($messageObject);
            $messages->add($message);
        }

        return new static($messages->getIterator());
    }

}
