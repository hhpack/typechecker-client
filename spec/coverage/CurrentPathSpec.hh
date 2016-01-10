<?hh //partial

namespace hhpack\typechecker\spec\coverage;

use hhpack\typechecker\coverage\CurrentPath;

describe(CurrentPath::class, function() {
  beforeEach(function() {
    $this->currentPath = new CurrentPath();
  });
  describe('#stringify', function() {
    it('return current path', function() {
      $this->currentPath->moveTo('tmp');
      expect($this->currentPath->stringify())->toBe('tmp');

      $this->currentPath->leave();
      expect($this->currentPath->stringify())->toBe('');
    });
  });
});
