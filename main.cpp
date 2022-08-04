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

    mensagemCriptografada = rsa.criptografar(mensagem);

    cout << "Mensagem Criptografada" << endl;
    for (int i = 0; i < mensagemCriptografada.size(); i++)
        cout << mensagemCriptografada[i];
    cout << endl;

    cout << "Mensagem Descriptografada" << endl;
    mensagem = rsa.descriptografar(mensagemCriptografada);

    cout << mensagem << endl;
}

/*
    n - 7 digitos
    bloco - 6

    mod n - 7




*/