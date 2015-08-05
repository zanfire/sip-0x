include ../../Makefile.inc

SRCS = mocks/TransportLayerMock.cpp \
	unittests/BaseTest.cpp \
	unittests/SIPParserTest.cpp \
	unittests/TestExecutor.cpp \
	unittests/TransactionTest.cpp \
	unittests/UACTest.cpp \
	unittests/UASTest.cpp \
	main.cpp \
	test_occurrences.cpp \
	test_sipmessages.cpp \
	test_tokens.cpp \
	test_utils.cpp

OBJS = $(SRCS:.cpp=.o)
INCLUDES = -I. -I../sip-0x -I../../vendors/asio-1.10.6/include
LIBS = -L../sip-0x -lsip0x

OUT = testrunner

.PHONY: depend clean
.SUFFIXES: .cpp

all: $(OUT)
	@echo  Compiled.

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o $@

$(OUT): $(OBJS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUT) $(OBJS) $(LFLAGS) $(LIBS)

clean:
	$(RM) *.o *~ $(OUT)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
