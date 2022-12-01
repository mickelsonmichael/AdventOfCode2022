DAY = Day00
FLAGS = -Wall -Wextra
CC = g++

build: ${DAY}.cpp Utilities.cpp
	${CC} ${FLAGS} ${DAY}.cpp Utilities.cpp -o ${DAY}.o

example:
	make build && echo && echo && ./${DAY}.o example.txt

input1:
	make build && echo && echo && ./${DAY}.o input1.txt

input2:
	make build && echo && echo && ./${DAY}.o input2.txt

clean:
	rm ${DAY}.o
