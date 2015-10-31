<?hh //partial

namespace hhpack\typechecker\check;

use hhpack\typechecker\Node;
use \stdClass;

final class Result implements Node<Result>
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

    public function getErrors() : Iterator<Error>
    {
        return $this->errors->getIterator();
    }

    public function hasErrors() : bool
    {
        return $this->errors->isEmpty() === false;
    }

    public static function fromObject(stdClass $result) : Result
    {
        $errors = Vector {};

        foreach ($result->errors as $errorObject) {
            $error = Error::fromObject($errorObject);
            $errors->add($error);
        }

        return new Result(
            $result->passed,
            $result->version,
            $errors->getIterator()
        );
    }

    public static function fromString(string $result) : Result
    {
        $json = preg_replace('/^([^\{]+)|([^\}]+)$/', "", $result);
        $object = json_decode(trim($json));

        return static::fromObject($object);
    }

}
