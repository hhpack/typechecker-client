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

use hhpack\typechecker\RootNode;
use \stdClass;

final class Result implements RootNode
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

    public function getErrors() : Iterable<Error>
    {
        return $this->errors->items();
    }

    public function hasErrors() : bool
    {
        return $this->errors->isEmpty() === false;
    }

    public static function fromObject(stdClass $result) : this
    {
        $errors = Vector {};

        foreach ($result->errors as $errorObject) {
            $error = Error::fromObject($errorObject);
            $errors->add($error);
        }

        return new static(
            $result->passed,
            $result->version,
            $errors->items()
        );
    }

    public static function fromString(string $result) : this
    {
        $json = preg_replace('/^([^\{]+)|([^\}]+)$/', "", $result);
        $object = json_decode(trim($json));

        return static::fromObject($object);
    }

}
