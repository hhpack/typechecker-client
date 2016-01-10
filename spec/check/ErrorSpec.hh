<?hh //partial

namespace hhpack\typechecker\spec\check;

use hhpack\typechecker\check\Error;

describe(Error::class, function() {
  beforeEach(function() {
    $this->error = Error::fromOptions(shape(
      'message' => shape(
        'code' => 2055,
        'descr' => "error message",
        'path' => "/foo/var/example.hh",
        'line' => 38,
        'end' => 26,
        'start' => 26
      )
    ));
  });
  describe('#messages', function() {
    it('return messages', function() {
      $messages = $this->error->messages();
      expect(count($messages))->toBe(1);
    });
  });
  describe('#hasMessages', function() {
    context('when there is an error message', function() {
      it('return true', function() {
        expect($this->error->hasMessages())->toBeTrue();
      });
    });
    context('when there is no message', function() {
      beforeEach(function() {
        $this->error = Error::fromOptions(shape(
          'message' => []
        ));
      });
      it('return false', function() {
        expect($this->error->hasMessages())->toBeFalse();
      });
    });
  });
});
