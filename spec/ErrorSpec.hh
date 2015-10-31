<?hh //partial

namespace hhpack\typechecker\spec;

use hhpack\typechecker\Error;
use stdClass;

describe('Error', function() {
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

        $this->errorObject = $errorObject;
        $this->error = Error::fromObject($errorObject);
    });
    describe('#getMessages', function() {
        it('return Iterator<Message> instance', function() {
            expect($this->error->getMessages())->toBeAnInstanceOf(Iterator::class);
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
                $errorObject = new stdClass();
                $errorObject->message = [];

                $this->errorObject = $errorObject;
                $this->error = Error::fromObject($errorObject);
            });
            it('return false', function() {
                expect($this->error->hasMessages())->toBeFalse();
            });
        });
    });
});
