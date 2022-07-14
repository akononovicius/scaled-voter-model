import numpy as np
import typer

from crun.fpt import get_passage_times
from stats.pdf import MakeLogPdf


def main(
    out_filename: str,
    *,
    birth_rate: float = 0.5,
    death_rate: float = 0.5,
    gamma: float = 1,
    X_0: int = 100,
    n_agents: int = 1000000,
    mult: int = 100,
    to: float = 0,
    n_points: int = 10000,
    max_time: float = 1e3,
    seed: int = -1,
):
    # auto-generate seed
    if seed < 0:
        np.random.seed()
        seed = np.random.randint(0, int(2**20))

    data = get_passage_times(
        to,
        max_time=max_time,
        n_points=n_points,
        birth_rate=birth_rate,
        death_rate=death_rate,
        gamma=gamma,
        initial=X_0,
        n_agents=n_agents,
        mult=mult,
        seed=seed,
    )
    pdf = MakeLogPdf(data)

    np.savetxt(out_filename, np.log10(pdf), fmt="%.4f", delimiter=",")


if __name__ == "__main__":
    typer.run(main)
