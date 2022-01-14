#include <stdio.h>
#include <vector>
#include <thread>
#include <atomic>
using namespace std;

#define aSIZ 65
#define P 2
#define N 1024*1024*P

static atomic<int> a[aSIZ] __attribute__ ((aligned(32)));

void threadFn(int tid, int count, int stride, int val){
    for(int i=0; i<count; i++){
        a[tid*stride] = val;
    }
}

int main(int argc, char const *argv[])
{
    
    vector<thread> threads;

    auto begin = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < P; i++)
    {
        threads.push_back(thread(threadFn, i, N, atoi(argv[1]), atoi(argv[1]) ));
    }
    for(auto &th : threads){th.join();}

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    float ms = 1e-6 * (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)).count();
    printf("%f ms\n", ms);
    
    return 0;
}
