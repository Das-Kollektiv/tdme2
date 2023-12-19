#
BIN = bin
LIB_DIR = lib
OBJ := obj

# determine platform
OSSHORT := $(shell sh -c 'uname -o 2>/dev/null')
OS := $(shell sh -c 'uname -s 2>/dev/null')
MACHINE := $(shell sh -c 'uname -m 2>/dev/null')

#
MAIN_LDFLAGS = -L lib -l miniscript

#
CPPVERSION = -std=c++2a
OFLAGS = -O3
EXTRAFLAGS =
INCLUDES = -Isrc -Iext -I.

#
CPPFLAGS := $(CPPFLAGS) $(INCLUDES)
CFLAGS := $(OFLAGS) $(EXTRAFLAGS) -g -pipe -MMD -MP -DAPP_BUILD_TYPE=$(APP_BUILD_TYPE) -DNDEBUG
CXXFLAGS := $(CFLAGS) $(CPPVERSION)

# source files
SRC = {$source-path}
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
