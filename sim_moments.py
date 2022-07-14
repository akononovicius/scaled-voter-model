import numpy as np
import typer

from crun.svm import generate_series


def main(
    out_filename: str,
    *,
    birth_rate: float = 3,
    death_rate: float = 3,
    gamma: float = 1,
    X_0: int = 100,
    n_agents: int = 10000000,
    mult: int = 1,
    t_min: float = 1e-8,
    t_max: float = 1,
    n_points: int = 30,
    n_simulations: int = 1000,
    seed: int = -1,
):
    # auto-generate seed
    if seed < 0:
        np.random.seed()
        seed = np.random.randint(0, int(2**20))

    x_0 = X_0 / n_agents
    times = np.logspace(np.log10(t_min), np.log10(t_max), n_points)

    data = np.array(
        [
            generate_series(
                times,
                birth_rate=birth_rate,
                death_rate=death_rate,
                gamma=gamma,
                initial=X_0,
                n_agents=n_agents,
                mult=mult,
                seed=seed + idx,
            )
            for idx in np.arange(n_simulations)
        ]
    )

    data_mean = np.mean(data, axis=0)
    th_mean = theory_mean(times, x_0, birth_rate, death_rate, gamma)
    data_var = np.var(data, axis=0)
    th_var = theory_var(times, x_0, birth_rate, death_rate, gamma)

    np.savetxt(
        out_filename,
        np.log10(np.array([times, data_mean, th_mean, data_var, th_var]).T),
        fmt="%.4f",
        delimiter=",",
    )


def theory_mean(times, x_0, birth_rate, death_rate, gamma):
    a = birth_rate + death_rate
    b = birth_rate / a
    exp = np.exp(-a * (times**gamma))
    return x_0 * exp + b * (1 - exp)


def theory_var(times, x_0, birth_rate, death_rate, gamma):
    a = birth_rate + death_rate
    b = birth_rate / a
    exp = np.exp(-a * (times**gamma))
    return 2 * x_0 / a * exp * (1 - exp) + (b / a) * ((1 - exp) ** 2)


if __name__ == "__main__":
    typer.run(main)
