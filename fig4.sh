#!/bin/sh

python sim_fpt.py "data/fig3a.csv" --max-time 30000 --n-points 10000 --gamma 0.75 --birth-rate 0.4 --death-rate 0.4 --x-0 5000 --n-agents 10000 --mult 1 --to 0.5779718474 --seed 11872
python sim_fpt.py "data/fig3b.csv" --max-time 3000  --n-points 10000 --gamma 0.75 --birth-rate 0.8 --death-rate 0.8 --x-0 5000 --n-agents 10000 --mult 1 --to 0.5779718474 --seed 15317
python sim_fpt.py "data/fig3c.csv" --max-time 1000  --n-points 10000 --gamma 1.0  --birth-rate 0.4 --death-rate 0.4 --x-0 5000 --n-agents 10000 --mult 1 --to 0.5779718474 --seed 26321
python sim_fpt.py "data/fig3d.csv" --max-time 300   --n-points 10000 --gamma 1.0  --birth-rate 0.8 --death-rate 0.8 --x-0 5000 --n-agents 10000 --mult 1 --to 0.5779718474 --seed 4907
python sim_fpt.py "data/fig3e.csv" --max-time 100   --n-points 10000 --gamma 1.5  --birth-rate 0.4 --death-rate 0.4 --x-0 5000 --n-agents 10000 --mult 1 --to 0.5779718474 --seed 12423
python sim_fpt.py "data/fig3f.csv" --max-time 100   --n-points 10000 --gamma 1.5  --birth-rate 0.8 --death-rate 0.8 --x-0 5000 --n-agents 10000 --mult 1 --to 0.5779718474 --seed 28948
