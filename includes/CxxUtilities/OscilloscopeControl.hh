/*
 * OscilloscopeControl.hh
 *
 *  Created on: Nov 27, 2012
 *      Author: yuasa
 */

#ifndef OSCILLOSCOPECONTROL_HH_
#define OSCILLOSCOPECONTROL_HH_

#include "TCPSocket.hh"
#include "CommonHeader.hh"

const size_t BufferSize = 1024;
uint8_t* buffer = new uint8_t[BufferSize];

void sendCommand(CxxUtilities::TCPSocket* socket, std::string command) {
	using namespace std;
	cout << "Sending command " << command << endl;
	string str = command + "´n´r";
	socket->send((void*) str.c_str(), str.size());
}

std::vector<uint8_t> receiveBinaryData(CxxUtilities::TCPSocket* socket) {
	using namespace std;
	using namespace CxxUtilities;
	size_t readDoneSize = 0;
	size_t sizeOfSizePart = 0;
	size_t sizeOfData = 0;
	size_t size;

	std::vector<uint8_t> data;

	//read header
	size = socket->receive(buffer, 2);
	sizeOfSizePart = ((unsigned char) buffer[1]) - '0';

	//read size part
	size = socket->receive(buffer, sizeOfSizePart);
	for (size_t i = 0; i < sizeOfSizePart; i++) {
		sizeOfData = sizeOfData * 10 + (((unsigned char) buffer[i]) - '0');
	}

	cout << "size=" << sizeOfData << endl;

	//read
	while (readDoneSize < sizeOfData) {
		size = socket->receive(buffer, BufferSize);
		for (size_t i = 0; i < size; i++) {
			data.push_back(buffer[i]);
		}
		readDoneSize += size;
	}
	cout << readDoneSize << "-byte binary data received." << endl;
	return data;
}

int main(int argc, char* argv[]) {
	using namespace std;
	using namespace CxxUtilities;
	TCPClientSocket* socket = new TCPClientSocket("192.168.0.2", 5025);
	ofstream ofs("file.png");
	string str;
	socket->setTimeout(1000);
	try {
		socket->open();

		sendCommand(socket, ":display:data? png");
		std::vector<uint8_t> data = receiveBinaryData(socket);

		//write to file
		for(size_t i=0;i<data.size();i++){
			ofs << data[i];
		}
	} catch (TCPSocketException& e) {
		cerr << "TCPSocketException " << e.toString() << endl;
	} catch (...) {
		cerr << "Exception" << endl;
	}

	ofs.close();
}

#endif /* OSCILLOSCOPECONTROL_HH_ */
