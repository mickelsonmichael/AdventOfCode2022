FLAGS = -Wall -Wextra -Wpedantic
CC = g++

build: main.cpp utils.cpp
	${CC} ${FLAGS} utils.cpp main.cpp  -o solution.o

example:
	make build && echo && echo && ./solution.o example.txt $(p)

input:
	make build && echo && echo && ./solution.o input.txt $(p)

clean:
	rm solution.o
