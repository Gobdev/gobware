.PHONY: config_tool/db_util.o clean

config_tool/db_util.o:
	$(MAKE) -C config_tool/ db_util.o

config_tool: config_tool.cpp config_tool/db_util.o
	$(CC) $(CFLAGS) -c config_tool.cpp -o config_tool.o $(LDFLAGS)
	$(CC) $(CFLAGS) config_tool/db_util.o config_tool.o -o config_tool_bin $(LDFLAGS)

clean:
	$(MAKE) -C config_tool/ clean
	rm *.o
