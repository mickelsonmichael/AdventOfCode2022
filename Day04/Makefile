DAY = Day04
FLAGS = -Wall -Wextra
CC = g++

build: ${DAY}.cpp Utilities.cpp
	${CC} ${FLAGS} ${DAY}.cpp Utilities.cpp -o ${DAY}.o

example:
	make build && echo && echo && ./${DAY}.o example.txt $(p)

input:
	make build && echo && echo && ./${DAY}.o input.txt $(p)

clean:
	rm ${DAY}.o
