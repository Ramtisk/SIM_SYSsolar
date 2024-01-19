//
// Created by anton on 19/01/2024.
//

#ifndef SOLARSYS_ESTRELA_H
#define SOLARSYS_ESTRELA_H

#include "../Include/CorpoCeleste.h"

using namespace std;

class Estrela : public CorpoCeleste{
public:
    Estrela(
            string nome;
            double massa;
            double raio;
            CartesianPosition posicao;
            CartesianPosition velocidade;
            double temperatura;
            double luminosidade;
    );

//Getters & Setters
double GetTemperatura() const;
double GetLuminosidade() const;

// Método para imprimir informações sobre a estrela
void imprimirInfo() const override;

private:
    // Atributos da estrela (private para encapsulamento)
    double temperatura;
    double luminosidade;

};

#endif //SOLARSYS_ESTRELA_H
