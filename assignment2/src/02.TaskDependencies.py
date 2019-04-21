#!/home/jarvis/.virtualenvs/ray/bin/python3
# -*- coding: utf-8 -*-
"""
Author: Gahan Saraiya
GiT: https://github.com/gahan9
StackOverflow: https://stackoverflow.com/users/story/7664524

Task Dependency Example
"""
import numpy as np
import ray

@ray.remote
def create_matrix(size):
    return np.random.normal(size=size)

@ray.remote
def multiply_matrices(x, y):
    return np.dot(x, y)

if __name__ == "__main__":
    ray.init()
    x_id = create_matrix.remote([1000, 1000])
    y_id = create_matrix.remote([1000, 1000])
    z_id = multiply_matrices.remote(x_id, y_id)

    # Get the results.
    z = ray.get(z_id)