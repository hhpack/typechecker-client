<?hh //strict

/**
 * This file is part of hhpack\typechecker package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\TypeChecker\Coverage;


final class CurrentPath
{

    private Vector<string> $pathSegments;

    public function __construct(
        Traversable<string> $pathSegments = []
    )
    {
        $this->pathSegments = Vector::fromItems($pathSegments);
    }

    public function moveTo(string $pathSegment) : void
    {
        $this->pathSegments->add($pathSegment);
    }

    public function leave() : void
    {
        $lastIndexAt = $this->pathSegments->count() - 1;

        if ($lastIndexAt < 0) {
            return;
        }

        $this->pathSegments->pop();
    }

    public function count() : int
    {
        return $this->pathSegments->count();
    }

    public function path() : string
    {
        return $this->stringify();
    }

    public function pathFrom(string $rootPath) : string
    {
        $root = $rootPath;

        if (substr($root, -1) === '/') {
            $root = substr($root, 0, -1);
        }

        return $root . '/' . $this->path();
    }

    public function stringify() : string
    {
        return (string) $this;
    }

    public function __toString() : string
    {
        $segments = $this->pathSegments->toValuesArray();
        return implode('/', $segments);
    }

    public static function fromPath(string $path) : this
    {
        $pathSegments = explode('/', $path);
        return new static($pathSegments);
    }

}
