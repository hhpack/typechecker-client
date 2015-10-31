<?hh //partial

namespace hhpack\typechecker\check\spec;

use hhpack\typechecker\check\Message;
use stdClass;

describe('Message', function() {
    beforeEach(function() {
        $object = new stdClass();
        $object->code = 2055;
        $object->descr = "error message";
        $object->path = "/foo/var/example.hh";
        $object->line = 38;
        $object->end = 26;
        $object->start = 26;

        $this->object = $object;
        $this->message = Message::fromObject($object);
    });
    describe('#fromObject', function() {
        it('return Message instance', function() {
            $message = Message::fromObject($this->object);
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
