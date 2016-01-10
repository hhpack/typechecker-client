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

use hhpack\typechecker\JSONResult;
use hhpack\typechecker\FromOptions;

final class Result implements ResultNode, FromOptions<ResultOptions>
{

    private ImmVector<Error> $errors;

    public function __construct
    (
        private bool $passed,
        private Version $version,
        Traversable<Error> $errors
    )
    {
        $this->errors = new ImmVector($errors);
    }

    public function isOk() : bool
    {
        return $this->passed;
    }

    public function isError() : bool
    {
        return $this->isOk() === false;
    }

    public function getVersion() : Version
    {
        return $this->version;
    }

    public function getErrors() : KeyedIterator<int, Error>
    {
        return $this->errors->lazy()->getIterator();
    }

    public function getErrorCount() : int
    {
        return $this->errors->count();
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

}
