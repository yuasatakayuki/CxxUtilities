/*
 * Message.hh
 *
 *  Created on: Jul 15, 2011
 *      Author: yuasa
 */

#ifndef MESSAGE_HH_
#define MESSAGE_HH_

#include "CxxUtilities/Exception.hh"
#include "CxxUtilities/Mutex.hh"
#include "CxxUtilities/Condition.hh"

namespace CxxUtilities {

class MessageException: public CxxUtilities::Exception {
public:
	enum {
		MessageIsTooLong,Timeout
	};
public:
	MessageException(unsigned int status) : Exception(status){
	}
};

class Message {
private:
	std::queue<std::string*> messagequeue;
	Mutex messagequeuemutex;
	Condition condition;
public:
	Message() {
	}

	~Message() {
	}

	void send(std::string message) throw (MessageException) {
		if (message.size() > BufferSize) {
			throw MessageException(MessageException::MessageIsTooLong);
		}
		std::string* newmessage = new std::string();
		*newmessage = message;
		messagequeuemutex.lock();
		messagequeue.push(newmessage);
		messagequeuemutex.unlock();
		condition.signal();
	}

	std::string receive() throw (MessageException) {
		return this->receive(0);
	}

	std::string receive(int timeoutInMillisecond) throw (MessageException) {
		using namespace std;
		int ellapsedtime = 0;
		loop: messagequeuemutex.lock();
		if (messagequeue.size() != 0) {
			string* receivedmessage = messagequeue.front();
			messagequeue.pop();
			messagequeuemutex.unlock();
			return *receivedmessage;
		}
		messagequeuemutex.unlock();
		condition.wait(WaitInterval);
		if (timeoutInMillisecond != 0) {
			ellapsedtime += WaitInterval;
			if (ellapsedtime > timeoutInMillisecond) {
				throw MessageException(MessageException::Timeout);
			}
		}
		goto loop;
	}
public:
	static const unsigned int BufferSize = 256;
	static const int DepthOfMessageQueue = 1024;
private:
	static const int WaitInterval = 10; //10ms
};

}
#endif /* MESSAGE_HH_ */
