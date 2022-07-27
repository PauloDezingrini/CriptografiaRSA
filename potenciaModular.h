#ifndef POTENCIAMODULAR_H
#define POTENCIAMODULAR_H

#include <iostream>

using namespace std;

long long potenciaModular(long long a, long long expoente, long long mod)
{
    // Caso base
    if (expoente == 1)
        return a;

    // Divisão em problemas menores
    long long x = potenciaModular(a, expoente / 2, mod) % mod;

    if (expoente % 2 == 0)
    {
        return (x * x) % mod;
    }
    else
    {
        return (x * x * a) % mod;
    }
}

#endif