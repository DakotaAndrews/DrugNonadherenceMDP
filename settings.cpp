using namespace std;

int num_of_states = 100;
double state_width = 1.1 / (num_of_states - 1);
double min_half_life = 0.083;
double max_half_life = 7.0;
double dt = 0.001;
double D = 0.1; // dosage
double V = 1.0; // Volume of distribution
double F = 1.0; // Bioavailability fraction
double tau = 1.0; // time between doses
double p = 0.8; // probability of remembering to take drug
double discount_factor = 0.2; // discount factor (value of future outcomes)
