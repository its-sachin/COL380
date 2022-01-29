void swap(uint32_t* a, uint32_t* b){
    uint32_t temp = *a;
    *a = *b;
    *b = temp;
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
    for (uint32_t i=n/2-1; i>=0; i--){
        heapify(heap,i,heapSize);
    }
    for (uint32_t i=n-1;i>0;i--){
        swap(&heap[0],&heap[i]);
        heapSize = heapSize-1;
        heapify(heap,0,heapSize);
    }
}
