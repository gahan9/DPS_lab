import time

# This is a generic wrapper for any driver function you want to time
def time_this(f):
    """Timing any fuction f
    Usage example:
    @time_this  # Added decorator
    def ex1():
        list1 = []
        for i in range(5):
            list1.append(ray.get(func.remote()))
    """
    def timed_wrapper(*args, **kw):
        start_time = time.time()
        result = f(*args, **kw)
        end_time = time.time()

        # Time taken = end_time - start_time
        print('| func:%r args:[%r, %r] took: %2.4f seconds |' % \
              (f.__name__, args, kw, end_time - start_time))
        return result
    return timed_wrapper
