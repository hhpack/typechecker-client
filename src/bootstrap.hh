<?hh //strict

namespace hhpack\typechecker
{
    type Version = string;
    type Errors = Traversable<Error>;
    type ImmutableErrors = ImmVector<Error>;
    type Messages = Traversable<Message>;
    type ImmutableMessages = ImmVector<Message>;
    type Path = string;
    type LineNumber = int;
    type ColumnNumber = int;
}
