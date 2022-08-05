#ifndef POTENCIAMODULAR_H
#define POTENCIAMODULAR_H

#include <iostream>

using namespace std;

unsigned long long potenciaModular(unsigned long long a, unsigned long long expoente, unsigned long long mod)
{
    // Caso base
    if (expoente == 1)
        return a;

    // Divisão em problemas menores
    unsigned long long x = potenciaModular(a, expoente / 2, mod) % mod;

    if (expoente % 2 == 0)
    {
        return (x * x) % mod;
    }
    else
    {
        return (((x * x) % mod) * a) % mod;
    }
}

#endif