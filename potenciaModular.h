#ifndef POTENCIAMODULAR_H
#define POTENCIAMODULAR_H

#include <iostream>

using namespace std;

unsigned int potenciaModular(unsigned int a, unsigned int expoente, unsigned int mod)
{
    // Caso base
    if (expoente == 1)
        return a;

    // Divisão em problemas menores
    unsigned int x = potenciaModular(a, expoente / 2, mod) % mod;

    if (expoente % 2 == 0)
    {
        return (x * x) % mod;
    }
    else
    {
        return (x * x * a) % mod;
    }
}

// unsigned int potenciaModular(unsigned int a,
//                              unsigned int expoente, unsigned int mod)
// {
//     if (a == 0)
//         return 0;
//     if (expoente == 0)
//         return 1;

//     unsigned int x;

//     if (expoente % 2 == 0)
//     {
//         x = potenciaModular(a, expoente / 2, mod);
//         x = (x * x) % mod;
//     }
//     else
//     {
//         x = a % mod;
//         x = (x * potenciaModular(a, expoente - 1, mod) % mod) % mod;
//     }

//     return ((x + mod) % mod);
// }

#endif