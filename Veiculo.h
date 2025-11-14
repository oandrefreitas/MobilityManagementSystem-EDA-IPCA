/*****************************************************************//**
 * \file   Veiculo.h
 * \brief  Struct para armazenar veículos de mobilidade elétrica - Trabalho EDA
 * 
 * \author AndreFreitas
 * \date   March 2023
 *********************************************************************/

#ifndef VEICULO_H
#define VEICULO_H

#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS

#define N 50
#define M 70

typedef struct Veiculo {
    int id;
    char matricula[N];
    char meio[N];
    char localizacao[M];
    float autonomia;
    float custo;
    struct Veiculo* next;
} Veiculo;

void ImprimeVeiculos();
Veiculo* AdicionarVeiculo(char matricula[], char meio[], char localizacao[], float autonomia, float custo);
void RemoverVeiculo(int id);
void EditarVeiculo(int id);
void ImprimeAutoDecre(Veiculo* listaVeiculos);
void ImprimeVeiculosLocalizacao(char localizacao[]);
void EncontrarVeiculoID(int id);
Veiculo* EncontrarVeiculoMatricula(Veiculo* listaVeiculos, char matricula[]);
Veiculo* EncontraVeiculo(Vertice* atual, Veiculo* veiculos);

#endif