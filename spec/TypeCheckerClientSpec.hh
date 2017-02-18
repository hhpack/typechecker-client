<?hh //partial

namespace HHPack\TypeChecker\Spec\Check;

use HHPack\TypeChecker\TypeCheckerClient;

describe(TypeCheckerClient::class, function() {
  beforeEach(function() {
    if (file_exists('/tmp/.hhconfig')) {
      unlink('/tmp/.hhconfig');
    }
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
