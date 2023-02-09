# Exploration of the scaled voter model

In this repository you can find an implementation of the scaled voter model.
In this particular implementation the transition rates are power-law
functions of time. With this modification voter model behaves as if driven
by the scaled Brownian motion, instead of the usual Brownian motion. From
the perspective of anomalous diffusion (temporal evolution of the first two
moments) and first passage times scaled Brownian motion is equivalent to
the fractional Brownian motion.

The difference from most implementation of the voter model, this technically
differs in two regards:

1. Modified next reaction method is used (instead of the usual
   rejection-based methods or Gillespie method).
1. Simulation scales (number of agents is increased) when most agents occupy
   the same state (X/N approaches either 0 or 1).

Shell scripts contained in this repository were used to obtain data used to
produce figures from [1]. In the said paper you can find more details as
well as analytical approximations for the simulation results.

**Note:** Model itself was implemented in C, to properly run it you will
have first to `make` (compile) it. Makefile is in the `crun` directory.

## References

1. R. Kazakevičius, A. Kononovicius. *Anomalous diffusion and long-range
   memory in the scaled voter model*. Physical Review E **107**: 024106
   (2023). [doi:
   10.1103/PhysRevE.107.024106](https://doi.org/10.1103/PhysRevE.107.024106).
   [arXiv:2301.08088 [cond-mat.stat-mech]](https://arxiv.org/abs/2301.08088).
