<?hh //strict

/**
 * This file is part of hhpack\typechecker package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\typechecker\coverage;

use hhpack\typechecker\JSONDecoder;

final class CoverageReportDecoder implements JSONDecoder<CoverageNode>
{

    public function decode(string $json) : CoverageNode
    {
        $object = new Map(json_decode($json, true));

        if (!$object->containsKey('name')) {
            $object->set('name', 'root');
        }

        return $this->decodeNode($object->toArray());
    }

    public function decodeNode(KeyedTraversable<string, mixed> $json) : CoverageNode
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
            'name' => (string) $object->at('name'),
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

    public function decodeChildren(KeyedTraversable<string, mixed> $json) : ImmMap<string, CoverageNode>
    {
        $children = Map {};

        foreach ($json as $key => $values) {
            if (!is_array($values)) {
                continue;
            }
            $values['name'] = $key;
            $children->set($key, $this->decodeNode($values));
        }

        return $children->toImmMap();
    }

}
