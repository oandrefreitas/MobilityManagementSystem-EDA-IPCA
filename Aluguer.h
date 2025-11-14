/*****************************************************************//**
 * \file   Aluguer.h
 * \brief  Struct para armazenar o aluguer de veiculos de transporte de mobilidade elétrica - Trabalho EDA
 * 
 * \author AndreFreitas
 * \date   March 2023
 *********************************************************************/

#ifndef ALUGUER_H
#define ALUGUER_H

#include <stdbool.h>
#include "Vertice.h"

#define _CRT_SECURE_NO_WARNINGS

#define N 50
#define M 70

typedef struct Aluguer {
	int id;
	int nifCliente;
	char matriculaVeiculo[N];
	float custoTotal;
	char origem[N];
	char destino[N];
	char dataInicio[N];
	char dataFim[N];
	struct Aluguer* next;
}Aluguer;

void ImprimeAlugueres();
int CalcularDuracaoAluguer(char dataInicio[], char dataFim[]);
void ObterInformacoesCliente(float* clienteLat, float* clienteLng, char* origem, char* destino);
void AdicionarAluguer(Vertice** listaVertices, Veiculo* listaVeiculos, Aluguer* listaAlugueres, char matriculaVeiculo[], int nifCliente, char dataInicio[], char dataFim[]);
void RemoverAluguer(int id);
void EncontrarAluguerID(int id);

#endif