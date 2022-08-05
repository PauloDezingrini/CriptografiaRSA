#include <iostream>
#include <string>
#include <vector>
#include "RSA.h"

using namespace std;

int main(int argc, char *argv[])
{
    RSA rsa;
    rsa.gerarChaves();

    cout << "( " << rsa.getChavePublica_n() << " , " << rsa.getChavePublica_e() << " )" << endl;

    cout << "Chave privada :" << rsa.getChavePrivada() << endl;

    cout << "Primos p : " << rsa.primoP << endl;
    cout << "Primos q : " << rsa.primoQ << endl;

    string mensagem = argv[1];
    vector<long long> mensagemCriptografada;

    vector<long long> mensagemAssinada;
    mensagemAssinada = rsa.gerarAssinatura(mensagem);

    cout << "Mensagem Assinada" << endl;
    for (int i = 0; i < mensagemAssinada.size(); i++)
        cout << mensagemAssinada[i];
    cout << endl;

    cout << "Mensagem Assinada Descriptografada" << endl;
    mensagem = rsa.descriptografarAssinatura(mensagemAssinada);

    cout << mensagem << endl;

    long long quebrar = 1886757083;
    rsa.quebrarCriptografia(quebrar);
}
