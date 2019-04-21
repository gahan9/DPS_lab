#!/home/jarvis/.virtualenvs/ray/bin/python3
# -*- coding: utf-8 -*-
"""
Author: Gahan Saraiya
GiT: https://github.com/gahan9
StackOverflow: https://stackoverflow.com/users/story/7664524

Experiment of loop of n^3 complexity without Ray
"""

import time

def stress_function(num):
    return sum([i*j*k 
                for i in range(num) 
                for j in range(i) 
                for k in range(j)
                ])


if __name__ == "__main__":
    inp = int(input("Enter a number: "))
    start = time.time()
    result = [stress_function(inp) for _ in range(inp)]
    print(time.time() - start)