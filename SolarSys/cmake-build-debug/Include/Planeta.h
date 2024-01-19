//
// Created by anton on 19/01/2024.
//

#ifndef SOLARSYS_PLANETA_H
#define SOLARSYS_PLANETA_H

#include "CorpoCeleste.h"


class Planeta : public CorpoCeleste {
public:
    Planeta(
            string nome,
            double massa,
            double raio,
            CartesianPosition posicao,
            CartesianVelocity velocidade,
            double PeriodoRotacao,
            double PeriodoTranslacao,
            );
    //Getters & Setters
    void adicionarLua(Satelite lua);
    Void removerLua(Satelite lua);
    void imprimirLuas() const;

    //sobrescrita do método imprimirInfo
    void imprimirInfo() const override;

    private:
        // Atributos do planeta (private para encapsulamento)
        double PeriodoRotacao;
        double PeriodoTranslacao;
        vector<Satelite> luas; //vetor de luas
};



#endif //SOLARSYS_PLANETA_H
