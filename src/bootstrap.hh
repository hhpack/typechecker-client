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
    type Version = string;
    type ConfigurationPath = string;
}

namespace hhpack\typechecker\check
{
    use hhpack\typechecker\range\IntegerRange;

    type Version = string;
    type Errors = Traversable<Error>;
    type ImmutableErrors = ImmVector<Error>;
    type Messages = Traversable<Message>;
    type ImmutableMessages = ImmVector<Message>;
    type Path = string;
    type LineNumber = int;
    type ColumnNumber = int;
    type ErrorCode = int;

    type LineRange = IntegerRange;

    type MessageOptions = shape(
        'descr' => string,
        'path' => Path,
        'line' => LineNumber,
        'start' => ColumnNumber,
        'end' => ColumnNumber,
        'code' => ErrorCode
    );
    type ErrorOptions = shape(
        'message' => array<MessageOptions>
    );
    type ResultOptions = shape(
        'passed' => bool,
        'version' => Version,
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
        'children' => ImmMap<string, CoverageNode>
    );
}
