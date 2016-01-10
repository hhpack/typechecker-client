<?hh //strict

/**
 * This file is part of hhpack\typechecker package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\typechecker
{
    type version = string;
    type configurationPath = string;
}

namespace hhpack\typechecker\check
{
    use hhpack\typechecker\range\IntegerRange;

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

namespace hhpack\typechecker\coverage
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
