<?hh //strict

namespace hhpack\typechecker;

interface Client
{
    public function restart(?string $cwd = (string) getcwd()) : Awaitable<void>;
    public function check(?string $cwd = (string) getcwd()) : Awaitable<Result>;
}
