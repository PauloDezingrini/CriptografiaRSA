#include <iostream>
#include <string>
#include <vector>
#include "controle.h"

using namespace std;

string lerMensagem()
{
    string mensagem;
    cout << "\t\tDigite a mensagem a ser cripografada: ";
    cin >> mensagem;
    return mensagem;
}

int main(int argc, char *argv[])
{
    int opcao = 0;
    long long n, e;
    string mensagem;
    RSA rsa;
    vector<long long> aux;

    while (opcao != 7)
    {
        cout << "Escolha uma opcão: " << endl;
        cout << "\t 1)Gerar e exibir todas as chaves;" << endl;
        cout << "\t 2)Gerar chaves e criptografar mensagem;" << endl;
        cout << "\t 3)Criptografar mensagem com chaves existentes;" << endl;
        cout << "\t 4)Gerar chaves, criptografar e descriptografar;" << endl;
        cout << "\t 5)Assinar mensagem;" << endl;
        cout << "\t 6)Assinar mensagem e desassinar mensagem;" << endl;
        cout << "\t 7)Sair." << endl;
        cout << "\t Digite sua escolha : ";
        cin >> opcao;
        switch (opcao)
        {
        case 1:
            cout << "\t\t=== Gerando chaves ===" << endl;
            gerarChaves();
            break;

        case 2:
            mensagem = lerMensagem();
            cout << "\n\t\t=== Criptografando mensagem ===" << endl;
            criptografarMensagem(mensagem);
            break;
        case 3:
            cout << "\t\tDigite a primeira parte da chave(n): ";
            cin >> n;
            cout << "\t\tDigite a segunda parte da chave(e): ";
            cin >> e;
            mensagem = lerMensagem();
            cout << "\n\t\t=== Criptografando mensagem ===" << endl;
            criptografarMensagem(n, e, mensagem);
            break;
        case 4:
            mensagem = lerMensagem();
            cout << "\n\t\t=== Criptografando e Descriptografando mensagem ===" << endl;
            execucaoCompleta(mensagem);
            break;
        case 5:
            mensagem = lerMensagem();
            cout << "\n\t\t=== Assinando mensagem ===" << endl;
            assinarMensagem(mensagem);
            break;
        case 6:
            mensagem = lerMensagem();
            cout << "\n\t\t=== Assinando e retirando a assinatura da mensagem ===" << endl;
            execucaoCompletaAssinatura(mensagem);

        default:
            break;
        }
    }
}
