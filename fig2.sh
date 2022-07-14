#!/bin/sh

python sim_moments.py "data/fig2ab.csv" --gamma 0.5 --t-min 1e-14 --t-max 3 --x-0 300 --n-agents 1000 --mult 1000 --seed 1310
python sim_moments.py "data/fig2cd.csv" --gamma 1.0 --t-min 1e-9  --t-max 3 --x-0 300 --n-agents 1000 --mult 1000 --seed 14039
python sim_moments.py "data/fig2ef.csv" --gamma 2.0 --t-min 1e-6  --t-max 3 --x-0 300 --n-agents 1000 --mult 1000 --seed 24466
