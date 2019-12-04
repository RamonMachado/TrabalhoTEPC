#!/bin/bash  

echo "Compilando seq pthread mpi 16k"
gcc -o main16k main16k.c -lm -lpthread -fopenmp -O3
echo "Rodando primeira vez"
./main16k
echo "Rodando segunda vez"
./main16k
echo "Rodando terceira vez"
./main16k
echo "Rodando quarta vez"
./main16k
echo "Rodando quinta vez"
./main16k
echo compilando calculadora media
gcc -o calculadoraMedia calcularMedia.c -Wall
echo executando calculadora
./calculadoraMedia Sequencial_stats_wallpaper16k.txt
./calculadoraMedia Pthread_stats_wallpaper16k_2thread.txt
./calculadoraMedia OpenMP_stats_wallpaper16k_2thread.txt
./calculadoraMedia Pthread_stats_wallpaper16k_4thread.txt
./calculadoraMedia OpenMP_stats_wallpaper16k_4thread.txt
./calculadoraMedia Pthread_stats_wallpaper16k_8thread.txt
./calculadoraMedia OpenMP_stats_wallpaper16k_8thread.txt