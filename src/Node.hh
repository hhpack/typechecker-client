<?hh //strict

namespace hhpack\typechecker;

use stdClass;

interface Node<T>
{
    public static function fromObject(stdClass $object) : T;
}
