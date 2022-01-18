CC=g++
CFLAGS=-std=c++11 -O2 -pg -g

sources=main.cpp classify.cpp
objects=$(sources:.cpp=.o)

classify:$(sources)
	$(CC) $(CFLAGS) -fopenmp $^ -o $@

run: classify
	./classify rfile dfile 1009072 4 3

r = rfile
d = dfile
n = 1009072
t = 4
x = 3
type = 1
test: classify
	./classify $(r) $(d) $(n) $(t) $(x) $(type)

clean: 
	-rm classify
	
%.o: %.cpp classify.h
	$(CC) $(CFLAGS) -c $<