CC=g++
#g++ -std=c++11 -O2 -mavx2 -c classify.cpp 
CFLAGS=-std=c++11 -O2 -pg

sources=main.cpp classify.cpp
objects=$(sources:.cpp=.o)

classify:$(sources)
	$(CC) $(CFLAGS) -fopenmp $^ -o $@

r = rfile
d = dfile
n = 1009072
t = 4
x = 3
type = 1
run: classify
	./classify $(r) $(d) $(n) $(t) $(x) $(type)

#classify.o: classify.h
#	touch classify.o
#	$(CC) $(CFLAGS) -c $<
#main.o: classify.h
#	$(CC) $(CFLAGS) -c $<

%.o: %.cpp classify.h
	$(CC) $(CFLAGS) -c $<
