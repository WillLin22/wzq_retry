
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

all: compile run

dir:
	mkdir -p $(BUILD_DIR)

compile: dir
	gcc -ggdb3 -o $(BUILD_DIR)/main $(SRC_DIR)/*.c -I${INCLUDE_DIR}


run:
	./$(BUILD_DIR)/main