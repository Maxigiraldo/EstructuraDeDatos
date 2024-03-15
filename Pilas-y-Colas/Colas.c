#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int info;
    struct nodo *sig;
};

int vacia(struct nodo *cabeza){
    if  (cabeza == NULL){
        return 1;
    }
    else {
        return 0;
    }
}

void insertar_nodo(struct nodo **cabeza, struct nodo **cola, int valor){
    struct nodo *nuevo;
    nuevo = malloc(sizeof(struct nodo));
    nuevo->info = valor;
    nuevo->sig = NULL;
    if (*cabeza == NULL){
        *cabeza = nuevo;
        *cola = nuevo;
    }
    else {
        (*cola)->sig = nuevo;
        *cola = nuevo;
    }
}

int extraer_nodo(struct nodo **cabeza, struct nodo **cola){
    struct nodo *temp = *cabeza;
    int valor = 0;
    if (vacia(*cabeza) != 1){
        valor = temp ->info;
        if (*cabeza == *cola){
            *cabeza = NULL;
            *cola = NULL;
        }
        else {
            *cabeza = temp ->sig;
        }
        free(temp);
        return valor;
    }
    else {
        return -1;
    }
}

void imprimir_cola(struct nodo **cabeza, struct nodo **cola){
    struct nodo *temp = NULL;
    int valor = 0, posicion = 1;
    if (*cabeza == NULL){
        printf("--La cola esta vacia--\n");
    }
    else {
        printf("======Datos======\n");
        while (vacia(*cabeza) != 1){
            valor = extraer_nodo(cabeza, cola);
            printf("-Posicion %d:\n", posicion);
            printf("\t> %d", valor);
            printf("\n-----------------\n");
            insertar_nodo(&temp, cola, valor);
            posicion++;
        }
        printf("=========Fin==========\n");
        while (temp != NULL){
            valor = extraer_nodo(&temp, cola);
            insertar_nodo(cabeza, cola, valor);
        }
    }
}

void vaciar(struct nodo **cabeza, struct nodo **cola){
    if (vacia(*cabeza) == 1){
        printf("La cola esta vacia");
    }
    else {
        while(vacia(*cabeza) != 1){
            extraer_nodo(cabeza, cola);
        }
    }
    printf("Cola vaciada\n");
}

int cantidad(struct nodo **cabeza, struct nodo **cola){
    struct nodo *temp = NULL;
    int cantidad_nodos = 0, valor = 0;
    if (vacia(*cabeza) == 1){
        return cantidad_nodos;
    }
    else {
        while(vacia(*cabeza) != 1){
            valor = extraer_nodo(cabeza, cola);
            insertar_nodo(&temp, cola, valor);
            cantidad_nodos++;
        }
        while(temp != NULL){
            valor = extraer_nodo(&temp, cola);
            insertar_nodo(cabeza, cola, valor);
        }
        return cantidad_nodos;
    }
}

void eliminar_posicion(struct nodo **cabeza, struct nodo **cola){
    struct nodo *temp = NULL;
    int cantidad_nodos = cantidad(cabeza, cola);
    int posicion = 0;
    printf("Ingrese la posicion que desea eliminar:\n");
    scanf("%d", &posicion);
    if (*cabeza == NULL){
        printf("Cola vacia\n");
    }
    else if (posicion < 1 || posicion > cantidad_nodos){
        printf("Posicion no encontrada\n");
    }
    else {
        for (int i = 1; i < posicion; i++){
            insertar_nodo(&temp, cola, extraer_nodo(cabeza, cola));
        }
        extraer_nodo(cabeza, cola);
        while (vacia(*cabeza) != 1){
            insertar_nodo(&temp, cola, extraer_nodo(cabeza, cola));
        }
        *cabeza = temp;
        printf("Nodo eliminado correctamente\n");
    }
}

void insertar_posicion(struct nodo **cabeza, struct nodo **cola){
    struct nodo *temp = NULL;
    int cantidad_nodos = cantidad(cabeza, cola);
    int posicion = 0, valor = 0;
    printf("Ingrese el valor:\n");
    scanf("%d", &valor);
    printf("Ingrese la posicion que desea insertar el nodo:\n");
    scanf("%d", &posicion);
    if (*cabeza == NULL){
        printf("Cola vacia\n");
    }
    else if (posicion < 1 || posicion > cantidad_nodos){
        printf("Posicion no encontrada\n");
    }
    else {
        for (int i = 1; i < posicion; i++){
            insertar_nodo(&temp, cola, extraer_nodo(cabeza, cola));
        }
        insertar_nodo(&temp, cola, valor);
        while (vacia(*cabeza) != 1){
            insertar_nodo(&temp, cola, extraer_nodo(cabeza, cola));
        }
        *cabeza = temp;
        printf("Nodo insertado correctamente\n");
    }
}

int main(){
    struct nodo *cabeza = NULL;
    struct nodo *cola = NULL;
    int op = 0, valor = 0;
    do {
        printf("===========Menu===============\n");
        printf("--> 1. Insertar nodo\n");
        printf("--> 2. Extraer nodo\n");
        printf("--> 3. Imprimir cola\n");
        printf("--> 4. Vaciar cola\n");
        printf("--> 5. Verificar si hay datos\n");
        printf("--> 6. Eliminar nodo en una poicion\n");
        printf("--> 7. Insertar en posicion\n");
        printf("--> 0. Salir");
        printf("\nEscoja una opcion:\n");
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("Ingrese el valor a agregar:\n");
                scanf("%d", &valor);
                insertar_nodo(&cabeza, &cola, valor);
                printf("Nodo insertado correctamente\n");
                break;
            case 2:
                printf("El nodo extraido fue: %i\n", extraer_nodo(&cabeza, &cola));
                break;
            case 3:
                imprimir_cola(&cabeza, &cola);
                break;
            case 4:
                vaciar(&cabeza, &cola);
                break;
            case 5:
                if (vacia(cabeza) == 1){
                    printf("Cola vacia\n");
                }
                else {
                    printf("Cola con datos\n");
                }
                break;  
            case 6:
                eliminar_posicion(&cabeza, &cola);
                break;  
            case 7:
                insertar_posicion(&cabeza, &cola);
                break;
            case 0:
                printf("Cerrando...\n");
                break;
            default:
                printf("Esa opcion no es valida\n");
                break;
        }
    } while (op != 0);
}
