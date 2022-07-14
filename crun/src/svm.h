#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

extern void get_time_series(long points, double* times, int from, int n_agents, int mult, double epsi_b, double epsi_d, double gamma, int rng_seed, int* output);
