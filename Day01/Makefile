DAY = Day01
FLAGS = -Wall -Wextra
CC = g++

build:
	${CC} ${FLAGS} ${DAY}.cc -o ${DAY}

example:
	make build && echo && echo && ./${DAY} example.txt

input1:
	make build && echo && echo && ./${DAY} input1.txt

input2:
	make build && echo && echo && ./${DAY} input2.txt

clean:
	rm ${DAY}
