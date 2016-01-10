<?hh //partial

namespace hhpack\typechecker\spec\coverage;

use hhpack\typechecker\coverage\CoverageReportDecoder;

describe(CoverageReportDecoder::class, function() {
  beforeEach(function() {
    $this->decoder = new CoverageReportDecoder();
  });
  describe('#decodeFile', function() {
    it('return decoded result', function() {
      $result = $this->decoder->decodeFile(__DIR__ . '/../fixtures/coverage/output.json');
      expect($result->hasChildren())->toBeTrue();
    });
  });
});
