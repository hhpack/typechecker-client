<?hh //partial

namespace hhpack\typechecker\spec\check;

use hhpack\typechecker\check\LineRange;
use hhpack\typechecker\check\FileContent;

describe(FileContent::class, function() {
  beforeEach(function() {
    $this->content = new FileContent("a\nb\nc\n");
  });
  describe('getLineCodesByLineRange', function() {
    it('returns range lines', function() {
      $lineCount = 0;
      $lines = $this->content->getLineCodesByRange(new LineRange(1, 1));
      foreach ($lines as $line) {
        $lineCount++;
      }
      expect($lineCount)->toBe(1);
    });
  });
});
