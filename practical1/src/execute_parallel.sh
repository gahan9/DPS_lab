# gcc -pg -fopenmp main.c -o vector_add_sequential
# time ./vector_add_sequential
# gprof vector_add_sequential gmon.out > vector_add_sequential.txt

# gcc -fopenmp main.c -o vector_add_parallel


# Sequential
gcc -pg -fopenmp main.c -o vector_add_sequential &&time ./vector_add_sequential


# Paralllel
gcc -pg -fopenmp vectorAddParallel.c -o vector_add_parallel && time ./vector_add_parallel