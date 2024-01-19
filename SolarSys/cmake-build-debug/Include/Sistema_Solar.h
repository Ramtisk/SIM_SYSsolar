//
// Created by anton on 19/01/2024.
//

#ifndef SOLARSYS_SISTEMA_SOLAR_H
#define SOLARSYS_SISTEMA_SOLAR_H

#include <vector>
#include "CorpoCeleste.h"

class SistemaSolar {
public:
    // Construtor
    SistemaSolar();

    // Métodos para adicionar/remover corpos celestes ao sistema
    void adicionarCorpoCeleste(const CorpoCeleste& corpoCeleste);
    void removerCorpoCeleste(const string& nome);

    // Método para simular o movimento dos corpos celestes ao longo do tempo
    void simularMovimento(double deltaTime);

    // Método para imprimir informações sobre todos os corpos celestes no sistema
    void imprimirInformacoes() const;

private:
    // Lista de corpos celestes no sistema solar
    std::vector<CorpoCeleste> corposCelestes;
};


#endif //SOLARSYS_SISTEMA_SOLAR_H
