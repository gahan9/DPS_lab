gcc -pg -fopenmp main.c -o vector_add_sequential
time ./vector_add_sequential
gprof vector_add_sequential gmon.out > vector_add_sequential.txt

gcc -fopenmp main.c -o vector_add_parallel
