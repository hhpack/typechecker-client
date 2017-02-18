<?hh //partial

namespace HHPack\TypeChecker\Spec\Check;

use HHPack\TypeChecker\Check\Message;
use HHPack\TypeChecker\Check\LineRange;

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
  describe('#fromOptions', function() {
    it('return Message instance', function() {
      $message = Message::fromOptions($this->options);
      expect($message)->toBeAnInstanceOf(Message::class);
    });
  });
  describe('#code', function() {
    it('return code value', function() {
      expect($this->message->code())->toBe(1002);
    });
  });
  describe('#description', function() {
    it('return description text', function() {
      expect($this->message->description())->toBe("Expected variable");
    });
  });
  describe('#path', function() {
    it('return file path', function() {
      expect($this->message->path())->toBe($this->sourcePath);
    });
  });
  describe('#lineNumber', function() {
    it('return line number', function() {
      expect($this->message->lineNumber())->toBe(6);
    });
  });
  describe('#startColumnNumber', function() {
    it('return start column number', function() {
      expect($this->message->startColumnNumber())->toBe(35);
    });
  });
  describe('#endColumnNumber', function() {
    it('return end column number', function() {
      expect($this->message->endColumnNumber())->toBe(35);
    });
  });

  describe('#detailCodes', function() {
    context('when greater then last line', function () {
      beforeEach(function() {
        $this->options = shape(
          'code' => 2055,
          'descr' => "Expected variable",
          'path' => $this->sourcePath,
          'line' => 9,
          'start' => 35,
          'end' => 35,
          'code'=> 1002
        );
        $this->message = Message::fromOptions($this->options);
      });
      it('return detail code', function() {
        $lines = $this->message->detailCodes();

        expect($lines->key())->toBe(7);
        expect($lines->current())->toBe('    {');

        $lines->next();
        expect($lines->key())->toBe(8);
        expect($lines->current())->toBe('    }');

        $lines->next();
        expect($lines->key())->toBe(9);
        expect($lines->current())->toBe('');

        $lines->next();
        expect($lines->key())->toBe(10);
        expect($lines->current())->toBe('}');
      });
    });

    context('when less then first line', function () {
      beforeEach(function() {
        $this->options = shape(
          'code' => 2055,
          'descr' => "Expected variable",
          'path' => $this->sourcePath,
          'line' => 2,
          'start' => 35,
          'end' => 35,
          'code'=> 1002
        );
        $this->message = Message::fromOptions($this->options);
      });
      it('return detail code', function() {
        $lines = $this->message->detailCodes();

        expect($lines->key())->toBe(1);
        expect($lines->current())->toBe('<?hh //strict');

        $lines->next();
        expect($lines->key())->toBe(2);
        expect($lines->current())->toBe('');

        $lines->next();
        expect($lines->key())->toBe(3);
        expect($lines->current())->toBe('class Example<Tk>');

        $lines->next();
        expect($lines->key())->toBe(4);
        expect($lines->current())->toBe('{');
      });
    });
  });

});
