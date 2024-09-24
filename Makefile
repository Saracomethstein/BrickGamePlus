#FLAGS
CC = g++
FLAGS = -Wall -Werror -Wextra -W

#SRC FILES
TETRIS_MODEL = brick_game/tetris/model/include/*.h brick_game/tetris/model/src/tetris.c brick_game/tetris/model/src/extern_tetris.cc
COMMON_MODEL = brick_game/common/*.h
CONTROLLER = controller/controller.cc controller/controller.h
CLI_VIEW = gui/cli/cli_views/view.cc gui/cli/cli_views/view.h
CLI_MAIN = gui/cli/main_cli.cc

SRC_FILES = ${wildcard $(TETRIS_MODEL) $(COMMON_MODEL) $(CONTROLLER) $(CLI_VIEW) $(CLI_MAIN)}
TRASH = $(wildcard brick_game/common/*.gch \
										brick_game/tetris/model/include/*.gch \
										controller/*.gch \
										gui/cli/cli_views/*.gch \
										*.o)

all:

build:
	@$(CC) $(FLAGS) -c $(SRC_FILES)

style:
	@clang-format --style=Google -i $(SRC_FILES)

clang:
	@clang-format --style=Google -n $(SRC_FILES)

clean:
	@rm -rf $(TRASH)