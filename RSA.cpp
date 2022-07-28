#include "RSA.h"
#include "primos.h"
#include "euclides.h"

RSA::RSA()
{
    this->chavePrivada = 0;
    this->chavePublica_n = 0;
    this->chavePublica_e = 0;
}

long long RSA::getChavePrivada()
{
    return this->chavePrivada;
}

long long RSA::getChavePublica_n()
{
    return this->chavePublica_n;
}

long long RSA::getChavePublica_e()
{
    return this->chavePublica_e;
}

void RSA::gerarChaves()
{
    long long p = gerarPseudoPrimo();
    long long q = gerarPseudoPrimo();

    this->primoP = p;
    this->primoQ = q;

    this->chavePublica_n = p * q;

    long long fi = (p - 1) * (q - 1);

    long long e;
    do
    {
        e = gerarPossivelPrimo(); // Talvez garantir que ele seja pseudoPrimo
    } while (euclides(e, fi) != 1);

    this->chavePublica_e = e;

    long long s, t;

    euclidesEstendido(e, fi, s, t);

    if (s >= 0)
        this->chavePrivada = s;
    else
        this->chavePrivada = s + fi;
}