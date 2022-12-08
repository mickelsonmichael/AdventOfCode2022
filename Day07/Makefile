DAY = Day07
FLAGS = -Wall -Wextra -Wpedantic
CC = g++

build: ${DAY}.cpp Utilities.cpp Dir.cpp Tree.cpp
	${CC} ${FLAGS} ${DAY}.cpp Utilities.cpp Dir.cpp Tree.cpp -o ${DAY}.o

example:
	make build && echo && echo && ./${DAY}.o example.txt $(p)

input:
	make build && echo && echo && ./${DAY}.o input.txt $(p)

clean:
	rm ${DAY}.o
