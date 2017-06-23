CC := g++
CFLAGS := -std=c++11 -I $(CURDIR)/include/
LDFLAGS := -lpqxx -lpq

export

.PHONY: config_tool clean

config_tool:
	$(MAKE) -C src/ config_tool
	cp src/config_tool_bin bin/config_tool
	rm src/config_tool_bin

clean:
	$(MAKE) -C src/ clean
