#include <iostream>
#include <string>
#include "codificador.h"
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
}