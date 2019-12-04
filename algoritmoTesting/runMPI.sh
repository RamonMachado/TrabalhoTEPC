#!/bin/bash  

n_cores="2"
echo "compilando"
mpicc mpi4k.c -o mpi4k -lm -O3
echo "Rodando primeira vez"
mpirun -np $n_cores mpi4k
echo "Rodando segunda vez"
mpirun -np $n_cores mpi4k
echo "Rodando terceira vez"
mpirun -np $n_cores mpi4k
echo "Rodando quarta vez"
mpirun -np $n_cores mpi4k
echo "Rodando quinta vez"
mpirun -np $n_cores mpi4k
echo compilando calculadora media
gcc -o calculadoraMedia calcularMedia.c -Wall
echo executando calculadora
./calculadoraMedia MPI_stats.txt

 

