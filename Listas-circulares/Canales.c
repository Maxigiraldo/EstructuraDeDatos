// Autor: Maximiliano Giraldo Ocampo
#include <stdio.h> // Incluye la biblioteca estándar de E/S
#include <stdlib.h> // Incluye la biblioteca estándar
#include <string.h> // Incluye la biblioteca de cadenas
#include <conio.h> // Incluye la biblioteca de entrada/salida
#include <windows.h> // Incluye la biblioteca de Windows

struct canal { // Estructura de un canal
    char nombre[50];
    int numero;
    struct programa *programas;
    struct canal *siguiente;
    struct canal *anterior;
};

struct programa { // Estructura de un programa
    char nombre[50];
    char hora[50];
    char duracion[30];
    struct programa *siguiente;
    struct programa *anterior;
};

void confirmacion(int op){ // Funcion para mostrar la confirmacion 
    system("cls");
    if (op == 0) { 
        printf(">> Si\n");
        printf("   No\n");
    } else {
        printf("   Si\n");
        printf(">> No\n");
    } 
}
void programa_nuevo(struct canal **actual){ // Funcion para agregar un programa
    struct programa *nuevo;
    nuevo = malloc(sizeof(struct programa)); // Reservar memoria para el nuevo programa
    fflush(stdin);
    printf("Ingrese el nombre del programa: ");
    fgets(nuevo->nombre, 50, stdin);
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = 0; // Eliminar el salto de linea
    printf("Ingrese la franja horaria del programa: ");
    fgets(nuevo->hora, 50, stdin);
    nuevo->hora[strcspn(nuevo->hora, "\n")] = 0; // Eliminar el salto de linea
    printf("Ingrese la duracion del programa: ");
    fgets(nuevo->duracion, 30, stdin);
    nuevo->duracion[strcspn(nuevo->duracion, "\n")] = 0; // Eliminar el salto de linea
    if ((*actual)->programas == NULL) { // Si no hay programas
        (*actual)->programas = nuevo; // Establecer el programa como el primero
        nuevo->siguiente = nuevo; // Establecer el siguiente programa como el mismo
        nuevo->anterior = nuevo; // Establecer el programa anterior como el mismo
    } else { // Si ya hay programas
        struct programa *aux = (*actual)->programas;
        while (aux->siguiente != (*actual)->programas) {
            aux = aux->siguiente; // Recorrer la lista de programas
        }
        aux->siguiente = nuevo; // Agregar el nuevo programa al final de la lista
        nuevo->anterior = aux; // Establecer el programa anterior como el ultimo
        nuevo->siguiente = (*actual)->programas; // Establecer el siguiente programa como el primero
        (*actual)->programas->anterior = nuevo; // Establecer el programa anterior al primero como el nuevo programa
    }
    printf("Programa agregado correctamente\n");
    system("cls");
    printf("Desea agregar otro programa?\n");
    Sleep(1000);
    char ch;
    int opcion = 0;
    do { // Mostrar la confirmacion
        system("cls");
        confirmacion(opcion);
        ch = getch();

        if (ch == 0 || ch == 224) { // Si es tecla especial
            switch (getch()) {
                case 72:  // Flecha arriba
                    opcion = (opcion - 1 + 2) % 2;
                    break;
                case 80:  // Flecha abajo
                    opcion = (opcion + 1) % 2;
                    break;
            }
        }
    } while (ch != 13);  // 13 es el codigo ASCII para la tecla Enter

    system("cls");

    switch (opcion) { // Segun la opcion seleccionada
        case 0:
            programa_nuevo(actual); // Agregar otro programa
            break;
        case 1:
            printf("Regresando...\n"); // Regresar
            Sleep(100);
            break;
    }
}

void ver_canal(struct canal *inicio){ // Funcion para mostrar el canal
    system("cls");
    printf("CANAL:\n");
    printf("\t>>%s\n", inicio->nombre);
    printf("ENTER para seleccionar\n");
    printf("ESC para salir\n");
}

void agregar_programas(struct canal **inicio){ // Funcion para agregar programas
    struct canal *actual = *inicio;
    int opcion = 0;
    char ch;
    if (actual == NULL) { // Si no hay canales
        printf("No hay canales\n");
        return;
    }
    printf("-------Agregar Programas--------\n\n"); 
    Sleep(1000);
    do { // Mostrar los canales
        printf("Seleccione un canal:\n");
        Sleep(100);
        ver_canal(actual);
        ch = getch();

        if (ch == 0 || ch == 224) { // Si es tecla especial
            switch (getch()) { // Segun la tecla presionada
                case 72:  // Flecha arriba
                    actual = actual->siguiente; // Seleccionar el canal siguiente
                    break;
                case 75:  // Flecha izquierda
                    actual = actual->anterior; // Seleccionar el canal anterior
                    break;
                case 77:  // Flecha derecha
                    actual = actual->siguiente; // Seleccionar el canal siguiente
                    break;
                case 80:  // Flecha abajo
                    actual = actual->anterior; // Seleccionar el canal anterior
                    break;
            }
        }     
    } while (ch != 27 && ch != 13); // 27 es el codigo ASCII para la tecla ESC y 13 para Enter  

    if (ch == 13) {
        programa_nuevo(&actual); // Agregar programas al canal seleccionado
    } else if (ch == 27) {
        printf("Regresando...\n"); // Regresar
    } 
}

void agregar_canal(struct canal **inicio, int *numero) { // Función para agregar un canal
    struct canal *nuevo;
    struct programa *programacion = NULL; // Inicializar la programación
    nuevo = malloc(sizeof(struct canal)); // Reservar memoria para el nuevo canal
    printf("Ingrese el nombre del canal: "); // Solicitar el nombre del canal
    fgets(nuevo->nombre, 50, stdin);
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = 0; // Eliminar el salto de linea
    (*numero)++; // Incrementar el número del canal
    nuevo->numero = *numero;
    nuevo->programas = programacion; // Establecer la programación como vacía
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    if (*inicio == NULL) { // Si no hay canales
        *inicio = nuevo; // Establecer el nuevo canal como el primero
        nuevo->siguiente = *inicio; // Establecer el siguiente canal como el primero
        nuevo->anterior = *inicio; // Establecer el canal anterior como el primero
    } else { // Si ya hay canales
        struct canal *aux = *inicio; // Crear un auxiliar
        while (aux->siguiente != *inicio) { // Recorrer la lista de canales
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo; // Agregar el nuevo canal al final de la lista
        nuevo->anterior = aux; // Establecer el canal anterior como el ultimo
        nuevo->siguiente = *inicio; // Establecer el siguiente canal como el primero
        (*inicio)->anterior = nuevo; // Establecer el canal anterior al primero como el nuevo canal
    }
    printf("Canal agregado correctamente\n");
}

void menu_consulta(int opcion) { // Funcion para mostrar el menu de opciones
    system("cls");
    printf("Como desea buscar el canal?\n\n");  
    if (opcion == 0) {
        printf(">> Numero\n");
        printf("   Nombre\n");
    } else {
        printf("   Numero\n");
        printf(">> Nombre\n");
    } 
}

void canal_encontrado(struct canal *aux){ // Funcion para mostrar el canal encontrado
        system("cls");
        printf("Nombre: %s\n", aux->nombre);
        printf("Numero: %d\n", aux->numero);
        printf("Programas: \n");
        if (aux->programas != NULL) { // Si hay programas
            struct programa *aux_programa = aux->programas; // Crear un auxiliar para los programas
            do { // Recorrer la lista de programas
                printf("\tNombre: %s\n", aux_programa->nombre);
                printf("\tHora: %s\n", aux_programa->hora);
                printf("\tDuracion: %s\n", aux_programa->duracion);
                aux_programa = aux_programa->siguiente;
            } while (aux_programa != aux->programas);  
        } else { // Si no hay programas
            printf("\tNo hay programas\n");
        }
}

void consulta_canal(struct canal **inicio){ // Funcion para consultar un canal
    struct canal *actual = *inicio; // Crear un auxiliar
    int opcion = 0;
    char ch;
    if (actual == NULL) { // Si no hay canales
        printf("No hay canales\n");
        return;
    }
    do { // Mostrar el menu de opciones de consulta
        menu_consulta(opcion); 
        ch = getch();
        if (ch == 0 || ch == 224) { // Si es tecla especial
                switch (getch()) {
                    case 72:  // Flecha arriba
                        opcion = (opcion - 1 + 2) % 2;
                        break;
                    case 80:  // Flecha abajo
                        opcion = (opcion + 1) % 2;
                        break;
                }
            }
    } while (ch != 13);  // 13 es el codigo ASCII para la tecla Enter

    system("cls");

    if (opcion == 0){ // Si se selecciona la opcion de numero
        printf("Ingrese el numero del canal: "); // Solicitar el número del canal
        int numero; 
        scanf("%d", &numero);
        struct canal *aux = *inicio;
        while (aux->numero != numero && aux->siguiente != *inicio) { // Recorrer la lista de canales
            aux = aux->siguiente;
        }
        if (aux->numero == numero) { // Si se encuentra el canal
            printf("Canal encontrado\n");
            Sleep(1000);
            do { // Mostrar el canal encontrado
                canal_encontrado(aux);
                printf("\nPresione ENTER o ESC para continuar\n");
                ch = getch();
            } while (ch != 13 && ch != 27); // 13 es el codigo ASCII para la tecla Enter y 27 para ESC
        } else {
            printf("Canal no encontrado\n");
        }   
    } else { // Si se selecciona la opcion de nombre
        printf("Ingrese el nombre del canal: "); // Solicitar el nombre del canal
        char nombre[50];
        fgets(nombre, 50, stdin);
        nombre[strcspn(nombre, "\n")] = 0; // Eliminar el salto de linea
        struct canal *aux = *inicio;
        while (strcmp(aux->nombre, nombre) != 0 && aux->siguiente != *inicio) { // Recorrer la lista de canales
            aux = aux->siguiente; 
        }
        if (strcmp(aux->nombre, nombre) == 0) { // Si se encuentra el canal
            printf("Canal encontrado\n");
            Sleep(1000); 
            do { // Mostrar el canal encontrado
                canal_encontrado(aux);
                printf("\nPresione ENTER o ESC para continuar\n");
                ch = getch();
            } while (ch != 13 && ch != 27); // 13 es el codigo ASCII para la tecla Enter y 27 para ESC   
        } else {
            printf("Canal no encontrado\n");
        }
    }
}

void eliminar_canal(struct canal **inicio){ // Funcion para eliminar un canal
    struct canal *actual = *inicio;
    int opcion = 0;
    char ch;
    if (actual == NULL) { // Si no hay canales
        printf("No hay canales\n");
        return;
    }
    do { // Mostrar el menu de opciones de consulta
        menu_consulta(opcion);
        ch = getch();
        if (ch == 0 || ch == 224) { // Si es tecla especial
                switch (getch()) {
                    case 72:  // Flecha arriba
                        opcion = (opcion - 1 + 2) % 2;
                        break;
                    case 80:  // Flecha abajo
                        opcion = (opcion + 1) % 2;
                        break;
                }
            }
    } while (ch != 13);  // 13 es el codigo ASCII para la tecla Enter

    system("cls");

    if (opcion == 0){ // Si se selecciona la opcion de numero
        printf("Ingrese el numero del canal: "); // Solicitar el numero del canal
        int numero;
        scanf("%d", &numero);
        struct canal *aux = *inicio;
        while (aux->numero != numero && aux->siguiente != *inicio) { // Recorrer la lista de canales
            aux = aux->siguiente;
        }
        if (aux->numero == numero) { // Si se encuentra el canal
            printf("Canal encontrado\n");
            canal_encontrado(aux);
            printf("Desea eliminar el canal?\n"); 
            opcion = 0;
            do { // Mostrar la confirmacion
                confirmacion(opcion);
                ch = getch();

                if (ch == 0 || ch == 224) { // Si es tecla especial
                    switch (getch()) {
                        case 72:  // Flecha arriba
                            opcion = (opcion - 1 + 2) % 2;
                            break;
                        case 80:  // Flecha abajo
                            opcion = (opcion + 1) % 2;
                            break;
                    }
                }
            } while (ch != 13);  // 13 es el codigo ASCII para la tecla Enter
            if (opcion == 0) { // Si se selecciona la opcion de si
                if (aux->siguiente == aux) { // Si hay un solo canal
                    *inicio = NULL;
                } else { // Si hay mas de un canal
                    aux->anterior->siguiente = aux->siguiente; // Establecer el siguiente canal como el siguiente del canal anterior
                    aux->siguiente->anterior = aux->anterior; // Establecer el canal anterior como el anterior del siguiente canal
                    if (*inicio == aux) { // Si el canal es el primero
                        *inicio = aux->siguiente; // Establecer el siguiente canal como el primero
                    }
                }
                free(aux); // Liberar la memoria del canal
                printf("Canal eliminado correctamente\n");
            }
        } else { // Si no se encuentra el canal
            printf("Canal no encontrado\n");
        }   
    } else { // Si se selecciona la opcion de nombre
        printf("Ingrese el nombre del canal: ");
        char nombre[50];
        fgets(nombre, 50, stdin);
        nombre[strcspn(nombre, "\n")] = 0; // Eliminar el salto de linea
        struct canal *aux = *inicio;
        while (strcmp(aux->nombre, nombre) != 0 && aux->siguiente != *inicio) { // Recorrer la lista de canales
            aux = aux->siguiente;
        }
        if (strcmp(aux->nombre, nombre) == 0) { // Si se encuentra el canal
            printf("Canal encontrado\n");
            canal_encontrado(aux);
            printf("Desea eliminar el canal?\n");
            opcion = 0;
            do { // Mostrar la confirmacion
                confirmacion(opcion);
                ch = getch();

                if (ch == 0 || ch == 224) { // Si es tecla especial
                    switch (getch()) {
                        case 72:  // Flecha arriba
                            opcion = (opcion - 1 + 2) % 2;
                            break;
                        case 80:  // Flecha abajo
                            opcion = (opcion + 1) % 2;
                            break;
                    }
                }
            } while (ch != 13);  // 13 es el codigo ASCII para la tecla Enter
            if (opcion == 0) { // Si se selecciona la opcion de si
                if (aux->siguiente == aux) { // Si hay un solo canal
                    *inicio = NULL;
                } else { // Si hay mas de un canal
                    aux->anterior->siguiente = aux->siguiente; // Establecer el siguiente canal como el siguiente del canal anterior
                    aux->siguiente->anterior = aux->anterior; // Establecer el canal anterior como el anterior del siguiente canal
                    if (*inicio == aux) { // Si el canal es el primero
                        *inicio = aux->siguiente; // Establecer el siguiente canal como el primero
                    }
                }
                free(aux); // Liberar la memoria del canal
                printf("Canal eliminado correctamente\n");
            }
        } else {
            printf("Canal no encontrado\n");
        }
    }
}

void eliminar_programacion(struct canal **inicio){ // Funcion para eliminar la programacion
    struct canal *actual = *inicio; 
    int opcion = 0;
    char ch;
    if (actual == NULL) { // Si no hay canales
        printf("No hay canales\n");
        return;
    }
    do { // Mostrar el menu de opciones de consulta 
        menu_consulta(opcion);
        ch = getch();
        if (ch == 0 || ch == 224) { // Si es tecla especial
                switch (getch()) {
                    case 72:  // Flecha arriba
                        opcion = (opcion - 1 + 2) % 2;
                        break;
                    case 80:  // Flecha abajo
                        opcion = (opcion + 1) % 2;
                        break;
                }
            }
    } while (ch != 13);  // 13 es el codigo ASCII para la tecla Enter

    system("cls");

    if (opcion == 0){ // Si se selecciona la opcion de numero
        printf("Ingrese el numero del canal: ");
        int numero;
        scanf("%d", &numero);
        struct canal *aux = *inicio;
        while (aux->numero != numero && aux->siguiente != *inicio) { // Recorrer la lista de canales
            aux = aux->siguiente; 
        }
        if (aux->numero == numero) { // Si se encuentra el canal
            printf("Canal encontrado\n");
            canal_encontrado(aux);
            if (aux->programas == NULL){
                Sleep(100);
                return;
            }
            printf("Desea eliminar la programacion?\n");
            opcion = 0;
            do { // Mostrar la confirmacion
                confirmacion(opcion); 
                ch = getch();

                if (ch == 0 || ch == 224) { // Si es tecla especial
                    switch (getch()) {
                        case 72:  // Flecha arriba
                            opcion = (opcion - 1 + 2) % 2;
                            break;
                        case 80:  // Flecha abajo
                            opcion = (opcion + 1) % 2;
                            break;
                    }
                }
            } while (ch != 13);  // 13 es el codigo ASCII para la tecla Enter
            if (opcion == 0) { // Si se selecciona la opcion de si
                if (actual->programas != NULL) { // Si hay programas
                    struct programa *aux = actual->programas;
                    struct programa *siguiente = NULL;

                    do { // Recorrer la lista de programas
                        siguiente = aux->siguiente; 
                        free(aux); // Liberar la memoria del programa
                        aux = siguiente;
                    } while (aux != actual->programas);

                    actual->programas = NULL; // Establecer la lista de programas como vacia
                    printf("Programacion eliminada correctamente\n");
                } else {
                    printf("No hay programas\n");
                }
            } else {
                printf("Regresando...\n");
            }
        } else {
            printf("Canal no encontrado\n");
        }   
    } else { // Si se selecciona la opcion de nombre
        printf("Ingrese el nombre del canal: ");
        char nombre[50];
        fgets(nombre, 50, stdin); // Solicitar el nombre del canal
        nombre[strcspn(nombre, "\n")] = 0; // Eliminar el salto de linea
        struct canal *aux = *inicio;
        while (strcmp(aux->nombre, nombre) != 0 && aux->siguiente != *inicio) { // Recorrer la lista de canales
            aux = aux->siguiente;
        }
        if (strcmp(aux->nombre, nombre) == 0) { // Si se encuentra el canal
            printf("Canal encontrado\n");
            canal_encontrado(aux);
            if (aux->programas == NULL){ // Si no hay programas
                printf("No hay programas\n");
                Sleep(100);
                return;
            }
            printf("Desea eliminar la programacion?\n");
            opcion = 0;
            do { // Mostrar la confirmacion
                confirmacion(opcion);
                ch = getch();

                if (ch == 0 || ch == 224) { // Si es tecla especial
                    switch (getch()) {
                        case 72:  // Flecha arriba
                            opcion = (opcion - 1 + 2) % 2;
                            break;
                        case 80:  // Flecha abajo
                            opcion = (opcion + 1) % 2;
                            break;
                    }
                }
            } while (ch != 13);  // 13 es el codigo ASCII para la tecla Enter
            if (opcion == 0) { // Si se selecciona la opcion de si
                 if (actual->programas != NULL) { // Si hay programas
                    struct programa *aux = actual->programas;
                    struct programa *siguiente = NULL;

                    do { // Recorrer la lista de programas
                        siguiente = aux->siguiente;
                        free(aux); // Liberar la memoria del programa
                        aux = siguiente;
                    } while (aux != actual->programas);

                    actual->programas = NULL; // Establecer la lista de programas como vacia
                    printf("Programacion eliminada correctamente\n");
                } else {
                    printf("No hay programas\n");
                }
            } else {
                printf("Regresando...\n");
            }
        } else {
            printf("Canal no encontrado\n");
        }
    }
}

void mostrar_guia(struct canal *actual, struct programa *programa){ // Funcion para mostrar los canales
    printf("CANAL:\n");
    printf("\t>>%s\n", actual->nombre);
    printf("NUMERO:\n");
    printf("\t>>%d\n", actual->numero);
    printf("PROGRAMAS:\n");
    if (actual->programas != NULL) {
        printf("\tNombre: %s\n", programa->nombre);
        printf("\tHora: %s\n", programa->hora);
        printf("\tDuracion: %s\n", programa->duracion);
    } else {
        printf("\tNo hay programas\n");
    }
    printf("\nESC para salir\n");
}

void guia_canales(struct canal **inicio){ // Funcion para mostrar la guia de canales
    struct canal *actual = *inicio; // Crear un auxiliar
    struct programa *programa = NULL; // Inicializar el programa
    system("cls");
    char ch;
    int opcion = 0;
    if (actual == NULL) { // Si no hay canales
        printf("No hay canales\n");
        return;
    }
    programa = actual->programas; // Establecer el programa como el primero
    printf("-------Guia de Canales--------\n\n");
    Sleep(1000);
    do { // Mostrar los canales
        mostrar_guia(actual, programa); // Mostrar el canal y el programa
        ch = getch();

        if (ch == 0 || ch == 224) { // Si es tecla especial
            switch (getch()) {
                case 72:  // Flecha arriba
                    actual = actual->siguiente; // Seleccionar el canal siguiente
                    programa = actual->programas; // Establecer el programa como el primero del canal
                    break;
                case 75:  // Flecha izquierda
                    if (programa == NULL) { // Si no hay programas
                        programa = actual->programas; // Manteer el programa como NULL
                    } else { // Si hay programas
                        programa = programa->anterior; // Seleccionar el programa anterior
                    }
                    break;
                case 77:  // Flecha derecha
                    if (programa == NULL) { // Si no hay programas
                        programa = actual->programas; // Manteer el programa como NULL
                    } else { // Si hay programas
                    programa = programa->siguiente; // Seleccionar el programa siguiente
                    }
                    break;
                case 80:  // Flecha abajo
                    actual = actual->anterior; // Seleccionar el canal anterior
                    programa = actual->programas; // Establecer el programa como el primero del canal
                    break;
            }
        } 
        system("cls");    
    } while (ch != 27); // 27 es el codigo ASCII para la tecla ESC
}

void menu_opciones(int opcion) { // Funcion para mostrar el menu de opciones
    system("cls");  
    if (opcion == 0) {
        printf(">> Agregar Canal\n");
        printf("   Agregar Programas\n");
        printf("   Consultar Canal\n");
        printf("   Eliminar Canal\n");
        printf("   Eliminar Programacion\n");
        printf("   Guia de Canales\n");
        printf("   Salir\n");
    } else if (opcion == 1) {
        printf("   Agregar Canal\n");
        printf(">> Agregar Programas\n");
        printf("   Consultar Canal\n");
        printf("   Eliminar Canal\n");
        printf("   Eliminar Programacion\n");
        printf("   Guia de Canales\n");
        printf("   Salir\n");
    } else if (opcion == 2) {
        printf("   Agregar Canal\n");
        printf("   Agregar Programas\n");
        printf(">> Consultar Canal\n");
        printf("   Eliminar Canal\n");
        printf("   Eliminar Programacion\n");
        printf("   Guia de Canales\n");
        printf("   Salir\n");
    } else if (opcion == 3) {
        printf("   Agregar Canal\n");
        printf("   Agregar Programas\n");
        printf("   Consultar Canal\n");
        printf(">> Eliminar Canal\n");
        printf("   Eliminar Programacion\n");
        printf("   Guia de Canales\n");
        printf("   Salir\n");
    } else if (opcion == 4) {
        printf("   Agregar Canal\n");
        printf("   Agregar Programas\n");
        printf("   Consultar Canal\n");
        printf("   Eliminar Canal\n");
        printf(">> Eliminar Programacion\n");
        printf("   Guia de Canales\n");
        printf("   Salir\n");
    } else if (opcion == 5) {
        printf("   Agregar Canal\n");
        printf("   Agregar Programas\n");
        printf("   Consultar Canal\n");
        printf("   Eliminar Canal\n");
        printf("   Eliminar Programacion\n");
        printf(">> Guia de Canales\n");
        printf("   Salir\n");
    } else {
        printf("   Agregar Canal\n");
        printf("   Agregar Programas\n");
        printf("   Consultar Canal\n");
        printf("   Eliminar Canal\n");
        printf("   Eliminar Programacion\n");
        printf("   Guia de Canales\n");
        printf(">> Salir\n");
    }
}

int main(){ // Función principal
    struct canal *inicio = NULL;
    int opcion = 0, numero = 100;
    do { // Mostrar el menu de opciones
        printf("-------Bienvenido a la red TV--------\n\n");
        Sleep(1000);
        char ch;
        opcion = 0;
        printf("Seleccione una opcion:\n");
        Sleep(1000);
        do {
            menu_opciones(opcion);
            ch = getch();

            if (ch == 0 || ch == 224) { // Si es tecla especial
                switch (getch()) {
                    case 72:  // Flecha arriba
                        opcion = (opcion - 1 + 7) % 7;
                        break;
                    case 80:  // Flecha abajo
                        opcion = (opcion + 1) % 7;
                        break;
                }
            }
        } while (ch != 13);  // 13 es el codigo ASCII para la tecla Enter

        system("cls"); 

        switch (opcion) {
            case 0:
                agregar_canal(&inicio, &numero); // Agregar un canal
                break;
            case 1:
                agregar_programas(&inicio); // Agregar programas
                break;
            case 2:
                consulta_canal(&inicio); // Consultar un canal
                break;
            case 3:
                eliminar_canal(&inicio); // Eliminar un canal
                break;
            case 4:
                eliminar_programacion(&inicio); // Eliminar la programación
                break;
            case 5:
                guia_canales(&inicio); // Mostrar la guía de canales
                break;
            case 6:
                printf("Cerrando...\n"); // Salir
                break;
        }
    } while (opcion != 6); // 6 es la opción para salir
    return 0;
}
