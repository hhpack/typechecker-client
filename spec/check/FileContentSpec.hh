<?hh //partial

namespace hhpack\typechecker\spec\check;

use hhpack\typechecker\range\IntegerRange;
use hhpack\typechecker\check\FileContent;

describe(FileContent::class, function() {
  beforeEach(function() {
    $this->content = new FileContent(file_get_contents(__DIR__ . '/../fixtures/failed/Example1.txt'));
  });
  describe('#getLineCode', function() {
    context('when start line', function () {
      it('returns end line', function() {
        $startAt = $this->content->getStartLineNumber();
        $lineCode = $this->content->getLineCode($startAt);
        expect($lineCode)->toBe("<?hh //strict");
      });
    });
    context('when end line', function () {
      it('returns end line', function() {
        $endAt = $this->content->getEndLineNumber();
        $lineCode = $this->content->getLineCode($endAt);
        expect($lineCode)->toBe("}");
      });
    });
  });
  describe('#getLineCodesByLineRange', function() {
    context('when one line', function () {
      it('returns range lines', function() {
        $lines = $this->content->getLineCodesByRange(IntegerRange::only(6));
        $lines->next();
        $lineCode = $lines->current();

        expect($lineCode)->toBe("    public function __construct(T $)");
      });
    });
    context('when two line', function () {
      it('returns range lines', function() {
        $lines = $this->content->getLineCodesByRange(IntegerRange::between(6, 7));

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
