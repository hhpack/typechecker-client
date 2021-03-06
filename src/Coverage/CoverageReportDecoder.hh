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

use HHPack\TypeChecker\JSONDecoder;
use RuntimeException;

final class CoverageReportDecoder implements JSONDecoder<ResultNode>
{

    private CurrentPath $path;

    public function __construct(
        private string $cwd
    )
    {
        $this->path = new CurrentPath();
    }

    public function decode(string $json) : ResultNode
    {
        $cleanContent = preg_replace('/^([^\{]+)|([^\}]+)$/', "", $json);
        $object = new Map(json_decode(trim($cleanContent), true));

        if (!$object->containsKey('name')) {
            $object->set('name', $this->cwd);
        }

        $this->path->moveTo( (string) $object->at('name') );

        return $this->decodeNode($object->toArray());
    }

    public function decodeFile(string $jsonFile) : ResultNode
    {
        if (!is_readable($jsonFile)) {
            throw new RuntimeException(sprintf('File %s is not a readable file', $jsonFile));
        }

        $content = file_get_contents($jsonFile);
        return $this->decode($content);
    }

    public function decodeNode(KeyedTraversable<string, mixed> $json) : ResultNode
    {
        $object = new ImmMap($json);

        $coverage = ImmMap {};
        $nodeChildren = ImmMap {};

        $result = $object->at('result');

        if (is_array($result)) {
            $coverage = $this->decodeResult($result);
        }

        $children = $object->get('children');

        if (is_array($children)) {
            $nodeChildren = $this->decodeChildren($children);
        }

        $options = shape(
            'name' => (string) $this->path,
            'result' => $coverage
        );

        if ($object->at('type') === 'file') {
            return File::fromOptions($options);
        } else {
            $options['children'] = $nodeChildren;
            return Directory::fromOptions($options);
        }
    }

    public function decodeCoverage(KeyedTraversable<string, mixed> $json) : Coverage
    {
        $object = new ImmMap($json);

        return new Coverage(
            (int) $object->at('checked'),
            (int) $object->at('partial'),
            (int) $object->at('unchecked')
        );
    }

    public function decodeResult(KeyedTraversable<string, mixed> $json) : ImmMap<string, Coverage>
    {
        $children = Map {};

        foreach ($json as $key => $values) {
            if (!is_array($values)) {
                continue;
            }
            $children->set($key, $this->decodeCoverage($values));
        }

        return $children->toImmMap();
    }

    public function decodeChildren(KeyedTraversable<string, mixed> $json) : ImmMap<string, ResultNode>
    {
        $children = Map {};

        foreach ($json as $key => $values) {
            if (!is_array($values)) {
                continue;
            }
            $this->path->moveTo( $key );
            $children->set($key, $this->decodeNode($values));
            $this->path->leave();
        }

        return $children->toImmMap();
    }

}
