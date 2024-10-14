#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct nodo {
    char dato[50];
    struct nodo *siguiente;
} Nodo;

void cargarDatos(FILE *archivo, Nodo **inicio);
Nodo *crearNodo(char contenido[MAX]);
void insertarAlInicio(Nodo **inicio, char contenido[MAX]);
void mostrarLista(Nodo *inicio);
void liberarMemoria(Nodo **inicio);

int main() {
    FILE *archivo;
    Nodo *inicio = NULL;
    char nombreArchivo[MAX];

    printf(" el nombre del archivo: ");
    scanf("%s", nombreArchivo);

    if ((archivo = fopen(nombreArchivo, "r")) == NULL) {
        printf("no se pudo abrir el archivo :(\n");
        exit(0);
    }
    cargarDatos(archivo, &inicio);
    mostrarLista(inicio);

    liberarMemoria(&inicio);
    fclose(archivo);

    return 0;
}

void cargarDatos(FILE *archivo, Nodo **inicio) {
    char linea[MAX];

    while (!feof(archivo)) {
        fgets(linea, MAX, archivo);
        insertarAlInicio(inicio, linea);
    }
}

void insertarAlInicio(Nodo **inicio, char contenido[MAX]) {
    Nodo *nuevoNodo = crearNodo(contenido);
    if (*inicio == NULL) {
        *inicio = nuevoNodo;
    } else {
        nuevoNodo->siguiente = *inicio;
        *inicio = nuevoNodo;
    }
}

Nodo *crearNodo(char contenido[MAX]) {
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));

    if (nuevoNodo) {
        strcpy(nuevoNodo->dato, contenido);
        nuevoNodo->siguiente = NULL;
        return nuevoNodo;
    }

    printf("Error al crear el nodo :(\n");
    exit(0);
}

void mostrarLista(Nodo *inicio) {
    Nodo *actual = inicio;
    while (actual) {
        printf("%s", actual->dato);
        actual = actual->siguiente;
    }
}

void liberarMemoria(Nodo **inicio) {
    Nodo *temporal;
    while (*inicio) {
        temporal = *inicio;
        *inicio = temporal->siguiente;
        free(temporal);
    }
}
