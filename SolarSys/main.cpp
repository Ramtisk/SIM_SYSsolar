#include <iostream>
#include <limits> // Para lidar com entradas inválidas

#include "./cmake-build-debug/Include/Estrela.h"
#include "./cmake-build-debug/Include/Planeta.h"
#include "./cmake-build-debug/Include/Satelite.h"
#include "./cmake-build-debug/Include/Sistema_Solar.h"
int main() {
    SistemaSolar sistemaSolar;

    do {
        // Limpar a tela do console (pode não funcionar em todos os sistemas operacionais)
        // Pode ser substituído por métodos específicos para limpar a tela no seu ambiente
        std::cout << "\033[2J\033[1;1H";

        // Exibir menu
        std::cout << "==== Sistema Solar Simulator ====\n";
        std::cout << "1. Adicionar Estrela\n";
        std::cout << "2. Adicionar Planeta\n";
        std::cout << "3. Adicionar Lua\n";
        std::cout << "4. Simular Movimento\n";
        std::cout << "5. Imprimir Informacoes\n";
        std::cout << "0. Sair\n";
        std::cout << "Escolha uma opcao: ";

        int opcao;
        std::cin >> opcao;

        switch (opcao) {
            case 1: {
                // Adicionar Estrela
                // Implemente a lógica para coletar os dados necessários e adicionar a estrela ao sistema
                break;
            }
            case 2: {
                // Adicionar Planeta
                // Implemente a lógica para coletar os dados necessários e adicionar o planeta ao sistema
                break;
            }
            case 3: {
                // Adicionar Lua
                // Implemente a lógica para coletar os dados necessários e adicionar a lua ao sistema
                break;
            }
            case 4: {
                // Simular Movimento
                // Implemente a lógica para coletar o delta time e simular o movimento dos corpos celestes
                break;
            }
            case 5: {
                // Imprimir Informacoes
                sistemaSolar.imprimirInformacoes();
                break;
            }
            case 0: {
                // Sair
                std::cout << "Saindo do programa.\n";
                return 0;
            }
            default: {
                // Opção inválida
                std::cout << "Opcao invalida. Tente novamente.\n";
                break;
            }
        }

        // Limpar buffer de entrada para evitar problemas com entradas inválidas
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Pausa para o usuário ler as mensagens antes de mostrar o menu novamente
        std::cout << "Pressione Enter para continuar...";
        std::cin.ignore();
    } while (true);

    return 0;
}
