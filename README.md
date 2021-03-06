PRACTICAL_LIST
==============
---
Distibuted Parallel Systems
---
[Practical 1: Speeding up performance with openmp](practical1/doc/practical1.pdf)

---

[Practical 2: MPI setup and sample code](practical2/doc/practical2.pdf)
Setup MPI and execute sample code given in MPI src.

Write steps for MPI setup. List problem observed during setup and execution . Specify cause and solution of each problem. 

Code should have following  basic functions:

1. print Computer machine name and rank id for each process.

2. MPI time function to measure time taken by given fragment.

3. Communication function (send/receive, scatter, broadcast etc.)

4. Find command to set fix process per node.

---

[Practical 3: Comparing openmp schedules]()

Write a code to find out all prime factors of given number.  

Analyse the same using various openmp pragma method listed below:  

- `#pragma omp parallel for schedule(static)`  
- `#pragma omp parallel for schedule(static, 1)`  
- `#pragma omp parallel for schedule(dynamic, 4)`  
- `#pragma omp parallel for schedule(guided, 4)`  

---