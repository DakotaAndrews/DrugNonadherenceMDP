#include <iostream>
#include <vector>
#include "MDP.h"
using namespace std;


int main(){
    vector<double> V_0 = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}; // initial values and initial recommendations
    double epsilon = pow(10, -6); // error tolerance
    vector<double> V_1 = iteration(V_0); // second iteration
    print_vector(V_0);

    while (norm(V_0, V_1) >= epsilon){ // prints out and calculates next iteration until we are below error tolerance level
        vector<double> V_2 = iteration(V_1);
        V_0 = V_1;
        V_1 = V_2;
        print_vector(V_0);
    }
    vector<double> V_n = iteration(V_1);
    print_vector(V_n);
}