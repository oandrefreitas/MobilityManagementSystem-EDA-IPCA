/*****************************************************************//**
 * \file   Vertice.c
 * \brief  Funções relativas aos vértices de um grafo
 * 
 * \author AndreFreitas
 * \date   May 2023
 *********************************************************************/

#include "Vertice.h"
#include "Aresta.h"

#include "Veiculo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

Vertice* listaVertices = NULL;  // Definição e inicialização da lista de vértices
int totalVertices = 0;  // Definição e inicialização do total de vértices


Vertice* CriaGrafo() {
    // N coisas!!!
    return NULL;
}

void ImprimeVertice(Vertice* vertice) {
    if (vertice == NULL) return;
    printf("ID: %d\n", vertice->id);
    printf("Localidade: %s\n", vertice->localidade);
    printf("Disponibilidade: %d\n", vertice->disponibilidade);
    printf("Latitude: %.6f\n", vertice->lat);
    printf("Longitude: %.6f\n", vertice->lng);
    ImprimeVertice(vertice->next);                             // Recursividade
}

Vertice* CriaVertice(int id, char* localidade, int disponibilidade, float lat, float lng) {
    Vertice* novo = (Vertice*)calloc(1, sizeof(Vertice));
    if (novo == NULL) return NULL;
    novo->id = id;
    strcpy(novo->localidade, localidade);
    novo->disponibilidade = disponibilidade;
    novo->lat = lat;
    novo->lng = lng;
    novo->next = NULL;

    int resultadoGravacao = GravarVertice(novo);
    if (resultadoGravacao == -1) {
        printf("Erro ao gravar vertice!\n");
    }

    return novo;
}

Vertice* InsereVertice(Vertice* vertice, Vertice* novo, bool* res) {
    if (vertice == NULL || novo->id < vertice->id) {
        novo->next = vertice;
        vertice = novo;
        *res = true;
    }
    else {
        Vertice* auxVertice = vertice;
        Vertice* antVertice = auxVertice;
        while (auxVertice != NULL && novo->id > auxVertice->id) {
            antVertice = auxVertice;
            auxVertice = auxVertice->next;
        }
        antVertice->next = novo;
        novo->next = auxVertice;
        *res = true;
    }
    return vertice;
}

int ProcuraVerticeId(Vertice* vertice, char* localidade) {
    if (vertice == NULL) return -1;
    if (strcmp(vertice->localidade, localidade) == 0) return vertice->id;
    return ProcuraVerticeId(vertice->next, localidade);
}

Vertice* ProcuraVerticeLocal(Vertice* vertice, char* localidade) {
    if (vertice == NULL) return NULL;
    if (strcmp(vertice->localidade, localidade) == 0) return vertice;
    return ProcuraVerticeLocal(vertice->next, localidade);
}

Vertice* RemoverVertice(Vertice* vertice, int id, bool* res) {
    if (vertice == NULL) {
        *res = false; // A lista de vértices está vazia, não há vértices para remover
        return NULL;
    }

    if (vertice->id == id) {
        Vertice* prox = vertice->next;
        free(vertice);
        *res = true;
        return prox;
    }

    Vertice* current = vertice;
    Vertice* anterior = NULL;
    while (current != NULL) {
        if (current->id == id) {
            anterior->next = current->next;
            free(current);
            *res = true;
            return vertice;
        }
        anterior = current;
        current = current->next;
    }

    *res = false; // O vértice com o ID especificado não foi encontrado
    return vertice;
}

void ResetarVisitados(Vertice* grafo) {
    Vertice* atual = grafo;
    while (atual != NULL) {
        atual->visitado = false;
        atual = atual->next;
    }
}

bool DepthFirstSearchRec(Vertice* g, int origem, int dest, char caminho[][N], int* contador) {
    if (origem == dest) return true;

    Vertice* aux = ProcuraVerticeId(g, origem);
    aux->visitado = true;

    Aresta* aresta = aux->arestas;
    while (aresta != NULL) {
        Vertice* auxDest = ProcuraVerticeId(g, aresta->id);
        if (auxDest->visitado == false) {
            bool existe = DepthFirstSearchRec(g, aresta->id, dest, caminho, contador);
            if (existe) {
                strcpy(caminho[*contador], auxDest->localidade);
                (*contador)++;
                return true;
            }
        }
        aresta = aresta->next;
    }

    return false;
}

/// <summary>
/// 
/// </summary>
/// <param name="grafo"></param>
/// <param name="origem"></param>
/// <param name="destino"></param>
/// <param name="caminho"></param>
/// <param name="contador"></param>
/// <returns></returns>
bool ExisteCaminho(Vertice* grafo, char* origem, char* destino, char caminho[][N], int* contador) {
    Vertice* verticeOrigem = ProcuraVerticeLocal(grafo, origem);
    Vertice* verticeDestino = ProcuraVerticeLocal(grafo, destino);

    if (verticeOrigem == NULL || verticeDestino == NULL) {
        printf("Vertices nao encontrados!\n");
        return false;
    }

    // Marca todos os vértices como não visitados
    ResetarVisitados(grafo);

    // Adicionar a origem como primeira etapa do caminho
    strcpy(caminho[*contador], origem);
    (*contador)++;

    return DepthFirstSearchRec(grafo, verticeOrigem->id, verticeDestino->id, caminho, contador);
}

/*
void CaixeiroViajante(Vertice* grafo, Veiculo* veiculos) {
    Vertice* atual = grafo;

    while (atual != NULL) {
        if (atual->veiculo == NULL) {
            Veiculo* veiculoAtual = EncontraVeiculo(atual, veiculos);

            if (veiculoAtual != NULL) {
                char caminho[20][N];
                int contador = 0;
                Vertice* partida = atual;
                Vertice* destino = grafo;

                while (destino != NULL) {
                    if (destino->veiculo != NULL && strcmp(destino->veiculo->localizacao, veiculoAtual->localizacao) == 0) {
                        if (ExisteCaminho(grafo, partida->localidade, destino->localidade, caminho, &contador)) {
                            printf("Trajeto:\n");
                            for (int i = 0; i < contador; i++) {
                                printf("%s\n", caminho[i]);
                            }
                            break;
                        }
                    }
                    destino = destino->next;
                }
            }
            else {
                printf("Nao foi encontrado um veiculo com autonomia inferior a 50%% para percorrer o grafo a partir de %s.\n", atual->localidade);
            }
        }
        atual = atual->next;
    }
}*/