file="code.c"
# echo "Enter file name/path to execute" | lolcat
# read file
echo "Enter number of processes to be execute" | lolcat
read processes
echo "Enter lucky number (termination number)" | lolcat
read lucky_number
mpicc $file -o $file'.out'
echo "running " $file "on " $processes "processes" | lolcat
mpirun -np $processes --hosts master ./$file'.out' $lucky_number
