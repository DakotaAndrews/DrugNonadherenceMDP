#include <iostream>
#include <fstream>
#include <vector>
#include "MDP.h"
using namespace std;


int main(){ // writes out csv data to data.txt in the form: half-life,concentration
    for (double i = 0; i <= 100; i+= 1){
        int k = floor(i);
        p = i / 100;
        string file_name = "Data/data" + to_string(k) + ".txt";
        ofstream fout(file_name);
        int iterations = ceil((max_half_life - min_half_life) / dt);
        double t_half = min_half_life;
        for (int i = 0; i < iterations; i++){
            fout << t_half << "," << dosage_cutoff(t_half) << endl;
            t_half += dt;
        }
    }
}