<?hh //partial

namespace HHPack\TypeChecker\Spec\Coverage;

use HHPack\TypeChecker\Coverage\CoverageReportDecoder;

describe(CoverageReportDecoder::class, function() {
  beforeEach(function() {
    $this->decoder = new CoverageReportDecoder(__DIR__);
  });
  describe('#decodeFile', function() {
    it('return decoded result', function() {
      $result = $this->decoder->decodeFile(__DIR__ . '/../fixtures/coverage/output.json');
      expect($result->hasChildren())->toBeTrue();
    });
  });
});
