.PHONY: config_tool clean

CONFIG_MODULES := config_tool db_util
CONFIG_SRC     := $(foreach subdir, $(CONFIG_MODULES), $(wildcard $(subdir)/*.cpp))
CONFIG_OBJ     := $(patsubst %.cpp, $(BUILD)/%.o, $(CONFIG_SRC))

config_tool: $(CONFIG_OBJ)
	$(CC) $(CFLAGS) $(CONFIG_OBJ) -o $(BIN)/config_tool $(LDFLAGS)

$(BUILD)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o
