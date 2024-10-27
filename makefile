
all: 
	gcc chip8.c -o chip8 -Wall -Wextra -Werror -I/usr/include/SDL2 -lSDL2