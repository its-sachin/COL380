#include "psort.h"
#include <omp.h>
#include <iostream>


void swap(uint32_t* a, uint32_t* b){
    uint32_t temp = *a;
    *a = *b;
    *b = temp;
}

uint32_t partition(uint32_t* a, uint32_t left, uint32_t right) {

    // partition about leftmost(if not randomized)
    uint32_t val = a[left];
    uint32_t i = left-1;
    uint32_t j = right+1;

    while(true){

        do {
            i++;
        } 
        while (a[i] < val);

        do {
            j--;
        } 
        while (a[j] > val);

        if (i >= j){
            return j;
        }
 
        swap(&a[i], &a[j]);

    }

}


void quickSort(uint32_t* a, uint32_t left, uint32_t right){
    if (left<right){
        uint32_t part = partition(a,left,right);
        quickSort(a,left,part);
        quickSort(a,part+1,right);
    }
}


void heapify(uint32_t* heap, uint32_t i, uint32_t heapSize){
    uint32_t l = 2*i+1;
    uint32_t r = 2*i+2;
    
    uint32_t largest = i;
    if (l<heapSize && heap[l]>heap[i]){
        largest = l;
    }
    if (r<heapSize && heap[r] > heap[largest]){
        largest = r;
    }

    if (largest != i){
        swap(&heap[largest],&heap[i]);
        heapify(heap,largest,heapSize);
    }
}

void heapSort(uint32_t* heap, uint32_t n){
    uint32_t heapSize = n;

    uint32_t i = n/2;
    do {
        i--;
        heapify(heap,i,heapSize);
    }
    while (i != 0);

    for (uint32_t i=n-1;i>0;i--){
        swap(&heap[0],&heap[i]);
        heapSize = heapSize-1;
        heapify(heap,0,heapSize);
    }
}


void SequentialSort(uint32_t *data, uint32_t n){
    std::cout<<"Seq Sort "<<n <<std::endl;
    // heapSort(data, n);
    quickSort(data, 0, n-1);
}

void sortR(uint32_t *data, uint32_t n, int p){
    ParallelSort(data, n, p);
}

void ParallelSort(uint32_t *data, uint32_t n, int p)
{
    // Entry point to your sorting implementation.
    // Sorted array should be present at location pointed to by data.

    std::cout<<"Parallel Sort "<<n <<std::endl;
    if(p*p >= n) {
        SequentialSort(data, n);
        return;
    }

    uint32_t INF = 4294967295;
    uint32_t threshold = 2*n/p;

    uint32_t* R = new uint32_t[p*p];
    int mod = n%p;
    for(int i=0; i<p; i++){
        int k = std::min(i, mod);
        for(int j=0; j<p; j++){
            R[i*p + j] = data[i*(n/p)+ j + k];        
        }
    }
    sortR(R, p*p, p);

    uint32_t* S = new uint32_t[p+1];
    for(int i=0; i<p-1; i++){
        S[i+1] = R[(i+1)*p];
    }
    S[p] = INF;
    S[0] = 0;

    delete R;
    // WORK OF TASK i:
    uint32_t** B = new uint32_t*[p];
    uint32_t* Bsize = new uint32_t[p];
    for(int i=0; i<p; i++){
        Bsize[i] = 0;
        B[i] = new uint32_t[n];
        #pragma omp task firstprivate(i), shared(B,Bsize)
        {
            uint32_t size = 0;
            for(uint32_t j=0; j<n; j++){
                if(S[i] < data[j] && data[j] <= S[i+1]){
                    B[i][size++] = data[j];
                }
            }
            if(Bsize[i] < threshold) SequentialSort(B[i], size);
            else ParallelSort(B[i], size, p);

            Bsize[i] = size;
        }
    }
    #pragma omp taskwait
    

    delete S;
    for(int i=1; i<p; i++) Bsize[i] += Bsize[i-1];
    for(int i=0; i<p; i++){
        #pragma omp task firstprivate(i), shared(B,Bsize)
        {
            int k = 0;
            if(i > 0) k = Bsize[i-1];
            for(uint32_t j=0; j<Bsize[i]-k; j++) data[k + j] = B[i][j];
            delete B[i];
        }
    }
    #pragma omp taskwait

    delete B;
    delete Bsize;
}