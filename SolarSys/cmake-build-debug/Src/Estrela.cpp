//
// Created by anton on 19/01/2024.
//

#include "../Include/Estrela.h"

#include <iostream>

using namespace std;

Estrela::Estrela(
        string nome,
        double massa,
        double raio,
        CartesianPosition,
        CartesianVelocity,
        double temperatura,
        double luminosidade
        ) : CorpoCeleste(nome, massa, raio, posicao, velocidade), temperatura(temperatura), luminosidade(luminosidade) {
    // Construtor da classe Estrela}

    double Estrela::GetTemperatura() const {
        return temperatura;
    }
    double Estrela::GetLuminosidade() const {
            return luminosidade;
    }

    void Estrela::imprimirInfo() const {
        cout << "Nome: " << GetNome() << endl;
        cout << "Massa: " << GetMassa() << endl;
        cout << "Raio: " << GetRaio() << endl;
        cout << "Posição: " << GetPosicao().x << ", " << GetPosicao().y << ", " << GetPosicao().z << endl;
        cout << "Velocidade: " << GetVelocidade().vx << ", " << GetVelocidade().vy << ", " << GetVelocidade().vz << endl;
        cout << "Temperatura: " << GetTemperatura() << endl;
        cout << "Luminosidade: " << GetLuminosidade() << endl;
    }
