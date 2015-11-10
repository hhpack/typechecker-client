<?hh //partial

namespace hhpack\typechecker\spec\check;

use hhpack\typechecker\check\LineRange;
use hhpack\typechecker\check\FileContent;

describe(FileContent::class, function() {
  beforeEach(function() {
    $this->content = new FileContent(file_get_contents(__DIR__ . '/../fixtures/failed/Example1.txt'));
  });
  describe('#getLineCodesByLineRange', function() {
    context('when one line', function () {
      it('returns range lines', function() {
        $lines = $this->content->getLineCodesByRange(LineRange::onlyAt(6));
        $lines->next();
        $lineCode = $lines->current();

        expect($lineCode)->toBe("    public function __construct(T $)");
      });
    });
    context('when two line', function () {
      it('returns range lines', function() {
        $lines = $this->content->getLineCodesByRange(LineRange::between(6, 7));

        $lines->next();
        $lineCode = $lines->current();
        expect($lineCode)->toBe("    public function __construct(T $)");

        $lines->next();
        $lineCode = $lines->current();
        expect($lineCode)->toBe("    {");
      });
    });
  });
});
