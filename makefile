CC := g++  # This is the main compiler
CFLAGS := -Wall -std=c++11

export

.PHONY: config_tool clean

config_tool:
	$(MAKE) -C src/ config_tool.o
	$(CC) $(CFLAGS) src/config_tool.o -o bin/config_tool

clean:
	$(MAKE) -C src/ clean
