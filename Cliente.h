/*****************************************************************//**
 * \file   Cliente.h
 * \brief  Struct para armazenar clientes de veiculos de transporte de mobilidade elétrica - Trabalho EDA
 * 
 * \author AndreFreitas
 * \date   March 2023
 *********************************************************************/

#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS

#define N 50
#define M 70

typedef struct Cliente {
    int id;
    int nif;
    float saldo;
    char nome[N];
    char morada[M];
    struct Cliente* next;
} Cliente;

void ImprimeClientes();
Cliente* AdicionarCliente(Cliente* listaClientes, int nif, float saldo, char nome[], char morada[]);
void RemoverCliente(int id);
void EditarCliente(int id);
void EncontrarClienteID(int id);
Cliente* EncontrarClienteNIF(int nif);
void CarregarSaldo(int nif, float valor);

#endif