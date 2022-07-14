#include <math.h>
#include <stdbool.h>

extern void scale_up(int last_x, int* x, int* n_agents, int* out_mult, bool* changed);
extern void scale_down(int last_x, int* x, int* n_agents, int* out_mult, bool* changed);
extern void scale_swich(int last_x, int* x, int* n_agents, int* out_mult);
