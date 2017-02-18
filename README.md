typechecker-client
======================================

[![Latest Stable Version](https://poser.pugx.org/hhpack/typechecker-client/version)](https://packagist.org/packages/hhpack/typechecker-client)
[![Build Status](https://travis-ci.org/hhpack/typechecker-client.svg?branch=master)](https://travis-ci.org/hhpack/typechecker-client)
[![Dependency Status](https://www.versioneye.com/user/projects/5634664636d0ab0016001f3b/badge.svg?style=flat)](https://www.versioneye.com/user/projects/5634664636d0ab0016001f3b)
[![License](https://poser.pugx.org/hhpack/typechecker-client/license)](https://packagist.org/packages/hhpack/typechecker-client)

Basic usage
--------------------------------------

Examples of the type of check will be as follows.

```hack
use HHPack\TypeChecker\TypeCheckerClient;

$client = new TypeCheckerClient(getcwd());

await $client->restart();

$result = await $client->check();

if ($result->isPassed()) {
    echo "Passed!!", PHP_EOL;
} else {
    echo "Failed!!", PHP_EOL;
}
```

Type of coverage
--------------------------------------

Examples of the type of coverage will be as follows.

```hack
use HHPack\TypeChecker\TypeCheckerClient;
use HHPack\TypeChecker\Coverage\File;

$client = new TypeCheckerClient(getcwd());
await $client->restart();

$result = await $client->coverage();
$files = $result->filter(($item) ==> {
    return $item instanceof File;
});

foreach ($files as $file) {
    $formattedParsentage = sprintf('%6.2f%%', (float) $file->parsentage() * 100); 
    echo $formattedParsentage, ' ', $file->name(), PHP_EOL;
}
```

API of Client
--------------------------------------

* **version** - return type checker version  
* **init** - generate configuration file
* **start** - starts a hack server
* **stop** - stops a hack server
* **restart** - restarts a hack server
* **check** - return result of type check
* **coverage** - return result of coverage

Run the test
----------------------------------------

You can run the test with the following command.

	composer install
	composer test
