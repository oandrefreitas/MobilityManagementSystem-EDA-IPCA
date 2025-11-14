/*****************************************************************//**
 * \file   Auxiliares.c
 * \brief  
 * 
 * \author AndreFreitas
 * \date   May 2023
 *********************************************************************/

#include "Auxiliares.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

// Função para realizar o login
int LoginGestor() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Solicitar o nome de utilizador ao utilizador
    printf("Digite o nome de utilizador: ");
    scanf("%s", username);

    // Verificar o nome de utilizador
    if (strcmp(username, "GestorIPCA") != 0) {
        printf("Nome de utilizador invalido.\n");
        return 0;  // Retornar 0 para indicar falha no login
    }

    // Solicita a palavra-passe ao utilizador
    printf("Digite a palavra-passe: ");
    scanf("%s", password);

    // Verificar a palavra-passe
    if (strcmp(password, "20ipca23") == 0) {
        printf("Login bem-sucedido!\n");
        return 1;  // Retorna 1 caso login bem-sucedido
    }
    else {
        printf("Palavra-passe invalida.\n");
        return 0;  // Retorna 0 caso falha no login
    }
}

int LoginCliente() {
    int nif;
    printf("Digite o seu NIF: ");
    scanf("%d", &nif);

    Cliente* cliente = EncontrarClienteNIF(nif);
    if (cliente == NULL) {
        return 0; // Termina a função e retorna 0
    }

    return 1; // Retorna 1 para indicar que o cliente foi autenticado
}

// Função para gravar os dados do novo cliente no arquivo Cliente.bin
void GravarNovoCliente(Cliente* novoCliente) {
    FILE* fp = fopen("Cliente.bin", "wb");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo Cliente.bin!\n");
        return;
    }

    fwrite(novoCliente, sizeof(Cliente), 1, fp);

    fclose(fp);

    free(novoCliente);
}

// Função para gravar os dados da edição de cliente no arquivo Cliente.bin
void GravarEditCliente(Cliente* listaClientes, int id, int nif, float saldo, char nome[], char morada[]) {
    FILE* fp = fopen("Cliente.bin", "wb");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo Cliente.bin!\n");
        return;
    }

    // Percorre a lista de clientes e grava as edições do cliente com o id especificado
    Cliente* atual = listaClientes;
    while (atual != NULL) {
        if (atual->id == id) {
            atual->nif = nif;
            atual->saldo = saldo;
            strncpy(atual->nome, nome, N - 1);
            strncpy(atual->morada, morada, M - 1);
        }

        // Grava o cliente atual no arquivo
        fwrite(atual, sizeof(Cliente), 1, fp);

        atual = atual->next;
    }

    fclose(fp);
}



// Função para gravar os dados do novo veiculo no arquivo Veiculo.txt
void GravarVeiculoNovo(Veiculo* novoVeiculo) {
    FILE* fp = fopen("Veiculo.txt", "a");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo Veiculo.txt!\n");
        return;
    }

    fprintf(fp, "%d,%s,%s,%s,%.2f,%.2f\n", novoVeiculo->id, novoVeiculo->matricula, novoVeiculo->meio, novoVeiculo->localizacao, novoVeiculo->autonomia, novoVeiculo->custo);

    fclose(fp);

    free(novoVeiculo);
}

// Função para gravar os dados da edição de veiculos no arquivo Veiculo.txt
void GravarEditVeiculo() {
    FILE* fp = fopen("Veiculo.txt", "a+");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo Veiculo.txt!\n");
        return;
    }

    Veiculo* atual = listaVeiculos;
    while (atual != NULL) {
        fprintf(fp, "%d,%s,%s,%s,%.2f,%.2f\n", atual->id, atual->matricula, atual->meio, atual->localizacao, atual->autonomia, atual->custo);
        atual = atual->next;
    }
    fclose(fp);
}


// Função para gravar os dados do novo aluguer no arquivo Aluguer.bin
void GravarNovoAluguer(Aluguer* novoAluguer) {
    FILE* fp = fopen("Aluguer.bin", "ab");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo Aluguer.bin!\n");
        return;
    }

    fwrite(novoAluguer, sizeof(Aluguer), 1, fp);

    fclose(fp);
}

int GravarVertice(Vertice* grafo) {
    FILE* fp;
    int resultado;

    fp = fopen("Vertice.bin", "ab");
    if (fp == NULL) return -1;

    resultado = fwrite(grafo, sizeof(Vertice), 1, fp);
    fclose(fp);

    if (resultado != 1) return -1;

    return 1;
}

int GravarAresta(Aresta* h, int idOrigem) {
    char* fileName = "Aresta.bin";
    FILE* fp;
    int resultado;

    if (h == NULL) return -2;
    fp = fopen(fileName, "ab");
    if (fp == NULL) return -1;

    Aresta* aux = h;
    while (aux) {
        ArestaFile auxFile;
        auxFile.idOrigem = idOrigem;
        auxFile.idDestino = aux->id;
        auxFile.distancia = aux->distancia;
        resultado = fwrite(&auxFile, sizeof(ArestaFile), 1, fp);
        if (resultado != 1) {
            // Tratar erro ao gravar aresta
        }
        aux = aux->next;
    }

    fclose(fp);
    return 1;
}

Vertice* LoadVertice(Vertice* h, bool* res) {
    *res = false;
    FILE* fp = fopen("Vertice.bin", "rb");
    if (fp == NULL) return NULL;
    Vertice aux;
    while (fread(&aux, sizeof(Vertice), 1, fp)) {
        Vertice* novo = CriaVertice(aux.id, aux.localidade, aux.disponibilidade, aux.lat, aux.lng);
        if (novo == NULL) {
            fclose(fp);
            return h;
        }
        h = InsereVertice(h, novo, res);
        if (!*res) {
            fclose(fp);
            return h;
        }
    }
    fclose(fp);
    *res = true;
    return h;
}

void LoadAresta(Vertice* grafo, bool* res) {
    *res = false;
    FILE* fp = fopen("Aresta.bin", "rb");
    if (fp == NULL) return;
    ArestaFile aux;
    while (fread(&aux, sizeof(ArestaFile), 1, fp)) {
        Vertice* origem = ProcuraVerticeId(grafo, aux.idOrigem);
        Vertice* destino = ProcuraVerticeId(grafo, aux.idDestino);
        if (origem != NULL && destino != NULL) {
            Aresta* novaAresta = CriaAresta(destino->id, aux.distancia, origem->id);
            origem->arestas = InsereAresta(origem->arestas, novaAresta, res);
            if (!*res) {
                fclose(fp);
                return;
            }
        }
    }
    fclose(fp);
    *res = true;
}
