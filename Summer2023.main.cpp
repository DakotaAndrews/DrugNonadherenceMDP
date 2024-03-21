#include <iostream>
#include <fstream>
#include <vector>
#include "MDP.h"
using namespace std;


int main(){ // writes out csv data to data.txt in the form: half-life,concentration
    ofstream fout("data.txt");
    int iterations = ceil((max_half_life - min_half_life) / dt);
    double t_half = min_half_life;
    for (int i = 0; i < iterations; i++){
        fout << t_half << "," << dosage_cutoff(t_half) << endl;
        t_half += dt;
    }
}
