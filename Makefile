SRC 	 := src
INCLUDE  := include
BUILD    := build
BIN      := bin

CC       := g++
CFLAGS   := -std=c++11 -I$(INCLUDE)
LDFLAGS  := -lpqxx -lpq -lncursesw

SRCFILES := $(shell find src/ -name *.cpp)   #All $SRC/.cpp files
OBJFILES := $(patsubst $(SRC)/%.cpp, $(BUILD)/%.o, $(SRCFILES))
DEPFILES := $(patsubst $(SRC)/%.cpp, $(BUILD)/%.d, $(SRCFILES))

$(BUILD)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/config_tool: $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -o $@ $(LDFLAGS)

include $(DEPFILES)

$(BUILD)/%.d: $(SRC)/%.cpp
	@mkdir -p $(@D)
	bash ./depend.sh `dirname $<` $(CFLAGS) $< > $@
