
TARGETS = \
test_Env \
test_TCPSocket_VHDL
#test_String_toUInt8Array \
#test_TCPSocket_receive \
#test_TCPSocket_server_accept_timeout \
#test_TCPSocket_server \
#test_Message
#test_TCPClientSocket \
#test_TCPServerSocket_packetSink

CXXFLAGS = -I$(CXXUTILITIES_PATH)/includes

all : $(TARGETS)

test_Env : test_Env.o
	$(CXX) -g $^ -o $@

test_TCPSocket_VHDL : test_TCPSocket_VHDL.o
	$(CXX) -g $^ -o $@

test_TCPSocket_server : test_TCPSocket_server.o
	$(CXX) -g $^ -o $@

test_Message : test_Message.o
	$(CXX) -g $^ -o $@

test_TCPSocket_server_accept_timeout : test_TCPSocket_server_accept_timeout.o
	$(CXX) -g $^ -o $@

test_TCPSocket_receive : test_TCPSocket_receive.o
	$(CXX) -g $^ -o $@

test_TCPServerSocket_packetSink : test_TCPServerSocket_packetSink.o
	$(CXX) -g $^ -o $@

test_TCPClientSocket : test_TCPClientSocket.o
	$(CXX) -g $^ -o $@

test_String_toUInt8Array : test_String_toUInt8Array.o
	$(CXX) -g $^ -o $@

.cc.o :
	$(CXX) -g -O0 $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -c $<
	  
clean : 
	rm $(TARGETS) $(addsuffix .o, $(TARGETS))
