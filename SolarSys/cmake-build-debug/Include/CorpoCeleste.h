//
// Created by anton on 19/01/2024.
//

#ifndef SOLARSYS_CORPOCELESTE_H
#define SOLARSYS_CORPOCELESTE_H


#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct CartesianPosition{
    double x;
    double y;
    double z;
};

struct CartesianVelocity{
    double vx;
    double vy;
    double vz;
};

class CorpoCeleste {
public:
    CorpoCeleste(){
        string nome;
        double massa;
        double raio;
        CartesianPosition posicao;
        CartesianVelocity velocidade;
    }

    //Getters & Setters
    string GetNome() const;
    double GetMassa() const;
    double GetRaio() const;
    CartesianPosition GetPosicao() const;
    CartesianVelocity GetVelocidade() const;

    void setPosicao(CartesianPosition posicao);
    void setVelocidade(CartesianVelocity velocidade);

    // Método para atualizar a posição com base na velocidade
    virtual void atualizarPosicao(double deltaTime);

    // Método para imprimir informações sobre o corpo celeste
    virtual void imprimirInfo() const;

protected:
    // Atributos
    string nome;
    double massa;
    double raio;
    CartesianPosition posicao;
    CartesianVelocity velocidade;
};



#endif //SOLARSYS_CORPOCELESTE_H
