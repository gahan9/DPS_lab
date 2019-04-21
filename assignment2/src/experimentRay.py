#!/home/jarvis/.virtualenvs/ray/bin/python3
# -*- coding: utf-8 -*-
"""
Author: Gahan Saraiya
GiT: https://github.com/gahan9
StackOverflow: https://stackoverflow.com/users/story/7664524

Experiment of loop of n^3 complexity with Ray
"""
import time
import ray

@ray.remote
def stress_function(num):
    # Example of loop O(n^3)
    return sum([i*j*k 
                for i in range(num) 
                for j in range(i) 
                for k in range(j)
    ])

if __name__ == "__main__":
    # Initialize ray
    ray.init()
    # ray.init(redis_address="0.0.0.0:6667")

    inp = int(input("Enter a number: "))
    start = time.time()
    # Remote function is invoked by .remote keyword
    result = ray.get([stress_function.remote(inp) for _ in range(inp)])
    print(time.time() - start)
