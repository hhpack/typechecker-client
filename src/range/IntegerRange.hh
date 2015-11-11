<?hh //strict

/**
 * This file is part of hhpack\typechecker package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\typechecker\range;

use hhpack\typechecker\Range;
use UnexpectedValueException;

final class IntegerRange implements Range<int>
{

    public function __construct(
        private int $first,
        private int $last,
        private int $min = 1
    )
    {
    }

    public function first() : int
    {
        return $this->first;
    }

    public function last() : int
    {
        return $this->last;
    }

    public function contains(int $value) : bool
    {
        return $this->first() <= $value && $this->last() >= $value;
    }

    private function validate() : void
    {
        $this->validateFirstValue();
        $this->validateLastValue();
        $this->validateRange();
    }

    private function validateFirstValue() : void
    {
        if ($this->first() >= $this->min) {
            return;
        }
        throw new UnexpectedValueException(
            sprintf("The first value is smaller than %d.\n  last: %d\n  min: %d",
                $this->min,
                $this->first(),
                $this->min
            )
        );
    }

    private function validateLastValue() : void
    {
        if ($this->last() >= $this->min) {
            return;
        }
        throw new UnexpectedValueException(
            sprintf("The last value is smaller than %d.\n  last: %d\n  min: %d",
                $this->min,
                $this->last(),
                $this->min
            )
        );
    }

    private function validateRange() : void
    {
        $result = $this->first() <= $this->last();

        if ($result === true) {
            return;
        }

        throw new LessThanException(
            sprintf("The first value is the value greater than the last value.\n  first: %d\n  last: %d)",
                $this->first(),
                $this->last()
            )
        );
    }

}
