/*****************************************************************//**
 * \file   Aresta.c
 * \brief  Funções relativas às arestas de um grafo
 * 
 * \author AndreFreitas
 * \date   May 2023
 *********************************************************************/

#include "Auxiliares.h"

#include "Aresta.h"
#include "Vertice.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS

#define M_PI 3.14159265358979323846

void ImprimeArestas(Aresta* h) {
    if (h == NULL) return;
    printf("\tAresta: %d - (%.0f)\n", h->id, h->distancia);
    ImprimeArestas(h->next);
}

float CalcularPontosGeoreferenciados(float lat1, float lng1, float lat2, float lng2) {
    // Converte as coordenadas de graus para radianos
    float lat1Rad = lat1 * M_PI / 180.0;
    float lng1Rad = lng1 * M_PI / 180.0;
    float lat2Rad = lat2 * M_PI / 180.0;
    float lng2Rad = lng2 * M_PI / 180.0;

    // Raio médio da Terra em quilômetros
    float raioTerra = 6371.0;

    // Diferença entre as latitudes e longitudes
    float difLat = lat2Rad - lat1Rad;
    float difLng = lng2Rad - lng1Rad;

    // Fórmula de Haversine para calcular a distância
    float a = sin(difLat / 2) * sin(difLat / 2) +
        cos(lat1Rad) * cos(lat2Rad) *
        sin(difLng / 2) * sin(difLng / 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    float distancia = raioTerra * c;

    return distancia;
}

Aresta* CriaAresta(int id, float distancia) {
    Aresta* novo = (Aresta*)calloc(1, sizeof(Aresta));
    if (novo == NULL) return NULL;
    novo->id = id;
    novo->distancia = distancia;
    novo->next = NULL;

    int resultado = GravarAresta(novo, id);  // Chamada da função GravarAresta
    if (resultado != 1) {
        printf("Erro ao gravar aresta!\n");
    }

    return novo;
}

Aresta* InsereAresta(Aresta* h, Aresta* novo, bool* res) {
    *res = false; // por defeito é falso

    if (novo == NULL) // Se nova aresta é nula, ignora operação
        return h;

    if (ProcuraArestaId(h, novo->id) == true) // Se nova aresta já existe, ignorar operação
        return h;

    // Inserir nova aresta!
    *res = true;
    if (h == NULL) { // Se lista de arestas é vazia, esta é a primeira aresta
        h = novo;
        return h;
    }

    novo->next = h;
    h = novo;

    return h;
}

Vertice* InsereArestaVertice(Vertice* vertice, char* origem, char* dest, float peso, bool* res) {
    *res = false; // Por defeito é falso

    if (vertice == NULL) return vertice; // Se o grafo está vazio, ignora a operação

    Vertice* aux = ProcuraVerticeLocal(vertice, origem);
    int id = ProcuraVerticeId(vertice, dest);

    // Se os vértices não são válidos, ignorar a operação
    if (aux == NULL || id <= 0) return vertice;

    // Não admite adjacências repetidas
    if (ProcuraArestaId(aux->arestas, id)) return vertice;

    // Insere nova adjacência no vértice "origem"
    Aresta* novaAresta = CriaAresta(id, peso);
    aux->arestas = InsereAresta(aux->arestas, novaAresta, res);

    // Insere caminho inverso, pois é não orientado, recursivamente
    return InsereArestaVertice(vertice, dest, origem, peso, res);
}

Aresta* RemoveAresta(Aresta* h, int id, bool* res) {
    *res = false; // por defeito é falso

    if (h == NULL) return NULL; // Se lista de arestas é vazia, não há arestas para remover

    // Se a primeira aresta da lista é a que queremos remover
    if (h->id == id) {
        Aresta* prox = h->next;
        free(h);
        *res = true;
        return prox;
    }

    // Percorrer a lista de arestas para encontrar a aresta a ser removida
    Aresta* current = h;
    while (current->next != NULL) {
        if (current->next->id == id) {
            Aresta* prox = current->next->next;
            free(current->next);
            current->next = prox;
            *res = true;
            return h;
        }
        current = current->next;
    }

    return h;
}

bool ProcuraArestaId(Aresta* h, int id) {
    if (h == NULL) return false;
    if (h->id == id) return true;
    return ProcuraArestaId(h->next, id);
}