<?hh //partial

namespace hhpack\typechecker\spec\check;

use hhpack\typechecker\check\Message;
use hhpack\typechecker\check\LineRange;

describe(Message::class, function() {
  beforeEach(function() {
    $this->sourcePath = realpath(__DIR__ . '/../fixtures/failed/Example1.txt');
    $this->options = shape(
      'code' => 2055,
      'descr' => "Expected variable",
      'path' => $this->sourcePath,
      'line' => 6,
      'start' => 35,
      'end' => 35,
      'code'=> 1002
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
      expect($this->message->getCode())->toBe(1002);
    });
  });
  describe('#getDescription', function() {
    it('return description text', function() {
      expect($this->message->getDescription())->toBe("Expected variable");
    });
  });
  describe('#getPath', function() {
    it('return file path', function() {
      expect($this->message->getPath())->toBe($this->sourcePath);
    });
  });
  describe('#getLineNumber', function() {
    it('return line number', function() {
      expect($this->message->getLineNumber())->toBe(6);
    });
  });
  describe('#getStartColumnNumber', function() {
    it('return start column number', function() {
      expect($this->message->getStartColumnNumber())->toBe(35);
    });
  });
  describe('#getEndColumnNumber', function() {
    it('return end column number', function() {
      expect($this->message->getEndColumnNumber())->toBe(35);
    });
  });
});
