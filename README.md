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
use hhpack\typechecker\TypeCheckerClient;

$client = new TypeCheckerClient(getcwd());

await $client->restart();

$result = await $client->check();

if ($result->isPassed()) {
    echo "Passed!!", PHP_EOL;
} else {
    echo "Failed!!", PHP_EOL;
}
```

API of Client
--------------------------------------

* **version** - return type checker version  
* **restart** - restarts a hack server
* **check** - return result of type check

Run the test
----------------------------------------

You can run the test with the following command.

	composer install
	composer test
