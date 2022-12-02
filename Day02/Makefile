DAY = Day02
FLAGS = -Wall -Wextra
CC = g++

build: ${DAY}.cpp Utilities.cpp
	${CC} ${FLAGS} ${DAY}.cpp Utilities.cpp -o ${DAY}.o

example:
	make build && echo && echo && ./${DAY}.o example.txt

input:
	make build && echo && echo && ./${DAY}.o input.txt

clean:
	rm ${DAY}.o
