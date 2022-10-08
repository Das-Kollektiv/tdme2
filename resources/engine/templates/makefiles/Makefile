# determine platform
OSSHORT := $(shell sh -c 'uname -o 2>/dev/null')
OS := $(shell sh -c 'uname -s 2>/dev/null')
ARCH := $(shell sh -c 'uname -m 2>/dev/null')

#
BIN = bin
LIB_DIR = lib
OBJ := obj
CPPVERSION = -std=c++2a
EXTRAFLAGS = -DRAPIDJSON_HAS_STDSTRING
OFLAGS =
INCLUDES = -Isrc -Iext -I. -Iext/reactphysics3d/src/ -Iext/v-hacd/src/VHACD_Lib/inc/

#EXTRAFLAGS := -D_GLIBCXX_DEBUG

# set platform specific flags
OSSHORT := $(shell sh -c 'uname -o 2>/dev/null')
OS := $(shell sh -c 'uname -s 2>/dev/null')
ARCH := $(shell sh -c 'uname -m 2>/dev/null')
ifeq ($(OS), Darwin)
	# MacOSX
	EXTRAFLAGS := $(EXTRAFLAGS) -DHAVE_UNISTD_H $(FLAGS)
	INCLUDES := $(INCLUDES) -Iext/fbx/macosx/include -Iext/glfw3/include
	MAIN_LDFLAGS := -L$(LIB_DIR) -ltdme2-ext -ltdme2 $(LDFLAGS)
	OFLAGS := -O2
else ifeq ($(OS), FreeBSD)
	# FreeBSD
	EXTRAFLAGS := $(EXTRAFLAGS) $(FLAGS)
	INCLUDES := $(INCLUDES) -I/usr/local/include
	MAIN_LDFLAGS := -L$(LIB_DIR) -ltdme2-ext -ltdme2 $(LDFLAGS)
	OFLAGS := -O2
else ifeq ($(OS), NetBSD)
	# NetBSD
	EXTRAFLAGS := $(EXTRAFLAGS) $(FLAGS)
	INCLUDES := $(INCLUDES) -I/usr/X11R7/include -I/usr/pkg/include
	MAIN_LDFLAGS := -L$(LIB_DIR) -ltdme2-ext -ltdme2 $(LDFLAGS)
	OFLAGS := -O2
else ifeq ($(OS), OpenBSD)
	# OpenBSD
	EXTRAFLAGS := $(EXTRAFLAGS) $(FLAGS)
	INCLUDES := $(INCLUDES) -I/usr/X11R6/include -I/usr/local/include
	MAIN_LDFLAGS := -L$(LIB_DIR) -ltdme2-ext -ltdme2 $(LDFLAGS)
	OFLAGS := -O2
else ifeq ($(OS), Haiku)
	# Haiku
	EXTRAFLAGS := $(EXTRAFLAGS) $(FLAGS)
	INCLUDES := $(INCLUDES) -I/boot/system/develop/headers
	MAIN_LDFLAGS := -L$(LIB_DIR) -ltdme2-ext -ltdme2 $(LDFLAGS)
	OFLAGS := -O2
else ifeq ($(OS), Linux)
	# Linux
	EXTRAFLAGS := $(EXTRAFLAGS) $(FLAGS)
	INCLUDES := $(INCLUDES) -L/usr/lib64
	MAIN_LDFLAGS := -L$(LIB_DIR) -ltdme2-ext -ltdme2 $(LDFLAGS)
	OFLAGS := -O2
else
	# Windows/MINGW
	EXTRAFLAGS := $(EXTRAFLAGS) $(FLAGS)
	INCLUDES := $(INCLUDES) -I/mingw64/include
	MAIN_LDFLAGS := -L$(LIB_DIR) -ltdme2-ext.dll -ltdme2.dll $(LDFLAGS)
	OFLAGS := -O2
endif

# set default application build type if not yet done
ifeq ($(APP_BUILD_TYPE),)
	override APP_BUILD_TYPE=0
endif

CFLAGS := -Wno-multichar
CPPFLAGS := $(CPPFLAGS) $(INCLUDES)
CFLAGS := $(CFLAGS) $(OFLAGS) $(EXTRAFLAGS) -g -pipe -MMD -MP -DAPP_BUILD_TYPE=$(APP_BUILD_TYPE) -DNDEBUG
#CFLAGS := $(CFLAGS) $(OFLAGS) $(EXTRAFLAGS) -g -pipe -MMD -MP -DAPP_BUILD_TYPE=$(APP_BUILD_TYPE)
#CFLAGS := $(CFLAGS) $(OFLAGS) $(EXTRAFLAGS) -pipe -MMD -MP -DAPP_BUILD_TYPE=$(APP_BUILD_TYPE) -DNDEBUG
CXXFLAGS := $(CFLAGS) $(CPPVERSION)

# source files
SRC = src
SRCS = {$source-files}

# executables source files
MAIN_SRCS = {$main-source-files}

#
MAINS = $(MAIN_SRCS:$(SRC)/%-main.cpp=$(BIN)/%)
OBJS = $(SRCS:$(SRC)/%.cpp=$(OBJ)/%.o)

all: $(OBJS)

define cpp-command
@mkdir -p $(dir $@); 
@echo Compile $<; $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
endef

$(OBJS):$(OBJ)/%.o: $(SRC)/%.cpp | print-opts
	$(cpp-command)

ifeq ($(OSSHORT), Msys)
$(MAINS):$(BIN)/%:$(SRC)/%-main.cpp $(OBJS)
	@mkdir -p $(dir $@);
	@EXECUTABLE=$$(echo $1 | grep -o '[a-zA-Z0-9]*-main' | sed -e 's/\-main//');
	@../tdme2/scripts/windows-mingw-create-executable-rc.sh "$<" $@.rc
	@windres $@.rc -o coff -o $@.rc.o
	$(CXX) $(STACKFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $@ $@.rc.o $< $(MAIN_LDFLAGS)
else
$(MAINS):$(BIN)/%:$(SRC)/%-main.cpp $(OBJS)
	@mkdir -p $(dir $@);
	$(CXX) $(STACKFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $@ $< $(MAIN_LDFLAGS)
endif

mains: $(MAINS)

clean:
	rm -rf $(OBJ) $(BIN)

print-opts:
	@echo Building with \"$(CXX) $(CPPFLAGS) $(CXXFLAGS)\"
	
.PHONY: all mains clean print-opts

-include $(OBJS:%.o=%.d)
