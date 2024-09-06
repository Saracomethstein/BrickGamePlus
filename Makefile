SNAKE_MDOEL = brick_game/snake/model/*.cc brick_game/snake/model/*.h 


all:

style:
	@clang-format --style=Google -i $(SNAKE_MDOEL)