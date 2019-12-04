#!/bin/bash  

n_cores="2"
echo "compilando"
mpicc algoritmoMPI.c -o algoritmoMPI -lm -O3
echo "Rodando primeira vez"
mpirun -np $n_cores algoritmoMPI
echo "Rodando segunda vez"
mpirun -np $n_cores algoritmoMPI
echo "Rodando terceira vez"
mpirun -np $n_cores algoritmoMPI
echo "Rodando quarta vez"
mpirun -np $n_cores algoritmoMPI
echo "Rodando quinta vez"
mpirun -np $n_cores algoritmoMPI
echo compilando calculadora media
gcc -o calculadoraMedia calcularMedia.c -Wall
echo executando calculadora
./calculadoraMedia MPI_stats.txt

 

