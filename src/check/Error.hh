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

final class Error implements Node<ErrorOptions>
{

    private ImmutableMessages $messages;

    public function __construct(Messages $messages)
    {
        $this->messages = new ImmVector($messages);
    }

    public function getMessages() : KeyedIterator<int, Message>
    {
        return $this->messages->lazy();
    }

    public function hasMessages() : bool
    {
        return $this->messages->isEmpty() === false;
    }

    public static function fromOptions(ErrorOptions $options) : this
    {
        $messages = Vector {};

        foreach ($options['message'] as $messageOptions) {
            $message = Message::fromOptions($messageOptions);
            $messages->add($message);
        }

        return new static( $messages->items() );
    }

}
