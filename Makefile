kex : main.cpp
	g++ -c -Wall -fpic ${CCFLAGS} -o $@ $?

clean:
	unlink ./kex
