# run file
gcc -o main.out main.c  # generates output file

time ./main.out

gcc -o main.out -pg main.c  # when executed main.out it will generate gmon.out for profiling

# execute code
./main.out  # will also generates gmon.out

# Profiling functions
gprof main.out gmon.out > profile_main.txt  # write execution profiling to text file


# Profiling every line
gcc -pg -fprofile-arcs main.c -ftest-coverage  # generates files with extension gcda, gcno, gmon.out

# generate file min.c.gcov covering profiling of all lines
gcov main.c

# one liner for above commands. Note: will overwrite existing a.out and gmon.out
gcc -pg main.c && ./a.out && gprof a.out gmon.out > profile.txt
