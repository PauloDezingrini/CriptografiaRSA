#ifndef CONTROLE_H
#define CONTROLE_H

#include <iostream>
#include <string>
#include <vector>
#include "RSA.h"

using namespace std;

/*
    Funções responsáveis por controlar e gerenciar o funcionamento da main
    Funções de exibição:
*/

void exibirChaves();
void exibirMensagemCriptografada(vector<long long> mensagemCriptografada);
void exibirMensagemDescriptografada(string mensagem);

/*
    Funções de controle
*/

RSA gerarChaves();
void criptografarMensagem(string mensagem);
void criptografarMensagem(long long n, long long e, string mensagem);
void descriptografarMensagem(long long n, long long e, long long d, string mensagem);
void assinarMensagem(string mensagem);
void execucaoCompleta(string mensagem);

/*
    Implementação das Funções de exibição
*/

void exibirChaves(RSA rsa)
{
    cout
        << "\t\tChaves públicas: ( " << rsa.getChavePublica_n() << " , " << rsa.getChavePublica_e() << " )" << endl;
    cout << "\t\tChave privada: " << rsa.getChavePrivada() << endl;
}

void exibirMensagemCriptografada(vector<long long> mensagemCriptografada)
{
    cout << "\t\tMensagem Criptografada: ";
    for (int i = 0; i < mensagemCriptografada.size(); i++)
        cout << mensagemCriptografada[i] << " ";
    cout << endl;
}

void exibirMensagemDescriptografada(string mensagem)
{
    cout << "\t\tMensagem Descriptografada: " << mensagem << endl;
}

/*
    Implementação das Funções de controle
*/

RSA gerarChaves()
{
    RSA rsa;
    rsa.gerarChaves();
    exibirChaves(rsa);
    return rsa;
}

void criptografarMensagem(string mensagem)
{
    RSA rsa = gerarChaves();
    vector<long long> mensagemCriptografada = rsa.criptografar(mensagem);
    exibirMensagemCriptografada(mensagemCriptografada);
}

void criptografarMensagem(long long n, long long e, string mensagem)
{
    RSA rsa(n, e);
    vector<long long> mensagemCriptografada = rsa.criptografar(mensagem);
    exibirMensagemCriptografada(mensagemCriptografada);
}

void descriptografarMensagem(long long n, long long e, long long d, string mensagem)
{
    RSA rsa(n, e, d);
    int tamanhoDoBloco = rsa.definirTamanhoDoBloco();
    cout << tamanhoDoBloco << endl;
    string aux;
    vector<long long> mensagemCriptografada;

    for (int i = 0; i < mensagem.length(); i += tamanhoDoBloco)
    {
        aux = "";
        for (int j = 0; j < tamanhoDoBloco && j + i < mensagem.length(); j++)
            aux.push_back(mensagem[i + j]);
        mensagemCriptografada.push_back(stoll(aux));
    }
    exibirMensagemCriptografada(mensagemCriptografada);
    aux = rsa.descriptografar(mensagemCriptografada);
    exibirMensagemDescriptografada(aux);
}

void execucaoCompleta(string mensagem)
{
    RSA rsa = gerarChaves();
    vector<long long> mensagemCriptografada = rsa.criptografar(mensagem);
    exibirMensagemCriptografada(mensagemCriptografada);
    string mensagemDescriptografada = rsa.descriptografar(mensagemCriptografada);
    exibirMensagemDescriptografada(mensagemDescriptografada);
}

void assinarMensagem(string mensagem)
{
    RSA rsa = gerarChaves();
    vector<long long> mensagemAssinada = rsa.gerarAssinatura(mensagem);
    exibirMensagemCriptografada(mensagemAssinada);
}

void execucaoCompletaAssinatura(string mensagem)
{
    RSA rsa = gerarChaves();
    vector<long long> mensagemAssinada = rsa.gerarAssinatura(mensagem);
    exibirMensagemCriptografada(mensagemAssinada);
    string mensagemDescriptografada = rsa.descriptografarAssinatura(mensagemAssinada);
    exibirMensagemDescriptografada(mensagemDescriptografada);
}

#endif