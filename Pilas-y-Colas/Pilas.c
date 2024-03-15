#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int info;
    struct nodo *siguiente;
};

void insertar_nodo(struct nodo **raiz, int valor){
    struct nodo *nuevo;
    nuevo = malloc(sizeof(struct nodo));
    nuevo->info = valor;
    if (*raiz == NULL) {
        *raiz = nuevo;
        nuevo->siguiente = NULL;
    } 
    else {
        nuevo->siguiente = *raiz;
        *raiz = nuevo;
    }
}

int extraer_nodo(struct nodo **raiz){
    struct nodo *temporal = *raiz;
    if (temporal == NULL) {
        printf("La pila está vacía.\n");
        return -1;
    } 
    else {
        int informacion = temporal->info;
        struct nodo *borrar = temporal;
        temporal = temporal->siguiente;
        free(borrar);
        *raiz = temporal;
        return informacion;
    }
}

int vacia(struct nodo *raiz){
    if (raiz == NULL)
        return 1;
    else
        return 0;
}

void imprimir(struct nodo **raiz){
    struct nodo *temporal = NULL;
    int valor = 0;
    int posicion = 1;
    if (*raiz == NULL) {
        printf("La pila está vacía.\n");
    } 
    else {
        printf("=======Informacion===========\n");
        while(vacia(*raiz) == 0){
            valor = extraer_nodo(raiz);
            printf("Posición %i\n\t----> %i\n", posicion, valor);
            printf("-----------------------------\n");
            insertar_nodo(&temporal, valor);
            posicion++;
        }
        printf("===========Fin===============\n");
        while(vacia(temporal) == 0){
            insertar_nodo(raiz, extraer_nodo(&temporal));
        }
        
    }
}

void liberar(struct nodo **raiz){
    while (vacia(*raiz) == 0) {
        extraer_nodo(raiz);
    }
    printf("La pila ha sido liberada.\n");
}

int cantidad(struct nodo **raiz){
    struct nodo *temporal = NULL;
    int cantidad = 0;
    while (vacia(*raiz) == 0) {
        insertar_nodo(&temporal, extraer_nodo(raiz));
        cantidad++;
    }
    while (vacia(temporal) == 0) {
        insertar_nodo(raiz, extraer_nodo(&temporal));
    }
    return cantidad;
}

void eliminar_posicion(struct nodo **raiz){
    struct nodo *temporal = NULL;
    int posicion = 0;
    int cant = cantidad(raiz);
    printf("Indique la posición a eliminar:\n");
    scanf("%d", &posicion);
    if (posicion <= 0 || posicion > cant) {
        printf("Posición inválida.\n");
    }
    else {
        for (int i = 1; i < posicion; i++) {
            insertar_nodo(&temporal, extraer_nodo(raiz));
        }
        extraer_nodo(raiz);
        while (vacia(temporal) == 0) {
            insertar_nodo(raiz, extraer_nodo(&temporal));
        }
        printf("Elemento eliminado.\n");
    }    
}

void insertar_posicion(struct nodo **raiz){
    struct nodo *temporal = NULL;
    int posicion = 0;
    int valor = 0;
    int cant = cantidad(raiz);
    printf("Indique la posición a insertar:\n");
    scanf("%d", &posicion);
    if (posicion <= 0 || posicion > cant) {
        printf("Posición inválida.\n");
    }
    else {
        printf("Indique el valor a insertar:\n");
        scanf("%d", &valor);
        for (int i = 1; i < posicion; i++) {
            insertar_nodo(&temporal, extraer_nodo(raiz));
        }
        insertar_nodo(raiz, valor);
        while (vacia(temporal) == 0) {
            insertar_nodo(raiz, extraer_nodo(&temporal));
        }
        printf("Elemento insertado.\n");
    }
}

int main(){
    struct nodo *raiz = NULL;
    int op = 0, valor = 0;
    do {
        printf("Menu\n");
        printf("-> 1. Insertar\n");
        printf("-> 2. Extraer\n");
        printf("-> 3. Mostrar\n");
        printf("-> 4. Cantidad\n");
        printf("-> 5. Limpiar\n");
        printf("-> 6. Eliminar en posición\n");
        printf("-> 7. Insertar en posición\n");
        printf("-> 0. Salir\n");
        printf("Escoja una opción:\n");
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("Indique valor:\n");
                scanf("%d", &valor);
                insertar_nodo(&raiz, valor);
                break;
            case 2:
                printf("Eliminamos nodo de la Pila: %i\n", extraer_nodo(&raiz));
                break;
            case 3:
                imprimir(&raiz);
                break;  
            case 4:
                printf("Cantidad de nodos en la pila: %d\n", cantidad(&raiz));
                break;
            case 5:
                liberar(&raiz);
                break;
            case 6:
                eliminar_posicion(&raiz);
                break;
            case 7:
                insertar_posicion(&raiz);
                break;
            case 0:
                printf("Ha salido del programa\n");
                break;
            default:
                printf("Opción inválida\n");
                break;
        }
    } while (op != 0);
    return 0;
}
