#
BIN = bin
LIB_DIR = lib
OBJ := obj
OBJ_DEBUG = obj-debug

# determine platform
OSSHORT := $(shell sh -c 'uname -o 2>/dev/null')
OS := $(shell sh -c 'uname -s 2>/dev/null')
MACHINE := $(shell sh -c 'uname -m 2>/dev/null')

#
NAME = yannet
ifeq ($(OS), Darwin)
	LIB_EXT = .dylib
else ifeq ($(OSSHORT), Msys)
	LIB_EXT = .dll
else
	LIB_EXT = .so
endif
LIB := lib$(NAME)$(LIB_EXT)
LIBS_LDFLAGS =
MAIN_LDFLAGS =
LDFLAG_LIB := $(NAME)

#
SRCS_PLATFORM =

#
CPPVERSION = -std=c++2a
OFLAGS =
EXTRAFLAGS =
INCLUDES = -Isrc

#
CXX := $(CXX) -fPIC

# set platform specific flags
ifeq ($(OS), Darwin)
	# MacOSX
	EXTRAFLAGS := $(EXTRAFLAGS) -DHAVE_UNISTD_H
	SRCS_PLATFORM := $(SRCS_PLATFORM) \
		src/yannet/os/network/platform/bsd/KernelEventMechanism.cpp
	LIBS_LDFLAGS := -framework Cocoa -framework IOKit -framework Carbon -lssl -lcrypto
	OFLAGS := -O3
else ifeq ($(OS), FreeBSD)
	# FreeBSD
	SRCS_PLATFORM := $(SRCS_PLATFORM) \
		src/yannet/os/network/platform/bsd/KernelEventMechanism.cpp
	INCLUDES := $(INCLUDES) -I/usr/local/include
	LIBS_LDFLAGS := -L/usr/local/lib -lssl -lcrypto
	OFLAGS := -O3
else ifeq ($(OS), NetBSD)
	# NetBSD
	SRCS_PLATFORM := $(SRCS_PLATFORM) \
		src/yannet/os/network/platform/bsd/KernelEventMechanism.cpp
	INCLUDES := $(INCLUDES) -I/usr/pkg/include
	LIBS_LDFLAGS := -L/usr/X11R7/lib -L/usr/pkg/lib -lssl -lcrypto
	OFLAGS := -O3
else ifeq ($(OS), OpenBSD)
	# OpenBSD
	SRCS_PLATFORM := $(SRCS_PLATFORM) \
		src/yannet/os/network/platform/bsd/KernelEventMechanism.cpp
	INCLUDES := $(INCLUDES) -I/usr/local/include
	LIBS_LDFLAGS := -L/usr/local/lib -lm -lstdc++ -lssl -lcrypto
	OFLAGS := -O3
else ifeq ($(OS), Haiku)
	# Haiku
	SRCS_PLATFORM := $(SRCS_PLATFORM) \
		src/yannet/os/network/platform/bsd/KernelEventMechanism.cpp
	INCLUDES := $(INCLUDES) -I/boot/system/develop/headers
	LIBS_LDFLAGS := -lnetwork -lssl -lcrypto
	OFLAGS := -O3
else ifeq ($(OS), Linux)
	# Linux
	SRCS_PLATFORM := $(SRCS_PLATFORM) \
		src/yannet/os/network/platform/linux/KernelEventMechanism.cpp
	INCLUDES := $(INCLUDES)
	LIBS_LDFLAGS := -L/usr/lib64 -lssl -lcrypto
	OFLAGS := -O3
else ifeq ($(OSSHORT), Msys)
	# Windows
	SRCS_PLATFORM:= $(SRCS_PLATFORM) \
		src/yannet/os/network/platform/fallback/KernelEventMechanism.cpp
	INCLUDES := $(INCLUDES) -I/mingw64/include
	LIBS_LDFLAGS = -L/mingw64/lib -lws2_32 -lssl -lcrypto
	OFLAGS := -O3
endif

CPPFLAGS := $(INCLUDES)
CFLAGS := -g $(OFLAGS) $(EXTRAFLAGS) -pipe -MMD -MP -DNDEBUG
CFLAGS_DEBUG := -g -pipe -MMD -MP
CXXFLAGS := $(CFLAGS) $(CPPVERSION)
CXXFLAGS_DEBUG := $(CFLAGS_DEBUG) $(CPPVERSION)

LIBS := $(LIB_DIR)/$(LIB)

SRC = src

SRCS = \
	src/yannet/network/httpclient/HTTPClient.cpp \
	src/yannet/network/httpclient/HTTPClientException.cpp \
	src/yannet/network/httpclient/HTTPDownloadClient.cpp \
	src/yannet/network/udpclient/NetworkClientException.cpp \
	src/yannet/network/udpclient/UDPClient.cpp \
	src/yannet/network/udpclient/UDPClientMessage.cpp \
	src/yannet/network/udpserver/NetworkServerException.cpp \
	src/yannet/network/udpserver/ServerClient.cpp \
	src/yannet/network/udpserver/ServerClientRequestHandlerHubException.cpp \
	src/yannet/network/udpserver/ServerRequest.cpp \
	src/yannet/network/udpserver/ServerWorkerThread.cpp \
	src/yannet/network/udpserver/ServerWorkerThreadPool.cpp \
	src/yannet/network/udpserver/UDPServer.cpp \
	src/yannet/network/udpserver/UDPServerClient.cpp \
	src/yannet/network/udpserver/UDPServerIOThread.cpp \
	src/yannet/os/filesystem/FileSystem.cpp \
	src/yannet/os/network/Network.cpp \
	src/yannet/os/network/NetworkException.cpp \
	src/yannet/os/network/NetworkIOException.cpp \
	src/yannet/os/network/NetworkSocketClosedException.cpp \
	src/yannet/os/network/NetworkKEMException.cpp \
	src/yannet/os/network/NetworkSocket.cpp \
	src/yannet/os/network/NetworkSocketException.cpp \
	src/yannet/os/network/UDPSocket.cpp \
	src/yannet/os/network/SecureTCPSocket.cpp \
	src/yannet/os/network/TCPSocket.cpp \
	src/yannet/os/threading/Barrier.cpp \
	src/yannet/tests/ThreadingTest_ConsumerThread.cpp \
	src/yannet/tests/ThreadingTest_ProducerThread.cpp \
	src/yannet/tests/ThreadingTest_TestThread.cpp \
	src/yannet/tests/UDPServerTest_UDPServer.cpp \
	src/yannet/tests/UDPServerTest_UDPServerClient.cpp \
	src/yannet/utilities/Base64.cpp \
	src/yannet/utilities/Console.cpp \
	src/yannet/utilities/ExceptionBase.cpp \
	src/yannet/utilities/Integer.cpp \
	src/yannet/utilities/RTTI.cpp \
	src/yannet/utilities/StringTools.cpp \
	src/yannet/utilities/StringTokenizer.cpp \
	$(SRCS_PLATFORM)

MAIN_SRCS = \
	src/yannet/tests/HTTPClientTest-main.cpp \
	src/yannet/tests/HTTPDownloadClientTest-main.cpp \
	src/yannet/tests/ThreadingTest-main.cpp \
	src/yannet/tests/UDPClientTest-main.cpp \
	src/yannet/tests/UDPServerTest-main.cpp

MAINS = $(MAIN_SRCS:$(SRC)/%-main.cpp=$(BIN)/%)
OBJS = $(SRCS:$(SRC)/%.cpp=$(OBJ)/%.o)
OBJS_DEBUG = $(SRCS_DEBUG:$(SRC)/%.cpp=$(OBJ_DEBUG)/%.o)

define cpp-command
@mkdir -p $(dir $@);
@echo Compile $<; $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
endef

define cpp-command-debug
@mkdir -p $(dir $@);
@echo Compile $<; $(CXX) $(CPPFLAGS) $(CXXFLAGS_DEBUG) -c -o $@ $<
endef

define c-command
@mkdir -p $(dir $@);
@echo Compile $<; $(CXX) -x c $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
endef

$(LIB_DIR)/$(LIB): $(OBJS) $(OBJS_DEBUG)

$(OBJS):$(OBJ)/%.o: $(SRC)/%.cpp | print-opts
	$(cpp-command)

$(OBJS_DEBUG):$(OBJ_DEBUG)/%.o: $(SRC)/%.cpp | print-opts
	$(cpp-command-debug)

$(LIB_DIR)/$(LIB):
	@echo Creating shared library $@
	@mkdir -p $(dir $@)
	@rm -f $@
ifeq ($(OSSHORT), Msys)
	@scripts/windows-mingw-create-library-rc.sh $@ $@.rc
	@windres $@.rc -o coff -o $@.rc.o
	$(CXX) -shared $(patsubst %$(LIB_EXT),,$^) -o $@ $@.rc.o $(LIBS_LDFLAGS) -Wl,--out-implib,$(LIB_DIR)/$(LIB).a
	@rm $@.rc
	@rm $@.rc.o
else
	$(CXX) -shared $(patsubst %$(LIB_EXT),,$^) -o $@ $(LIBS_LDFLAGS)
endif
	@echo Done $@

ifeq ($(OSSHORT), Msys)
$(MAINS):$(BIN)/%:$(SRC)/%-main.cpp $(LIBS)
	@mkdir -p $(dir $@);
	@scripts/windows-mingw-create-executable-rc.sh "$<" $@.rc
	@windres $@.rc -o coff -o $@.rc.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $@.rc.o $< -L$(LIB_DIR) -l$(LDFLAG_LIB) $(MAIN_LDFLAGS)
	@rm $@.rc
	@rm $@.rc.o
else
$(MAINS):$(BIN)/%:$(SRC)/%-main.cpp $(LIBS)
	@mkdir -p $(dir $@);
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $< -L$(LIB_DIR) -l$(LDFLAG_LIB) $(MAIN_LDFLAGS)
endif

mains: $(MAINS)

all: mains

clean:
	rm -rf obj obj-debug $(LIB_DIR) $(BIN)

print-opts:
	@echo Building with \"$(CXX) $(CPPFLAGS) $(CXXFLAGS)\"
	
.PHONY: all mains clean print-opts

-include $(OBJS:%.o=%.d)
-include $(OBJS_DEBUG:%.o=%.d)
