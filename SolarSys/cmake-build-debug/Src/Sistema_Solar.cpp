//
// Created by anton on 19/01/2024.
//

#include "../Include/Sistema_Solar.h"

#include "SistemaSolar.h"
#include <iostream>

// Implementação dos métodos da classe SistemaSolar

SistemaSolar::SistemaSolar() {
    // Inicialize aqui se necessário
}

void SistemaSolar::adicionarCorpoCeleste(const CorpoCeleste& corpoCeleste) {
    corposCelestes.push_back(corpoCeleste);
}

void SistemaSolar::removerCorpoCeleste(const string& nome) {
    // Implemente a lógica para remover um corpo celeste pelo nome
    // (pode usar std::remove_if e erase para remover um elemento do vector)
}

void SistemaSolar::simularMovimento(double deltaTime) {
    // Implemente a lógica para simular o movimento de todos os corpos celestes
    // Atualize as posições com base nas velocidades e outros fatores
}

void SistemaSolar::imprimirInformacoes() const {
    // Implemente a lógica para imprimir informações sobre todos os corpos celestes
    for (const CorpoCeleste& corpoCeleste : corposCelestes) {
        corpoCeleste.imprimirInfo();
        std::cout << "------------------------\n";
    }
}
