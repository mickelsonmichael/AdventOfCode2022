DAY = Day07
FLAGS = -Wall -Wextra -Wpedantic
CC = g++

build: ${DAY}.cpp Utilities.cpp Item.cpp Dir.cpp File.cpp
	${CC} ${FLAGS} ${DAY}.cpp Utilities.cpp Item.cpp Dir.cpp File.cpp -o ${DAY}.o

example:
	make build && echo && echo && ./${DAY}.o example.txt $(p)

input:
	make build && echo && echo && ./${DAY}.o input.txt $(p)

clean:
	rm ${DAY}.o
