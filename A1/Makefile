all:
	g++ -std=c++11 -fPIC -g -c -Wall psort.cpp -fopenmp
	g++ -std=c++11 -shared -Wl,-soname,libsort.so -o libsort.so psort.o -lc
	g++ -std=c++11 -fopenmp -Wall psort.cpp driver.cpp -o a.out

data = input.txt
thread = 4

run:
	./a.out $(data) $(thread) 

clean:
	rm *.so *.o *.out