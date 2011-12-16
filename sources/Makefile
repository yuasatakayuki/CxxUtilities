
TARGETS = \
test_String_toUInt8Array \
test_TCPClientSocket

CXXFLAGS = -I$(CXXUTILITIES_PATH)/includes

all : $(TARGETS)

$(EXECUTABLES) : 
	$(CXX) $@ $@.o $(LDLIBS) $(LDOBJS) $(LDFLAGS)
.cc.o :
	$(CXX) -g -O0 $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -c $<
	  
clean : 
	rm $(TARGETS)
