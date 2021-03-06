<?hh //strict

/**
 * This file is part of hhpack\typechecker package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\TypeChecker\Check;

use HHPack\TypeChecker\FromOptions;

final class Error implements ResultNode, FromOptions<ErrorOptions>
{

    private ImmVector<Message> $messages;

    public function __construct(Traversable<Message> $messages)
    {
        $this->messages = new ImmVector($messages);
    }

    public function messages() : ImmVector<Message>
    {
        return $this->messages;
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
