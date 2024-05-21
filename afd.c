#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct transicao {
    char simbolo;
    struct estado *estado_destino;
};

struct estado {
    int id;
    bool e_inicial;
    bool e_final;
    int num_transicoes;
    struct transicao *transicoes;
};

// Declaração de funções
struct estado* busca_estado(struct estado *estados, int *num_estados, int id) {
    for (int i = 0; i < *num_estados; i++) {
        if (estados[i].id == id) {
            return &estados[i];
        }
    }
    return NULL;
}

struct estado* cria_estado(struct estado *estados, int *num_estados, int id) {
    estados[*num_estados].id = id;
    estados[*num_estados].num_transicoes = 0;
    estados[*num_estados].transicoes = NULL;
    estados[*num_estados].e_inicial = false;
    estados[*num_estados].e_final = false;
    (*num_estados)++;
    return &estados[(*num_estados) - 1];
}

void cria_transicao(struct estado *origem, struct transicao *nova_transicao) {
    int num_transicoes = origem->num_transicoes;

    // Redimensiona o array de transições para acomodar uma nova e a transição nula final
    origem->transicoes = realloc(origem->transicoes, (num_transicoes + 2) * sizeof(struct transicao));
    origem->transicoes[num_transicoes] = *nova_transicao;
    origem->transicoes[num_transicoes + 1].estado_destino = NULL;

    origem->num_transicoes++;
}

bool verifica_entrada(char *entrada, int indice, struct estado *estado_atual) {
    if (entrada[indice] == '\0') {
        return estado_atual->e_final;
    }

    for (int i = 0; i < estado_atual->num_transicoes; i++) {
        if (estado_atual->transicoes[i].simbolo == entrada[indice]) {
            if (verifica_entrada(entrada, indice + 1, estado_atual->transicoes[i].estado_destino)) {
                return true;
            }
        }
    }

    return false;
}


void imprime_estado(struct estado *estado) {
    printf("Estado ID: %d\n", estado->id);
    estado->e_inicial ? printf("E um estado inicial\n") : (void)0;
    estado->e_final ? printf("E um estado final\n") : (void)0;
    printf("Transicoes:\n");
    if (estado->transicoes) {
        int i = 0;
        while (estado->transicoes[i].estado_destino != NULL) {
            printf("    Simbolo: %c, Estado destino ID: %d\n",
                   estado->transicoes[i].simbolo, estado->transicoes[i].estado_destino->id);
            i++;
        }
    } else {
        printf("    Sem transicoes\n");
    }
}

int main() {
    int num_estados, num_estados_add = 0, num_alfabeto;
    scanf("%d", &num_estados);
    scanf("%d", &num_alfabeto);

    // Alocação de memória para os símbolos do alfabeto
    char *simbolos = malloc(num_alfabeto * sizeof(char));

    for (int i = 0; i < num_alfabeto; i++){
        scanf(" %c", &simbolos[i]);
    }

    // Alocação de memória para os estados
    struct estado *estados = malloc(num_estados * sizeof(struct estado));

    for (int i = 0; i < num_estados * num_alfabeto; i++){
        int id_origem, id_destino;
        char simbolo;

        scanf("%d %c %d", &id_origem, &simbolo, &id_destino);

        // printf("%d %c %d\n", id_origem, simbolo, id_destino);

        struct estado *origem = busca_estado(estados, &num_estados_add, id_origem);
        struct estado *destino = busca_estado(estados, &num_estados_add, id_destino);

        if (!origem) origem = cria_estado(estados, &num_estados_add, id_origem);
        if (!destino) destino = cria_estado(estados, &num_estados_add, id_destino);

        struct transicao *nova_transicao = malloc(sizeof(struct transicao));
        nova_transicao->simbolo = simbolo;
        nova_transicao->estado_destino = destino;

        cria_transicao(origem, nova_transicao);

        // printf("Estados adicionados:\n");
        // for (int i = 0; i < num_estados_add; i++){
        //     printf("%d ", estados[i].id);
        // }
        // printf("\n");

        // imprime_estado(origem);
    }

    int estado_inicial_id;
    struct estado *estado_inicial;

    scanf("%d", &estado_inicial_id);
    for (int i = 0; i < num_estados_add; i++){
        if(estados[i].id == estado_inicial_id){
            estados[i].e_inicial = true;
            estado_inicial = &estados[i];
            break;
        }
    }

    int num_estados_finais, estado_final_id;
    scanf("%d", &num_estados_finais);
    for (int i = 0; i < num_estados_finais; i++){
        scanf("%d", &estado_final_id);
        for (int j = 0; j < num_estados_add; j++){
            if(estados[j].id == estado_final_id){
                estados[j].e_final = true;
                break;
            }
        }
    }

    char entrada[100];
    scanf("%s", entrada);

    if (verifica_entrada(entrada, 0, estado_inicial)) printf("Aceito\n");
    else printf("Rejeito\n");

    return 0;
}