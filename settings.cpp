using namespace std;

double D = 0.1; // dosage
double V = 1.0; // Volume of distribution
double F = 1.0; // Bioavailability fraction
double tau = 1.0; // time between doses
double t_half = 6.6; // half-life
double alpha = pow(2, -tau / t_half); // fractional amount of drug left after 1 'cycle'
double p = 0.8; // probability of remembering to take drug
double discount_factor = 0.2; // discount factor (value of future outcomes)
double C_perf = alpha * D * F  / (V * (1 - alpha)); // perfect patient drug concentration, C_perf(tau)
double C_perf_max = D * F  / (V * (1 - alpha)); // C_perf(0)