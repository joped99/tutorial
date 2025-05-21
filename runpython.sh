#!/bin/bash --login

#activating conda
[[ -f ~/.bashrc ]] && source ~/.bashrc

#activating standard environment
conda activate pystd

# running python file
python tutorial.py