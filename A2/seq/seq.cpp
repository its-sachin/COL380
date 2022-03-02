#include<bits/stdc++.h>

using namespace std;


bool order(pair<int,int> &a, pair<int,int> &b)
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

void writeIt(pair<int,int> p, ofstream &out){

    pair<int,int> p1 = {lTob(p.first), lTob(p.second)};
    out.write((char*)&p1.first, 4);
    out.write((char*)&p1.second, 4);
}

void writeIt(pair<string,string> p, ofstream &out){

    out.write((char*)&p.first, 4);
    out.write((char*)&p.second, 4);
}

int read(fstream &fss){
    unsigned char vc[4];
    fss.read((char *)&vc, 4);
    
    return (int)vc[3] | (int)vc[2]<<8 | (int)vc[1]<<16 | (int)vc[0]<<24;
}


int main(int argc, char const *argv[])
{
    assert(argc > 8);
    std::string graph_file = argv[1];
    int num_nodes = std::stoi(argv[2]);
    int num_edges = std::stoi(argv[3]);
    float restart_prob = std::stof(argv[4]);
    int num_steps = std::stoi(argv[5]);
    int num_walks = std::stoi(argv[6]);
    int num_rec = std::stoi(argv[7]);
    int seed = std::stoi(argv[8]);

    srand(seed);

    vector<int> graph[num_nodes];

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

    unordered_map<int,int> scores[num_nodes];
    for(int src = 0; src < num_nodes; src ++){
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
                        int prob = rand()%100;
                        if(prob <= restart_prob*100){
                            curr = v;
                        }
                        else{
                            int next = rand()%graph[curr].size();
                            curr = graph[curr][next];
                            if(scores[src].find(curr) == scores[src].end()){
                                scores[src][curr] = 1;
                            }
                            else{
                                scores[src][curr] += 1;
                            }
                        }
                    }
                    step++;
                }
            }
        }
        if(scores[src].find(src) != scores[src].end()){
            scores[src][src] = -1;
        }
        for(int i = 0; i < graph[src].size(); i++){
            int v = graph[src][i];
            if(scores[src].find(v) != scores[src].end()){
                scores[src][v] = -1;
            }
        }
    }

    ofstream outfile("out.dat", ios::out | ios::binary);

    for(int src = 0; src < num_nodes; src ++){

        int size = graph[src].size();
        writeIt({src, size}, outfile);

        vector<pair<int,int>> recs;
        for(auto it = scores[src].begin(); it != scores[src].end(); it++){
            if(it->second > 0){
                recs.push_back(make_pair(it->first, it->second));
            }
        }
        sort(recs.begin(), recs.end(), order);

        for(int i = 0; i < num_rec; i++){
            if(i < recs.size()){
                writeIt({recs[i].first, recs[i].second}, outfile);
            }
            else{
                outfile << "NULLNULL";
            }
        }
    }


    // std::fstream fs1(argv[1], std::ios::in | std::ios::binary);
    // std::fstream fs2(argv[2], std::ios::in | std::ios::binary);

    // cout << lTob(0) << endl;

    // int cols = 41;
    // int rows = 8717;
    // for (int i = 0; i < rows; i++) {
    //     bool error = false;
    //     for (int j = 0; j < cols; j++) {
    //         int u = read(fs1);
    //         int v = read(fs2);
    //         cout << u << " " << v << endl;
    //         if(v != u){
    //             cout << "Error at " << i+1 << "."<<j+1<< endl;
    //             error = true;
    //             break;
    //         }
    //     }
    //     if(error){
    //         break;
    //     }
    //     cout<<endl;
    // }
    
    return 0;
}