<?hh //partial

namespace hhpack\typechecker\spec\check;

use hhpack\typechecker\check\Result;
use stdClass;

describe(Result::class, function() {
  beforeEach(function() {
    $message = new stdClass();
    $message->code = 2055;
    $message->descr = "error message";
    $message->path = "/foo/var/example.hh";
    $message->line = 38;
    $message->end = 26;
    $message->start = 26;

    $errorObject = new stdClass();
    $errorObject->message = [
      $message
    ];

    $resultObject = new stdClass();
    $resultObject->passed = true;
    $resultObject->version = "817b3a0 Nov 15 2014 13:25:51";
    $resultObject->errors = [
      $error
    ];

    $this->resultObject = $resultObject;
    $this->result = Result::fromObject($resultObject);
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
        $this->resultObject->passed = false;
        $this->failedResult = Result::fromObject($this->resultObject);
      });
      it('return false', function() {
        expect($this->failedResult->isPassed())->toBeFalse();
      });
    });
  });
  describe('#getErrors', function() {
    it('return Iterator<Error> instance', function() {
      expect($this->result->getErrors())->toBeAnInstanceOf(Iterator::class);
    });
  });
  describe('#hasErrors', function() {
    context('when there is no error', function() {
      beforeEach(function() {
        $this->resultObject->passed = true;
        $this->resultObject->errors = [];
        $this->passedResult = Result::fromObject($this->resultObject);
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
