SNAKE_MDOEL = brick_game/snake/model/src/*.cc brick_game/snake/model/include/*.h 


all:

style:
	@clang-format --style=Google -i $(SNAKE_MDOEL)