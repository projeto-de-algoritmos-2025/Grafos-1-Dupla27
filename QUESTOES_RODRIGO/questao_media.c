#include <stdio.h>
#include <string.h>

//Queremos principalmente ler as entradas, sendo essas compostas de linhas
//com duas strings, descobrindo a pós ordem por meio da pré, inordem e da
//raiz.

void fazerPosOrdem(char* preordem, char* inordem, int n) {
    if (n == 0) return;
    char raiz = preordem[0];

    int i;
    for (i = 0; i < n; i++) {
        if (inordem[i] == raiz)
            break;
    }
    
    // Com isso, temos as raizes da Preordem e da Inordem. Agora, vamos
    // chamar recursivamente a função pra percorrer as strings, e imprimir
    // as raizes, até compor a ordem da Pós Ordem.

    // Esquerda
    fazerPosOrdem(preordem + 1, inordem, i);

    // Direita
    fazerPosOrdem(preordem + i + 1, inordem + i + 1, n - i - 1);

    putchar(raiz);
}

int main() {
    char preordem[27], inordem[27];
    //número máximo de caracteres, como as strings são compostas de 
    //letras do alfabeto

    while (scanf("%s %s", preordem, inordem) == 2) {
        int len = strlen(preordem);
        fazerPosOrdem(preordem, inordem, len);
        putchar('\n');
    }

    return 0;
}
