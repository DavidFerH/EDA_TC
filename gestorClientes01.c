#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 1000

typedef struct {
    char * nombre;
    char * ID;
    char * vehiculo;
    char * matricula; 
} cliente;

cliente * hashTable[MAX_SIZE];

int precargado=0;

bool hashTableInit();
bool comprobarRegistro(char *ID);
unsigned int hashFunction(char *ID);
bool insertarCliente();
void mostrarClientePorID(char dni[]);
void mostrarClientes();
void ficheroClientes ();
void precargarDatos();
void buscarCliente();
void mostrarMenu();

void main() {
    hashTableInit();    
    mostrarMenu();
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

    while (c = *ID ++) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    hash = hash % MAX_SIZE;
    return hash;
}

/* 
    Método que obtiene y muestra el cliente por el ID (dni) dado
*/

void mostrarClientePorID(char dni[]) {
    /* obtenemos el hash a partir del ID (DNI) */
    unsigned long hash = hashFunction(dni);  
    cliente * cli = NULL;

   /* Si se encuentra un valor */
    while(hashTable[hash] != NULL) {
        if(strcmp(hashTable[hash]->ID, dni) == 0) {
            cli = hashTable[hash];
            break;
        } 
                
        /* Hay conflicto ya que el guardado no es el buscado. Miramos el siguiente */
        ++ hash;
            
        /* Si llegasemos al final empezaríamos de nuevo al inicio */
        hash %= MAX_SIZE;
    } 

    if(cli !=NULL){
        printf("Se ha podido encontrar un cliente con dni %s y cuyos datos son:",dni);
        printf("\n\t Clave Nombre: %s ",cli->nombre);
        printf("\n\t Clave ID (DNI): %s ",cli->ID);
        printf("\n\t Clave Vehículo: %s ",cli->vehiculo);
        printf("\n\t Clave Matrícula: %s ",cli->matricula);

    }
    else{
        printf("\nNo se ha podido encontrar un cliente con ID %s",dni);
    }

}

/* 
    Metodo auxiliar para inserción de 5 elementos
*/
cliente * create_mock_client() {

    /* Reservar memoria */
    size_t size = sizeof(cliente);
    cliente *item = (cliente *) malloc(size);

    item->ID = "35223223L";
    item->matricula = "4445LYJ";
    item->nombre = "Veronica Bravo Alonso";
    item->vehiculo = "Merchi clase A";

    return item;
}

cliente * create_mock_client2() {
    cliente *item = (cliente*) malloc(sizeof(cliente));
    
    item->ID = "99578421E";
    item->matricula = "C-4527-A";
    item->nombre = "Uxía Llañez Pentecostés";
    item->vehiculo = "Jeep";  

    return item;
}

cliente * create_mock_client3() {
    cliente *item = (cliente*) malloc(sizeof(cliente));
   
    item->ID = "2244558F";
    item->matricula = "8888JHD";
    item->nombre = "Luis Acción Pita";
    item->vehiculo = "Seat Leon";  

    return item;
}

cliente * create_mock_client4() {
    cliente *item = (cliente*) malloc(sizeof(cliente));
    
    item->vehiculo = "Audi TT";  
    item->ID = "44552211G";
    item->matricula = "4455LKJ";
    item->nombre = "Fernando Lopez Rodriguez";

    return item;
}

cliente * create_mock_client5() {
    cliente *item = (cliente*) malloc(sizeof(cliente));
    
    item->vehiculo = "Volvo v40";  
    item->ID = "12345678A";
    item->matricula = "1452FAS";
    item->nombre = "Luis Rodríguez Cagiao";

    return item;
}


/*
    Método para añadir un registro de cliente a la tabla hash
*/

void add_client(cliente *item) {  
    /* Se calcula el hash para saber la posición */
    unsigned long hashIndex = hashFunction(item->ID);
    int posBusc = 0;

    /* solución para colisiones. (En el caso de usarse) */
    while(hashTable[hashIndex] != NULL && strcmp(hashTable[hashIndex]->ID,item->ID)!=0) {
        /* Existe elemento en la posición y no coincide su ID */
        /* se busca la siguiente posición vacía */
        ++ hashIndex;
		
        /* Si se llega al final se empieza desde el principio */
        hashIndex %= MAX_SIZE;

        posBusc++;

        if(posBusc==MAX_SIZE) {
            printf("No ha podido insertarse el elemento ya que la tabla está llena");
            return;
        }
    }
	/* Se almacena */
    hashTable[hashIndex] = item;
}

/* 
    Método para la precarga de 5 clientes 
*/

void precargarDatos(){
    cliente * cliente1 = create_mock_client();
    cliente * cliente2 = create_mock_client2();
    cliente * cliente3 = create_mock_client3();
    cliente * cliente4 = create_mock_client4();
    cliente * cliente5 = create_mock_client5();

    add_client(cliente1);
    add_client(cliente2);
    add_client(cliente3);
    add_client(cliente4);
    add_client(cliente5);
}


/*
    Función para mostrar el listado de clientes registrados en la tabla hasta ese momento.
*/

void mostrarClientes() {
printf("\t\t\t\t Listado de clientes almacenados en la base de datos: \n");
   for(int i = 0; i< MAX_SIZE; i++) {
	   if(hashTable[i] != NULL) {
          printf("CLIENTE %d \n", i);
          printf("Nombre: %s \n", hashTable[i]->nombre);
          printf("DNI: %s \n", hashTable[i]->ID);
          printf("Vehiculo: %s  \n", hashTable[i]->vehiculo);
          printf("Matricula: %s \n", hashTable[i]->matricula);
              printf("\n");
        }
    }
}

/*
    Función para guardar en un fichero los clientes registrados hasta ese momento.
*/

void ficheroClientes () {
    freopen ("clientes.txt", "w", stdout);
    for(int i = 0; i< MAX_SIZE; i++) {
	   if(hashTable[i] != NULL) {
          printf("CLIENTE %d \n", i);
          printf("Nombre: %s \n", hashTable[i]->nombre);
          printf("DNI: %s \n", hashTable[i]->ID);
          printf("Vehiculo: %s  \n", hashTable[i]->vehiculo);
          printf("Matricula: %s \n", hashTable[i]->matricula);
              printf("\n");
        }
    }
    fclose(stdout);
}


/*
    Método que pregunta un DNI para la búsqueda de cliente y lo imprime por pantalla
*/

void buscarCliente() {
    char dni;

    printf("\nBúsqueda de cliente por ID(dni)");
    printf("\nPor favor, indique el DNI del cliente a buscar:");
    scanf("%s",&dni);
    mostrarClientePorID(dni);
}


/*
    Función de menú para escoger las opciones
*/

void mostrarMenu() {
    printf("\n\nPractica de algoritmos\n");
    printf("Elige entre las opciones:\n");

    if(precargado==0) {
        printf("1. Precargar datos de la tabla hash (disponible)\n");
    } else {
        printf("1. Precargar datos de la tabla hash (no disponible)\n");
    }
    
    printf("2. Imprimir clientes de la tabla\n");
    printf("3. Guardar clientes en fichero\n");
    printf("4. Anadir datos de cliente\n");
    printf("5. Buscar cliente por DNI\n");
    printf("6. Salir\n");

    int valor;
    scanf("%d",&valor);

    switch (valor){
        case 1:
            if(precargado==0){ 
                printf("Precargando datos...\n\n");
                precargarDatos();
                precargado=1;
            }else{
                printf("Ya se ha realizado la precarga. Escoja otra opcion\n\n");
            }
            break;

        case 2: 
            printf("Imprimiendo datos de clientes...\n\n");
            mostrarClientes();
            break;

        case 3:
            printf("Guardando datos de clientes en documento de texto...\n\n"); 
            ficheroClientes();
            break;

        case 4:
            printf("Añadiendo datos de un nuevo cliente...\n\n");
            printf("Funcionalidad no realizada");
            break;

        case 5:
            buscarCliente();
            break;

        case 6: 
            return;

        default:
            printf("Has escogido una opción incorrecta\n\n");
       
    }
    mostrarMenu();
}