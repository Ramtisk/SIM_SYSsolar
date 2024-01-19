//
// Created by anton on 19/01/2024.
//

#ifndef SOLARSYS_SATELITE_H
#define SOLARSYS_SATELITE_H


#include "../Include/CorpoCeleste.h"

class Satelite : public CorpoCeleste {
public:
    // Construtor
    Satelite(
            string nome,
            double massa,
            double raio,
            CartesianPosition posicao,
            CartesianVelocity velocidade,
            double periodoOrbital
    );

    // Métodos específicos para satélites
    double getPeriodoOrbital() const;

    // Sobrescrita do método imprimirInfo
    void imprimirInfo() const override;
};


#endif //SOLARSYS_SATELITE_H
