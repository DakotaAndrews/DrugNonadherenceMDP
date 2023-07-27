#include <vector>
#include <cmath>
#include "settings.cpp"
using namespace std;



double reward(double con, double action){ // reward function for a given concentration and number of doses
    return (con + action * D) * alpha / C_perf;
}

double new_state(double con, double action){ // returns new state for a given concentration and number of doses
    double new_con = alpha * (con + D * action);
    new_con = 10 * new_con / C_perf_max;
    new_con = ceil(new_con);
    if (new_con > 11){
        new_con = 11.0;
    }
    new_con = C_perf_max * new_con / 10;
    return new_con;
}

void print_vector(vector<double> vec){ // prints out the vector with the tuple (concentration, score, action)
    int n = vec.size();
    n = n / 2;
    for (int i = 0; i < n - 1; i ++){
        cout << "(" << 0.1 * C_perf_max * i << ", " << vec[i] << ", " << vec[i + 12] << "), ";
    }
    cout << "(" << 1.1 * C_perf_max << ", " << vec[11] << ", " << vec[23] << ")" << endl;
    return;
}


double norm(vector<double> X, vector<double> Y){ // Euclidean norm of 2 vectors of equal size
    int n = X.size();
    double total = 0.0;
    for (int i=0; i < n; i++){
        total += pow(X[i] - Y[i], 2);
    }
    return sqrt(total);
}

vector<double> iteration(vector<double> prev_iteration){ // calculates the score and recommended action given a vector of previous scores
    vector<double> curr_iteration(prev_iteration.size());
    for (int state = 0; state <= 11; state ++){
        double prev_con = state * C_perf_max / 10.0;
        vector<double> outcomes(2);
        for (int action = 1; action < 3; action ++){
            double new_state_rem = new_state(prev_con, action);
            double new_state_for = new_state(prev_con, 0.0);
            double score = p * (reward(prev_con, action) + discount_factor * prev_iteration[new_state_rem]) + 
                           (1 - p) * (reward(prev_con, 0.0) + discount_factor * prev_iteration[new_state_for]);
            outcomes[action - 1] = score;
        }
        curr_iteration[state] = outcomes[0];
        curr_iteration[state + 12] = 1.0;
        if (abs(1 - outcomes[0]) > abs(1 - outcomes[1])){
            curr_iteration[state] = outcomes[1];
            curr_iteration[state + 12] = 2.0;
        }
    }
    return curr_iteration;
}