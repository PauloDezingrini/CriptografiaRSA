#ifndef RSA_H
#define RSA_H

#include <vector>
#include <string>

using namespace std;

class RSA
{
private:
    unsigned long long chavePrivada;
    unsigned long long chavePublica_n;
    unsigned long long chavePublica_e;

    int definirTamanhoDoBloco();

public:
    unsigned long long primoP;
    unsigned long long primoQ;
    RSA();

    unsigned long long getChavePrivada();
    unsigned long long getChavePublica_n();
    unsigned long long getChavePublica_e();

    void gerarChaves();
    vector<unsigned long long> criptografar(string entrada);
    string descriptografar(vector<unsigned long long> mensagemCriptografada);
};

#endif