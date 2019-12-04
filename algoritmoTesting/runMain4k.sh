#!/bin/bash  

echo "Compilando seq pthread mpi 4k"
gcc -o main4k main4k.c -lm -lpthread -fopenmp -O3
echo "Rodando primeira vez"
./main4k
echo "Rodando segunda vez"
./main4k
echo "Rodando terceira vez"
./main4k
echo "Rodando quarta vez"
./main4k
echo "Rodando quinta vez"
./main4k
echo compilando calculadora media
gcc -o calculadoraMedia calcularMedia.c -Wall
echo executando calculadora
./calculadoraMedia Sequencial_stats_wallpaper4k.txt
./calculadoraMedia Pthread_stats_wallpaper4k_2thread.txt
./calculadoraMedia OpenMP_stats_wallpaper4k_2thread.txt
./calculadoraMedia Pthread_stats_wallpaper4k_4thread.txt
./calculadoraMedia OpenMP_stats_wallpaper4k_4thread.txt
./calculadoraMedia Pthread_stats_wallpaper4k_8thread.txt
./calculadoraMedia OpenMP_stats_wallpaper4k_8thread.txt