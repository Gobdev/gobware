SRC 	 := $(CURDIR)/src
INCLUDE  := $(CURDIR)/include
BUILD    := $(CURDIR)/build
BIN      := $(CURDIR)/bin

CC       := g++
CFLAGS   := -std=c++11 -I$(INCLUDE)
LDFLAGS  := -lpqxx -lpq -lncursesw

export

.PHONY: config_tool clean

config_tool:
	$(MAKE) -C src/ $(BIN)/config_tool

clean:
	$(MAKE) -C src/ clean
