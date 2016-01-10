<?hh //partial

namespace hhpack\typechecker\spec\check;

use hhpack\typechecker\range\IntegerRange;
use hhpack\typechecker\check\FileContent;

describe(FileContent::class, function() {
  beforeEach(function() {
    $this->content = new FileContent(file_get_contents(__DIR__ . '/../fixtures/failed/Example1.txt'));
  });
  describe('#lineCodeAt', function() {
    context('when start line', function () {
      it('returns start line', function() {
        $startAt = $this->content->startLineNumber();
        $lineCode = $this->content->lineCodeAt($startAt);
        expect($lineCode)->toBe("<?hh //strict");
      });
    });
    context('when end line', function () {
      it('returns end line', function() {
        $endAt = $this->content->endLineNumber();
        $lineCode = $this->content->lineCodeAt($endAt);
        expect($lineCode)->toBe("}");
      });
    });
  });
  describe('#lineCodesByRange', function() {
    context('when one line', function () {
      it('returns range lines', function() {
        $lines = $this->content->lineCodesByRange(IntegerRange::only(6));
        $lineCode = $lines->current();

        expect($lineCode)->toBe("    public function __construct(T $)");
      });
    });
    context('when two line', function () {
      it('returns range lines', function() {
        $lines = $this->content->lineCodesByRange(IntegerRange::between(6, 7));

        $lineCode = $lines->current();
        expect($lineCode)->toBe("    public function __construct(T $)");

        $lines->next();
        $lineCode = $lines->current();
        expect($lineCode)->toBe("    {");
      });
    });
  });
});
