<?hh //strict

namespace hhpack\typechecker;

use hhpack\typechecker\check\Result;

interface Client
{
    public function restart(?string $cwd = (string) getcwd()) : Awaitable<void>;
    public function check(?string $cwd = (string) getcwd()) : Awaitable<Result>;
}
