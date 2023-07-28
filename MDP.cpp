#include <vector>
#include <cmath>
#include "settings.cpp"
using namespace std;



double reward(double con, double action, double alpha, double C_perf){ // reward function for a given concentration and number of doses
    return (con + action * D) * alpha / C_perf;
}

double new_state(double con, double action, double alpha, double C_perf_max){ // returns new state for a given concentration and number of doses
    double new_con = alpha * (con + D * action);
    new_con = new_con / (C_perf_max * state_width);
    new_con = ceil(new_con);
    if (new_con > num_of_states - 1){
        new_con = (double) num_of_states;
    }
    new_con = C_perf_max * new_con * state_width;
    return new_con;
}

void print_vector(vector<double> vec, double C_perf_max){ // prints out the vector with the tuple (concentration, score, action)
    int n = vec.size();
    n = n / 2;
    for (int i = 0; i < n - 1; i ++){
        cout << "(" << C_perf_max * i * state_width << ", " << vec[i] << ", " << vec[i + num_of_states] << "), ";
    }
    cout << "(" << 1.1 * C_perf_max << ", " << vec[num_of_states - 1] << ", " << vec[2 * num_of_states - 1] << ")" << endl;
    return;
}


double norm(vector<double> X, vector<double> Y){ // Euclidean norm of 2 vectors of equal size
    double total = 0.0;
    for (int i=0; i < num_of_states; i++){
        total += pow(X[i] - Y[i], 2);
    }
    return sqrt(total);
}

vector<double> iteration(vector<double> prev_iteration, double t_half, double alpha, double C_perf_max){ // calculates the score and recommended action given a vector of previous scores
    double C_perf = alpha * D * F  / (V * (1 - alpha)); // perfect patient drug concentration, C_perf(tau)
    vector<double> curr_iteration(prev_iteration.size());
    for (int state = 0; state < num_of_states; state ++){
        double prev_con = state * C_perf_max * state_width;
        vector<double> outcomes(2);
        for (int action = 1; action < 3; action ++){
            double new_state_rem = new_state(prev_con, action, alpha, C_perf_max);
            double new_state_for = new_state(prev_con, 0.0, alpha, C_perf_max);
            double score = p * (reward(prev_con, action, alpha, C_perf) + discount_factor * prev_iteration[new_state_rem]) + 
                           (1 - p) * (reward(prev_con, 0.0, alpha, C_perf) + discount_factor * prev_iteration[new_state_for]);
            outcomes[action - 1] = score;
        }
        curr_iteration[state] = outcomes[0];
        curr_iteration[state + num_of_states] = 1.0;
        if (abs(1 - outcomes[0]) > abs(1 - outcomes[1])){
            curr_iteration[state] = outcomes[1];
            curr_iteration[state + num_of_states] = 2.0;
        }
    }
    return curr_iteration;
}

double dosage_cutoff(double t_half){ // calculates the cutoff for where the MDP recommends 1 or 2 doses; averages the concentrations of largest concentration that recommends 2 and smallest concentration that recommends 1 dose
    double alpha = pow(2, -tau / t_half); // fractional amount of drug left after 1 'cycle'
    double C_perf_max = D * F  / (V * (1 - alpha)); // C_perf(0)
    vector<double> V_0(2 * num_of_states);
    for (int i = 0; i < num_of_states; i++){
        V_0[i] = 0.5;
        V_0[i + num_of_states] = 1.0;
    }
    double epsilon = pow(10, -6); // error tolerance
    vector<double> V_1 = iteration(V_0, t_half, alpha, C_perf_max); // second iteration
    bool too_many_iterations = false;
    int iterations = 0;
    while (norm(V_0, V_1) >= epsilon && !too_many_iterations){ // prints out and calculates next iteration until we are below error tolerance level
        vector<double> V_2 = iteration(V_1, t_half, alpha, C_perf_max);
        V_0 = V_1;
        V_1 = V_2;
        iterations += 1;
        if (iterations > 100){too_many_iterations = true;}
    }
    vector<double> V_n = iteration(V_1, t_half, alpha, C_perf_max);
    for (double i = num_of_states; i < 2 * num_of_states; i++){
        if (V_n[i] == 1.0){
            if (i == num_of_states){
                return 0.0;
            }
            if (i == 2 * num_of_states - 1){
                return 1.1 * C_perf_max;
            }
            return C_perf_max * state_width * (i - num_of_states - 0.5);
        }
    }
    return -1.0;
}