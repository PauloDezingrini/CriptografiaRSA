#ifndef CODIFICADOR_H
#define CODIFICADOR_H

#include <string>
#include <map>

using namespace std;

string codificar(string entrada)
{
    map<char, string> codificacao = {{'A', "00"}, {'B', "01"}, {'C', "02"}, {'D', "03"}, {'E', "04"}, {'F', "05"}, {'G', "06"}, {'H', "07"}, {'I', "08"}, {'J', "09"}, {'K', "10"}, {'L', "11"}, {'M', "12"}, {'N', "13"}, {'O', "14"}, {'P', "15"}, {'Q', "16"}, {'R', "17"}, {'S', "18"}, {'T', "19"}, {'U', "20"}, {'V', "21"}, {'W', "22"}, {'X', "23"}, {'Y', "24"}, {'Z', "25"}};

    map<char, string>::iterator it;

    string entradaCodificada = "";

    for (char letra : entrada)
    {
        it = codificacao.find(letra);

        entradaCodificada.append(it->second);
    }

    return entradaCodificada;
}

string decodificar(string textoCodificado)
{
    map<string, char> decodificacao = {{"00", 'A'}, {"01", 'B'}, {"02", 'C'}, {"03", 'D'}, {"04", 'E'}, {"05", 'F'}, {"06", 'G'}, {"07", 'H'}, {"08", 'I'}, {"09", 'J'}, {"10", 'K'}, {"11", 'L'}, {"12", 'M'}, {"13", 'N'}, {"14", 'O'}, {"15", 'P'}, {"16", 'Q'}, {"17", 'R'}, {"18", 'S'}, {"19", 'T'}, {"20", 'U'}, {"21", 'V'}, {"22", 'W'}, {"23", 'X'}, {"24", 'Y'}, {"25", 'Z'}};

    map<string, char>::iterator it;

    string textoDescodificado = "";

    int tamanhoTexto = textoCodificado.size();

    string aux;
    for (int i = 0; i < tamanhoTexto; i += 2)
    {
        aux = textoCodificado.substr(i, 2);

        it = decodificacao.find(aux);

        textoDescodificado.push_back(it->second);
    }

    return textoDescodificado;
}

#endif
