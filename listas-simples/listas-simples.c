#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo {
    int id;
    char nombre[30];
    struct nodo *siguiente;
};

struct nodo_disco {
    int id;
    char nombre[30];
};

void agregar_nodo(struct nodo **primero){
    struct nodo *nuevo;
    nuevo = malloc(sizeof(struct nodo));
    printf("Ingrese la id:\n");
    scanf("%d", &nuevo->id);
    fflush(stdin);
    printf("Ingrese el nombre:\n");
    gets(nuevo->nombre);
    if(*primero == NULL){
        nuevo-> siguiente = NULL;
        *primero = nuevo;
        printf("Nodo ingresado correctamente\n");
    }
    else{
        struct nodo *temp = *primero;
        while (temp -> siguiente != NULL){
            temp = temp ->siguiente;
        }
        nuevo ->siguiente = NULL;
        temp ->siguiente = nuevo;
        printf("Nodo ingresado correctamente\n");
    }
}

void agregar_nodo_pos(struct nodo **primero){
    struct nodo *nuevo;
    int posicion = 1, posicion_actual = 1;
    nuevo = malloc(sizeof(struct nodo));
    printf("Ingrese la id:\n");
    scanf("%d", &nuevo->id);
    fflush(stdin);
    printf("Ingrese el nombre:\n");
    gets(nuevo->nombre);
    printf("Ingrese la poscion en la que desea agregar el nodo:\n");
    scanf("%d", &posicion);
    if(*primero == NULL){
        nuevo-> siguiente = NULL;
        *primero = nuevo;
    }
    else{
        if (posicion_actual == posicion){
            nuevo ->siguiente = *primero;
            *primero = nuevo;
            printf("Nodo ingresado correctamente\n");
        }
        else{
            struct nodo *temp = *primero;
            while(posicion_actual < posicion){
                if (temp == NULL){
                    printf("No se encuentra la posicion\n");
                    break;
                }
                else { 
                    temp = temp->siguiente;
                    posicion_actual++;
                }
            }
            if (temp != NULL){
                nuevo -> siguiente = temp -> siguiente;
                temp -> siguiente = nuevo;
                printf("Nodo ingresado correctamente\n");
            }
        
        }
    }
}

void agregar_nodo_id(struct nodo **primero){
    struct nodo *nuevo;
    int id = 0;
    nuevo = malloc(sizeof(struct nodo));
    printf("Ingrese la id:\n");
    scanf("%d", &nuevo->id);
    fflush(stdin);
    printf("Ingrese el nombre:\n");
    gets(nuevo->nombre);
    printf("Ingrese el id de la persona anterior donde ingresara el nodo:\n");
    scanf("%d", &id);
    if(*primero == NULL){
        nuevo-> siguiente = NULL;
        *primero = nuevo;
        printf("Nodo ingresado correctamente\n");
    }
    else{
        struct nodo *temp = *primero;
            while(temp != NULL && temp -> id != id){
                    temp = temp ->siguiente;
            }
            if (temp == NULL){
                printf("No se encuentra la id\n");
            }
            else{
                nuevo -> siguiente = temp -> siguiente;
                temp -> siguiente = nuevo;
                printf("Nodo ingresado correctamente\n");
            }
    }
    
}

void eliminar_nodo(struct nodo **primero){
    struct nodo *temp = *primero;
    int posicion = 1, posicion_actual = 1;
    printf("Ingrese la poscion en la que desea eliminar el nodo:\n");
    scanf("%d", &posicion);
    if(*primero == NULL){
        printf("Lista vacia");      
    }
    else{
        if (posicion == posicion_actual){
            *primero = temp ->siguiente;
            free(temp);
        }
        else{
            struct nodo *temp2 = temp;
            while(temp2 != NULL && posicion_actual < posicion){
                temp = temp2;
                temp2 = temp2->siguiente;
                posicion_actual++;
            }
            if (temp2 == NULL){
                printf("No se encuentra la posicion\n");
            }
            else {
                temp->siguiente = temp2->siguiente;
                free(temp2);
                printf("Nodo eliminado\n");
            }
        }
    }
}

void eliminar_nodo_id(struct nodo **primero){
    struct nodo *temp = *primero;
    int id = 0;
    printf("Ingrese el id del nodo que desea eliminar:\n");
    scanf("%d", &id);
    if(*primero == NULL){
        printf("Lista vacia");      
    }
    else{
        if (temp->id == id){
            *primero = temp ->siguiente;
            free(temp);
        }
        else{
            struct nodo *temp2 = temp;
            while(temp2 != NULL && temp2 ->id != id){
                temp = temp2;
                temp2 = temp2->siguiente;
            }
            if (temp2 == NULL){
                printf("No se encuentra la id\n");
            }
            else {
                temp->siguiente = temp2->siguiente;
                free(temp2);
                printf("Nodo eliminado\n");
            }
        }
    }
}

void imprimir_datos(struct nodo *primero){
    struct nodo *temp = primero;
    int n = 1;
    if (primero == NULL){
        printf("No hay datos en la lista\n");
    }
    else {
        printf("|==================DATOS ALMECENADOS EN MEMORIA ================|\n");
        while (temp != NULL){
            printf("Nodo %d\n", n);
            printf("\t===> ID: %d\n", temp->id);
            printf("\t===> NOMBRE: %s\n", temp->nombre);
            printf("----------------------------\n");
            temp = temp -> siguiente;
            n++;
        }
        printf("|========================FIN DE LA LISTA========================|\n");
    }
}

void vaciar_lista(struct nodo **primero){
    struct nodo *temp = *primero;
    if (temp == NULL){
        printf("Lista vacia\n");
    }
    else {
        struct nodo *temp2 = temp;
        while (temp != NULL){
            temp2 = temp;
            temp = temp ->siguiente;
            free(temp2);
        }
        *primero = temp;
        printf("Lista vaciada correctamente\n");
    }
}

void intercambiar_contenido(struct nodo **primero){
    struct nodo *temp = *primero;
    char nombre_aux[30];
    int id_aux = 0, posicion_1 = 1, posicion_2 = 1, posicion_actual = 1;
    printf("Ingrese la primera posicion a intercambiar:\n");
    scanf("%d", &posicion_1);
    printf("Ingrese la segunda posicion a intercambiar:\n");
    scanf("%d", &posicion_2);
    if (posicion_1 > posicion_2){
        posicion_actual = posicion_2;
        posicion_2 = posicion_1;
        posicion_1 = posicion_actual;
    }
    posicion_actual = 1;
    if (temp == NULL){
        printf("La lista esta vacia\n");
    }
    else if (posicion_1 == posicion_2){
        printf("Misma posicion\n");
    }
    else {
        struct nodo *temp2 = temp;
        while (temp != NULL && posicion_actual < posicion_1){
            temp = temp ->siguiente;
            posicion_actual++;
        }
        temp2 = temp;
        while (temp2 != NULL && posicion_actual < posicion_2){
            temp2 = temp2 ->siguiente;
            posicion_actual++;
        }
        if (temp == NULL || temp2 == NULL){
            printf("No se encontraron los nodos\n");
        }
        else{
            id_aux = temp2->id;
            strcpy(nombre_aux,temp2->nombre);
            temp2->id = temp ->id;
            strcpy(temp2->nombre,temp->nombre);
            temp->id = id_aux;
            strcpy(temp->nombre,nombre_aux);
            printf("Contenido intercambiado correctamente\n");
        }
    }
}

void intercambiar_nodos(struct nodo **primero){
    struct nodo *temp = *primero;
    char nombre_aux[30];
    int id_aux = 0, posicion_1 = 1, posicion_2 = 1, posicion_actual = 1;
    printf("Ingrese la primera posicion a intercambiar:\n");
    scanf("%d", &posicion_1);
    printf("Ingrese la segunda posicion a intercambiar:\n");
    scanf("%d", &posicion_2);
    if (posicion_1 > posicion_2){
        posicion_actual = posicion_2;
        posicion_2 = posicion_1;
        posicion_1 = posicion_actual;
    }
    posicion_actual = 1;
    if (posicion_actual == posicion_1){
        struct nodo *temp2 = temp;
        struct nodo *temp3 = temp;
        struct nodo *temp4 = temp;
        while(temp2 != NULL && posicion_actual < posicion_2){
            temp3 = temp2;
            temp2 = temp2   -> siguiente;
            posicion_actual++;
        }
        if (temp2 == NULL){
            printf("No se encontro la posicion\n");
        }
        else {
            temp3 ->siguiente = temp;
            temp4 = temp2->siguiente;
            temp2 ->siguiente = temp ->siguiente;
            temp -> siguiente = temp4;
            *primero = temp2;
            printf("Intercambio realizado\n");
        }
    }
    else if(posicion_1 == posicion_2 - 1){
        struct nodo *temp2 = temp;
        struct nodo *temp3 = temp;
        struct nodo *temp4 = temp;
        while (temp != NULL && posicion_actual<posicion_1){
            temp3 = temp;
            temp = temp->siguiente;
            posicion_actual++;
        }
        if (temp == NULL){
            printf("No se encuentra la posicion\n");
        }
        else{
            temp2 = temp;
            while (temp2 != NULL && posicion_actual<posicion_2){
                temp2 = temp2->siguiente;
                posicion_actual++;
            }
            if (temp2 == NULL){
                printf("No se encuentra la posicion\n");
            }
            else {
                temp4 = temp2 ->siguiente;
                temp3 ->siguiente = temp2;
                temp2 ->siguiente = temp;
                temp ->siguiente = temp4;
                printf("Intercambio realizado\n");
            }
        }
    }
    else{
        struct nodo *temp2 = temp;
        struct nodo *temp3 = temp;
        struct nodo *temp4 = temp;
        struct nodo *temp5 = temp;
        while (temp != NULL && posicion_actual<posicion_1){
            temp3 = temp;
            temp = temp->siguiente;
            posicion_actual++;
        }
        if (temp == NULL){
            printf("No se encuentra la posicion\n");
        }
        else{
            temp2 = temp;
            temp4 = temp;
            while (temp2 != NULL && posicion_actual<posicion_2){
                temp4 = temp2;
                temp2 = temp2->siguiente;
                posicion_actual++;
            }
            if (temp2 == NULL){
                printf("No se encuentra la posicion\n");
            }
            else {
                temp5 = temp2->siguiente;
                temp3 ->siguiente = temp2;
                temp2 -> siguiente = temp ->siguiente;
                temp4 ->siguiente = temp;
                temp ->siguiente = temp5;
                printf("Intercambio realizado\n");
            }
        }

    }
}

void guardar_datos(struct nodo *primero){
    struct nodo *datos = primero;
    FILE *archivo;
    archivo = fopen("datos.bin", "wb");
    if (archivo == NULL){
        printf("Error al abrir el archivo\n");
    }
    
    while(datos != NULL){
        struct nodo_disco nodo_guardado;
        nodo_guardado.id = datos ->id;
        strcpy(nodo_guardado.nombre,datos->nombre);

        fwrite(&nodo_guardado, sizeof(nodo_guardado), 1, archivo);
        datos = datos ->siguiente;
    }

    printf("Datos guardados correctamnte\n");

    fclose(archivo);
}

void recuperar_datos(struct nodo **primero){
    FILE *archivo;
    archivo = fopen("datos.bin", "rb");
    if (archivo == NULL){
        printf("Error al abrir el archivo\n");
    }
    struct nodo_disco nodo_guardado;
    while (fread(&nodo_guardado, sizeof(struct nodo_disco),1,archivo) == 1){
        struct nodo *datos = malloc(sizeof(struct nodo));
        if (datos == NULL){
            printf("No hay datos en la lista\n");
            fclose(archivo);
            return;
        }
        datos ->id = nodo_guardado.id;
        strcpy(datos->nombre,nodo_guardado.nombre);
        datos->siguiente = NULL;
        if (*primero == NULL){
            *primero = datos;
        }
        else{
            struct nodo *temp = *primero;
            while (temp->siguiente != NULL){
                temp = temp->siguiente;
            }
            temp ->siguiente = datos;
        }
    }

    printf("Datos recuperados\n");
    fclose(archivo);
}

int main(){
    struct nodo *primero = NULL;
    int op = 0;
    //Menu
    do {
        printf("¿Que desea hacer?\n");
        printf("-> 1. Agregar nodo\n");
        printf("-> 2. Agregar nodo en una posicion\n");
        printf("-> 3. Agregar nodo despues de una persona\n");
        printf("-> 4. Eliminar nodo en una posicion\n");
        printf("-> 5. Eliminar nodo por id\n");
        printf("-> 6. Mostrar lista\n");
        printf("-> 7. Vaciar lista\n");
        printf("-> 8. Intercambiar contenido\n");
        printf("-> 9. Intercambiar posiciones\n");
        printf("-> 10. Guardar datos\n");
        printf("-> 11. Recuperar datos\n");
        printf("-> 0. Salir\n");
        scanf("%d", &op);
        switch(op){
            case 1:
                agregar_nodo(&primero);
                break;
            case 2:
                agregar_nodo_pos(&primero);
                break;
            case 3:
                agregar_nodo_id(&primero);
                break;
            case 4:
                eliminar_nodo(&primero);
                break;
            case 5:
                eliminar_nodo_id(&primero);
                break;
            case 6:
                imprimir_datos(primero);  
                break;
            case 7:
                vaciar_lista(&primero);
                break;
            case 8:
                intercambiar_contenido(&primero);
                break;
            case 9:
                intercambiar_nodos(&primero);
                break;
            case 10:
                guardar_datos(primero);
                break;
            case 11:
                recuperar_datos(&primero);
                break;
            case 0:
                printf("Se ha cerrado el programa\n");
                break;
        }
    } while (op != 0);
    return 0;
}
