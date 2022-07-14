#include <math.h>
#include <stdbool.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

extern void get_passage_times(long points, double max_time, int from, int n_agents, int mult, double to, double epsi_b, double epsi_d, double gamma, int rng_seed, double* output);
