#ifndef RSA_H
#define RSA_H

#include <vector>
#include <string>

using namespace std;

class RSA
{
private:
    unsigned int chavePrivada;
    unsigned int chavePublica_n;
    unsigned int chavePublica_e;

    int definirTamanhoDoBloco();

public:
    unsigned int primoP;
    unsigned int primoQ;
    RSA();

    unsigned int getChavePrivada();
    unsigned int getChavePublica_n();
    unsigned int getChavePublica_e();

    void gerarChaves();
    vector<unsigned int> criptografar(string entrada);
    string descriptografar(vector<unsigned int> mensagemCriptografada);
};

#endif