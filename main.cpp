#include <iostream>
#include <string>
#include <vector>
#include "RSA.h"

using namespace std;

int main()
{
    RSA rsa;
    rsa.gerarChaves();

    cout << "( " << rsa.getChavePublica_n() << " , " << rsa.getChavePublica_e() << " )" << endl;
    
    
    cout << "Chave privada :" << rsa.getChavePrivada() << endl;

    cout << "Primos p : " << rsa.primoP << endl;
    cout << "Primos q : " << rsa.primoQ << endl;

    string mensagem = "PAU";
    vector<unsigned long long> mensagemCriptografada;

    mensagemCriptografada = rsa.criptografar(mensagem);

    cout << "Mensagem Criptografada" << endl;
    for (int i = 0; i < mensagemCriptografada.size(); i++)
        cout << mensagemCriptografada[i];
    cout << endl;

    cout << "Mensagem Descriptografada" << endl;
    mensagem = rsa.descriptografar(mensagemCriptografada);

    cout << mensagem << endl;
}