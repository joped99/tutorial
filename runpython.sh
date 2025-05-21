#!/bin/bash --login

[[ -f ~/.bashrc ]] && source ~/.bashrc

conda activate pystd

# running python file
python tutorial.py