#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo {
    char nombre[100];
    int anio;
    struct nodo *izq;
    struct nodo *der;
};

struct nodo* raiz = NULL;

int posicionar(struct nodo** actual, struct nodo* nuevo) {
    if (*actual == NULL) {
        *actual = nuevo;
        return 1;
    }
    if (nuevo->anio < (*actual)->anio) {
        return posicionar(&((*actual)->izq), nuevo);
    } else if (nuevo->anio > (*actual)->anio) {
        return posicionar(&((*actual)->der), nuevo);
    } else {
        printf("\n[!] El a\u00f1o de producci\u00f3n ya existe.\n");
        return 0;
    }
}

void registrar() {
    struct nodo* nuevo = (struct nodo*) malloc(sizeof(struct nodo));
    printf("Nombre de la pel\u00edcula: ");
    getchar(); // limpiar buffer
    fgets(nuevo->nombre, 100, stdin);
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = 0; // eliminar salto de l\u00ednea
    printf("A\u00f1o de producci\u00f3n: ");
    scanf("%d", &nuevo->anio);
    nuevo->izq = nuevo->der = NULL;

    posicionar(&raiz, nuevo);
}

void mostrar(struct nodo* actual) {
    if (actual != NULL) {
        mostrar(actual->izq);
        printf("\nNombre: %s\nA\u00f1o: %d\n", actual->nombre, actual->anio);
        mostrar(actual->der);
    }
}

struct nodo* encontrarMinimo(struct nodo* actual) {
    while (actual->izq != NULL)
        actual = actual->izq;
    return actual;
}

struct nodo* eliminar(struct nodo* actual, char nombre[]) {
    if (actual == NULL) return NULL;

    int cmp = strcmp(nombre, actual->nombre);
    if (cmp < 0) {
        actual->izq = eliminar(actual->izq, nombre);
    } else if (cmp > 0) {
        actual->der = eliminar(actual->der, nombre);
    } else {
        if (actual->izq == NULL && actual->der == NULL) {
            free(actual);
            return NULL;
        } else if (actual->izq == NULL) {
            struct nodo* temp = actual->der;
            free(actual);
            return temp;
        } else if (actual->der == NULL) {
            struct nodo* temp = actual->izq;
            free(actual);
            return temp;
        } else {
            struct nodo* sucesor = encontrarMinimo(actual->der);
            strcpy(actual->nombre, sucesor->nombre);
            actual->anio = sucesor->anio;
            actual->der = eliminar(actual->der, sucesor->nombre);
        }
    }
    return actual;
}

void eliminarNodo() {
    char nombre[100];
    printf("Nombre de la pel\u00edcula a eliminar: ");
    getchar(); // limpiar buffer
    fgets(nombre, 100, stdin);
    nombre[strcspn(nombre, "\n")] = 0; // eliminar salto de l\u00ednea
    raiz = eliminar(raiz, nombre);
}

int main() {
    int opcion;
    do {
        printf("\n1. Registrar pel\u00edcula\n");
        printf("2. Mostrar \u00e1rbol\n");
        printf("3. Eliminar por nombre\n");
        printf("4. Salir\n");
        printf("Opci\u00f3n: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: registrar(); break;
            case 2: mostrar(raiz); break;
            case 3: eliminarNodo(); break;
        }
    } while (opcion != 4);

    return 0;
}
