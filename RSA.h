#ifndef RSA_H
#define RSA_H

#include <vector>
#include <string>

using namespace std;

class RSA
{
private:
     long long chavePrivada;
     long long chavePublica_n;
     long long chavePublica_e;

    int definirTamanhoDoBloco();

public:
     long long primoP;
     long long primoQ;
    RSA();

    long long getChavePrivada();
    long long getChavePublica_n();
    long long getChavePublica_e();

    void gerarChaves();
    vector< long long> criptografar(string entrada);
    
    string descriptografar(vector< long long> mensagemCriptografada);
    string descriptografarAssinatura(vector< long long> mensagemCriptografada);
    vector< long long> gerarAssinatura(string entrada);
};

#endif