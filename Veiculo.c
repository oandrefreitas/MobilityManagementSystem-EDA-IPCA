/*****************************************************************//**
 * \file   Veiculo.c
 * \brief  Funções relativas a veiculos de mobilidade elétrica - Trabalho EDA
 * 
 * \author AndreFreitas
 * \date   March 2023
 *********************************************************************/

#include "Auxiliares.h"

#include "Veiculo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

Veiculo* listaVeiculos = NULL;
static int totalVeiculos = 0;

// Função para imprimir lista de veículos
void ImprimeVeiculos() {
    Veiculo* atual = listaVeiculos;
    printf("Lista de Veiculos:\n");
    while (atual != NULL) {
        printf("ID: %d\n", atual->id);
        printf("Matricula: %s\n", atual->matricula);
        printf("Veiculo: %s\n", atual->meio);
        printf("Localizacao: %s\n", atual->localizacao);
        printf("Autonomia: %.2f\n", atual->autonomia);
        printf("Custo: %.2f\n", atual->custo);
        printf("--------------------\n");
        atual = atual->next;
    }
}

Veiculo* AdicionarVeiculo(char matricula[], char meio[], char localizacao[], float autonomia, float custo) {
    Veiculo* novoVeiculo = (Veiculo*)malloc(sizeof(Veiculo));
    if (novoVeiculo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return listaVeiculos;
    }

    // Preenche os dados do novo veículo
    novoVeiculo->id = ++totalVeiculos;
    strncpy(novoVeiculo->matricula, matricula, N - 1);
    strncpy(novoVeiculo->meio, meio, N - 1);
    strncpy(novoVeiculo->localizacao, localizacao, M - 1);
    novoVeiculo->autonomia = autonomia;
    novoVeiculo->custo = custo;
    novoVeiculo->next = NULL;

    // Adiciona o novo veículo à lista de veículos
    if (listaVeiculos == NULL) {
        listaVeiculos = novoVeiculo;
    }
    else {
        Veiculo* atual = listaVeiculos;
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = novoVeiculo;
    }

    // Grava os dados do novo veículo no arquivo Veiculo.txt
    GravarVeiculoNovo(novoVeiculo);

    return listaVeiculos;
}

// Função para remover um veículo
void RemoverVeiculo(int id) {
    // Percorre a lista de veículos procurando pelo veículo com o ID indicado
    Veiculo* veiculoAtual = listaVeiculos;
    Veiculo* veiculoAnterior = NULL;
    while (veiculoAtual != NULL && veiculoAtual->id != id) {
        veiculoAnterior = veiculoAtual;
        veiculoAtual = veiculoAtual->next;
    }

    // Se o veículo foi encontrado, remove-o da lista
    if (veiculoAtual != NULL) {
        if (veiculoAnterior == NULL) {
            listaVeiculos = veiculoAtual->next;
        }
        else {
            veiculoAnterior->next = veiculoAtual->next;
        }
        free(veiculoAtual);
        printf("Veiculo removido com sucesso!\n");

        // Atualiza o valor de totalClientes
        totalVeiculos--;
    }
    else {
        printf("Veiculo nao encontrado!\n");
    }
}

// Função para editar um veículo
void EditarVeiculo(int id) {
    Veiculo* atual = listaVeiculos;
    while (atual != NULL) {
        if (atual->id == id) {
            // Atualiza os dados do veículo
            char novaMatricula[N] = "UV10IL"; // Nova matrícula
            char novoMeio[N] = "Trotinete"; // Novo veiculo
            char novaLocalizacao[M] = "Porto"; // Nova localização
            float novaAutonomia = 800.0; // Nova autonomia
            float novoCusto = 350.0; // Novo custo
            strncpy(atual->matricula, novaMatricula, N - 1);
            strncpy(atual->meio, novoMeio, N - 1);
            strncpy(atual->localizacao, novaLocalizacao, M - 1);
            atual->autonomia = novaAutonomia;
            atual->custo = novoCusto;

            // Grava as alterações no arquivo Veiculo.txt
            GravarEditVeiculo();

            return;
        }
        atual = atual->next;
    }
    printf("Veículo com ID %d não encontrado.\n", id);
}

void ImprimeAutoDecre(Veiculo* listaVeiculos) {
    // Cria uma cópia da lista de veículos
    Veiculo* copiaListaVeiculos = NULL;
    Veiculo* atual = listaVeiculos;
    while (atual != NULL) {
        Veiculo* novoVeiculo = (Veiculo*)malloc(sizeof(Veiculo));
        if (novoVeiculo == NULL) {
            printf("Erro ao alocar memoria!\n");
            return;
        }
        *novoVeiculo = *atual;
        novoVeiculo->next = NULL;
        if (copiaListaVeiculos == NULL) {
            copiaListaVeiculos = novoVeiculo;
        }
        else {
            Veiculo* atualCopia = copiaListaVeiculos;
            while (atualCopia->next != NULL) {
                atualCopia = atualCopia->next;
            }
            atualCopia->next = novoVeiculo;
        }
        atual = atual->next;
    }

    // Ordena a cópia da lista de veículos por ordem decrescente de autonomia
    Veiculo* anterior = NULL;
    Veiculo* atualCopia = copiaListaVeiculos;
    while (atualCopia != NULL) {
        Veiculo* proximo = atualCopia->next;
        if (anterior == NULL || anterior->autonomia >= atualCopia->autonomia) {
            atualCopia->next = anterior;
            anterior = atualCopia;
        }
        else {
            Veiculo* atualAnterior = anterior;
            while (atualAnterior->next != NULL && atualAnterior->next->autonomia < atualCopia->autonomia) {
                atualAnterior = atualAnterior->next;
            }
            atualCopia->next = atualAnterior->next;
            atualAnterior->next = atualCopia;
        }
        atualCopia = proximo;
    }

    // Imprime a cópia da lista de veículos ordenada
    printf("Lista de Veiculos por ordem decrescente de autonomia:\n");
    atualCopia = anterior;
    while (atualCopia != NULL) {
        printf("ID: %d\n", atualCopia->id);
        printf("Matricula: %s\n", atualCopia->matricula);
        printf("Meio: %s\n", atualCopia->meio);
        printf("Localizacao: %s\n", atualCopia->localizacao);
        printf("Autonomia: %.2f\n", atualCopia->autonomia);
        printf("Custo: %.2f\n", atualCopia->custo);
        printf("--------------------\n");
        atualCopia = atualCopia->next;
    }

    // Libera a memória alocada para a cópia da lista de veículos
    while (copiaListaVeiculos != NULL) {
        Veiculo* proximo = copiaListaVeiculos->next;
        free(copiaListaVeiculos);
        copiaListaVeiculos = proximo;
    }
}

// Função para imprimir veículos por localização
void ImprimeVeiculosLocalizacao(char localizacao[]) {
    Veiculo* atual = listaVeiculos;
    printf("Veiculos na localizacao %s:\n", localizacao);
    while (atual != NULL) {
        if (strcmp(atual->localizacao, localizacao) == 0) {
            printf("ID: %d\n", atual->id);
            printf("Matricula: %s\n", atual->matricula);
            printf("Veiculo: %s\n", atual->meio);
            printf("Autonomia: %.2f\n", atual->autonomia);
            printf("Custo: %.2f\n", atual->custo);
            printf("--------------------\n");
        }
        atual = atual->next;
    }
}

void EncontrarVeiculoID(int id) {
    Veiculo* atual = listaVeiculos;
    while (atual != NULL) {
        if (atual->id == id) {
            printf("Informacoes do Veiculo:\n");
            printf("ID: %d\n", atual->id);
            printf("Matricula: %s\n", atual->matricula);
            printf("Veiculo: %s\n", atual->meio);
            printf("Localizacao: %s\n", atual->localizacao);
            printf("Autonomia: %.2f\n", atual->autonomia);
            printf("Custo: %.2f\n", atual->custo);
            return;
        }
        atual = atual->next;
    }
    printf("Veiculo com o ID %d nao encontrado.\n", id);
}

//Função para encontrar veículo por matrícula
Veiculo* EncontrarVeiculoMatricula(Veiculo* listaVeiculos, char matricula[]) {
    Veiculo* atual = listaVeiculos;
    while (atual != NULL) {
        if (strcmp(atual->matricula, matricula) == 0) {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

Veiculo* EncontraVeiculo(Vertice* atual, Veiculo* veiculos) {
    Veiculo* veiculoAtual = veiculos;
    while (veiculoAtual != NULL) {
        if (veiculoAtual->autonomia < 50 && strcmp(veiculoAtual->localizacao, atual->localidade) == 0) {
            return veiculoAtual;
        }
        veiculoAtual = veiculoAtual->next;
    }
    return NULL;
}