#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void readAndPrint();

void main() {
    readAndPrint();

    printf("David => %u\n", hashFunction("71185239D"));
    printf("Pedro => %u\n", hashFunction("123456789A"));
    printf("Juan => %u\n", hashFunction("123456789B"));
    printf("Carlos => %u\n", hashFunction("123456789C"));
    printf("Luis => %u\n", hashFunction("123456789D"));
}

void readAndPrint() {
    FILE *datosPrueba = fopen("datosPrueba.txt", "r");
    int c;

    if ((datosPrueba == NULL)) {
        printf("Imposible abrir el ficheros\n");
    } else {
        while ((c = fgetc(datosPrueba)) != EOF) {
            putchar(c);
        }

        if (fclose(datosPrueba) != 0) {
            printf("Imposible cerrar el fichero\n");
        }
    }
}

unsigned int hashFunction(char *ID) {
    unsigned long hash = 0;
    int c;

    while (c = *ID++) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    hash = hash % MAX_SIZE;
    return hash;
}