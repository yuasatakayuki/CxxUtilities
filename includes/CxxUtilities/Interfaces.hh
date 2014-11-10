/*
 * Interfaces.hh
 *
 *  Created on: Jun 16, 2012
 *      Author: yuasa
 */

#ifndef CXXUTILITIES_INTERFACES_HH_
#define CXXUTILITIES_INTERFACES_HH_

#include "CommonHeader.hh"
#include "CxxUtilities/Condition.hh"
#include "CxxUtilities/Thread.hh"
#include "CxxUtilities/TCPSocket.hh"

namespace CxxUtilities {

class ClassnameInterface {
protected:
	std::string classname;

public:
	ClassnameInterface(std::string classname) {
		setClassname(classname);
	}

public:
	std::string getClassname() {
		return classname;
	}

	std::string getClassName() {
		return classname;
	}

	void setClassname(std::string classname) {
		this->classname = classname;
	}

	void setClassName(std::string classname) {
		this->classname = classname;
	}
};

class InstanceNameInterface {
private:
	std::string instanceName;

public:
	InstanceNameInterface(std::string instanceName) {
		this->instanceName = instanceName;
	}

public:
	std::string getInstanceName() {
		return instanceName;
	}

public:
	void setInstanceName(std::string instanceName) {
		this->instanceName = instanceName;
	}

};

template<typename T>
class TerminateInterface_ {
private:
	static std::vector<TerminateInterface_<int>*> db;
	static Mutex mutex;

public:
	class TerminateThread: public CxxUtilities::Thread {
	private:
		TerminateInterface_<int>* instance;
	public:
		TerminateThread(TerminateInterface_<int>* instance) {
			this->instance = instance;
		}
	public:
		void run() {
			instance->terminate();
		}
	};

public:
	TerminateInterface_() {
		db.push_back(this);
	}
	virtual ~TerminateInterface_() {
		mutex.lock();
		std::vector<TerminateInterface_<int>*>::iterator it = db.begin();
		for (; it != db.begin(); it++) {
			if ((*it) == this) {
				db.erase(it);
				break;
			}
		}
		mutex.unlock();
	}

public:
	static void terminateAll() {
		for (size_t i = 0; i < db.size(); i++) {
			TerminateThread* thread = new TerminateThread(db[i]);
			thread->start();
		}
		CxxUtilities::Condition c;
		c.wait(DefaultWaitDurationForTerminateAllInMs);
	}

public:
	static constexpr double DefaultWaitDurationForTerminateAllInMs = 1000.0; //ms

public:
	virtual void terminate() = 0;

};

template<typename T>
std::vector<TerminateInterface_<int>*> TerminateInterface_<T>::db;

template<typename T>
Mutex TerminateInterface_<T>::mutex;

typedef TerminateInterface_<int> TerminateInterface;

class MultipleTCPClientInterface: public CxxUtilities::StoppableThread {
public:
	std::vector<TCPServerAcceptedSocket*> acceptedSockets;

private:
	int tcpPortNumber = 0;
	TCPServerSocket* serverSocket;

public:
	MultipleTCPClientInterface(int tcpPortNumber) {
		this->tcpPortNumber = tcpPortNumber;
	}

public:
	static constexpr double AcceptTimeoutDuration=1000;//ms

public:
	void run() {
		serverSocket = new TCPServerSocket(tcpPortNumber);
		try {
			serverSocket->open();
		} catch (TCPSocketException& e) {
			using namespace std;
			cerr << "TCPServerSocket open failed (" << e.toString() << ")" << endl;
			cerr << "MultipleTCPClientInterface is stopped" << endl;
			return;
		}
		while (!this->stopped) {
			try {
				TCPServerAcceptedSocket* acceptedSocket =  serverSocket->accept(AcceptTimeoutDuration);
			} catch (TCPSocketException& e) {
				if (e.getStatus() == TCPSocketException::Timeout) {
					continue;
				}
				using namespace std;
				cerr << "TCPServerSocket accept failed (" << e.toString() << ")" << endl;
				cerr << "MultipleTCPClientInterface is stopped" << endl;
				this->stop();
				return;
			}
		}
	}

public:
	size_t getNAcceptedSockets() {
		return acceptedSockets.size();
	}

public:
	void disconnectAll() {
		for (auto socket : acceptedSockets) {
			socket->close();
		}
		acceptedSockets.clear();
	}

public:

};

}

#endif /* CXXUTILITIES_INTERFACES_HH_ */
