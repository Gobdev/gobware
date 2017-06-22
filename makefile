CC := g++ -std=c++11 # This is the main compiler

.PHONY: config_tool

config_tool:
	$(MAKE) -C src/
	$(CC) src/config_tool.o -o bin/config_tool
