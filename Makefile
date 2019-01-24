objects = json.o

all : fhs_json

fhs_json : $(objects)
	g++ -g  -o fhs_json $(objects) -pthread -lgtest

json.o : json.cpp json.h
	g++ -g -c json.cpp -pthread -lgtest

.PHONY :clean

test : 
	g++ -g -o json_test json.cpp jsontest.cpp  -lgtest
html :
	g++ -std=c++11 jsontest.cpp json.cpp -o main -lgtest -lpthread -g -Wall -Wshadow -fprofile-arcs -ftest-coverage
	./main
	gcov json.cpp
	gcov jsontest.cpp
	lcov -c -d . -o gcov.info
	genhtml -o json gcov.info
clean :
	-rm -rf *.o  *.gcda *.gcno fhs_json json_test main* 
