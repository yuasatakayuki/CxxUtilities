/*
 * TCPSocket.hh
 *
 *  Created on: Aug 5, 2011
 *      Author: yuasa
 */

#ifndef CXXUTILITIES_TCPSOCKET_HH_
#define CXXUTILITIES_TCPSOCKET_HH_

#include "CxxUtilities/CommonHeader.hh"
#include "CxxUtilities/Exception.hh"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>

namespace CxxUtilities {

class TCPSocketException: public CxxUtilities::Exception {
public:
	enum {
		Disconnected,
		Timeout,
		TCPSocketError,
		PortNumberError,
		BindError,
		ListenError,
		AcceptException,
		OpenException,
		CreateException,
		HostEntryError,
		ConnectFailed,
		ConnectExceptionWhenChangingSocketModeToNonBlocking,
		ConnectExceptionWhenWaitingForConnection,
		ConnectExceptionNonBlockingConnectionImmediateluSucceeded,
		ConnectExceptionNonBlockingConnectionReturnedUnexpecedResult,
		ConnectExceptionWhenChangingSocketModeToBlocking,
		Undefined
	};

public:
	TCPSocketException(uint32_t status) :
			CxxUtilities::Exception(status) {
	}

public:
	std::string toString() {
		std::string result;
		switch (status) {
		case Disconnected:
			result = "Disconnected";
			break;
		case Timeout:
			result = "Timeout";
			break;
		case TCPSocketError:
			result = "TCPSocketError";
			break;
		case PortNumberError:
			result = "PortNumberError";
			break;
		case BindError:
			result = "BindError";
			break;
		case ListenError:
			result = "ListenError";
			break;
		case AcceptException:
			result = "AcceptException";
			break;
		case OpenException:
			result = "OpenException";
			break;
		case CreateException:
			result = "CreateException";
			break;
		case HostEntryError:
			result = "HostEntryError";
			break;
		case ConnectFailed:
			result = "ConnectFailed";
			break;
		case ConnectExceptionWhenChangingSocketModeToNonBlocking:
			result = "ConnectExceptionWhenChangingSocketModeToNonBlocking";
			break;
		case ConnectExceptionWhenWaitingForConnection:
			result = "ConnectExceptionWhenWaitingForConnection";
			break;
		case ConnectExceptionNonBlockingConnectionImmediateluSucceeded:
			result = "ConnectExceptionNonBlockingConnectionImmediateluSucceeded";
			break;
		case ConnectExceptionNonBlockingConnectionReturnedUnexpecedResult:
			result = "ConnectExceptionNonBlockingConnectionReturnedUnexpecedResult";
			break;
		case ConnectExceptionWhenChangingSocketModeToBlocking:
			result = "ConnectExceptionWhenChangingSocketModeToBlocking";
			break;
		case Undefined:
			result = "Undefined";
			break;
		default:
			result = "Undefined status";
			break;
		}
		return result;
	}
};

class TCPSocket {
public:
	enum {
		TCPSocketInitialized, TCPSocketCreated, TCPSocketBound, TCPSocketListening, TCPSocketConnected
	};

protected:
	int status;

private:
	std::string name;
	double timeoutDurationInMilliSec;

protected:
	int socketdescriptor;
	int port;

public:
	TCPSocket() {
		status = TCPSocketInitialized;
		timeoutDurationInMilliSec = 0;
		setPort(-1);
	}

	~TCPSocket() {

	}

	int getStatus() {
		return status;
	}

	bool isConnected() {
		if (status == TCPSocketConnected) {
			return true;
		} else {
			return false;
		}
	}

public:
	long send(void* data, size_t length) throw (TCPSocketException) {
		long result = ::send(socketdescriptor, data, length, 0);
		if (result < 0) {
			throw TCPSocketException(TCPSocketException::TCPSocketError);
		}
		return result;
	}

	long receive(void* data, unsigned int length) throw (TCPSocketException) {
		long result = 0;
		_CxxUtilities_loop_receive: result = ::recv(socketdescriptor, data, length, 0);
		if (result <= 0) {
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				//todo
				throw TCPSocketException(TCPSocketException::Timeout);
			} else {
				std::string err;
				switch (errno) {
				case EBADF:
					err = "EBADF";
					break;
				case ECONNREFUSED:
					err = "ECONNREFUSED";
					break;
				case EFAULT:
					err = "EFAULT";
					break;
				case EINTR:
					err = "EINTR";
					break;
				case EINVAL:
					err = "EINVAL";
					break;
				case ENOMEM:
					err = "ENOMEM";
					break;
				case ENOTCONN:
					err = "ENOTCONN";
					break;
				case ENOTSOCK:
					err = "ENOTSOCK";
					break;
				}
				//temporary fixing 20120809 Takayuki Yuasa for CentOS VM environment
				if (errno == EINTR) {
					goto _CxxUtilities_loop_receive;
				} else {
					usleep(1000000);
					throw TCPSocketException(TCPSocketException::Disconnected);
				}
			}
		}
		return result;
	}

public:
	void setSocketDescriptor(int socketdescriptor) {
		this->socketdescriptor = socketdescriptor;
	}

	void setPort(unsigned short port) {
		this->port = port;
	}

	int getPort() {
		return port;
	}

	void setTimeout(double durationInMilliSec) {
		if (socketdescriptor != 0) {
			timeoutDurationInMilliSec = durationInMilliSec;
			struct timeval tv;
			tv.tv_sec = (unsigned int) (floor(durationInMilliSec / 1000.));
			if (durationInMilliSec > floor(durationInMilliSec)) {
				tv.tv_usec = (int) ((durationInMilliSec - floor(durationInMilliSec)) * 1000);
			} else {
				tv.tv_usec = (int) (durationInMilliSec * 1000);
			}
			setsockopt(socketdescriptor, SOL_SOCKET, SO_RCVTIMEO, (char *) &tv, sizeof tv);
		}
	}

	double getTimeoutDuration() {
		return timeoutDurationInMilliSec;
	}

	void setName(std::string name) {
		this->name = name;
	}

	std::string getName() {
		return name;
	}

public:
	void setNoDelay() {
		int flag = 1;
		int result = setsockopt(socketdescriptor, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int));
	}
};

class TCPServerAcceptedSocket: public TCPSocket {
private:
	struct ::sockaddr_in address;

public:
	TCPServerAcceptedSocket() :
			TCPSocket() {
		int n = 1;
#ifdef SO_NOSIGPIPE
		::setsockopt(this->socketdescriptor, SOL_SOCKET, SO_NOSIGPIPE, &n, sizeof(n));
#endif
	}

	~TCPServerAcceptedSocket() {
	}

	void open() throw (TCPSocketException) {
		throw TCPSocketException(TCPSocketException::OpenException);
	}

	void close() {
		switch (status) {
		case TCPSocketCreated:
		case TCPSocketBound:
		case TCPSocketListening:
		case TCPSocketConnected:
			::close(socketdescriptor);
			break;
		default:
			break;
		}
		status = TCPSocketInitialized;
	}

	bool isServerSocket() {
		return false;
	}

	void setAddress(struct ::sockaddr_in* address) {
		memcpy(&address, address, sizeof(struct ::sockaddr_in));
	}
};

class TCPServerSocket: public TCPSocket {
private:
	static const int maxofconnections = 5;

public:
	TCPServerSocket(int portNumber) :
			TCPSocket() {
		setPort(portNumber);
	}

	~TCPServerSocket() {
	}

	void open() throw (TCPSocketException) {
		if (getPort() < 0) {
			throw TCPSocketException(TCPSocketException::PortNumberError);
		}
		create();
		bind();
		listen();
		int n = 1;
#ifdef SO_NOSIGPIPE
		::setsockopt(this->socketdescriptor, SOL_SOCKET, SO_NOSIGPIPE, &n, sizeof(n));
#endif
	}

	void close() {
		switch (status) {
		case TCPSocketCreated:
		case TCPSocketBound:
		case TCPSocketListening:
		case TCPSocketConnected:
			::close(socketdescriptor);
			break;
		default:
			break;
		}
		status = TCPSocketInitialized;
	}

	bool isServerSocket() {
		return true;
	}

	void create() throw (TCPSocketException) {
		int result = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (result < 0) {
			throw TCPSocketException(TCPSocketException::TCPSocketError);
		} else {
			status = TCPSocketCreated;
			socketdescriptor = result;
		}
	}

	void bind() throw (TCPSocketException) {
		using namespace std;
		struct ::sockaddr_in serveraddress;
		memset(&serveraddress, 0, sizeof(struct ::sockaddr_in));
		serveraddress.sin_family = AF_INET;
		serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
		serveraddress.sin_port = htons(getPort());
		int yes = 1;
		setsockopt(socketdescriptor, SOL_SOCKET, SO_REUSEADDR, (const char *) &yes, sizeof(yes));
		int result = ::bind(socketdescriptor, (struct ::sockaddr*) &serveraddress, sizeof(struct ::sockaddr_in));
		if (result < 0) {
			throw TCPSocketException(TCPSocketException::BindError);
		} else {
			status = TCPSocketBound;
		}
	}

	void listen() throw (TCPSocketException) {
		int result = ::listen(socketdescriptor, maxofconnections);
		if (result < 0) {
			throw TCPSocketException(TCPSocketException::ListenError);
		} else {
			status = TCPSocketListening;
		}
	}

	TCPServerAcceptedSocket* accept() throw (TCPSocketException) {
		using namespace std;
		struct ::sockaddr_in clientaddress;
		int length = sizeof(clientaddress);
		int result = ::accept(socketdescriptor, (struct ::sockaddr*) &clientaddress, (::socklen_t*) &length);
		if (result < 0) {
			throw TCPSocketException(TCPSocketException::AcceptException);
		} else {
			int acceptedSocketDescriptor = result;
			TCPServerAcceptedSocket* acceptedsocket = new TCPServerAcceptedSocket();
			acceptedsocket->setAddress(&clientaddress);
			acceptedsocket->setPort(getPort());
			acceptedsocket->setSocketDescriptor(result);
			/*
			 int option = 1;
			 ::setsockopt(acceptedSocketDescriptor, SOL_SOCKET, SO_KEEPALIVE, (void*) &option, sizeof(option));
			 option = 1;
			 setsockopt(acceptedSocketDescriptor, IPPROTO_TCP, TCP_KEEPIDLE, (void*) &option, sizeof(option));
			 option = 1;
			 setsockopt(acceptedSocketDescriptor, IPPROTO_TCP, TCP_KEEPINTVL, (void*) &option, sizeof(option));
			 option = 3;
			 setsockopt(acceptedSocketDescriptor, IPPROTO_TCP, TCP_KEEPCNT, (void*) &option, sizeof(option));
			 */
			return acceptedsocket;
		}
	}

	TCPServerAcceptedSocket* accept(double timeoutDurationInMilliSec) throw (TCPSocketException) {
		fd_set mask;
		FD_ZERO(&mask);
		FD_SET(socketdescriptor, &mask);
		struct timeval tv;
		tv.tv_sec = (unsigned int) (floor(timeoutDurationInMilliSec / 1000.));
		tv.tv_usec = (int) (timeoutDurationInMilliSec * 1000 /* us */
		- ((int) ((timeoutDurationInMilliSec * 1000)) / 10000));
		using namespace std;
		int result = select(socketdescriptor + 1, &mask, NULL, NULL, &tv);
		if (result < 0) {
			throw TCPSocketException(TCPSocketException::AcceptException);
		}
		if (result == 0) {
			throw TCPSocketException(TCPSocketException::Timeout);
		}

		struct ::sockaddr_in clientaddress;
		int acceptedSocketDescriptor = result;

		int length = sizeof(clientaddress);
		result = 0;
		result = ::accept(socketdescriptor, (struct ::sockaddr*) &clientaddress, (::socklen_t*) &length);

		if (result < 0) {
			throw TCPSocketException(TCPSocketException::AcceptException);
		} else {
			TCPServerAcceptedSocket* acceptedsocket = new TCPServerAcceptedSocket();
			acceptedsocket->setAddress(&clientaddress);
			acceptedsocket->setPort(getPort());
			acceptedsocket->setSocketDescriptor(result);
			/*
			 int option = 1;
			 ::setsockopt(acceptedSocketDescriptor, SOL_SOCKET, SO_KEEPALIVE, (void*) &option, sizeof(option));
			 option = 1;
			 setsockopt(acceptedSocketDescriptor, IPPROTO_TCP, TCP_KEEPIDLE, (void*) &option, sizeof(option));
			 option = 1;
			 setsockopt(acceptedSocketDescriptor, IPPROTO_TCP, TCP_KEEPINTVL, (void*) &option, sizeof(option));
			 option = 3;
			 setsockopt(acceptedSocketDescriptor, IPPROTO_TCP, TCP_KEEPCNT, (void*) &option, sizeof(option));
			 */
			return acceptedsocket;
		}
	}
};

class TCPClientSocket: public TCPSocket {
private:
	std::string url;
	struct ::sockaddr_in serveraddress;

public:
	TCPClientSocket() :
			TCPSocket() {
		setURL("");
		socketdescriptor = NULL;
	}

	TCPClientSocket(std::string url, int port) :
			TCPSocket() {
		setURL(url);
		setPort(port);
		socketdescriptor = NULL;
	}

	~TCPClientSocket() {
	}

	void open(double timeoutDurationInMilliSec = 1000) throw (TCPSocketException) {
		if (url.size() == 0) {
			throw TCPSocketException(TCPSocketException::OpenException);
		}
		create();
		connect(timeoutDurationInMilliSec);
	}

	void open(std::string url, int port, double timeoutDurationInMilliSec = 1000) throw (TCPSocketException) {
		setURL(url);
		setPort(port);
		open(timeoutDurationInMilliSec);
		int n = 1;
#ifdef SO_NOSIGPIPE
		::setsockopt(this->socketdescriptor, SOL_SOCKET, SO_NOSIGPIPE, &n, sizeof(n));
#endif
	}

	void close() {
		switch (status) {
		case TCPSocketCreated:
		case TCPSocketBound:
		case TCPSocketListening:
		case TCPSocketConnected:
			::close(socketdescriptor);
			break;
		default:
			break;
		}
		status = TCPSocketInitialized;
	}

	bool isServerSocket() {
		return false;
	}

	void create() throw (TCPSocketException) {
		int result = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (result < 0) {
			throw TCPSocketException(TCPSocketException::CreateException);
		} else {
			status = TCPSocketCreated;
			socketdescriptor = result;
		}
	}

	void connect(double timeoutDurationInMilliSec) throw (TCPSocketException) {
		using namespace std;
		int result;
		if (status == TCPSocketConnected) {
			return;
		}
		struct ::sockaddr_in serveraddress;
		memset(&serveraddress, 0, sizeof(struct ::sockaddr_in));
		serveraddress.sin_family = AF_INET;
		serveraddress.sin_port = htons(getPort());
		//set url or ip address
		struct ::hostent* hostentry;
		hostentry = ::gethostbyname(url.c_str());
		if (hostentry == NULL) {
			throw TCPSocketException(TCPSocketException::HostEntryError);
		} else {
			serveraddress.sin_addr.s_addr = *((unsigned long*) hostentry->h_addr_list[0]);
		}

		result = 0;
		int flag = fcntl(socketdescriptor, F_GETFL, 0);
		if (flag < 0) {
			throw TCPSocketException(TCPSocketException::ConnectExceptionWhenChangingSocketModeToNonBlocking);
		}
		if (fcntl(socketdescriptor, F_SETFL, flag | O_NONBLOCK) < 0) {
			throw TCPSocketException(TCPSocketException::ConnectExceptionWhenChangingSocketModeToNonBlocking);
		}

		result = ::connect(socketdescriptor, (struct ::sockaddr*) &serveraddress, sizeof(struct ::sockaddr_in));

		if (result < 0) {
			if (errno == EINPROGRESS) {
				struct timeval tv;
				tv.tv_sec = (unsigned int) (floor(timeoutDurationInMilliSec / 1000.));
				tv.tv_usec = (int) ((timeoutDurationInMilliSec - floor(timeoutDurationInMilliSec)) * 1000);
				fd_set rmask, wmask;
				FD_ZERO(&rmask);
				FD_ZERO(&wmask);
				FD_SET(socketdescriptor, &wmask);
				result = select(socketdescriptor + 1, NULL, &wmask, NULL, &tv);
				if (result < 0) {
					throw TCPSocketException(TCPSocketException::ConnectExceptionWhenWaitingForConnection);
				} else if (result == 0) {
					//timeout happened
					throw TCPSocketException(TCPSocketException::Timeout);
				} else {
					struct sockaddr_in name;
					socklen_t len = sizeof(name);
					if (getpeername(socketdescriptor, (struct sockaddr*) &name, &len) >= 0) {
						//connected
						status = TCPSocketConnected;
						//reset flag
						if (fcntl(socketdescriptor, F_SETFL, flag) < 0) {
							throw TCPSocketException(
									TCPSocketException::ConnectExceptionWhenChangingSocketModeToBlocking);
						}
						return;
					} else {
						throw TCPSocketException(TCPSocketException::ConnectFailed);
					}
				}
			} else {
				throw TCPSocketException(
						TCPSocketException::ConnectExceptionNonBlockingConnectionReturnedUnexpecedResult);
			}
		} else {
			throw TCPSocketException(TCPSocketException::ConnectExceptionNonBlockingConnectionImmediateluSucceeded);
		}
	}

	void setURL(std::string url) {
		this->url = url;
	}
};

}
#endif /* CXXUTILITIES_TCPSOCKET_HH_ */
