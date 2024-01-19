//
// Created by anton on 19/01/2024.
//

#include "../Include/Satelite.h"
#include <iostream>

// Implementação dos métodos da classe Satelite

Satelite::Satelite(
        string nome,
        double massa,
        double raio,
        CartesianPosition posicao,
        CartesianVelocity velocidade,
        double periodoOrbital
) : CorpoCeleste(nome, massa, raio, posicao, velocidade), periodoOrbital(periodoOrbital) {
    // Construtor da classe base (CorpoCeleste) é chamado para inicializar membros comuns
}

double Satelite::getPeriodoOrbital() const {
    return periodoOrbital;
}

void Satelite::imprimirInfo() const {
    // Impressão das informações específicas do satélite
    CorpoCeleste::imprimirInfo(); // Chama o método da classe base
    std::cout << "Período Orbital: " << periodoOrbital << " dias" << std::endl;
}
