from multiprocessing import Pool
import time
import multiprocessing

TOTAL_NUMBERS = 100


def f(x):
    return x * x


def foo():
    # start 4 worker processes
    with Pool(processes=4) as pool:
        start_time = time.time()
        # print "[0, 1, 4,..., 81]"
        print(pool.map(f, range(TOTAL_NUMBERS)))
        print("[method:MAP] Time Elapsed: {}".format(time.time() - start_time))
        # print same numbers in arbitrary order
        start_time = time.time()
        for i in pool.imap_unordered(f, range(TOTAL_NUMBERS)):
            print("[method:iMAP] res: {} Time Elapsed: {}".format(i, time.time() - start_time))


if __name__ == '__main__':
    # cProfile.run('foo()')
    f(10)
    NUM_WORKERS = multiprocessing.cpu_count()
    print('worker count: %d' % NUM_WORKERS)
    foo()

