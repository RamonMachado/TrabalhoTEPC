#!/bin/bash  

echo "Compilando seq pthread mpi 8k"
gcc -o main8k main8k.c -lm -lpthread -fopenmp -O3
echo "Rodando primeira vez"
./main8k
echo "Rodando segunda vez"
./main8k
echo "Rodando terceira vez"
./main8k
echo "Rodando quarta vez"
./main8k
echo "Rodando quinta vez"
./main8k
echo compilando calculadora media
gcc -o calculadoraMedia calcularMedia.c -Wall
echo executando calculadora
./calculadoraMedia Sequencial_stats_wallpaper8k.txt
./calculadoraMedia Pthread_stats_wallpaper8k_2thread.txt
./calculadoraMedia OpenMP_stats_wallpaper8k_2thread.txt
./calculadoraMedia Pthread_stats_wallpaper8k_4thread.txt
./calculadoraMedia OpenMP_stats_wallpaper8k_4thread.txt
./calculadoraMedia Pthread_stats_wallpaper8k_8thread.txt
./calculadoraMedia OpenMP_stats_wallpaper8k_8thread.txt