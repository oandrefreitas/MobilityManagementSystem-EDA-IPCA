/*****************************************************************//**
 * \file   Main.c
 * \brief  Main - Incomplete
 * 
 * \author AndreFreitas
 * \date   March 2023
 *********************************************************************/

#include "Auxiliares.h"

#include "Cliente.h"
#include "Veiculo.h"
#include "Aluguer.h"

#include "Vertice.h"
#include "Aresta.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS

int main() {

    Cliente* listaClientes = NULL;
    Veiculo* listaVeiculos = NULL;  // Inicializa a lista de veículos como vazio
    Aluguer* listaAlugueres = NULL;
    Vertice* listaVertices = NULL;

#pragma region GRAFO

    Vertice* grafo = CriaGrafo();
    bool resultado;

    // Criar vértices (pontos de recolha) e inseri-los no grafo
    Vertice* braga = CriaVertice(1, "Braga", 10, 41.551667, -8.422778);
    grafo = InsereVertice(grafo, braga, &resultado);

    Vertice* barcelos = CriaVertice(2, "Barcelos", 5, 41.531389, -8.618889);
    grafo = InsereVertice(grafo, barcelos, &resultado);

    Vertice* esposende = CriaVertice(3, "Esposende", 8, 41.532778, -8.781111);
    grafo = InsereVertice(grafo, esposende, &resultado);

    Vertice* famalicao = CriaVertice(4, "Famalicao", 9, 41.4125, -8.520556);
    grafo = InsereVertice(grafo, famalicao, &resultado);

    Vertice* guimaraes = CriaVertice(5, "Guimaraes", 7, 41.441944, -8.295556);
    grafo = InsereVertice(grafo, guimaraes, &resultado);

    Vertice* vizela = CriaVertice(6, "Vizela", 2, 41.375278, -8.303056);
    grafo = InsereVertice(grafo, vizela, &resultado);

    Vertice* fafe = CriaVertice(7, "Fafe", 5, 41.448611, -8.172222);
    grafo = InsereVertice(grafo, fafe, &resultado);

    Vertice* amares = CriaVertice(8, "Amares", 4, 41.631389, -8.349167);
    grafo = InsereVertice(grafo, amares, &resultado);

    Vertice* vilaverde = CriaVertice(9, "VilaVerde", 3, 41.651389, -8.435833);
    grafo = InsereVertice(grafo, vilaverde, &resultado);


    // Insere as arestas de conexão entre os pontos de recolha
    grafo = InsereArestaVertice(grafo, "Braga", "Barcelos", 22.2, &resultado);
    grafo = InsereArestaVertice(grafo, "Braga", "Famalicao", 19.1, &resultado);
    grafo = InsereArestaVertice(grafo, "Braga", "Guimaraes", 24.9, &resultado);
    grafo = InsereArestaVertice(grafo, "Braga", "Amares", 17.0, &resultado);
    grafo = InsereArestaVertice(grafo, "Braga", "VilaVerde", 16.6, &resultado);

    grafo = InsereArestaVertice(grafo, "Barcelos", "Esposende", 15.5, &resultado);
    grafo = InsereArestaVertice(grafo, "Barcelos", "Famalicao", 20.4, &resultado);
    grafo = InsereArestaVertice(grafo, "Barcelos", "VilaVerde", 24.0, &resultado);

    grafo = InsereArestaVertice(grafo, "Famalicao", "Guimaraes", 33.1, &resultado);

    grafo = InsereArestaVertice(grafo, "Guimaraes", "Fafe", 14.7, &resultado);
    grafo = InsereArestaVertice(grafo, "Guimaraes", "Vizela", 9.6, &resultado);

    grafo = InsereArestaVertice(grafo, "Amares", "VilaVerde", 10.2, &resultado);

    // Verifica o valor de "resultado" para cada chamada. Se for true, a inserção da aresta foi bem-sucedida.

#pragma endregion GRAFO

#pragma region CLIENTES e Veiculos

#pragma region CLIENTES e Veiculos

    /*// Adiciona 5 clientes
    listaClientes = AdicionarCliente(listaClientes, 123456789, 100.0, "Andre", "Rua 1");
    listaClientes = AdicionarCliente(listaClientes, 987654321, 200.0, "Maria", "Rua 2");
    listaClientes = AdicionarCliente(listaClientes, 111222333, 150.0, "Clementina", "Rua 3");
    listaClientes = AdicionarCliente(listaClientes, 444555666, 50.0, "Francisco", "Rua 4");
    listaClientes = AdicionarCliente(listaClientes, 777888999, 300.0, "Luzia", "Rua 5"); */

   /*// Adiciona 10 veículos
    listaVeiculos = AdicionarVeiculo(listaVeiculos, "ABC123", "Trotinete", "Braga", 500.0, 10.0);
    listaVeiculos = AdicionarVeiculo(listaVeiculos, "DEF456", "Mota", "Braga", 300.0, 30.0);
    listaVeiculos = AdicionarVeiculo(listaVeiculos, "GHI789", "Bicicleta", "Vizela", 200.0, 15.0);
    listaVeiculos = AdicionarVeiculo(listaVeiculos, "JKL012", "Carro", "Amares", 400.0, 50.0);
    listaVeiculos = AdicionarVeiculo(listaVeiculos, "MNO345", "Mota", "VilaVerde", 250.0, 30.0);
    listaVeiculos = AdicionarVeiculo(listaVeiculos, "PQR678", "Bicicleta", "Guimaraes", 150.0, 15.0);
    listaVeiculos = AdicionarVeiculo(listaVeiculos, "STU901", "Carro", "Fafe", 450.0, 50.0);
    listaVeiculos = AdicionarVeiculo(listaVeiculos, "VWX234", "Mota", "Esposende", 350.0, 30.0);
    listaVeiculos = AdicionarVeiculo(listaVeiculos, "YZA567", "Bicicleta", "Barcelos", 180.0, 15.0);
    listaVeiculos = AdicionarVeiculo(listaVeiculos, "BCD890", "Carro", "Famalicao", 550.0, 50.0); */

#pragma endregion CLIENTES e Veiculos

#pragma region MENU

    int option;
    int menuOption;

    int nif;
    float saldo;
    char nome[N];
    char morada[M];

    do {
        printf("\nGreenWheels - Rent N' Go\n");
        printf("\n");
        printf("1. Area de Cliente\n");
        printf("2. Area de Gestor\n");
        printf("3. Efetuar registo de Cliente\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &option);

        switch (option) {
        case 1:
   /*{//*/  if (LoginCliente()) {
                do {
                    printf("\nArea de Cliente\n");
                    printf("1. Registar aluguer\n");
                    printf("2. Carregar saldo\n");
                    printf("0. Voltar ao menu principal\n");
                    printf("Opcao: ");
                    scanf("%d", &menuOption);

                    switch (menuOption) {
                    case 1:
                    {
                        char matriculaVeiculo[N];
                        int nifCliente;
                        char dataInicio[N];
                        char dataFim[N];

                        printf("\nRegistar aluguer\n");
                        printf("Matricula do veiculo: ");
                        scanf("%s", matriculaVeiculo);
                        printf("NIF do cliente: ");
                        scanf("%d", &nifCliente);
                        printf("Data de inicio (DD/MM/AAAA): ");
                        scanf("%s", dataInicio);
                        printf("Data de fim (DD/MM/AAAA): ");
                        scanf("%s", dataFim);

                        AdicionarAluguer(&listaVertices, listaVeiculos, listaAlugueres, matriculaVeiculo, nifCliente, dataInicio, dataFim);
                    }
                    break;
                    case 2:
                    {
                        int nifCliente;
                        float valor;

                        printf("\nCarregar saldo\n");
                        printf("NIF do cliente: ");
                        scanf("%d", &nifCliente);
                        printf("Valor: ");
                        scanf("%f", &valor);

                        CarregarSaldo(nifCliente, valor);
                    }
                    break;
                    case 0:
                        break;
                    default:
                        printf("Opcao invalida.\n");
                        break;
                    }
                } while (menuOption != 0);
            }
            break;

        case 2:
            if (LoginGestor()) {
                do {
                    printf("\nArea de Gestor\n");
                    printf("1. Gerir clientes\n");
                    printf("2. Gerir veiculos\n");
                    printf("3. Gerir alugueres\n");
                    printf("4. Gerir pontos de recolha\n");
                    printf("0. Voltar ao menu principal\n");
                    printf("Opcao: ");
                    scanf("%d", &menuOption);

                    switch (menuOption) {
                    case 1:
                        // Funções relativas à gestão de clientes
                        break;
                    case 2:
                        // Funções relativas à gestão de veiculos
                        break;
                    case 3:
                        // Funções relativas à gestão de alugueres
                        break;
                    case 4:
                        // Funções relativas à gestão de PontosRecolha
                        break;
                    case 0:
                        break;
                    default:
                        printf("Opcao invalida.\n");
                        break;
                    }
                } while (menuOption != 0);
            }
            break;

        case 3:
            printf("Digite o NIF do cliente: ");
            scanf("%d", &nif);
            printf("Digite o saldo do cliente: ");
            scanf("%f", &saldo);
            printf("Digite o nome do cliente: ");
            scanf("%s", nome);
            printf("Digite a morada do cliente: ");
            scanf("%s", morada);

            listaClientes = AdicionarCliente(listaClientes, nif, saldo, nome, morada);
            printf("Cliente adicionado com sucesso!\n");
            break;

        case 0:
            break;

        default:
            printf("Opcao invalida.\n");
            break;
        }
    } while (option != 0);

#pragma endregion MENU

    return 0;
}