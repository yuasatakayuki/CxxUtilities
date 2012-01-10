
TARGETS = \
test_String_toUInt8Array \
test_TCPClientSocket \
test_TCPServerSocket_packetSink

CXXFLAGS = -I$(CXXUTILITIES_PATH)/includes

all : $(TARGETS)

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
