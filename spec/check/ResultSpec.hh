<?hh //partial

namespace hhpack\typechecker\spec\check;

use hhpack\typechecker\check\Result;

describe(Result::class, function() {
  beforeEach(function() {
    $messageOptions = shape(
      'code' => 2055,
      'descr' => "error message",
      'path' => "/foo/var/example.hh",
      'line' => 38,
      'end' => 26,
      'start' => 26
    );

    $errorOptions = shape(
      'message' => [ $messageOptions ]
    );

    $resultOptions = shape(
      'passed' => true,
      'version' => "817b3a0 Nov 15 2014 13:25:51",
      'errors' => [ $errorOptions ]
    );

    $this->resultOptions = $resultOptions;
    $this->result = Result::fromOptions($resultOptions);
  });
  describe('#getVersion', function() {
    it('return version text', function() {
      expect($this->result->getVersion())->toBe("817b3a0 Nov 15 2014 13:25:51");
    });
  });
  describe('#isPassed', function() {
    context('when passed', function() {
      it('return true', function() {
        expect($this->result->isPassed())->toBeTrue();
      });
    });
    context('when failed', function() {
      beforeEach(function() {
        $this->resultOptions['passed'] = false;
        $this->failedResult = Result::fromOptions($this->resultOptions);
      });
      it('return false', function() {
        expect($this->failedResult->isPassed())->toBeFalse();
      });
    });
  });
  describe('#getErrors', function() {
    it('return errors', function() {
      $errors = $this->result->getErrors();
      expect(count($errors))->toBe(1);
    });
  });
  describe('#hasErrors', function() {
    context('when there is no error', function() {
      beforeEach(function() {
        $this->resultOptions['passed'] = true;
        $this->resultOptions['errors'] = [];
        $this->passedResult = Result::fromOptions($this->resultOptions);
      });
      it('return false', function() {
        expect($this->passedResult->hasErrors())->toBeFalse();
      });
    });
    context('when there is an error', function() {
      it('return true', function() {
        expect($this->result->hasErrors())->toBeTrue();
      });
    });
  });

  describe('#fromString', function() {
    beforeEach(function() {
      $this->content = file_get_contents(__DIR__ . '/../fixtures/failed/output.json');
      $this->content = str_replace('{$rootDirectory}', realpath(__DIR__ . '/../fixtures/failed') , $this->content);
      $this->content = "Typechecking ....\n\n" .  $this->content . "\nDone\n";
    });
    it('return type checked result', function () {
      $result = Result::fromString($this->content);
      expect($result->getVersion())->toBe('817b3a0 Nov 15 2014 13:25:51');
    });
  });

});
