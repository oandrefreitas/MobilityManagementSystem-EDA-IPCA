/*****************************************************************//**
 * \file   Aresta.h
 * \brief  Structs para as arestas do grafo
 * 
 * \author AndreFreitas
 * \date   May 2023
 *********************************************************************/

#ifndef Aresta_H
#define Aresta_H

#include "Vertice.h"

#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS

#define N 50
#define M 70

typedef struct Aresta {
	int id;		            
	float distancia;		// Peso da aresta
	struct Aresta* next;
}Aresta;

typedef struct ArestaFile {
	int idOrigem;
	int idDestino;
	float distancia;
} ArestaFile;


void ImprimeArestas(Aresta* h);
float CalcularPontosGeoreferenciados(float lat1, float lng1, float lat2, float lng2);
Aresta* CriaAresta(int id, float distancia);
Aresta* InsereAresta(Aresta* h, Aresta* novo, bool* res);
Vertice* InsereArestaVertice(Vertice* vertice, char* origem, char* dest, float peso, bool* res);
Aresta* RemoveAresta(Aresta* h, int id, bool* res);
bool ProcuraArestaId(Aresta* h, int id);

#endif