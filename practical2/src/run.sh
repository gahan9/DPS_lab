read processes

mpicc main.c -o main

mpirun -np $processes --hosts master,node ./main > output.txt
