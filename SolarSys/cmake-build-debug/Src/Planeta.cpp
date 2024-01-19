//
// Created by anton on 19/01/2024.
//

#include "../Include/Planeta.h"
#include "../Include/CorpoCeleste.h"
#include <iostream>

using namespace std;

// Implementação dos métodos da classe Planeta

Planeta::Planeta(
        string nome,
        double massa,
        double raio,
        CartesianPosition posicao,
        CartesianVelocity velocidade,
        double periodoRotacao,
        double periodoTranslacao
) : CorpoCeleste(nome, massa, raio, posicao, velocidade),
    periodoRotacao(periodoRotacao),
    periodoTranslacao(periodoTranslacao) {
    // Construtor da classe base (CorpoCeleste) é chamado para inicializar membros comuns
}

void Planeta::adicionarLua(const Satelite& lua) {
    luas.push_back(lua);
}

void Planeta::removerLua(const string& nomeLua) {
    // Implemente a lógica para remover uma lua pelo nome
    // (pode usar std::remove_if e erase para remover um elemento do vector)
}

void Planeta::imprimirLuas() const {
    // Implemente a lógica para imprimir as informações das luas
}

void Planeta::imprimirInfo() const {
    // Impressão das informações específicas do planeta
    CorpoCeleste::imprimirInfo(); // Chama o método da classe base
    cout << "Período de Rotação: " << periodoRotacao << " horas" << endl;
    cout << "Período de Translação: " << periodoTranslacao << " dias" << endl;

    // Chama a função para imprimir informações sobre as luas
    imprimirLuas();
}

