//Por Maximiliano Giraldo Ocampo
#include <stdio.h>
#include <stdlib.h>

//Estructura de un nodo
struct nodo {
    int id;
    char nombre[30];
    struct nodo *siguiente;
};

//Funcion para agregar un nodo en una posicion
void agregar_nodo_lista(struct nodo **primero){
    //Se crea un nuevo nodo
    struct nodo *nuevo;
    //Variables para la posicion
    int posicion_actual = 0, posicion = 0;
    //Se reserva memoria para el nuevo nodo
    nuevo = malloc(sizeof(struct nodo));
    //Se piden los datos del nuevo nodo
    printf("Ingrese el id:\n");
    scanf("%d", &nuevo->id);
    fflush(stdin);
    printf("Ingrese su nombre:\n");
    gets(nuevo->nombre);
    //Se pide la posicion en la que se quiere agregar el nodo
    printf("Ingrese la posicion en la que desea agregar el nodo:\n");
    scanf("%d", &posicion);
    //Si la lista está vacia, se agrega el nodo al principio
    if (*primero == NULL){
        nuevo -> siguiente = NULL;
        *primero = nuevo;
    }
    //Si la lista no está vacia, se recorre la lista hasta llegar a la posicion deseada
    else{
        struct nodo *temp = *primero;
        while(temp != NULL){
            if(posicion == 0){
                nuevo -> siguiente = temp;
                *primero = nuevo;
                break;
            }
            else if(posicion_actual == posicion - 1){
                nuevo -> siguiente = temp -> siguiente;
                temp -> siguiente = nuevo;
                break;
            }
            else{
                temp = temp -> siguiente;
                posicion_actual++;
            }
        }
    }
}

//Funcion para agregar un nodo despues de una persona
void agregar_nodo_id(struct nodo **primero){
    struct nodo *nuevo;
    int id_temp = 0;
    nuevo = malloc(sizeof(struct nodo));
    printf("Ingrese el id:\n");
    scanf("%d", &nuevo->id);
    fflush(stdin);
    printf("Ingrese su nombre:\n");
    gets(nuevo->nombre);
    //Se pide la ID anterior al nodo que se quiere agregar
    printf("Ingrese la ID anterior al nodo que desea agregar");
    scanf("%d", &id_temp);
    //Si la lista está vacia, se agrega el nodo al principio
    if (*primero == NULL){
        nuevo -> siguiente = NULL;
        *primero = nuevo;
    }
    //Si la lista no está vacia, se recorre la lista hasta llegar a la ID deseada
    else{
        struct nodo *temp = *primero;
        while(temp != NULL){
            if(temp->id == id_temp && temp->siguiente != NULL){
                nuevo -> siguiente = temp -> siguiente;
                temp -> siguiente = nuevo;
                break;
            }
            else if(temp->id == id_temp && temp->siguiente == NULL){
                temp -> siguiente = nuevo;
                nuevo -> siguiente = NULL;
                break;
            }
            else{
                temp = temp -> siguiente;
            }
        }
    }
}

//Funcion para eliminar un nodo en una posicion
void eliminar_nodo_lista(struct nodo **primero){
    int posicion_actual = 0, posicion = 0;
    printf("Ingrese la posicion en la que desea eliminar el nodo:\n");
    scanf("%d", &posicion);
    if (*primero == NULL){
        printf("La lista está vacia\n");
    }
    //Si la lista no está vacia, se recorre la lista hasta llegar a la posicion deseada
    else{
        struct nodo *temp = *primero;
        while(temp != NULL){
            if(posicion == 0){
                *primero = temp -> siguiente;
                free(temp);
                break;
            }
            else if(posicion_actual == posicion - 1){
                struct nodo *temp2 = temp -> siguiente;
                temp -> siguiente = temp2 -> siguiente;
                free(temp2);
                break;
            }
            else{
                temp = temp -> siguiente;
                posicion_actual++;
            }
        }
    }
}

//Funcion para eliminar un nodo despues de una persona
void eliminar_nodo_id(struct nodo **primero){
    int id_temp = 0;
    printf("Ingrese la ID anterior del nodo que desea eliminar:\n");
    scanf("%d", &id_temp);
    if (*primero == NULL){
        printf("La lista está vacia\n");
    }
    //Si la lista no está vacia, se recorre la lista hasta llegar a la ID deseada
    else{
        struct nodo *temp = *primero;
        while(temp != NULL){
            if(temp->id == id_temp && temp->siguiente != NULL){
                struct nodo *temp2 = temp -> siguiente;
                temp -> siguiente = temp2 -> siguiente;
                free(temp2);
                break;
            }
            else if(temp->id == id_temp && temp->siguiente == NULL){
                free(temp);
                break;
            }
            else{
                temp = temp -> siguiente;
            }
        }
    }
}

//Funcion para imprimir los datos de la lista
void imprimir_datos_lista(struct nodo *primero){
    struct nodo *temp = primero;
    if (primero == NULL){
            printf("La lista está vacia\n");
        }
    //Si la lista no está vacia, se recorre la lista e imprime los datos
    else{
        while(temp != NULL){
            printf("ID: %d\n", temp -> id);
            printf("NOMBRE: %s\n", temp -> nombre);
            temp = temp -> siguiente;
        }
        printf("\n");
    }
   
}

//Funcion principal
int main(){
    struct nodo *primero = NULL;
    int op = 0;
    //Menu
    do {
        printf("¿Que desea hacer?\n");
        printf("1. Agregar nodo en una posicion\n");
        printf("2. Agregar nodo despues de una persona\n");
        printf("3. Eliminar nodo en una posicion\n");
        printf("4. Eliminar nodo despues de una persona\n");
        printf("5. Mostrar lista\n");
        printf("0. Salir\n");
        scanf("%d", &op);
        switch(op){
            case 1:
                agregar_nodo_lista(&primero);
                break;
            case 2:
                agregar_nodo_id(&primero);
                break;
            case 3:
                eliminar_nodo_lista(&primero);
                break;
            case 4:
                eliminar_nodo_id(&primero);
                break;
            case 5:
                imprimir_datos_lista(primero);  
                break;
            case 0:
                printf("Se ha cerrado el programa\n");
                break;
        }
    } while (op != 0);
    return 0;
}