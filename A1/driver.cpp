#include <iostream>
#include <fstream>
#include <stdint.h>
#include <chrono>
#include <omp.h>
#include "psort.h"
#include <bits/stdc++.h>


void check_sorted(uint32_t *data, uint32_t* dataCopy, int n)
{
    // for (int i = 0; i < n - 1; i++)
    // {
    //     if (data[i] > data[i + 1])
    //     {
    //         std::cout << "\nData is not sorted.\n";
    //         return;
    //     }
    // }
    
    std::sort(dataCopy, dataCopy + n);
    for (int i = 0; i < n; i++)
    {
        if (data[i] != dataCopy[i])
        {
            std::cout << "\nData is not sorted.\n";
            return;
        }
    }

    std::cout << "\nData is sorted.\n";
    return;
}


void SortData(uint32_t *data, uint32_t n, int p, int n_threads)
{
    #pragma omp parallel num_threads(n_threads)
    {
        #pragma omp single
        ParallelSort(data, n, p);
    }
}


int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Insufficient Arguments\n"; // <datafile> <n_threads>
        return 0;
    }

    std::fstream fs(argv[1], std::fstream::in);

    // Reading data
    uint32_t n, d = 0;
    int p, n_threads = atoi(argv[2]);
    fs >> n >> p;
    uint32_t *data = new uint32_t[n];
    uint32_t *dataCopy = new uint32_t[n];

    std::cout << "n_threads = " << n_threads << std::endl;
    std::cout << "N = " << n << " p = " << p << '\n'<< std::endl;

    while (fs >> data[d++]){
        dataCopy[d-1] = data[d-1];
        if(d == n)
            break;
    }

    fs.close();

    // Sorting
    auto begin = std::chrono::high_resolution_clock::now();
    SortData(data, n, p, n_threads);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    double duration = (1e-6 * (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)).count());

    check_sorted(data, dataCopy, n);
    std::cout << "Time taken for sorting " << n << " elements with "
        << p << " buckets = " << duration << "ms" << std::endl;

    // Clean-up
    delete data;
    delete dataCopy;

    return 0;
}