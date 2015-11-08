<?hh //partial

namespace hhpack\typechecker\spec\check;

use hhpack\typechecker\check\Message;

describe(Message::class, function() {
  beforeEach(function() {
    $this->options = shape(
      'code' => 2055,
      'descr' => "error message",
      'path' => "/foo/var/example.hh",
      'line' => 38,
      'end' => 26,
      'start' => 26
    );
    $this->message = Message::fromOptions($this->options);
  });
  describe('#fromObject', function() {
    it('return Message instance', function() {
      $message = Message::fromOptions($this->options);
      expect($message)->toBeAnInstanceOf(Message::class);
    });
  });
  describe('#getCode', function() {
    it('return code value', function() {
      expect($this->message->getCode())->toBe(2055);
    });
  });
  describe('#getDescription', function() {
    it('return description text', function() {
      expect($this->message->getDescription())->toBe("error message");
    });
  });
  describe('#getPath', function() {
    it('return file path', function() {
      expect($this->message->getPath())->toBe("/foo/var/example.hh");
    });
  });
  describe('#getLineNumber', function() {
    it('return line number', function() {
      expect($this->message->getLineNumber())->toBe(38);
    });
  });
  describe('#getStartColumnNumber', function() {
    it('return start column number', function() {
      expect($this->message->getStartColumnNumber())->toBe(26);
    });
  });
  describe('#getEndColumnNumber', function() {
    it('return end column number', function() {
      expect($this->message->getEndColumnNumber())->toBe(26);
    });
  });
});
