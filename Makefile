# FLAGS
CC = g++
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lncurses

# SRC FILES
TETRIS_MODEL_SRC = brick_game/tetris/model/src/tetris.c brick_game/tetris/model/src/extern_tetris.cc
# COMMON_MODEL_SRC = brick_game/common/common.cc  # предполагается, что есть какой-то .cc файл, т.к. .h не компилируется
CONTROLLER_SRC = controller/controller.cc
CLI_VIEW_SRC = gui/cli/cli_views/view.cc
CLI_MAIN_SRC = gui/cli/main_cli.cc

SRC_FILES = $(TETRIS_MODEL_SRC) $(CONTROLLER_SRC) $(CLI_VIEW_SRC) $(CLI_MAIN_SRC)

TRASH = $(wildcard brick_game/common/*.gch \
										brick_game/tetris/model/include/*.gch \
										controller/*.gch \
										gui/cli/cli_views/*.gch \
										*.o)

all: build/game

build:
	@mkdir -p build

build/game: build $(SRC_FILES)
	@$(CC) $(SRC_FILES) -o build/game $(CFLAGS) $(LDFLAGS)

style:
	@clang-format --style=Google -i $(SRC_FILES)

clang:
	@clang-format --style=Google -n $(SRC_FILES)

clean:
	@rm -rf $(TRASH) build/
