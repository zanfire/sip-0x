include ../../Makefile.inc

SRCS = parser/factory/FactoryContextSIPMessage.cpp \
	parser/tokens/RegexConstStrings.cpp \
	parser/tokens/TokenAbstract.cpp \
	parser/Parser.cpp \
	parser/ParserResult.cpp \
	protocol/SIPMessage.cpp \
	utils/Clock.cpp \
	utils/Connection.cpp \
	utils/ConnectionManager.cpp \
	utils/Logger.cpp \
	utils/LoggerFactory.cpp \
	utils/utils.cpp \
Endpoint.cpp \
	RegisterClient.cpp \
	RemotePeer.cpp \
	Transaction.cpp \
	TransactionLayer.cpp \
	TransportLayer.cpp \
	TransportLayerTCP.cpp \
	UA.cpp \
	UAS.cpp \
	UAC.cpp

OBJS = $(SRCS:.cpp=.o)
INCLUDES = -I. -I../../vendors/asio-1.10.6/include
OUT = libsip0x.a

.PHONY: depend clean
.SUFFIXES: .cpp

all: $(OUT)
	@echo  Compiled.

#$(MAIN): $(OBJS) 
#	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o $@

$(OUT): $(OBJS)
	ar rcs $(OUT) $(OBJS)

clean:
	$(RM) *.o *~ $(OUT)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
