/*****************************************************************//**
 * \file   Cliente.c
 * \brief  Funções relativas a clientes de veiculos de mobilidade elétrica - Trabalho EDA
 * 
 * \author AndreFreitas
 * \date   March 2023
 *********************************************************************/

#include "Auxiliares.h"

#include "Cliente.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

Cliente* listaClientes = NULL;
static int totalClientes = 0;

// Função para imprimir lista de clientes
void ImprimeClientes() {
    Cliente* atual = listaClientes;
    while (atual != NULL) {
        printf("ID: %d\n", atual->id);
        printf("NIF: %d\n", atual->nif);
        printf("Saldo: %.2f\n", atual->saldo);
        printf("Nome: %s\n", atual->nome);
        printf("Morada: %s\n", atual->morada);
        printf("\n");
        atual = atual->next;
    }
}

// Função para adicionar um novo cliente
Cliente* AdicionarCliente(Cliente* listaClientes, int nif, float saldo, char nome[], char morada[]) {

    Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente));
    if (novoCliente == NULL) {
        printf("Erro ao alocar memoria!\n");
        return listaClientes;
    }

    // Preenche os dados do novo cliente
    novoCliente->id = ++totalClientes;
    novoCliente->nif = nif;
    novoCliente->saldo = saldo;
    strncpy(novoCliente->nome, nome, N - 1);
    strncpy(novoCliente->morada, morada, M - 1);
    novoCliente->next = NULL;

    // Adiciona o novo cliente à lista de clientes
    if (listaClientes == NULL) {        // se a lista está vazia, o novo cliente é o primeiro da lista
        listaClientes = novoCliente;
    }
    else {                              // caso contrário, adiciona o novo cliente no final da lista
        Cliente* atual = listaClientes;
        while (atual->next != NULL) {   // procura o último nó da lista
            atual = atual->next;
        }
        atual->next = novoCliente;      // adiciona o novo cliente ao final da lista
    }

    GravarNovoCliente(novoCliente);     // grava os dados do novo cliente no arquivo

    return novoCliente; // retorna o novo cliente adicionado
}

// Função para remover um cliente
void RemoverCliente(int id) {
    // Percorre a lista de clientes procurando pelo cliente com o ID indicado
    Cliente* clienteAtual = listaClientes;
    Cliente* clienteAnterior = NULL;
    while (clienteAtual != NULL && clienteAtual->id != id) {
        clienteAnterior = clienteAtual;
        clienteAtual = clienteAtual->next;
    }

    // Se o cliente foi encontrado, remove-o da lista
    if (clienteAtual != NULL) {
        if (clienteAnterior == NULL) {
            listaClientes = clienteAtual->next;
        }
        else {
            clienteAnterior->next = clienteAtual->next;
        }
        free(clienteAtual);
        printf("Cliente com ID %d removido com sucesso!\n", id);

        // Atualiza o valor de totalClientes
        totalClientes--;
    }
    else {
        printf("Cliente com ID %d nao encontrado!\n", id);
    }
}

// Função para editar um cliente
void EditarCliente(int id) {
    Cliente* atual = listaClientes;
    while (atual != NULL) {
        if (atual->id == id) {
            // Atualiza os dados do cliente
            int novoNif = 201201227; // Novo NIF
            float novoSaldo = 1500.0; // Novo saldo
            char novoNome[N] = "Joana Costa Silva"; // Novo nome
            char novaMorada[M] = "Rua da Aventura"; // Nova morada
            atual->nif = novoNif;
            atual->saldo = novoSaldo;
            strncpy(atual->nome, novoNome, N - 1);
            strncpy(atual->morada, novaMorada, M - 1);

            // Grava as alterações no arquivo Cliente.bin
            GravarEditCliente(listaClientes, atual->id, atual->nif, atual->saldo, atual->nome, atual->morada);
            return;
        }
        atual = atual->next;
    }
    printf("Cliente com o ID %d nao encontrado.\n", id);
}

// Função para encontrar um cliente pelo ID e imprimir suas informações
void EncontrarClienteID(int id) {
    Cliente* atual = listaClientes;
    while (atual != NULL) {
        if (atual->id == id) {
            printf("Cliente encontrado:\n");
            printf("ID: %d\n", atual->id);
            printf("NIF: %d\n", atual->nif);
            printf("Saldo: %.2f\n", atual->saldo);
            printf("Nome: %s\n", atual->nome);
            printf("Morada: %s\n", atual->morada);
            return;
        }
        atual = atual->next;
    }
    printf("Cliente com o ID %d nao encontrado.\n", id);
}

// Função para encontrar um cliente pelo NIF e imprimir suas informações
Cliente* EncontrarClienteNIF(int nif) {
    Cliente* atual = listaClientes;
    while (atual != NULL) {
        if (atual->nif == nif) {
            printf("Cliente encontrado:\n");
            printf("ID: %d\n", atual->id);
            printf("NIF: %d\n", atual->nif);
            printf("Saldo: %.2f\n", atual->saldo);
            printf("Nome: %s\n", atual->nome);
            printf("Morada: %s\n", atual->morada);
            return atual;  // Retorna o apontador para o cliente encontrado
        }
        atual = atual->next;
    }
    printf("Cliente com NIF %d nao encontrado.\n", nif);
    return NULL;  // Retornar NULL se o cliente não for encontrado
}

void CarregarSaldo(int nif, float valor) {
    Cliente* atual = listaClientes;
    while (atual != NULL) {
        if (atual->nif == nif) {
            atual->saldo += valor; // Adiciona o valor ao saldo do cliente
            printf("Saldo carregado com sucesso!\n");
            printf("Novo saldo: %.2f\n", atual->saldo);
            return;
        }
        atual = atual->next;
    }
    printf("Cliente com o NIF %d nao encontrado.\n", nif);
}