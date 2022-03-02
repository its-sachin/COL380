#include <string>
#include <mpi.h>
#include <assert.h>
#include "randomizer.hpp"
#include<bits/stdc++.h>


bool order(std::pair<int,int> &a, std::pair<int,int> &b)
{
    if(a.second == b.second)
        return a.first < b.first;
    return a.second > b.second;
}

int lTob(int n){
    int words[4];
    for(int i = 0; i < 4; i++){
        words[i] = n & 0xff;
        n >>= 8;
    }

    int ans = 0;
    for(int i = 0; i < 4; i++){
        ans <<= 8;
        ans |= words[i];
    }
    return ans;
}

void writeIt(int n, std::fstream &out){
    int conv = lTob(n);
    // std::cout<<"func : " <<conv<<std::endl;
    out.write((char*)&conv, 4);
}


int main(int argc, char* argv[]){
    assert(argc > 8);
    std::string graph_file = argv[1];
    int num_nodes = std::stoi(argv[2]);
    int num_edges = std::stoi(argv[3]);
    float restart_prob = std::stof(argv[4]);
    int num_steps = std::stoi(argv[5]);
    int num_walks = std::stoi(argv[6]);
    int num_rec = std::stoi(argv[7]);
    int seed = std::stoi(argv[8]);
    
    //Only one randomizer object should be used per MPI rank, and all should have same seed
    Randomizer random_generator(seed, num_nodes, restart_prob);
    int rank, size;

    //Starting MPI pipeline
    MPI_Init(NULL, NULL);
    
    // Extracting Rank and Processor Count
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    std::vector<int> *graph = new std::vector<int>[num_nodes];
    for(int i = 0; i < num_nodes; i++){
        graph[i] = std::vector<int>();
    }

    std::fstream fs(graph_file, std::ios::in | std::ios::binary);
    for (int i = 0; i < num_edges; i++) {
        unsigned char uc[4];
        unsigned char vc[4];
        fs.read((char *)&uc, 4);
        fs.read((char *)&vc, 4);
        
        int u = (int)uc[3] | (int)uc[2]<<8 | (int)uc[1]<<16 | (int)uc[0]<<24;
        int v = (int)vc[3] | (int)vc[2]<<8 | (int)vc[1]<<16 | (int)vc[0]<<24;

        graph[u].push_back(v);
    }

    int** scores = new int*[num_nodes];
    for(int src = rank; src < num_nodes; src +=size){
        scores[src] = new int[num_nodes];
        for (int i =0; i<num_nodes; i++){
            scores[src][i] = 0;
        }
        for(int i = 0; i < graph[src].size(); i++){
            int v = graph[src][i];
            for(int walk = 0; walk < num_walks; walk++){
                int curr = v;
                int step = 0;
                while(step < num_steps){
                    if(graph[curr].size() == 0){
                        curr = v;
                    }
                    else {
                        int prob = random_generator.get_random_value(src);
                        if(prob < 0){
                            curr = v;
                        }
                        else{
                            int next = prob%graph[curr].size();
                            curr = graph[curr][next];
                            scores[src][curr] += 1;
                        }
                    }
                    step++;
                }
            }
        }
        scores[src][src] = -1;
        for(int i = 0; i < graph[src].size(); i++){
            int v = graph[src][i];
            scores[src][v] = -1;
        }
    }

    std::cout << rank << " : work done"<< std::endl;
    std::string name = "_" + std::to_string(size) + "_"+ std::to_string(num_nodes) + "_" + std::to_string(num_edges) + "_" + std::to_string(num_steps) + "_" + std::to_string(num_walks) + "_" + std::to_string(num_rec) + "_" + std::to_string(seed);

    std::fstream outfile("out" + name + ".dat", std::ios::out | std::ios::binary);

    // if(rank > 0){
    //     int flag = 0;
    //     MPI_Status status;
    //     MPI_Recv(&flag, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);

    //     while(flag == 0);
        
    //     std::cout << "rank " << rank << " received" << std::endl;
        
    // }

    for(int src = rank; src < num_nodes; src += size){
        
        outfile.seekg(4*src*(2*num_rec + 1), std::ios::beg);
        writeIt(graph[src].size(), outfile);

        std::vector<std::pair<int,int>> recs;
        for(int i =0; i<num_nodes; i++){
            if(scores[src][i] > 0){
                recs.push_back({i, scores[src][i]});
            }
        }

        std::sort(recs.begin(), recs.end(), order);
        for(int i = 0; i < num_rec; i++){
            if(i < recs.size()){
                writeIt(recs[i].first, outfile);
                writeIt(recs[i].second, outfile);
            }
            else{
                outfile << "NULL"<<"NULL";
            }
        }
    }

    std::cout << rank << " : done" << std::endl;

    // if(rank < size - 1){
    //     int flag = 1;
    //     MPI_Send(&flag, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
    // }
    
    MPI_Finalize();
}