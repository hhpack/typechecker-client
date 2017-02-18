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

use HHPack\TypeChecker\JSONDecoder;
use RuntimeException;

final class TypeCheckReportDecoder implements JSONDecoder<Result>
{

    public function decode(string $json) : Result
    {
        $cleanContent = preg_replace('/^([^\{]+)|([^\}]+)$/', "", $json);
        $options = json_decode(trim($cleanContent), true);

        return Result::fromOptions($options);
    }

}
