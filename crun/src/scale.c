#include "scale.h"

#define MIN_AGENTS 1000
#define SWITCH_UP 30
#define SWITCH_DOWN 310
#define SCALE_FACTOR 10

void scale_up(int last_x, int* x, int* n_agents, int* out_mult, bool* changed) {
    if(*changed) {
        return ;
    }
    int ALT_SWITCH=*n_agents-SWITCH_UP;
    if(!(*x==SWITCH_UP || *x==ALT_SWITCH)) {
        return ;
    }
    if(*out_mult==1) {
        return ;
    }
    if(!(SWITCH_UP<last_x && last_x<ALT_SWITCH)) {
        return ;
    }
    *changed=true;
    *x=(*x)*SCALE_FACTOR;
    *out_mult=(*out_mult)/SCALE_FACTOR;
    *n_agents=(*n_agents)*SCALE_FACTOR;
}

void scale_down(int last_x, int* x, int* n_agents, int* out_mult, bool* changed) {
    if(*changed) {
        return ;
    }
    int ALT_SWITCH=*n_agents-SWITCH_DOWN;
    if(!(*x==SWITCH_DOWN || *x==ALT_SWITCH)) {
        return ;
    }
    if(!(*n_agents>MIN_AGENTS)) {
        return ;
    }
    if(!(last_x<SWITCH_DOWN || ALT_SWITCH<last_x)) {
        return ;
    }
    *changed=true;
    *x=(*x)/SCALE_FACTOR;
    *out_mult=(*out_mult)*SCALE_FACTOR;
    *n_agents=(*n_agents)/SCALE_FACTOR;
}

void scale_swich(int last_x, int* x, int* n_agents, int* out_mult) {
    bool changed=false;
    scale_up(last_x, x, n_agents, out_mult, &changed);
    scale_down(last_x, x, n_agents, out_mult, &changed);
}
