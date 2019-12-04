#!/bin/bash  

n_cores="8"
echo "compilando"
gcc -o algoritmoSequencial algoritmoSequencial.c -lm -O3
echo "Rodando primeira vez"
./algoritmoSequencial
echo "Rodando segunda vez"
./algoritmoSequencial
echo "Rodando terceira vez"
./algoritmoSequencial
echo "Rodando quarta vez"
./algoritmoSequencial
echo "Rodando quinta vez"
./algoritmoSequencial
echo compilando calculadora media
gcc -o calculadoraMedia calcularMedia.c -Wall
echo executando calculadora
./calculadoraMedia Sequencial_stats.txt

 

