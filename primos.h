#ifndef PRIMOS_H
#define PRIMOS_H

#include <iostream>
#include <math.h>
#include <random>
#include <chrono>
#include "potenciaModular.h"

long long gerarPossivelPrimo()
{

    // Pega a seed a partir do relógid do sistema
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    // Seta a seed para o gerador de números aleatórios de 24 bits
    std::ranlux24 generator(seed);

    long long possivelPrimo = generator();

    if (possivelPrimo < 0)
        possivelPrimo *= -1;

    return possivelPrimo;
}

unsigned long long gerarPossivelPrimoIntervalo(unsigned long long vMax)
{
    // Define um valor mínimo para não correr o risco de gerar valores muito pequenos.
    int minBits = 18;
    unsigned long long m = pow(2, minBits);

    // Pega a seed a partir do relógid do sistema
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    // Seta a seed para o gerador de números aleatórios de 24 bits
    std::ranlux24 generator(seed);

    unsigned long long num;
    do
    {
        num = generator();
    } while (num > vMax || num == 1);

    // TROCAR AQUI
    // return 7 ;

    cout << "primo " << num << endl;

    return num;
}

/*
    p - candidato a primo
    a -> Números primos
    a ^ p - 1 != 1 (mod p) -> Tem certeza que não é primo
*/
bool verificaPrimo(unsigned long long possivelPrimo) // Implementação do teste do pequeno teorema de Fermat
{
    int primos[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53,
                    59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157,
                    163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263,
                    269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379,
                    383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491,
                    499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617,
                    619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 701, 709, 719, 727, 733, 739, 743, 751};

    unsigned long long size = sizeof(primos) / sizeof(int);

    unsigned long long a;

    for (int i = 0; i < size; i++)
    {
        a = potenciaModular(primos[i], possivelPrimo - 1, possivelPrimo);

        if (a != 1)
            return false;
    }

    return true;
}

unsigned long long gerarPseudoPrimo()
{
    bool verifica = false;

    int possivelPrimo;

    do
    {
        possivelPrimo = gerarPossivelPrimo();
    } while (!verificaPrimo(possivelPrimo));

    return possivelPrimo;
}

#endif