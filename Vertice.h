/*****************************************************************//**
 * \file   Vertice.h
 * \brief  Structs para os vértices do grafo
 * 
 * \author AndreFreitas
 * \date   May 2023
 *********************************************************************/

#ifndef Vertice_H
#define Vertice_H

#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS

#define N 50
#define M 70

#define TOTALVERTICE 24

typedef struct Vertice {
	int id;
	char localidade[N];                // localidade
	int disponibilidade;
	float lat;                       // localização - latitude
	float lng;                       // localização - longitude     
	bool visitado;
	struct Vertice* next;
	struct Aresta* arestas;         // Lista de arestas conectadas a este Vertice
}Vertice;

void ImprimeVertice(Vertice* ponto);
Vertice* CriaGrafo();
Vertice* CriaVertice(int id, char* localidade, int disponibilidade, float lat, float lng);
Vertice* InsereVertice(Vertice* vertice, Vertice* novo, bool* res);
int ProcuraVerticeId(Vertice* ponto, char* localidade);
Vertice* ProcuraVerticeLocal(Vertice* vertice, char* localidade);
Vertice* RemoverVertice(Vertice* ponto, int id, bool* res);
void ResetarVisitados(Vertice* grafo);
bool DepthFirstSearchRec(Vertice* g, int origem, int dest, char caminho[][N], int* contador);
bool ExisteCaminho(Vertice* grafo, char* origem, char* destino, char caminho[][N], int* contador);

#endif