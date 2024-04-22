// Presentado por: Maximiliano Giralo Ocampo
#include <stdio.h> // Libreria para el manejo de entrada y salida de datos
#include <stdlib.h> // Libreria para el manejo de memoria dinamica
#include <conio.h> // Libreria para el manejo de teclas
#include <windows.h> // Libreria para el manejo de funciones del sistema operativo
#define ESC 27 // Definicion de la tecla ESC
#define ENTER 13 // Definicion de la tecla ENTER

struct nodo{ // Estructura para el arbol binario
    int dato;
    struct nodo *izq;
    struct nodo *der;
};

typedef struct nodo arbol; // Definicion de la estructura arbol



void moverse(){ // Funcion para mostrar las instrucciones de movimiento en el menu
    printf("Presione las teclas de arriba o abajo para moverse en el menu\n");
    printf("Presione Enter para seleccionar una opcion\n");
    printf("Presione ESC para salir del menu\n");
}

void insertar(arbol **raiz, int dato){ // Funcion para insertar un nodo en el arbol
    printf("Desea insertar el dato por izquierda o por derecha?\n");
    printf("- Izquierda\n");
    printf("- Derecha\n");
    moverse();
    int op, eleccion;
    while (op != ESC && op != ENTER){ // Bucle para seleccionar la opcion de insercion
        op = getch(); // Se obtiene la tecla presionada
        system("cls");
        switch (op){ // Se evalua la tecla presionada
            case 72:
                printf("--> Izquierda\n");
                eleccion = 72;
                break;
            case 80:
                printf("--> Derecha\n");
                eleccion = 80;
                break;
            default:
                printf("Presione una tecla valida\n");
                break;
        }
        printf("\n");
        
    }
    if (op == ENTER){ // Si se presiona ENTER se inserta el nodo
        if(*raiz == NULL){ // Si el arbol esta vacio se crea el nodo raiz
            *raiz = malloc(sizeof(arbol));
            (*raiz)->dato = dato;
            (*raiz)->izq = NULL;
            (*raiz)->der = NULL;
        }else{ // Si el arbol no esta vacio se va la raiz a la izquierda o derecha segun la eleccion
            switch(eleccion){
                case 72:
                    insertar(&(*raiz)->izq, dato);
                    break;
                case 80:
                    insertar(&(*raiz)->der, dato);
                    break;
            }
        }
    }
}

void mostrar(arbol *raiz){ // Funcion para mostrar el arbol en formato in-order
    printf("Mostrando arbol\n\n");
    if(raiz != NULL){ // Si la raiz no es nula se muestra el arbol
        mostrar(raiz->izq); 
        printf("%d\n", raiz->dato);
        mostrar(raiz->der);
    }
}

int main(int argc, char *argv[]) { // Funcion principal
    arbol *raiz = NULL; // Se crea un arbol vacio
    int menu, op, dato; // Variables para el menu y la opcion seleccionada

    printf("Menu\n"); // Se muestra el menu
    printf("- Insertar nodo\n");
    printf("- Mostrar nodo\n");
    printf("- Salir\n");
    moverse();
    printf("\n");

    Sleep(1000);

    while(menu != ESC) { // Bucle para seleccionar una opcion del menu
        menu = getch(); // Se obtiene la tecla presionada

        system("cls"); // Se limpia la pantalla

        switch(menu) { // Se evalua la tecla presionada
            case 72:
                printf("\t--> Insertar nodo");
                op = 72;
                break;
            case 80:
                printf("\t--> Mostrar nodo");
                op = 80;
                break;
            default:
                printf("Presione una tecla valida\n");
                break;
        }
        printf("\n");
        if (menu == ENTER){ // Si se presiona ENTER se ejecuta la opcion seleccionada
            switch(op){
                case 72: // Si se selecciona la opcion de insertar nodo
                    fflush(stdin);
                    printf("Ingrese el dato a insertar:\n"); // Se solicita el dato a insertar
                    scanf("%d", &dato);
                    insertar(&raiz, dato);
                    printf("Nodo insertado\n");
                    moverse();
                    break;
                case 80: // Si se selecciona la opcion de mostrar nodo
                    mostrar(raiz);
                    moverse();
                    break;
            }
        }
    }
    printf("Saliendo del programa\n"); // Se muestra un mensaje de salida
	return 0;
}
