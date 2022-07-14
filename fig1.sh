#!/bin/sh

python sim_moments.py "data/fig1ab.csv" --gamma 0.5 --t-min 1e-14 --t-max 3 --seed 29639
python sim_moments.py "data/fig1cd.csv" --gamma 1.0 --t-min 1e-9  --t-max 3 --seed 15280
python sim_moments.py "data/fig1ef.csv" --gamma 2.0 --t-min 1e-6  --t-max 3 --seed 19163
