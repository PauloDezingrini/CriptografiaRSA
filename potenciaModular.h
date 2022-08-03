#ifndef POTENCIAMODULAR_H
#define POTENCIAMODULAR_H

#include <iostream>

using namespace std;

unsigned long long potenciaModular(unsigned long long a, 
unsigned long long expoente, unsigned long long mod)
{
    if (a == 0) return 0;
    if (expoente == 0) return 1;

    long long step;

    if (expoente % 2 == 0) {
        step = potenciaModular(a, expoente / 2, mod);
        step = (step * step) % mod;
    }
    else {
        step = a % mod;
        step = (step * potenciaModular(a, expoente - 1, mod) % mod) % mod;
    }

    return ((step + mod) % mod);
}

#endif