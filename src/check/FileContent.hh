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

final class FileContent
{

    private ImmVector<string> $lines;

    public function __construct
    (
        string $content
    )
    {
        $this->lines = ImmVector::fromItems(explode(PHP_EOL, $content));
    }

    public function getStartLineNumber() : LineNumber
    {
        return 1;
    }

    public function getEndLineNumber() : LineNumber
    {
        return $this->lines->count();
    }

    public function getLineCodes() : ImmVector<string>
    {
        return $this->lines;
    }

    public function getLineCodesByRange(LineRange $range) : ImmVector<string>
    {
        $lines = Vector {};
        $endAt = $range->getEndLineNumber();

        for ($lineAt = $range->getStartLineNumber(); $lineAt <= $endAt; $lineAt++) {
            $lines->add( $this->lines->at($lineAt) );
        }

        return $lines->toImmVector();
    }

}
