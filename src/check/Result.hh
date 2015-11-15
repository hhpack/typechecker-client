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
use hhpack\typechecker\JSONResult;

final class Result implements JSONResult<ResultOptions>, Node<ResultOptions>
{

    private ImmutableErrors $errors;

    public function __construct
    (
        private bool $passed,
        private Version $version,
        Errors $errors
    )
    {
        $this->errors = new ImmVector($errors);
    }

    public function isPassed() : bool
    {
        return $this->passed;
    }

    public function getVersion() : Version
    {
        return $this->version;
    }

    public function getErrors() : KeyedIterator<int, Error>
    {
        return $this->errors->lazy()->getIterator();
    }

    public function hasErrors() : bool
    {
        return $this->errors->isEmpty() === false;
    }

    public static function fromOptions(ResultOptions $options) : this
    {
        $errors = Vector {};

        foreach ($options['errors'] as $errorOptions) {
            $error = Error::fromOptions($errorOptions);
            $errors->add($error);
        }

        return new static(
            $options['passed'],
            $options['version'],
            $errors->items()
        );
    }

    public static function fromString(string $result) : this
    {
        $json = preg_replace('/^([^\{]+)|([^\}]+)$/', "", $result);
        $values = json_decode(trim($json), true);

        return static::fromOptions($values);
    }

}
