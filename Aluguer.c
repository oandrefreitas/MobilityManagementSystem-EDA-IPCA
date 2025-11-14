/*****************************************************************//**
 * \file   Aluguer.c
 * \brief  Funções relativas ao aluguer de veiculos de mobilidade elétrica - Trabalho EDA
 * 
 * \author AndreFreitas
 * \date   March 2023
 *********************************************************************/

#include "Auxiliares.h"

#include "Cliente.h"
#include "Veiculo.h"
#include "Aluguer.h"

#include "Vertice.h"
#include "Aresta.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS

extern int totalVertices; // Declaração da variável global definida em outro arquivo
extern Vertice* listaVertices;
Aluguer* listaAlugueres = NULL;
static int totalAlugueres = 0;
Veiculo* veiculo;

// Função para imprimir todos os alugueres registados
void ImprimeAlugueres() {
    if (listaAlugueres == NULL) {
        printf("Nenhum aluguer registado.\n");
        return;
    }

    Aluguer* atual = listaAlugueres;
    while (atual != NULL) {
        printf("ID: %d\n", atual->id);
        printf("NIF Cliente: %d\n", atual->nifCliente);
        printf("Matrícula Veículo: %s\n", atual->matriculaVeiculo);
        printf("Custo Total: %.2f\n", atual->custoTotal);
        printf("Origem: %s\n", atual->origem);
        printf("Destino: %s\n\n", atual->destino);
        printf("Data de Início: %s\n", atual->dataInicio);
        printf("Data de Fim: %s\n", atual->dataFim);

        atual = atual->next;
    }
}

// Função para calcular a duração do aluguer
int CalcularDuracaoAluguer(const char dataInicio[], const char dataFim[]) {
    struct tm tmInicio, tmFim;
    memset(&tmInicio, 0, sizeof(struct tm));  // Garante que todos os campos da estrutura estejam corretamente definidos.
    memset(&tmFim, 0, sizeof(struct tm));

    sscanf(dataInicio, "%d/%d/%d", &tmInicio.tm_mday, &tmInicio.tm_mon, &tmInicio.tm_year);
    sscanf(dataFim, "%d/%d/%d", &tmFim.tm_mday, &tmFim.tm_mon, &tmFim.tm_year);

    tmInicio.tm_mon -= 1; // Os meses em tm_mom são indexados a partir de 0 (janeiro = 0)
    tmFim.tm_mon -= 1;

    time_t timeInicio = mktime(&tmInicio);
    time_t timeFim = mktime(&tmFim);
    double diferenca = difftime(timeFim, timeInicio);
    int duracao = (int)(diferenca / (24 * 60 * 60)); // Conversão de segundos para dias

    return duracao;
}

void ObterInformacoesCliente(float* clienteLat, float* clienteLng, char* origem, char* destino) {
    printf("Digite a latitude da sua localizacao: ");
    scanf("%f", clienteLat);

    printf("Digite a longitude da sua localizacao: ");
    scanf("%f", clienteLng);

    printf("Escolha o ponto de recolha (origem):\n");
    ImprimeVertice(listaVertices);  // Chama a função para imprimir os vértices registrados
    printf("Digite o nome do ponto de recolha (origem): ");
    scanf("%s", origem);

    printf("Escolha o ponto de recolha (destino):\n");
    ImprimeVertice(listaVertices);  // Chama a função para imprimir os vértices registrados
    printf("Digite o nome do ponto de recolha (destino): ");
    scanf("%s", destino);
}

void AdicionarAluguer(Vertice** listaVertices, Veiculo* listaVeiculos, Aluguer* listaAlugueres, char matriculaVeiculo[], int nifCliente, char dataInicio[], char dataFim[]) {
    float clienteLat, clienteLng;
    char origem[N], destino[N];

    ObterInformacoesCliente(&clienteLat, &clienteLng, origem, destino);
    // Encontrar o veiculo com a matricula especificada
    Veiculo* veiculo = EncontrarVeiculoMatricula(listaVeiculos, matriculaVeiculo);
    if (veiculo == NULL) {
        printf("Veiculo com matricula %s nao encontrado.\n", matriculaVeiculo);
        return;
    }

    // Verificar o saldo do cliente
    Cliente* cliente = EncontrarClienteNIF(nifCliente);
    if (cliente == NULL) {
        printf("Cliente com NIF %d nao encontrado.\n", nifCliente);
        return;
    }
    if (cliente->saldo < veiculo->custo) {
        printf("Saldo Indisponivel. Saldo atual: %.2f\n", cliente->saldo);
        return;
    }

    // Criar um novo vertice na localizacao do cliente
    Vertice* clienteVertice = CriaVertice(totalVertices + 1, "Cliente", 1, clienteLat, clienteLng);
    if (clienteVertice == NULL) {
        printf("Erro ao criar o vertice na localizacao do cliente.\n");
        return;
    }

    // Inserir o vertice da localizacao do cliente no grafo
    bool insercaoSucesso = false;
    *listaVertices = InsereVertice(*listaVertices, clienteVertice, &insercaoSucesso);
    if (!insercaoSucesso) {
        printf("Erro ao inserir o vertice da localizacao do cliente no grafo.\n");
        free(clienteVertice);
        return;
    }

    // Encontrar os vertices de origem e destino
    Vertice* origemVertice = ProcuraVerticeLocal(*listaVertices, origem);
    Vertice* destinoVertice = ProcuraVerticeLocal(*listaVertices, destino);
    if (origemVertice == NULL || destinoVertice == NULL) {
        printf("Origem ou destino invalido.\n");
        return;
    }

    // Criar uma aresta entre o vertice na localizacao do cliente e o ponto de recolha de origem
    bool insercaoArestaSucesso = false;
    float distancia = CalcularPontosGeoreferenciados(clienteLat, clienteLng, origemVertice->lat, origemVertice->lng);
    origemVertice->arestas = InsereArestaVertice(origemVertice->arestas, clienteVertice, origemVertice->localidade, distancia, &insercaoArestaSucesso);
    if (!insercaoArestaSucesso) {
        printf("Erro ao criar a aresta entre a localizacao do cliente e o ponto de recolha de origem.\n");
        return;
    }

    // Calcular a duracao do aluguer
    int duracaoAluguer = CalcularDuracaoAluguer(dataInicio, dataFim);

    // Calcular o custo total do aluguer
    float custoTotal = veiculo->custo * duracaoAluguer;

    // Verificar se o cliente tem saldo suficiente
    if (cliente->saldo < custoTotal) {
        printf("Saldo Indisponivel. Saldo atual: %.2f\n", cliente->saldo);
        return;
    }

    // Descontar o valor do saldo do cliente
    cliente->saldo -= custoTotal;
    printf("%.2f saldo descontado.\n", custoTotal);

    // Criar um novo aluguer
    Aluguer* novoAluguer = (Aluguer*)malloc(sizeof(Aluguer));
    if (novoAluguer == NULL) {
        printf("Erro ao alocar memoria para o novo aluguer.\n");
        return;
    }

    novoAluguer->id = ++totalAlugueres;
    novoAluguer->nifCliente = nifCliente;
    strcpy(novoAluguer->matriculaVeiculo, matriculaVeiculo);
    strcpy(novoAluguer->origem, origem);
    strcpy(novoAluguer->destino, destino);
    strcpy(novoAluguer->dataInicio, dataInicio);
    strcpy(novoAluguer->dataFim, dataFim);
    novoAluguer->custoTotal = custoTotal;
    novoAluguer->next = NULL;

    // Verificar se a lista de alugueres está vazia
    if (listaAlugueres == NULL) {
        listaAlugueres = novoAluguer;
    }
    else {
        // Encontra o último aluguer na lista
        Aluguer* atual = listaAlugueres;
        while (atual->next != NULL) {
            atual = atual->next;
        }

        // Adiciona o novo aluguer como próximo aluguer do último
        atual->next = novoAluguer;
    }

    // Atualizar a disponibilidade de veículos nos pontos de recolha
    origemVertice->disponibilidade--;
    destinoVertice->disponibilidade++;

    // Gravar o novo aluguer no ficheiro bin
    GravarNovoAluguer(novoAluguer);

    // Mostrar o caminho ao cliente
    char caminho[N];
    int contador = 0;

    bool existeCaminho = ExisteCaminho(*listaVertices, origem, destino, caminho, &contador);
    if (existeCaminho) {
        printf("Caminho sugerido para o cliente:\n");
        for (int i = 0; i < contador; i++) {
            printf("%d. %s -> %s\n", i + 1, caminho[i], caminho[i + 1]);
        }
    }
    else {
        printf("Nao existe caminho entre a origem e o destino.\n");
    }

    printf("Aluguer registado com sucesso.\n");
}


// Função para remover um aluguer com um ID especificado
void RemoverAluguer(int id) {
    if (listaAlugueres == NULL) {
        printf("Nenhum aluguer registado.\n");
        return;
    }

    if (listaAlugueres->id == id) {
        Aluguer* temp = listaAlugueres;
        listaAlugueres = listaAlugueres->next;
        free(temp);
        printf("Aluguer removido com sucesso.\n");
        return;
    }

    Aluguer* atual = listaAlugueres->next;
    Aluguer* anterior = listaAlugueres;
    while (atual != NULL) {
        if (atual->id == id) {
            anterior->next = atual->next;
            free(atual);
            printf("Aluguer removido com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->next;
    }

    printf("Aluguer com ID %d nao encontrado.\n", id);
}

// Função para encontrar um aluguer com um ID especificado
void EncontrarAluguerID(int id) {
    Aluguer* atual = listaAlugueres;
    while (atual != NULL) {
        if (atual->id == id) {
            printf("ID: %d\n", atual->id);
            printf("NIF Cliente: %d\n", atual->nifCliente);
            printf("Matrícula Veículo: %s\n", atual->matriculaVeiculo);
            printf("Custo Total: %.2f\n", atual->custoTotal);
            printf("Origem: %s\n", atual->origem);
            printf("Destino: %s\n\n", atual->destino);
            printf("Data de Início: %s\n", atual->dataInicio);
            printf("Data de Fim: %s\n", atual->dataFim);
            return;
        }
        atual = atual->next;
    }

    printf("Aluguer com ID %d não encontrado.\n", id);
}