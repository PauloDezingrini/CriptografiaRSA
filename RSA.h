#ifndef RSA_H
#define RSA_H

class RSA
{
private:
    long long chavePrivada;
    long long chavePublica_n;
    long long chavePublica_e;

public:
    long long primoP;
    long long primoQ;
    RSA();

    long long getChavePrivada();
    long long getChavePublica_n();
    long long getChavePublica_e();

    void gerarChaves();
};

#endif