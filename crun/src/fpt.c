#include "fpt.h"
#include "scale.h"

double birth_rate(int n, int x, double e) {
    return (n-x)*(e+x);
}

double death_rate(int n, int x, double e) {
    return x*(e+n-x);
}

bool is_in_state(double X, double N, double dest) {
    double cur=X/N;
    double epsi=0.5/N;
    return fabs(cur-dest) < epsi;
}

void get_passage_times(long points, double max_time, int from, int n_agents, int mult, double to, double epsi_b, double epsi_d, double gamma, int rng_seed, double* output) {
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
    int initial_x=x;
    int initial_mult=out_mult;
    int initial_n=n_agents;
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
    long idx=0;
    double fpt=0;
    for(;idx<points;idx+=1) {
        fpt=clock;
        while(!is_in_state(x, n_agents, to) && (clock-fpt)<max_time) {
            last_x=x;
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
        output[idx]=clock-fpt;
        if(output[idx]>max_time) {
            output[idx]=max_time;
        }
        x=initial_x;
        out_mult=initial_mult;
        n_agents=initial_n;
        clock = 0; // comment this line if you want to study consecutive passage times
    }
    /* destroy GSL random number generator*/
    gsl_rng_free(rng);
}
