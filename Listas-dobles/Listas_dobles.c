//Presentado por Maximiliano Giraldo Ocampo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declaracion de estructuras
struct nodo {
    struct nodo *anterior;
    int id;
    char nombre[30];
    struct nodo *siguiente;
};

struct nodo_disco {
    int id;
    char nombre[30];
};

//Funcion agregar nodo
void agregar_nodo(struct nodo **primero, struct nodo **ultimo){
    struct nodo *nuevo; //Crear nodo nuevo
    nuevo = malloc(sizeof(struct nodo)); //Reservar memoria
    printf("Ingrese la id:\n"); //Ingresar datos
    scanf("%d", &nuevo->id);
    fflush(stdin);
    printf("Ingrese el nombre:\n");
    gets(nuevo->nombre);
    if(*primero == NULL && *ultimo == NULL){ //Agregar en primera posicion
        nuevo-> siguiente = NULL; //Asignar valores
        nuevo-> anterior = NULL; 
        *primero = nuevo;
        *ultimo = nuevo;
        printf("Nodo ingresado correctamente\n");
    }
    else{ //Agregar en ultima posicion
        nuevo->siguiente = NULL; //Asignar valores
        nuevo->anterior = *ultimo;
        (*ultimo)->siguiente = nuevo;
        *ultimo = nuevo;
        printf("Nodo ingresado correctamente\n");
    }
}

//Funcion agregar por posicion
void agregar_nodo_pos(struct nodo **primero, struct nodo **ultimo){
    struct nodo *nuevo; //Crear nodo nuevo
    int posicion = 1, posicion_actual = 1; //Variables para la posicion
    nuevo = malloc(sizeof(struct nodo)); //Reservar memoria
    printf("Ingrese la id:\n"); //Ingresar datos
    scanf("%d", &nuevo->id); 
    fflush(stdin);
    printf("Ingrese el nombre:\n");
    gets(nuevo->nombre);
    printf("Ingrese la poscion en la que desea agregar el nodo:\n"); //Ingresar posicion
    scanf("%d", &posicion); 
    if(*primero == NULL && *ultimo == NULL){ //Agregar en primera posicion
        printf("Lista vacia se creara la lista\n");
        nuevo-> siguiente = NULL; //Asignar valores
        nuevo-> anterior = NULL;
        *primero = nuevo;
        *ultimo = nuevo;
    }
    else{ //Agregar en una posicion
        if (posicion_actual == posicion){ //Agregar en primera posicion
            nuevo->anterior = (*primero) ->anterior; //Asignar valores
            (*primero) ->anterior = nuevo;
            nuevo ->siguiente = *primero;
            *primero = nuevo;
            printf("Nodo ingresado correctamente\n");
        }
        else{ //Agregar en una posicion diferente a la primera
            struct nodo *temp = *primero;
            while(posicion_actual < posicion){ //Recorrer la lista
                if (temp == NULL){ //Si no se encuentra la posicion
                    printf("No se encuentra la posicion\n");
                    break;
                }
                else { //Si se encuentra la posicion
                    temp = temp->siguiente;
                    posicion_actual++;
                }
            }
            if (temp == NULL){
                printf("La posicion todavia no existe en el sistema\n");
            }
            else if (temp->siguiente == NULL) { //Agregar en ultima posicion
                nuevo ->siguiente = temp; //Asignar valores
                temp->anterior->siguiente = nuevo;
                nuevo->anterior = temp->anterior;
                temp->anterior = nuevo;
            }
            else if (temp != NULL){ //Agregar en una posicion diferente a la primera y ultima
                nuevo -> siguiente = temp; //Asignar valores
                temp->anterior->siguiente = nuevo;
                nuevo->anterior = temp->anterior;
                temp->anterior = nuevo;
                printf("Nodo ingresado correctamente\n");
            }
        
        }
    }
}

//Funcion agregar por id
void agregar_nodo_id(struct nodo **primero, struct nodo **ultimo){
    struct nodo *nuevo; //Crear nodo nuevo
    int id = 0; //Variable para la id
    nuevo = malloc(sizeof(struct nodo)); //Reservar memoria
    printf("Ingrese la id:\n"); //Ingresar datos
    scanf("%d", &nuevo->id);
    fflush(stdin);
    printf("Ingrese el nombre:\n");
    gets(nuevo->nombre);
    printf("Ingrese el id de la persona anterior donde ingresara el nodo:\n"); //Ingresar id
    scanf("%d", &id);
    if(*primero == NULL){ //Agregar en primera posicion
        printf("La lista esta vacia, se creara una nueva lista\n");
        nuevo-> siguiente = NULL; //Asignar valores
        nuevo->anterior = NULL;
        *primero = nuevo;
        *ultimo = nuevo;
        printf("Nodo ingresado correctamente\n");
    }
    else{ //Agregar en una posicion
        struct nodo *temp = *primero;
        while(temp != NULL && temp -> id != id){ //Recorrer la lista
            temp = temp ->siguiente;
        }
        if (temp == NULL){ //Si no se encuentra la id
            printf("No se encuentra la id\n");
        }
        else if (temp->siguiente == NULL){ //Agregar en ultima posicion
            nuevo->siguiente = temp->siguiente; //
            nuevo->anterior = temp; 
            temp->siguiente = nuevo;
            *ultimo = nuevo;
        }
        else { //Agregar en una posicion diferente a la primera y ultima
            nuevo -> siguiente = temp->siguiente; //Asignar valores
            nuevo ->anterior = temp;
            temp->siguiente->anterior = nuevo;
            temp -> siguiente = nuevo;
            printf("Nodo ingresado correctamente\n");
        }
    }
    
}

//Funcion eliminar nodo por posicion
void eliminar_nodo(struct nodo **primero, struct nodo **ultimo){
    struct nodo *temp = *primero; //Crear nodo temporal
    int posicion = 1, posicion_actual = 1; //Variables para la posicion
    printf("Ingrese la poscion en la que desea eliminar el nodo:\n"); //Ingresar posicion
    scanf("%d", &posicion);
    if(*primero == NULL){ //Si la lista esta vacia
        printf("Lista vacia");      
    }
    else{ //Si la lista no esta vacia
        if (posicion == posicion_actual){ //Eliminar en primera posicion
            *primero = temp ->siguiente; //Asignar valores
            temp->siguiente->anterior = NULL;
            free(temp); //Liberar memoria
            printf("Nodo eliminado\n");
        }
        else{ //Eliminar en una posicion diferente a la primera
            struct nodo *temp2 = temp;
            while(temp2 != NULL && posicion_actual < posicion){ //Recorrer la lista
                temp = temp2; //Asignar valores
                temp2 = temp2->siguiente;
                posicion_actual++;
            }
            if (temp2 == NULL){ //Si no se encuentra la posicion
                printf("No se encuentra la posicion\n");
            }
            else if (temp2 -> siguiente == NULL){ //Eliminar en ultima posicion
                temp->siguiente = temp2->siguiente; //Asignar valores
                *ultimo = temp;
                free(temp2); //Liberar memoria
                printf("Nodo eliminado\n"); 
            }
            else { //Eliminar en una posicion diferente a la primera y ultima
                temp-> siguiente = temp2->siguiente; //Asignar valores
                temp2-> siguiente -> anterior = temp;
                free(temp2); //Liberar memoria
                printf("Nodo eliminado\n");
            }
        }
    }
}

//Funcion eliminar nodo por id
void eliminar_nodo_id(struct nodo **primero, struct nodo **ultimo){
    struct nodo *temp = *primero; //Crear nodo temporal
    int id = 0; //Variable para la id
    printf("Ingrese el id del nodo que desea eliminar:\n"); //Ingresar id
    scanf("%d", &id);
    if(*primero == NULL){ //Si la lista esta vacia
        printf("Lista vacia");      
    } 
    else{ //Si la lista no esta vacia
        if (temp->id == id){ //Eliminar en primera posicion
            *primero = temp ->siguiente; //Asignar valores
            temp->siguiente->anterior = NULL;
            free(temp); //Liberar memoria
            printf("Nodo eliminado\n");
        }
        else{ //Eliminar en una posicion diferente a la primera
            struct nodo *temp2 = temp; //Crear nodo temporal
            while(temp2 != NULL && temp2 ->id != id){ //Recorrer la lista
                temp = temp2; //Asignar valores
                temp2 = temp2->siguiente;
            }
            if (temp2 == NULL){ //Si no se encuentra la id
                printf("No se encuentra la id\n"); 
            }
            else if (temp2->siguiente == NULL){ //Eliminar en ultima posicion
                temp->siguiente = temp2->siguiente; //Asignar valores
                *ultimo = temp;
                free(temp2); //Liberar memoria
                printf("Nodo eliminado\n");
            }
            else { //Eliminar en una posicion diferente a la primera y ultima
                temp->siguiente = temp2->siguiente; //Asignar valores
                temp2->siguiente->anterior = temp;
                free(temp2); //Liberar memoria
                printf("Nodo eliminado\n");
            }
        }
    }
}

//Funcion imprimir datos
void imprimir_datos(struct nodo *primero, struct nodo *ultimo){
    struct nodo *temp = primero; //Crear nodo temporal
    struct nodo *temp2 = ultimo;
    int n = 1; //Variable para el nodo
    int op = 0; //Variable para la opcion
    printf("Desea ver la lista desde el primero hacia adelante o desde el ultimo hacia atras?\n"); //Preguntar por la opcion
    do { //Ciclo para la opcion
        printf("===>1. Desde el primer elemento\n===>2. Desde el ultimo\n"); //Opciones
        scanf("%d", &op); //Ingresar opcion
        if (op != 1 && op != 2){
            printf("Vuelva a intentar...\n\n");
        } 
    } while(op != 1 && op != 2); //Condicion para la opcion
    if (primero == NULL){ //Si la lista esta vacia
        printf("No hay datos en la lista\n");
    }
    else { 
        printf("|==================DATOS ALMECENADOS EN MEMORIA ================|\n"); //Imprimir datos
        if (op == 1){ //Si se elige la opcion 1
            while (temp != NULL){ //Recorrer la lista
                printf("Nodo %d\n", n);
                printf("\t===> ID: %d\n", temp->id);
                printf("\t===> NOMBRE: %s\n", temp->nombre);
                printf("----------------------------\n");
                temp = temp -> siguiente;
                n++;
            }
        }
        else if (op == 2){ //Si se elige la opcion 2
            while (temp2 != NULL){ //Recorrer la lista
                printf("Nodo %d\n", n);
                printf("\t===> ID: %d\n", temp2->id);
                printf("\t===> NOMBRE: %s\n", temp2->nombre);
                printf("----------------------------\n");
                temp2 = temp2 -> anterior;
                n++;
            }
        }
        printf("|========================FIN DE LA LISTA========================|\n");
    }
}

//Funcion vaciar lista
void vaciar_lista(struct nodo **primero, struct nodo **ultimo){
    struct nodo *temp = *primero; //Crear nodo temporal
    if (temp == NULL){ //Si la lista esta vacia
        printf("Lista vacia\n");
    }
    else { //Si la lista no esta vacia
        struct nodo *temp2 = temp; //Crear nodo temporal
        while (temp != NULL){ //Recorrer la lista
            temp2 = temp;
            temp = temp ->siguiente;
            free(temp2); //Liberar memoria
        }
        *primero = temp; //Asignar valores
        *ultimo = temp;
        printf("Lista vaciada correctamente\n");
    }
}

//Funcion intercambiar contenido
void intercambiar_contenido(struct nodo **primero){
    struct nodo *temp = *primero; //Crear nodo temporal
    char nombre_aux[30]; //Variable para el nombre
    int id_aux = 0, posicion_1 = 1, posicion_2 = 1, posicion_actual = 1; //Variables para las posiciones
    printf("Ingrese la primera posicion a intercambiar:\n"); //Ingresar posicion
    scanf("%d", &posicion_1);
    printf("Ingrese la segunda posicion a intercambiar:\n");
    scanf("%d", &posicion_2);
    if (posicion_1 > posicion_2){ //Intercambiar posiciones
        posicion_actual = posicion_2;
        posicion_2 = posicion_1;
        posicion_1 = posicion_actual;
    }
    posicion_actual = 1;
    if (temp == NULL){ //Si la lista esta vacia
        printf("La lista esta vacia\n");
    }
    else if (posicion_1 == posicion_2){ //Si las posiciones son iguales
        printf("Misma posicion\n");
    }
    else { //Si las posiciones son diferentes
        struct nodo *temp2 = temp; //Crear nodo temporal
        while (temp != NULL && posicion_actual < posicion_1){ //Recorrer la lista
            temp = temp ->siguiente;
            posicion_actual++;
        }
        temp2 = temp; //Asignar valores
        while (temp2 != NULL && posicion_actual < posicion_2){ //Recorrer la lista
            temp2 = temp2 ->siguiente;
            posicion_actual++;
        }
        if (temp == NULL || temp2 == NULL){ //Si no se encuentran los nodos
            printf("No se encontraron los nodos\n");
        }
        else{ //Si se encuentran los nodos  
            id_aux = temp2->id; //Asignar valores
            strcpy(nombre_aux,temp2->nombre);
            temp2->id = temp ->id;
            strcpy(temp2->nombre,temp->nombre);
            temp->id = id_aux;
            strcpy(temp->nombre,nombre_aux);
            printf("Contenido intercambiado correctamente\n");
        }
    }
}

//Funcion intercambiar posiciones
void intercambiar_nodos(struct nodo **primero, struct nodo **ultimo){
    struct nodo *temp = *primero; //Crear nodo temporal
    char nombre_aux[30]; //Variable para el nombre
    int id_aux = 0, posicion_1 = 1, posicion_2 = 1, posicion_actual = 1; //Variables para las posiciones
    printf("Ingrese la primera posicion a intercambiar:\n"); //Ingresar posicion
    scanf("%d", &posicion_1);
    printf("Ingrese la segunda posicion a intercambiar:\n");
    scanf("%d", &posicion_2);
    if (posicion_1 > posicion_2){ //Intercambiar posiciones
        posicion_actual = posicion_2;
        posicion_2 = posicion_1;
        posicion_1 = posicion_actual;
    }
    posicion_actual = 1;
    if (posicion_actual == posicion_1){ //Intercambiar posiciones en primera posicion
        struct nodo *temp2 = temp; //Crear nodo temporal
        while(temp2 != NULL && posicion_actual < posicion_2){ //Recorrer la lista
            temp2 = temp2 -> siguiente;
            posicion_actual++;
        }
        if (temp2 == NULL){
            printf("No se encontro la posicion\n");
        }
        else { //Intercambiar posiciones
            if (posicion_1 == posicion_2 - 1){ //Intercambiar posiciones en nodos consecutivos
                temp->siguiente = temp2->siguiente; //Asignar valores
                temp->siguiente->anterior = temp;
                temp2->siguiente = temp;
                temp2->anterior = temp->anterior;
                if (temp->anterior != NULL){
                    temp2->anterior->siguiente = temp2;
                }
                temp->anterior = temp2;
                *primero = temp2;
            }
            else { //Intercambiar posiciones en nodos no consecutivos
                struct nodo *temp3 = temp2->siguiente; //Crear nodo temporal
                struct nodo *temp4 = temp2->anterior;
                temp2 ->anterior->siguiente = temp; //Asignar valores
                temp->siguiente->anterior = temp2;
                if (temp2->siguiente != NULL) { //Ultima posicion   
                    temp2->siguiente->anterior = temp;
                }
                temp2->anterior = temp->anterior;
                temp -> anterior = temp4;
                temp2 ->siguiente = temp ->siguiente;
                temp -> siguiente = temp3;
                if (*ultimo == temp2){
                    *ultimo = temp;
                }
                *primero = temp2;
            }
            printf("Intercambio realizado\n");
        }
    }
    else if(posicion_1 == (posicion_2 - 1)){ //Intercambiar posiciones en consecutivas
        posicion_actual = 1;
        while (temp != NULL && posicion_actual < posicion_1){ //Recorrer la lista
            temp = temp->siguiente;
            posicion_actual++;
        }
        struct nodo *temp2 = temp; //Crear nodo temporal
        if (temp == NULL){
            printf("No se encuentra la posicion\n");
        }
        else{ //Intercambiar posiciones
            while(temp2 != NULL && posicion_actual < posicion_2){ //Recorrer la lista
                temp2 = temp2 -> siguiente;
                posicion_actual++;
            }
            if (temp2 == NULL){
                printf("No se encuentra la posicion\n");
            }
            else { //Intercambiar posiciones
                struct nodo *temp3 = temp2->siguiente; //Crear nodo temporal
                if (temp2->siguiente != NULL){ //Ultima posicion
                    temp2->siguiente->anterior = temp;
                }
                temp2->siguiente = temp; //Asignar valores
                temp2->anterior = temp->anterior;
                temp->anterior->siguiente = temp2;
                temp->siguiente = temp3;
                temp->anterior = temp2;
                if (*ultimo == temp2) {
                    *ultimo = temp;
                }
                printf("Intercambio realizado\n");
            }
        }
    }
    else{ //Intercambiar posiciones en no consecutivas
        while (temp != NULL && posicion_actual < posicion_1){ //Recorrer la lista
            temp = temp->siguiente;
            posicion_actual++;
        }
        struct nodo *temp2 = temp; //Crear nodo temporal
        if (temp == NULL){
            printf("No se encuentra la posicion\n");
        }
        else{ //Intercambiar posiciones
            while (temp2 != NULL && posicion_actual < posicion_2){ //Recorrer la lista
                temp2 = temp2->siguiente;
                posicion_actual++;
            }
            if (temp2 == NULL){
                printf("No se encuentra la posicion\n");
            }
            else { //Intercambiar posiciones
                struct nodo *temp3 = temp->siguiente; //Crear nodo temporal
                struct nodo *temp4 = temp->anterior;
                temp->siguiente->anterior = temp2; //Asignar valores
                temp->anterior->siguiente = temp2;
                temp->anterior = temp2->anterior;
                temp->siguiente = temp2->siguiente;
                if (temp2->siguiente != NULL){ //Ultima posicion
                    temp2->siguiente->anterior = temp;
                }
                temp2->anterior->siguiente = temp;
                temp2->siguiente = temp3;
                temp2->anterior = temp4;
                if (*ultimo == temp2){
                    *ultimo = temp;
                }
                printf("Intercambio realizado\n");
            }
        }

    }
}

//Funcion guardar datos
void guardar_datos(struct nodo *primero){
    struct nodo *datos = primero; //Crear nodo temporal
    FILE *archivo; //Crear archivo
    archivo = fopen("datos.bin", "wb"); //Abrir archivo
    if (archivo == NULL){ //Si no se puede abrir el archivo
        printf("Error al abrir el archivo\n");
    }
    
    while(datos != NULL){ //Recorrer la lista
        struct nodo_disco nodo_guardado; //Crear nodo temporal
        nodo_guardado.id = datos ->id; //Asignar valores
        strcpy(nodo_guardado.nombre,datos->nombre);

        fwrite(&nodo_guardado, sizeof(nodo_guardado), 1, archivo); //Escribir en el archivo
        datos = datos ->siguiente; //Asignar valores
    }

    printf("Datos guardados correctamnte\n");

    fclose(archivo);
}

//Funcion recuperar datos
void recuperar_datos(struct nodo **primero, struct nodo **ultimo){
    FILE *archivo; //Crear archivo
    archivo = fopen("datos.bin", "rb"); //Abrir archivo
    if (archivo == NULL){ //Si no se puede abrir el archivo
        printf("Error al abrir el archivo\n");
    }
    struct nodo_disco nodo_guardado; //Crear nodo temporal
    while (fread(&nodo_guardado, sizeof(struct nodo_disco),1,archivo) == 1){ //Leer el archivo
        struct nodo *datos = malloc(sizeof(struct nodo)); //Reservar memoria
        if (datos == NULL){ //Si no hay datos en la lista
            printf("No hay datos en la lista\n");
            fclose(archivo); //Cerrar archivo
            return; //Retornar
        } 
        datos ->id = nodo_guardado.id; //Asignar valores
        strcpy(datos->nombre,nodo_guardado.nombre);
        datos->siguiente = NULL;
        datos->anterior = NULL;
        if (*primero == NULL){ //Agregar en primera posicion
            *primero = datos;
            *ultimo = datos;
        }
        else{ //Agregar en las demas posiciones
            struct nodo *temp = *primero; //Crear nodo temporal
            while (temp->siguiente != NULL){ //Recorrer la lista
                temp = temp->siguiente;
            }
            temp ->siguiente = datos; //Asignar valores
            datos ->anterior = temp;
            *ultimo = datos;
        }
    }

    printf("Datos recuperados\n");
    fclose(archivo); //Cerrar archivo
}

//Funcion para principal
int main(){
    struct nodo *primero = NULL; //Crear nodo
    struct nodo *ultimo = NULL;
    int op = 0; //Variable para la opcion
    //Menu
    do {
        printf("=======Que desea hacer?=======\n");
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
                agregar_nodo(&primero, &ultimo);
                break;
            case 2:
                agregar_nodo_pos(&primero, &ultimo);
                break;
            case 3:
                agregar_nodo_id(&primero, &ultimo);
                break;
            case 4:
                eliminar_nodo(&primero, &ultimo);
                break;
            case 5:
                eliminar_nodo_id(&primero, &ultimo);
                break;
            case 6:
                imprimir_datos(primero, ultimo);  
                break;
            case 7:
                vaciar_lista(&primero, &ultimo);
                break;
            case 8:
                intercambiar_contenido(&primero);
                break;
            case 9:
                intercambiar_nodos(&primero, &ultimo);
                break;
            case 10:
                guardar_datos(primero);
                break;
            case 11:
                recuperar_datos(&primero, &ultimo);
                break;
            case 0:
                printf("Se ha cerrado el programa\n");
                break;
        }
    } while (op != 0);
    return 0;
}
