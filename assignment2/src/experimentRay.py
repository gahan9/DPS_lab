#!/home/jarvis/.virtualenvs/ray/bin/python3
# -*- coding: utf-8 -*-
"""
Author: Gahan Saraiya
GiT: https://github.com/gahan9
StackOverflow: https://stackoverflow.com/users/story/7664524

Experiment of loop of n^2 complexity with Ray
"""
import time
import ray


@ray.remote
def stress_function(num):
    # Example of loop O(n^2)
    return sum([i * j * 1
                for i in range(num)
                for j in range(num)
                for k in range(1)
                ])


if __name__ == "__main__":
    # Initialize ray
    ray.init()
    # ray.init(redis_address="0.0.0.0:6667")
    TEST_LIS = [100, 200, 300, 500, 700, 1000]
    for t in TEST_LIS:
        start = time.time()
        # Remote function is invoked by .remote keyword
        result = ray.get([stress_function.remote(t) for _ in range(t)])
        print("Time Elapsed for Input Size {}: {:.4f}".format(t, time.time() - start))
