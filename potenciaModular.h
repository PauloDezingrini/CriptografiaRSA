#ifndef POTENCIAMODULAR_H
#define POTENCIAMODULAR_H

#include <iostream>

using namespace std;


// unsigned long long potenciaModular(unsigned long long base, 
// unsigned long long exp, unsigned long long mod)
// {
//     if (exp == 1) return base%mod;
//     else if(exp %2==0) return 
//     (potenciaModular(base, exp/2,mod)*
//     potenciaModular(base, exp/2, mod))%mod;
    
//     return 
//     (((potenciaModular(base, (exp-1)/2,mod)*
//     potenciaModular(base, (exp-1)/2, mod))%mod)*
//     potenciaModular(base, 1, mod))%mod;
   
// }
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