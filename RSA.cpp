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

unsigned int RSA::getChavePrivada()
{
    return this->chavePrivada;
}

unsigned int RSA::getChavePublica_n()
{
    return this->chavePublica_n;
}

unsigned int RSA::getChavePublica_e()
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
        unsigned int maiorCombinacao = 25;
        int i;
        for (i = 2; maiorCombinacao < this->chavePublica_n; i += 2)
            maiorCombinacao += 25 * pow(10, i);

        return i;
    }
}

void RSA::gerarChaves()
{
    unsigned int p = 541;
    unsigned int q = 547;

    // unsigned int p = gerarPseudoPrimo();
    // unsigned int q = gerarPseudoPrimo();
    unsigned int s, t, x;
    this->primoP = p;
    this->primoQ = q;

    this->chavePublica_n = p * q;

    unsigned int fi = (p - 1) * (q - 1);
    // cout << "fi " << fi << endl;
    unsigned int e;
    do
    {
        e = gerarPseudoPrimo(); // Talvez garantir que ele seja pseudoPrimo
    } while (euclidesEstendido(e, fi, s, t) != 1);
    // cout << "e " << e << endl;

    this->chavePublica_e = e;
    this->chavePrivada = s;
    if (chavePrivada < 0)
        this->chavePrivada = s;
    else
        this->chavePrivada = s + fi;
}

vector<unsigned int> RSA::criptografar(string entrada)
{
    // int tamanhoDoBloco = definirTamanhoDoBloco();
    int tamanhoDoBloco = 1;

    string mensagemCodificada = codificar(entrada);

    /*
        Vector será utilizado para armazenar a mensagem criptografada,
        onde cada posição representará um bloco da mensagem
    */
    vector<unsigned int> mensagemCriptografada;

    // Variáveis auxiliares
    unsigned int sequenciaCriptografada;

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
            tamanhoDaMensagem += 1;
        }

        while (blocoDeMensagem.length() != tamanhoDaMensagem * 2)
        {
            blocoDeMensagem += "25";
        }
        /*
            Completa o bloco com 23 (Código do X) caso não tenha sido possível
            colocar a mensagem em um número exato de blocos
        */
        // while (blocoDeMensagem.length() < tamanhoDoBloco)
        //     blocoDeMensagem += "23";

        cout << "bloco mensagem " << blocoDeMensagem << endl;

        sequenciaCriptografada =
            potenciaModular(stoll(blocoDeMensagem), this->chavePublica_e,
                            this->chavePublica_n);

        mensagemCriptografada.push_back(sequenciaCriptografada);
    }

    return mensagemCriptografada;
}

string RSA::descriptografar(vector<unsigned int> mensagemCriptografada)
{
    string mensagemDescriptografada = "";
    string aux;
    unsigned int sequenciaCriptografada;
    unsigned int sequenciaDescriptografada;

    int tamanhoDoBloco = definirTamanhoDoBloco();
    cout << "tamanho bloco " << tamanhoDoBloco << endl;
    int zerosPraCompletar;

    cout << "tamanho mensagem criptografada " << mensagemCriptografada.size() << endl;

    for (int i = 0; i < mensagemCriptografada.size(); i++)
    {
        zerosPraCompletar = 0;

        sequenciaCriptografada = mensagemCriptografada[i];

        sequenciaDescriptografada = potenciaModular(sequenciaCriptografada,
                                                    this->chavePrivada, this->chavePublica_n);

        aux = to_string(sequenciaDescriptografada);
        cout << "seq " << sequenciaDescriptografada << endl;

        if (tamanhoDoBloco > aux.length())
            zerosPraCompletar = tamanhoDoBloco - aux.length() - 2;

        cout << "ZEROS: " << zerosPraCompletar << endl;

        aux.insert(0, zerosPraCompletar, '0');

        mensagemDescriptografada.append(aux);
        cout << "mensagem descrit " << mensagemDescriptografada << endl;
    }

    return decodificar(mensagemDescriptografada);
}
