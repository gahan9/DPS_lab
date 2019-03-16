mpicc main.c -o main && mpirun -np 15 --hosts master,node ./main
