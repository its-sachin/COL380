#include "classify.h"
#include <omp.h>


Data classify(Data &D, const Ranges &R, unsigned int numt)
{ // Classify each item in D into intervals (given by R). Finally, produce in D2 data sorted by interval

   assert(numt < MAXTHREADS);
   Counter counts[R.num()]; // I need on counter per interval. Each counter can keep pre-thread subcount.

   auto begin = std::chrono::high_resolution_clock::now();

   #pragma omp parallel num_threads(numt)
   {
      int tid = omp_get_thread_num(); // I am thread number tid
      for(int i=tid; i<D.ndata; i+=numt) { // Threads together share-loop through all of Data
      // int lim = std::min(((tid+1)*D.ndata)/numt,D.ndata);

      // unsigned int K = D.ndata/numt;
      // for(int i= tid*K ; i < std::min((tid+1)*K,D.ndata); i+=1) {
         // std::cout << tid << " "<<sizeof(D.data)*D.ndata << "\n"<<std::endl;
         
         int v = D.data[i].value = R.range(D.data[i].key);// For each data, find the interval of data's key,
							  // and store the interval id in value. D is changed.
         counts[v].increase(tid); // Found one key in interval v
      }
   }

   auto end = std::chrono::high_resolution_clock::now();
   auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
   std::cout << "time " <<1e-6 * (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)).count() << std::endl;


   // Accumulate all sub-counts (in each interval;'s counter) into rangecount
   unsigned int *rangecount = new unsigned int[R.num()];
   for(int r=0; r<R.num(); r++) { // For all intervals
      rangecount[r] = 0;
      for(int t=0; t<numt; t++) // For all threads
         rangecount[r] += counts[r].get(t);
      // std::cout << rangecount[r] << " elements in Range "<< R.lo(r)<<" "<<R.hi(r)<<" " << r << "\n"; // Debugging statement
   }

   // Compute prefx sum on rangecount.
   for(int i=1; i<R.num(); i++) {
      rangecount[i] += rangecount[i-1];
   }

   // Now rangecount[i] has the number of elements in intervals before the ith interval.

   Data D2 = Data(D.ndata); // Make a copy
   
   #pragma omp parallel num_threads(numt)
   {
      int tid = omp_get_thread_num();
      unsigned int rnum = R.num();
      // int lim = std::min(((tid+1)*rnum)/numt,rnum);

      // for(int r= tid*K ; r< (tid+1)*K -1; r+=1) { // Thread together share-loop through the intervals 
      for(int r=tid; r<R.num(); r+=numt) { // Thread together share-loop through the intervals 
         // std::cout<<r<<std::endl;
         int rcount = 0;
         for(int d=0; d<D.ndata; d++) // For each interval, thread loops through all of data and  
             if(D.data[d].value == r) // If the data item is in this interval 
                 D2.data[rangecount[r-1]+rcount++] = D.data[d]; // Copy it to the appropriate place in D2.
      }
   }

   return D2;
}
