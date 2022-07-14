#include "svm.h"
#include "scale.h"

double birth_rate(int n, int x, double e) {
    return (n-x)*(e+x);
}

double death_rate(int n, int x, double e) {
    return x*(e+n-x);
}

void get_time_series(long points, double* times, int from, int n_agents, int mult, double epsi_b, double epsi_d, double gamma, int rng_seed, int* output) {
    /* initialize GSL random number generator*/
    gsl_rng_env_setup();
    gsl_rng* rng=gsl_rng_alloc(gsl_rng_taus);
    long seed=(long)rng_seed;
    gsl_rng_set(rng, seed);
    /* initial global state */
    double clock=0;
    double tau=0;
    double rel_tau=0;
    int x=from;
    int last_x=x;
    int out_mult=mult;
    int last_mult=out_mult;
    /* initial birth process state */
    double birth_tau=0;
    double birth_rate_cur=0;
    double clock_birth_cur=0;
    double clock_birth_next=gsl_ran_exponential(rng, 1.0);
    /* initial death process state */
    double death_tau=0;
    double death_rate_cur=0;
    double clock_death_cur=0;
    double clock_death_next=gsl_ran_exponential(rng, 1.0);
    /* generate event series */
    long idt=0;
    for(;idt<points;idt+=1) {
        while(clock<times[idt]) {
            last_x=x;
            last_mult=out_mult;
            // simulation step according to modified next reaction method
            birth_rate_cur=birth_rate(n_agents, x, epsi_b);
            death_rate_cur=death_rate(n_agents, x, epsi_d);

            birth_tau=INFINITY;
            if(birth_rate_cur>0) {
                birth_tau=(clock_birth_next-clock_birth_cur)/birth_rate_cur;
                if(clock>0) {
                    birth_tau=pow(pow(clock, gamma)+birth_tau, 1.0/gamma) - clock;
                } else {
                    birth_tau=pow(birth_tau, 1.0/gamma);
                }
            }
            death_tau=INFINITY;
            if(death_rate_cur>0) {
                death_tau=(clock_death_next-clock_death_cur)/death_rate_cur;
                if(clock>0) {
                    death_tau=pow(pow(clock, gamma)+death_tau, 1.0/gamma) - clock;
                } else {
                    death_tau=pow(death_tau, 1.0/gamma);
                }
            }

            tau=0;
            if(birth_tau<death_tau) { // birth occurs first
                tau=birth_tau;
                rel_tau=pow(clock+tau, gamma)-pow(clock, gamma);
                x=x+1;
                clock_birth_cur=clock_birth_next;
                clock_death_cur=clock_death_cur+death_rate_cur*rel_tau;
                clock_birth_next=clock_birth_next+gsl_ran_exponential(rng, 1.0);
            } else { // death occurs first
                tau=death_tau;
                rel_tau=pow(clock+tau, gamma)-pow(clock, gamma);
                x=x-1;
                clock_birth_cur=clock_birth_cur+birth_rate_cur*rel_tau;
                clock_death_cur=clock_death_next;
                clock_death_next=clock_death_next+gsl_ran_exponential(rng, 1.0);
            }
            clock=clock+tau;
            //= end simulation step

            scale_swich(last_x, &x, &n_agents, &out_mult);
        }
        output[idt]=last_x*last_mult;
    }
    /* destroy GSL random number generator*/
    gsl_rng_free(rng);
}
