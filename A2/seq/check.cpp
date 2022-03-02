#include <iostream>
#include <mpi.h>
#include<bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
    //Starting MPI pipeline
    MPI_Init(NULL,NULL);
    int rank, size;
    
    // Extracting Rank and Processor Count
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Open a new file for input/output operations
    fstream myFile("test.txt", ios::in | ios::out | ios::trunc);

    // 123456

    myFile.seekg(rank*2, ios::beg);
    myFile << "lo";
    


    MPI_Finalize();
}
