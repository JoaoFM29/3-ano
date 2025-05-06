#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("Utilização: %s <nome_do_ficheiro>\n", argv[0]);
        return 1; 
    }
    
    setuid(1000);
    
    FILE *ficheiro = fopen(argv[1], "r");
    if(ficheiro == NULL) {
        perror("Erro ao abrir o ficheiro");
        return 1; 
    }


    int caracter;
    while((caracter = fgetc(ficheiro)) != EOF) {
        putchar(caracter);
    }


    fclose(ficheiro);

    return 0;
}

