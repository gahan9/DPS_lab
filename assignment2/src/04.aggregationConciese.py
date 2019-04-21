# -*- coding: utf-8 -*-
"""
Author: Gahan Saraiya
GiT: https://github.com/gahan9
StackOverflow: https://stackoverflow.com/users/story/7664524

Speeding up aggregation
"""
import ray
import time
import cProfile

@ray.remote
def add(x, y):
    time.sleep(1)
    return x + y

if __name__ == "__main__":
    # Slow approach.
    values = [1, 2, 3, 4, 5, 6, 7, 8]
    while len(values) > 1:
        values = [add.remote(values[0], values[1])] + values[2:]
    result = ray.get(values[0])


    # Fast approach.
    values = [1, 2, 3, 4, 5, 6, 7, 8]
    while len(values) > 1:
        values = values[2:] + [add.remote(values[0], values[1])]
    result = ray.get(values[0])