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

use HHPack\TypeChecker\JSONResult;
use HHPack\TypeChecker\Selectable;
use HHPack\TypeChecker\FromOptions;

final class Result implements ResultNode, FromOptions<ResultOptions>, Selectable<Error>
{

    private ImmVector<Error> $errors;

    public function __construct
    (
        private bool $passed,
        private version $version,
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

    public function version() : version
    {
        return $this->version;
    }

    public function errors() : ImmVector<Error>
    {
        return $this->errors;
    }

    public function errorCount() : int
    {
        return $this->errors->count();
    }

    public function hasErrors() : bool
    {
        return $this->errors->isEmpty() === false;
    }

    public function filter((function(Error):bool) $selector) : ImmVector<Error>
    {
        return ImmVector::fromItems($this->errors)->filter($selector);
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
