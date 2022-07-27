#ifndef PRIMOS_H
#define PRIMOS_H

#include <math.h>
#include <random>
#include <chrono>

long long gerarPossivelPrimo()
{
    // Define um valor mínimo para não correr o risco de gerar valores muito pequenos.
    int minBits = 32;
    long long m = pow(2, minBits);

    // Pega a seed a partir do relógid do sistema
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    // Seta a seed para o gerador de números aleatórios de 48 bits
    std::ranlux48 generator(seed);

    return generator() + m;
}

bool pequenoTeoremaDeFermat(long long possivelPrimo)
{
}

#endif