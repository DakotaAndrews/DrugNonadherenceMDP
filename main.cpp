#include <iostream>
#include <fstream>
#include <vector>
#include "MDP.h"
using namespace std;


int main(){
    ofstream fout("data.txt");
    double min_half_life = 0.083;
    double max_half_life = 10.0;
    double dt = 0.02;
    int iterations = ceil((max_half_life - min_half_life) / dt);
    double t_half = min_half_life;
    for (int i = 0; i < iterations; i++){
        fout << t_half << "," << dosage_cutoff(t_half) << endl;
        t_half += dt;
    }
}