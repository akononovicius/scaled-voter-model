import ctypes as c
import os as os
import gc

import numpy as np

___ctypes_local_dir = os.path.dirname(os.path.realpath(__file__)) + "/"
___lib_c = c.CDLL(___ctypes_local_dir + "libfpt.so")
___lib_c.get_passage_times.argtypes = [
    c.c_long,  # points
    c.c_double,  # max_time
    c.c_int,  # from
    c.c_int,  # n_agents
    c.c_int,  # mult
    c.c_double,  # to
    c.c_double,  # epsi_b
    c.c_double,  # epsi_d
    c.c_double,  # gamma
    c.c_int,  # rng_seed
    c.POINTER(c.c_double),  # output
]
___lib_c.get_passage_times.restype = None


def get_passage_times(
    to,
    *,
    n_points: int = 10000,
    max_time: float = 1e3,
    birth_rate: float = 0.5,
    death_rate: float = 0.5,
    gamma: float = 1,
    initial: int = 500,
    n_agents: int = 1000,
    mult: int = 1000,
    seed: int = -1
) -> np.ndarray:
    # auto-generate seed
    if seed < 0:
        np.random.seed()
        seed = np.random.randint(0, int(2**20))

    data = (c.c_double * n_points)()
    ___lib_c.get_passage_times(
        n_points,
        max_time,
        initial,
        n_agents,
        mult,
        to,
        birth_rate,
        death_rate,
        gamma,
        seed,
        data,
    )
    ret = np.array([d for d in data])
    del data
    gc.collect()

    return ret
