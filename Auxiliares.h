/*****************************************************************//**
 * \file   Auxiliares.h
 * \brief  
 * 
 * \author AndreFreitas
 * \date   May 2023
 *********************************************************************/

#ifndef AUXILIARES_H
#define AUXILIARES_H

#include "Vertice.h"
#include "Aresta.h"

#include "Cliente.h"
#include "Veiculo.h"
#include "Aluguer.h"

#define _CRT_SECURE_NO_WARNINGS

extern Cliente* listaClientes;
extern Veiculo* listaVeiculos;
extern Aluguer* listaAlugueres;

int LoginGestor();
int LoginCliente();
void GravarNovoCliente(Cliente* novoCliente);
void GravarEditCliente(Cliente* listaClientes, int id, int nif, float saldo, char nome[], char morada[]);
void GravarVeiculoNovo(Veiculo* novoVeiculo);
void GravarEditVeiculo();
void GravarNovoAluguer(Aluguer* novoAluguer);
int GravarVertice(Vertice* grafo);
int GravarAresta(Aresta* h, int idOrigem);
Vertice* LoadVertice(Vertice* h, bool* res);
void LoadAresta(Vertice* grafo, bool* res);

#endif