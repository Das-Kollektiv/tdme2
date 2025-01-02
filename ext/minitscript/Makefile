#
BIN = bin
LIB_DIR = lib
OBJ = obj

#
INSTALL_BIN_DIR = /usr/local/bin
INSTALL_LIB_DIR = /usr/local/lib
INSTALL_DATA_DIR = /usr/local/share
INSTALL_MAN_DIR = /usr/local/share/man
INSTALL_LDCONFIG = YES

# determine platform
OSSHORT = $(shell sh -c 'uname -o 2>/dev/null')
OS = $(shell sh -c 'uname -s 2>/dev/null')

#
NAME = minitscript
ifeq ($(OS), Darwin)
	LIB_EXT = .dylib
else ifeq ($(OSSHORT), Msys)
	LIB_EXT = .dll
else
	LIB_EXT = .so
endif
LIB = lib$(NAME)$(LIB_EXT)
MAIN_LDFLAGS = -L $(LIB_DIR) -l $(NAME)

#
CPPVERSION = -std=c++2a
OFLAGS = -O3
EXTRAFLAGS = -DMINITSCRIPT_DATA=string\(\".\"\)
INCLUDES = -Isrc -Iext -I.
STACKFLAGS =
PLATFORM = Unknown

# set platform specific flags
ifeq ($(OS), Darwin)
	# MacOSX
	LIBS_LDFLAGS = -lssl -lcrypto
	STACKFLAGS = -Wl,-stack_size -Wl,0xA00000
	PLATFORM = Darwin
else ifeq ($(OS), FreeBSD)
	# FreeBSD
	INCLUDES := $(INCLUDES) -I/usr/local/include
	LIBS_LDFLAGS = -L/usr/local/lib -lssl -lcrypto
	STACKFLAGS = -Wl,-stack_size -Wl,0xA00000
	PLATFORM = FreeBSD
else ifeq ($(OS), NetBSD)
	# NetBSD
	INCLUDES := $(INCLUDES) -I/usr/pkg/include
	LIBS_LDFLAGS = -L/usr/pkg/lib -lssl -lcrypto
	PLATFORM = NetBSD
else ifeq ($(OS), OpenBSD)
	# OpenBSD
	INCLUDES := $(INCLUDES) -I/usr/local/include
	LIBS_LDFLAGS = -L/usr/local/lib -lssl -lcrypto
	STACKFLAGS = -Wl,-stack_size -Wl,10485760
	PLATFORM = OpenBSD
else ifeq ($(OS), Haiku)
	# Haiku
	INCLUDES := $(INCLUDES) -I/boot/system/develop/headers
	LIBS_LDFLAGS = -lnetwork -lssl -lcrypto
	PLATFORM = Haiku
	INSTALL_BIN_DIR = /boot/home/config/non-packaged/bin
	INSTALL_LIB_DIR = /boot/home/config/non-packaged/lib
	INSTALL_DATA_DIR = /boot/home/config/non-packaged/data
	INSTALL_MAN_DIR = /boot/home/config/non-packaged/man
	INSTALL_LDCONFIG = NO
else ifeq ($(OS), Linux)
	# Linux
	LIBS_LDFLAGS = -L/usr/lib64 -lssl -lcrypto
	PLATFORM = Linux
else ifeq ($(OSSHORT), Msys)
	INCLUDES := $(INCLUDES) -I/mingw64/include
	LIBS_LDFLAGS = -L/mingw64/lib -lws2_32 -lssl -lcrypto
	STACKFLAGS = -Wl,--stack,10485760
	PLATFORM = Msys
endif

#
CPPFLAGS = $(INCLUDES)
CFLAGS = -g $(OFLAGS) $(EXTRAFLAGS) -pipe -MMD -MP -DNDEBUG -fPIC
CXXFLAGS = $(CFLAGS) $(CPPVERSION)

SRC = src

SRCS = \
	src/minitscript/minitscript/ApplicationMethods.cpp \
	src/minitscript/minitscript/ArrayMethods.cpp \
	src/minitscript/minitscript/BaseMethods.cpp \
	src/minitscript/minitscript/ByteArrayMethods.cpp \
	src/minitscript/minitscript/CryptographyMethods.cpp \
	src/minitscript/minitscript/ConsoleMethods.cpp \
	src/minitscript/minitscript/ContextMethods.cpp \
	src/minitscript/minitscript/Context.cpp \
	src/minitscript/minitscript/Documentation.cpp \
	src/minitscript/minitscript/FileSystemMethods.cpp \
	src/minitscript/minitscript/Generator.cpp \
	src/minitscript/minitscript/HTTPDownloadClientClass.cpp \
	src/minitscript/minitscript/JSONMethods.cpp \
	src/minitscript/minitscript/Library.cpp \
	src/minitscript/minitscript/MapMethods.cpp \
	src/minitscript/minitscript/MathMethods.cpp \
	src/minitscript/minitscript/MinitScript.cpp \
	src/minitscript/minitscript/NetworkMethods.cpp \
	src/minitscript/minitscript/ScriptMethods.cpp \
	src/minitscript/minitscript/SetMethods.cpp \
	src/minitscript/minitscript/Setup.cpp \
	src/minitscript/minitscript/StringMethods.cpp \
	src/minitscript/minitscript/TimeMethods.cpp \
	src/minitscript/minitscript/Transpiler.cpp \
	src/minitscript/minitscript/Validations.cpp \
	src/minitscript/minitscript/Version.cpp \
	src/minitscript/minitscript/XMLMethods.cpp \
	src/minitscript/network/httpclient/HTTPClient.cpp \
	src/minitscript/network/httpclient/HTTPClientException.cpp \
	src/minitscript/network/httpclient/HTTPDownloadClient.cpp \
	src/minitscript/os/filesystem/FileSystem.cpp \
	src/minitscript/os/network/Network.cpp \
	src/minitscript/os/network/NetworkException.cpp \
	src/minitscript/os/network/NetworkIOException.cpp \
	src/minitscript/os/network/NetworkSocket.cpp \
	src/minitscript/os/network/NetworkSocketClosedException.cpp \
	src/minitscript/os/network/NetworkSocketException.cpp \
	src/minitscript/os/network/SecureTCPSocket.cpp \
	src/minitscript/os/network/TCPSocket.cpp \
	src/minitscript/utilities/Base64.cpp \
	src/minitscript/utilities/Console.cpp \
	src/minitscript/utilities/ErrorConsole.cpp \
	src/minitscript/utilities/ExceptionBase.cpp \
	src/minitscript/utilities/Float.cpp \
	src/minitscript/utilities/Hex.cpp \
	src/minitscript/utilities/Integer.cpp \
	src/minitscript/utilities/Properties.cpp \
	src/minitscript/utilities/RTTI.cpp \
	src/minitscript/utilities/SHA256.cpp \
	src/minitscript/utilities/StringTools.cpp \
	src/minitscript/utilities/StringTokenizer.cpp \
	src/minitscript/utilities/UTF8StringTools.cpp \
	src/minitscript/utilities/UTF8StringTokenizer.cpp

MAIN_SRCS = \
	src/minitscript/tools/minitscript-main.cpp \
	src/minitscript/tools/minitscriptbuild-main.cpp \
	src/minitscript/tools/minitscriptdocumentation-main.cpp \
	src/minitscript/tools/minitscriptlibrary-main.cpp \
	src/minitscript/tools/minitscriptmain-main.cpp \
	src/minitscript/tools/minitscriptmakefile-main.cpp \
	src/minitscript/tools/minitscriptnmakefile-main.cpp \
	src/minitscript/tools/minitscripttranspiler-main.cpp \
	src/minitscript/tools/minitscriptuntranspiler-main.cpp

MAINS = $(MAIN_SRCS:$(SRC)/%-main.cpp=$(BIN)/%)
OBJS = $(SRCS:$(SRC)/%.cpp=$(OBJ)/%.o)

define cpp-command
@mkdir -p $(dir $@);
@echo Compile $<; $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
endef

$(LIB_DIR)/$(LIB): $(OBJS)

$(OBJS):$(OBJ)/%.o: $(SRC)/%.cpp | print-opts
	$(cpp-command)

$(LIB_DIR)/$(LIB): $(OBJS)
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
$(MAINS):$(BIN)/%:$(SRC)/%-main.cpp $(LIB_DIR)/$(LIB)
	@mkdir -p $(dir $@);
	@scripts/windows-mingw-create-executable-rc.sh "$<" $@.rc
	@windres $@.rc -o coff -o $@.rc.o
	$(CXX) $(STACKFLAGS) $(CPPFLAGS) $(CXXFLAGS) -o $@ $@.rc.o $< $(MAIN_LDFLAGS) 
	@rm $@.rc
	@rm $@.rc.o
else
$(MAINS):$(BIN)/%:$(SRC)/%-main.cpp $(LIB_DIR)/$(LIB)
	@mkdir -p $(dir $@);
	$(CXX) $(STACKFLAGS) $(CPPFLAGS) $(CXXFLAGS) -o $@ $< $(MAIN_LDFLAGS)
endif

platform-check:
ifeq ($(PLATFORM), Unknown)
	@echo "Unknown platform. Exiting";\
	exit 1;
endif

release-check:
ifeq ($(RELEASE), YES)
ifeq ($(OS), Haiku)
EXTRAFLAGS = -DMINITSCRIPT_DATA=string\(\"/boot/home/config/non-packaged/data/minitscript\"\)
else
EXTRAFLAGS = -DMINITSCRIPT_DATA=string\(\"/usr/local/share/minitscript\"\)
endif
endif

mains: platform-check release-check $(MAINS)

all: mains

clean:
	rm -rf obj obj-debug $(LIB_DIR) $(BIN)

install: platform-check $(MAINS)
	# for now, this was only tested with Linux Mint 21.2, Haiku Nightly
	@echo "Installing resources to $(INSTALL_DATA_DIR)/minitscript"
	rm -rf $(INSTALL_DATA_DIR)/minitscript
	mkdir $(INSTALL_DATA_DIR)/minitscript
	cp -r ./resources $(INSTALL_DATA_DIR)/minitscript/
	cp -r ./src $(INSTALL_DATA_DIR)/minitscript/
	cp -r ./ext $(INSTALL_DATA_DIR)/minitscript/
	cp -r ./lib $(INSTALL_DATA_DIR)/minitscript/
	@echo "Installing library to $(INSTALL_LIB_DIR)"
	cp $(LIB_DIR)/$(LIB) $(INSTALL_LIB_DIR)/
ifeq ($(INSTALL_LDCONFIG), YES)
	echo "$(INSTALL_LIB_DIR)" > /etc/ld.so.conf.d/libminitscript.conf
	ldconfig
endif
	@echo "Installing binaries to $(INSTALL_BIN_DIR)"
	cp ./bin/minitscript/tools/* $(INSTALL_BIN_DIR)/
	@echo "Installing man page to $(INSTALL_MAN_DIR)/man7"
	mkdir -p $(INSTALL_MAN_DIR)/man7
	cp ./resources/minitscript/man/minitscript.7 $(INSTALL_MAN_DIR)/man7/

print-opts:
	@echo Building with \"$(CXX) $(CPPFLAGS) $(CXXFLAGS)\"
	
.PHONY: all mains clean print-opts

-include $(OBJS:%.o=%.d)
