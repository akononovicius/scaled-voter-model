#!/bin/sh

python sim_fpt.py "data/fig3a.csv" --max-time 100 --n-points 100000 --gamma 0.5 --x-0 100 --n-agents 100000 --mult 1000 --seed 26538
python sim_fpt.py "data/fig3b.csv" --max-time 100 --n-points 100000 --gamma 0.5 --x-0 100 --n-agents 10000 --mult 10000 --seed 15078
python sim_fpt.py "data/fig3c.csv" --max-time 100 --n-points 100000 --gamma 1.0 --x-0 100 --n-agents 100000 --mult 1000 --seed 11651
python sim_fpt.py "data/fig3d.csv" --max-time 100 --n-points 100000 --gamma 1.0 --x-0 100 --n-agents 10000 --mult 10000 --seed 4108
python sim_fpt.py "data/fig3e.csv" --max-time 100 --n-points 100000 --gamma 2.0 --x-0 100 --n-agents 100000 --mult 1000 --seed 24315
python sim_fpt.py "data/fig3f.csv" --max-time 100 --n-points 100000 --gamma 2.0 --x-0 100 --n-agents 10000 --mult 10000 --seed 3014
