.PHONY:all
all:mycommand otherExe

mycommand:mycommand.c
	gcc -o $@ $^ -std=c99
otherExe:otherExe.cpp
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -f mycommand otherExe
