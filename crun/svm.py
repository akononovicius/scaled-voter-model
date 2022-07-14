import ctypes as c
import os as os
import gc

import numpy as np

___ctypes_local_dir = os.path.dirname(os.path.realpath(__file__)) + "/"
___lib_c = c.CDLL(___ctypes_local_dir + "libsvm.so")
___lib_c.get_time_series.argtypes = [
    c.c_long,  # points
    c.POINTER(c.c_double),  # times
    c.c_int,  # from
    c.c_int,  # n_agents
    c.c_int,  # mult
    c.c_double,  # epsi_b
    c.c_double,  # epsi_d
    c.c_double,  # gamma
    c.c_int,  # rng_seed
    c.POINTER(c.c_int),  # output
]
___lib_c.get_time_series.restype = None


def generate_series(
    times: np.ndarray,
    *,
    birth_rate: float = 1,
    death_rate: float = 1,
    gamma: float = 1,
    initial: int = 500,
    n_agents: int = 1000,
    mult: int = 1000,
    seed: int = -1
) -> np.ndarray:
    n_points = len(times)

    # auto-generate seed
    if seed < 0:
        np.random.seed()
        seed = np.random.randint(0, int(2**20))

    c_times = (c.c_double * n_points)(*times)
    data = (c.c_int * n_points)()
    ___lib_c.get_time_series(
        n_points,
        c_times,
        initial,
        n_agents,
        mult,
        birth_rate,
        death_rate,
        gamma,
        seed,
        data,
    )
    ret = np.array([d for d in data])
    del data
    gc.collect()

    return ret/(n_agents*mult)
