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

final class LineRange
{

    public function __construct
    (
        private int $startAt,
        private int $endAt
    )
    {
        $this->validate();
    }

    public function getStartLineNumber() : LineNumber
    {
        return $this->startAt;
    }

    public function getEndLineNumber() : LineNumber
    {
        return $this->endAt;
    }

    private function validate() : void
    {
        $this->validateLineNumber();
        $this->validateLineRange();
    }

    private function validateLineNumber() : void
    {
        if ($this->getStartLineNumber() < 1) {
            throw new UnexpectedLineNumberException(sprintf(
                'Start line is less than 1, the start line has been specified %d.',
                $this->getStartLineNumber())
            );
        }

        if ($this->getEndLineNumber() < 1) {
            throw new UnexpectedLineNumberException(sprintf(
                'End line is less than 1, the start line has been specified %d.',
                $this->getEndLineNumber())
            );
        }
    }

    private function validateLineRange() : void
    {
        $result = $this->getStartLineNumber() <= $this->getEndLineNumber();

        if ($result === true) {
            return;
        }

        throw new LessThanLineNumberException(sprintf(
            'The start line is larger than the end line, the start line is %d, the end line is %d.',
                $this->getStartLineNumber(),
                $this->getEndLineNumber()
            )
        );
    }

    public static function onlyAt(LineNumber $lineAt) : this
    {
        return new static($lineAt, $lineAt);
    }

    public static function between(LineNumber $startAt, LineNumber $endAt) : this
    {
        return new static($startAt, $endAt);
    }

}
