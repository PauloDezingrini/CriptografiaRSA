#include "RSA.h"
#include "primos.h"
#include "euclides.h"
#include "codificador.h"
#include "potenciaModular.h"

#include <math.h>
#include <vector>
#include <string>

using namespace std;

RSA::RSA()
{
    this->chavePrivada = 0;
    this->chavePublica_n = 0;
    this->chavePublica_e = 0;
}

unsigned long long RSA::getChavePrivada()
{
    return this->chavePrivada;
}

unsigned long long RSA::getChavePublica_n()
{
    return this->chavePublica_n;
}

unsigned long long RSA::getChavePublica_e()
{
    return this->chavePublica_e;
}

int RSA::definirTamanhoDoBloco()
{
    // Retorna 0 no caso da chave pública ser 0, ou seja, não foi gerada/Inicializada
    if (this->getChavePublica_n() == 0)
        return 0;
    else
    {
        unsigned long long maiorCombinacao = 25;
        int i;
        for (i = 2; maiorCombinacao < this->chavePublica_n; i += 2)
            maiorCombinacao += 25 * pow(10, i);

        return i - 2;
    }
}

void RSA::gerarChaves()
{
    // unsigned long long p = 541;
    // unsigned long long q = 547;

    unsigned long long p = gerarPseudoPrimo();
    unsigned long long q = gerarPseudoPrimo();
    unsigned long long s, t, x;
    this->primoP = p;
    this->primoQ = q;

    this->chavePublica_n = p * q;

    unsigned long long fi = (p - 1) * (q - 1);
    // cout << "fi " << fi << endl;
    unsigned long long e;
    do
    {
        e = gerarPseudoPrimo(); // Talvez garantir que ele seja pseudoPrimo
    } while (e > fi || euclidesEstendido(e, fi, s, t) != 1);

    this->chavePublica_e = e;
    this->chavePrivada = s;
    if (chavePrivada < 0)
        this->chavePrivada = s + fi;
    else
        this->chavePrivada = s;
}

vector<unsigned long long> RSA::criptografar(string entrada)
{
    int tamanhoDoBloco = definirTamanhoDoBloco();

    cout << "SIZE: " << tamanhoDoBloco << endl;

    string mensagemCodificada = codificar(entrada);

    /*
        Vector será utilizado para armazenar a mensagem criptografada,
        onde cada posição representará um bloco da mensagem
    */
    vector<unsigned long long> mensagemCriptografada;

    // Variáveis auxiliares
    unsigned long long sequenciaCriptografada;

    for (int i = 0; i < mensagemCodificada.length();)
    {
        string blocoDeMensagem = "";

        int tamanhoDaMensagem = 0;

        // Monta os blocos
        while (tamanhoDaMensagem < tamanhoDoBloco && i < mensagemCodificada.length())
        {
            blocoDeMensagem += mensagemCodificada[i];
            blocoDeMensagem += mensagemCodificada[i + 1];
            i += 2;
            tamanhoDaMensagem += 2;
        }

        /*
            Completa o bloco com 23 (Código do X) caso não tenha sido possível
            colocar a mensagem em um número exato de blocos
        */
        while (blocoDeMensagem.length() < tamanhoDoBloco)
        {
            blocoDeMensagem += "23";
        }

        cout << "bloco mensagem " << blocoDeMensagem << endl;

        sequenciaCriptografada =
            potenciaModular(stoll(blocoDeMensagem), this->chavePublica_e,
                            this->chavePublica_n);

        mensagemCriptografada.push_back(sequenciaCriptografada);
    }

    return mensagemCriptografada;
}

string RSA::descriptografar(vector<unsigned long long> mensagemCriptografada)
{
    string mensagemDescriptografada = "";
    string aux;
    unsigned long long sequenciaCriptografada;
    unsigned long long sequenciaDescriptografada;

    int tamanhoDoBloco = definirTamanhoDoBloco();
    // cout << "tamanho bloco " << tamanhoDoBloco << endl;

    // cout << "tamanho mensagem criptografada " << mensagemCriptografada.size() << endl;

    for (int i = 0; i < mensagemCriptografada.size(); i++)
    {

        sequenciaCriptografada = mensagemCriptografada[i];

        sequenciaDescriptografada = potenciaModular(sequenciaCriptografada,
                                                    this->chavePrivada, this->chavePublica_n);

        aux = to_string(sequenciaDescriptografada);
        // cout << "seq " << sequenciaDescriptografada << endl;

        /*
            Bloco: 6
            Tem que completar com 0,
        */
        while (aux.length() < tamanhoDoBloco)
            aux.insert(0, 1, '0');

        // cout << "Aux: " << zerosPraCompletar << endl;

        mensagemDescriptografada.append(aux);
        // cout << "mensagem descrit " << mensagemDescriptografada << endl;
    }

    return decodificar(mensagemDescriptografada);
}
