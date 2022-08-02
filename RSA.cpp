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

long long RSA::getChavePrivada()
{
    return this->chavePrivada;
}

long long RSA::getChavePublica_n()
{
    return this->chavePublica_n;
}

long long RSA::getChavePublica_e()
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

        return i;
    }
}

void RSA::gerarChaves()
{
    long long p = gerarPseudoPrimo();
    long long q = gerarPseudoPrimo();

    this->primoP = p;
    this->primoQ = q;

    this->chavePublica_n = p * q;

    unsigned long long fi = (p - 1) * (q - 1);

    unsigned long long e;
    do
    {
        e = gerarPossivelPrimo(); // Talvez garantir que ele seja pseudoPrimo
    } while (euclides(e, fi) != 1);

    this->chavePublica_e = e;

    unsigned long long s, t;

    euclidesEstendido(e, fi, s, t);

    if (s >= 0)
        this->chavePrivada = s;
    else
        this->chavePrivada = s + fi;
}

vector<unsigned long long> RSA::criptografar(string entrada)
{
    int tamanhoDoBloco = definirTamanhoDoBloco();

    string mensagemCodificada = codificar(entrada);

    /*
        Vector será utilizado para armazenar a mensagem criptografada,
        onde cada posição representará um bloco da mensagem
    */
    vector<unsigned long long> mensagemCriptografada;

    // Variáveis auxiliares
    unsigned long long sequenciaCriptografada;
    int i = 0;

    while (i < mensagemCodificada.length())
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
            blocoDeMensagem += "23";

        cout << blocoDeMensagem << endl;

        sequenciaCriptografada = potenciaModular(stoll(blocoDeMensagem), this->chavePublica_e, this->chavePublica_n);
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
    int zerosPraCompletar;

    for (int i = 0; i < mensagemCriptografada.size(); i++)
    {
        zerosPraCompletar = 0;

        sequenciaCriptografada = mensagemCriptografada[i];

        sequenciaDescriptografada = potenciaModular(sequenciaCriptografada, this->chavePrivada, this->chavePublica_n);

        aux = to_string(sequenciaDescriptografada);

        if (tamanhoDoBloco > aux.length())
            zerosPraCompletar = tamanhoDoBloco - aux.length();

        mensagemDescriptografada.append((aux.insert(0, zerosPraCompletar, '0')));
    }

    return decodificar(mensagemDescriptografada);
}
