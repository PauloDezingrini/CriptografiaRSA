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

RSA::RSA(long long _chavePublica_n, long long _chavePublica_e)
{
    this->chavePublica_n = chavePublica_n;
    this->chavePublica_e = chavePublica_e;
}
RSA::RSA(long long _chavePublica_n, long long _chavePublica_e, long long _chavePrivada)
{
    this->chavePublica_n = _chavePublica_n;
    this->chavePublica_e = _chavePublica_e;
    this->chavePrivada = _chavePrivada;
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
        long long maiorCombinacao = 25;
        int i;
        for (i = 2; maiorCombinacao < this->chavePublica_n; i += 2)
            maiorCombinacao += 25 * pow(10, i);

        return i - 2;
    }
}

void RSA::gerarChaves()
{
    /*
        ( 1886757083 , 56569 )
        Chave privada :1176879169
        Primos p : 52391
        Primos q : 36013
    */

    long long p = gerarPseudoPrimo();
    long long q = gerarPseudoPrimo();
    long long s, t, x;
    this->primoP = p;
    this->primoQ = q;

    this->chavePublica_n = p * q;

    long long fi = (p - 1) * (q - 1);

    long long e;
    do
    {
        e = gerarPseudoPrimo();
    } while (euclidesEstendido(e, fi, s, t) != 1);

    this->chavePublica_e = e;
    this->chavePrivada = s;
    if (chavePrivada < 0)
        this->chavePrivada = s + fi;
    else
        this->chavePrivada = s;
}

vector<long long> RSA::criptografar(string entrada)
{
    int tamanhoDoBloco = definirTamanhoDoBloco();

    string mensagemCodificada = codificar(entrada);

    /*
        Vector será utilizado para armazenar a mensagem criptografada,
        onde cada posição representará um bloco da mensagem
    */
    vector<long long> mensagemCriptografada;

    long long sequenciaCriptografada;

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

        sequenciaCriptografada =
            potenciaModular(stoll(blocoDeMensagem), this->chavePublica_e,
                            this->chavePublica_n);

        mensagemCriptografada.push_back(sequenciaCriptografada);
    }

    return mensagemCriptografada;
}

string RSA::descriptografar(vector<long long> mensagemCriptografada)
{
    string mensagemDescriptografada = "";
    string aux;
    long long sequenciaCriptografada;
    long long sequenciaDescriptografada;

    int tamanhoDoBloco = definirTamanhoDoBloco();

    for (int i = 0; i < mensagemCriptografada.size(); i++)
    {

        sequenciaCriptografada = mensagemCriptografada[i];

        sequenciaDescriptografada = potenciaModular(sequenciaCriptografada,
                                                    this->chavePrivada, this->chavePublica_n);

        aux = to_string(sequenciaDescriptografada);

        while (aux.length() < tamanhoDoBloco)
            aux.insert(0, 1, '0');

        mensagemDescriptografada.append(aux);
    }

    return decodificar(mensagemDescriptografada);
}

vector<long long> RSA::gerarAssinatura(string entrada)
{

    int tamanhoDoBloco = definirTamanhoDoBloco();

    string mensagemCodificada = codificar(entrada);

    /*
        Vector será utilizado para armazenar a mensagem criptografada,
        onde cada posição representará um bloco da mensagem
    */
    vector<long long> mensagemCriptografada;

    // Variáveis auxiliares
    long long sequenciaCriptografada;

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

        sequenciaCriptografada =
            potenciaModular(stoll(blocoDeMensagem), this->chavePrivada,
                            this->chavePublica_n);

        mensagemCriptografada.push_back(sequenciaCriptografada);
    }
    return mensagemCriptografada;
}
string RSA::descriptografarAssinatura(vector<long long> mensagemCriptografada)
{
    string mensagemDescriptografada = "";
    string aux;
    long long sequenciaCriptografada;
    long long sequenciaDescriptografada;

    int tamanhoDoBloco = definirTamanhoDoBloco();

    for (int i = 0; i < mensagemCriptografada.size(); i++)
    {

        sequenciaCriptografada = mensagemCriptografada[i];

        sequenciaDescriptografada = potenciaModular(sequenciaCriptografada,
                                                    this->chavePublica_e, this->chavePublica_n);

        aux = to_string(sequenciaDescriptografada);

        while (aux.length() < tamanhoDoBloco)
            aux.insert(0, 1, '0');

        mensagemDescriptografada.append(aux);
    }

    return decodificar(mensagemDescriptografada);
}

void RSA::quebrarCriptografia(long long ch)
{
    // fatorar chave publica N até encontrar o valor de p * q
    //
    long long primo = 3;
    long long x = long(sqrt(ch));
    while (primo <= x)
    {

        if (ch % primo == 0)
        {
            cout << "N " << primo << " E " << ch / primo << endl;
            // cout << "ACHOUUUU" << primo << endl;
            break;
        }
        else
        {
            primo += 2;
        }
    }