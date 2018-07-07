COMPILER_OPTIONS = -std=c99 -lm -Iinclude
# Source subdirs quoted for bashes without globstar or other shells
SOURCES = src/*.c src/builtins/*.c src/run/*.c
BIN_DIR = bin
BIN_NAME = pseudoc

BIN_PATH = $(BIN_DIR)/$(BIN_NAME)

.PHONY: all clean
all: $(BIN_DIR) $(BIN_PATH)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_PATH):
	gcc $(COMPILER_OPTIONS) $(SOURCES) -o $(BIN_PATH) || make clean

clean:
	rm -f $(BIN_PATH)
	rmdir --ignore-fail-on-non-empty $(BIN_DIR)
