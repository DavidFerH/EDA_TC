#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 10

typedef struct {
    char nombre[255];
    char ID[9];
    char vehiculo[255];
    char matricula[7];
} cliente;

cliente * hashTable[MAX_SIZE];

bool hashTableInit();
bool comprobarRegistro(char *ID);
unsigned int hashFunction(char *ID);
bool insertarCliente();
// void mostrarClientes();

void main() {
    hashTableInit();

    cliente David = {.nombre = "David", .ID = "12345678D", .vehiculo = "Porsche Macan", .matricula = "7256LCK"};
    cliente Pablo = {.nombre = "Pablo", .ID = "12345678Z", .vehiculo = "Porsche Panamera", .matricula = "1212LCS"};
    cliente Pedro = {.nombre = "Pedro", .ID = "12345678B", .vehiculo = "Tesla Model Y", .matricula = "7234LLL"};
    cliente Juan = {.nombre = "Juan", .ID = "12345678C", .vehiculo = "Ferrari LaFerrari", .matricula = "2563LRM"};

    insertarCliente(&David);
    insertarCliente(&Pablo);
    insertarCliente(&Pedro);
    insertarCliente(&Juan);

    // mostrarClientes();
}

/*
    - Inicializacion de la tabla hash de tamaño 'MAX_SIZE' a null -
    Mediante un bucle for recorremos todas las posiciones de la tabla y les asignamos el valor null
*/

bool hashTableInit() {
    for (int i = 0; i < MAX_SIZE; i++){
        hashTable[i] = NULL;
    }
}

/*
    - Creación del hash para almacenar los datos en memoria -
    Mediante la utilización de un algoritmo de hash ya existente (sdbm - http://www.cse.yorku.ca/~oz/hash.html#:~:text=If%20you%20just%20want%20to,K%26R%5B1%5D%2C%20etc.)
*/

unsigned int hashFunction(char *ID) {
    unsigned long hash = 0;
    int c;

    while (c = *ID++) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    hash = hash % MAX_SIZE;
    return hash;
}

/*
    - Inserción del cliente en la tabla hash -
*/

bool insertarCliente(cliente *cli) {
    if (cli == NULL) return false;

    int index = hashFunction(cli->ID);
    if (hashTable[index] != NULL) {
        return false;
    }

    hashTable[index] = cli;

    return true;
}

// void mostrarClientes() {
//     printf("\tListado de clientes:\n");

//     for (int i = 0; i < MAX_SIZE; i++){
//         if (hashTable[i] != NULL) {
//             printf("\t%i\t%s\n", (i + 1), hashTable[i]->nombre);
//         } else {
//             printf("\t%i\t----\n", (i + 1));
//         }
//     }
// }