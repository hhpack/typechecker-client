<?hh //partial

namespace hhpack\typechecker\spec\check;

use hhpack\typechecker\TypeCheckerClient;

describe(TypeCheckerClient::class, function() {
  beforeEach(function() {
    unlink('/tmp/.hhconfig');
    $this->checker = new TypeCheckerClient('/tmp');
  });
  describe('#init', function() {
    it('return config file path', function() {
      $handle = $this->checker->init();
      $handle->import();
      $file = $handle->result();

      expect(file_exists($file))->toBeTrue();
    });
  });
});
