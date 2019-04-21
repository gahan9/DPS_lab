#!/home/jarvis/.virtualenvs/ray/bin/python3
# -*- coding: utf-8 -*-
"""
Author: Gahan Saraiya
GiT: https://github.com/gahan9
StackOverflow: https://stackoverflow.com/users/story/7664524

using Actor classes
"""

import ray
import time 

@ray.remote
class Counter(object):
    def __init__(self):
        self.x = 0
    
    def inc(self):
        self.x += 1
    
    def get_value(self):
        return self.x

if __name__ == "__main__":
    ray.init()
    # Create an actor process.
    c = Counter.remote()

    # Check the actor's counter value.
    print(ray.get(c.get_value.remote()))  # 0

    # Increment the counter twice and check the value again.
    c.inc.remote()
    c.inc.remote()
    print(ray.get(c.get_value.remote())) # 2