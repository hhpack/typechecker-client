<?hh //strict

/**
 * This file is part of hhpack\typechecker package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\TypeChecker
{
    type version = string;
    type configurationPath = string;
}

namespace HHPack\TypeChecker\Check
{
    use HHPack\TypeChecker\Range\IntegerRange;

    type version = string;
    type LineRange = IntegerRange;

    type MessageOptions = shape(
        'descr' => string,
        'path' => string,
        'line' => int,
        'start' => int,
        'end' => int,
        'code' => int
    );
    type ErrorOptions = shape(
        'message' => array<MessageOptions>
    );
    type ResultOptions = shape(
        'passed' => bool,
        'version' => version,
        'errors' => array<ErrorOptions>
    );
}

namespace HHPack\TypeChecker\Coverage
{
    type FileOptions = shape(
        'name' => string,
        'result' => ImmMap<string, Coverage>
    );

    type DirectoryOptions = shape(
        'name' => string,
        'result' => ImmMap<string, Coverage>,
        'children' => ImmMap<string, ResultNode>
    );
}
