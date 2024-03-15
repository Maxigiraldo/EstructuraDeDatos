#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int info;
    struct nodo *sig;
};

int vacia(struct nodo *raiz){
    if (raiz == NULL)
        return 1;
    else
        return 0;
}

void insertar_nodo(struct nodo **raiz, struct nodo **fondo, int valor){
    struct nodo *nuevo;
    nuevo = malloc(sizeof(struct nodo));
    nuevo->info = valor;
    nuevo->sig = NULL;
    if (vacia(*raiz) == 0){
        (*raiz)->sig = nuevo;
        (*fondo)->sig = nuevo;
    }
    else{
        (*fondo)->sig = nuevo;
        *fondo = nuevo;
    }
    printf("Nodo ingresado\n");
}

int extraer_nodo(struct nodo **raiz){
    struct nodo *temporal = *raiz;
    if (temporal == NULL) {
        printf("La cola está vacía.\n");
        return -1;
    } 
    else {
        int informacion = temporal->info;
        struct nodo *borrar = temporal;
        temporal = temporal->sig;
        free(borrar);
        *raiz = temporal;
        return informacion;
    }
}

void imprimir(struct nodo **raiz, struct nodo **fondo){
    struct nodo *temporal = NULL;
    int valor = 0;
    int posicion = 1;
    if (*raiz == NULL) {
        printf("La cola está vacía.\n");
    } 
    else {
        printf("=======Informacion===========\n");
        while(vacia(*raiz) == 0){
            valor = extraer_nodo(raiz);
            printf("Posición %i\n\t----> %i\n", posicion, valor);
            printf("-----------------------------\n");
            insertar_nodo(&temporal, fondo, valor);
            posicion++;
        }
        while(vacia(temporal) == 0){
            insertar_nodo(raiz, fondo, extraer_nodo(&temporal));
        }
    }
}

int cantidad(struct nodo **raiz){
    struct nodo *temporal = NULL;
    int cant = 0;
    while (vacia(*raiz) == 0) {
        insertar_nodo(&temporal, raiz, extraer_nodo(raiz));
        cant++;
    }
    while (vacia(temporal) == 0) {
        insertar_nodo(raiz, &temporal, extraer_nodo(&temporal));
    }
    return cant;
}

void liberar(struct nodo **raiz){
    while (vacia(*raiz) == 0) {
        extraer_nodo(raiz);
    }
    printf("La cola ha sido vaciada\n");
}

void eliminar_posicion(struct nodo **raiz, int posicion){
    struct nodo *temporal = NULL;
    int cant = cantidad(raiz);
    if (posicion <= 0 || posicion > cant) {
        printf("Posición inválida.\n");
        return;
    }
    for (int i = 1; i < posicion; i++) {
        insertar_nodo(&temporal, raiz, extraer_nodo(raiz));
    }
    extraer_nodo(raiz);
    while (vacia(temporal) == 0) {
        insertar_nodo(raiz, &temporal, extraer_nodo(&temporal));
    }
}

void insertar_posicion(struct nodo **raiz){
    struct nodo *temporal = NULL;
    int posicion = 0;
    int valor = 0;
    int cant = cantidad(raiz);
    if (posicion <= 0 || posicion > cant + 1) {
        printf("Posición inválida.\n");
        return;
    }
    for (int i = 1; i < posicion; i++) {
        insertar_nodo(&temporal, raiz, extraer_nodo(raiz));
    }
    while (vacia(temporal) == 0) {
        insertar_nodo(raiz, &temporal, extraer_nodo(&temporal));
    }

}

int main(){
    struct nodo *raiz = NULL;
    struct nodo *fondo = NULL;
    int op = 0, valor = 0;
    do {
        printf("-> 1. Ingresar nodo\n"); 
        printf("-> 2. Extraer nodo\n");
        printf("-> 3. Imprimir cola\n");
        printf("-> 4. Vaciar cola\n");
        printf("-> 5. Ver si esta vacia la cola\n");
        printf("-> 6. Eliminar posicion\n");
        printf("-> 7. Insertar posicion\n");
        printf("0. Salir\n");
        printf("Escoja una opción:\n");
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("Ingrese el valor:\n");
                scanf("%d", &valor);
                insertar_nodo(&raiz, &fondo, valor);
                break;
            case 2:
                printf("Nodo extraído: %d\n", extraer_nodo(&raiz));
                break;
            case 3:
                imprimir(&raiz, &fondo);
                break;
            case 4:
                liberar(&raiz);
                break;
            case 5:
                if (vacia(raiz) == 0)
                    printf("La cola tiene información\n");
                else
                    printf("La cola está vacía\n");
                break;
            case 6:
                eliminar_posicion(&raiz, valor);
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
