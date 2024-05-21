#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char entrada[100];
    char pilha[100] = {'0'};
    int cont = 0;

    while (scanf("%s", entrada) != EOF) {
        cont = 0;

        for (int i = 0; entrada[i] != '\0'; i++) {
            if (cont == 0) {
                pilha[cont] = entrada[i];
                cont++;
            } else {
                if (pilha[cont - 1] == entrada[i]) {
                    pilha[cont] = entrada[i];
                    cont++;
                } else {
                    pilha[cont] = '0';
                    cont--;
                }
            }

            if(cont == 0) printf("nil\n");
            else{
                // Imprime os elementos da pilha
                for (int i = 0; i < cont; i++) {
                    if(cont == 0) printf("nil\n");
                    else printf("%c", toupper(pilha[i]));
                }
                printf("\n"); // Adiciona uma nova linha após a impressão  
            }
        }
    
        if(cont == 0) printf("Aceito\n");
        else printf("Rejeito\n");

        printf("\n");
    }

    return 0;
}