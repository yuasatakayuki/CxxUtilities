/*
 * Message.hh
 *
 *  Created on: Jul 15, 2011
 *      Author: yuasa
 */

#ifndef CXXUTILITIES_MESSAGE_HH_
#define CXXUTILITIES_MESSAGE_HH_

#ifndef _PTHREAD_H
#include <pthread.h>
#endif

#ifndef _USER_SIGNAL_H
#include <signal.h>
#endif

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

	virtual ~MessageException(){}

public:
	std::string toString(){
		std::string result;
		switch(status){
		case MessageIsTooLong:
			result="MessageIsTooLong";
			break;
		case Timeout:
			result="Timeout";
			break;
		default:
			result="UndefinedException";
			break;
		}
		return result;
	}
};

/** A class which provides a wrapper for a condition object used for inter-thread communication.
 * By using this class, a thread can send a string message to another thread.
 */
class Message {
private:
	std::queue<std::string*> messagequeue;
	Mutex messagequeuemutex;
	Condition condition;
public:
	/** Constructs an instance.
	 */
	Message() {
	}

	/** Destructor.
	 */
	~Message() {
	}

public:
	/** Sends a string message.
	 * @param message a message string.
	 */
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

	/** Trys to receive a message from another thread.
	 * This method will wait forever.
	 * @return a received message string.
	 */
	std::string receive() throw (MessageException) {
		return this->receive(0);
	}


	/** Trys to receive a message from another thread.
	 * This method will time out in a specified time.
	 * @param timeoutInMillisecond timeout duration in millisecond.
	 * @return a received message string.
	 */
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
#endif /* CXXUTILITIES_MESSAGE_HH_ */
