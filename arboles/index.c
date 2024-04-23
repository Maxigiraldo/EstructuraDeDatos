#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define ESC 27
#define ENTER 13

struct arbol {
    int dato;
    struct arbol *izq;
    struct arbol *der;
};

void moverse() {
    printf("Presione las teclas de arriba o abajo para moverse en el menu\n");
    printf("Presione Enter para seleccionar una opcion\n");
    printf("Presione ESC para salir del programa\n");
}

void insertar(struct arbol **raiz, int dato) {
    int eleccion = 0;
    system("cls");
    printf("Desea insertar el dato por izquierda o por derecha?\n");
    printf("- Izquierda\n");
    printf("- Derecha\n");
    moverse();
    int op;
    while (op != ESC && op != ENTER) {
        op = getch();
        system("cls");
        switch (op) {
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
    if (op == ENTER) {
        if (*raiz == NULL) {
            *raiz = malloc(sizeof(struct arbol));
            (*raiz)->dato = dato;
            (*raiz)->izq = NULL;
            (*raiz)->der = NULL;
        } else {
            switch (eleccion) {
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

void mostrar(struct arbol *raiz) {
    if (raiz != NULL) {
        mostrar(raiz->izq);
        printf("\t-> %d\n", raiz->dato);
        mostrar(raiz->der);
    }
}

int mostrar_menu(){
    printf("Menu\n");
    printf("- Insertar nodo\n");
    printf("- Mostrar nodo\n");
    printf("- Salir\n");
    moverse();
    printf("\n");
}

int main() {
    struct arbol *raiz = NULL;
    int menu = 0, op = 0, dato;

    mostrar_menu();

    Sleep(1000);

    while (menu != ESC) {
        menu = getch();
        system("cls");
        switch (menu) {
            case 72:
                printf("\t--> Insertar nodo\n");
                op = 72;
                break;
            case 80:
                printf("\t--> Mostrar nodo\n");
                op = 80;
                break;
            default:
                printf("Presione una tecla valida\n");
                break;
        }
        printf("\n");
        if (menu == ENTER) {
            switch (op) {
                case 72:
                    fflush(stdin);
                    system("cls");
                    printf("Ingrese el dato a insertar:\n");
                    scanf("%d", &dato);
                    insertar(&raiz, dato);
                    system("cls");
                    printf("Nodo insertado\n");
                    Sleep(1000);
                    system("cls");
                    mostrar_menu();
                    break;
                case 80:
                    system("cls");
                    printf("Mostrando arbol\n");
                    mostrar(raiz);
                    Sleep(2000);
                    printf("\n");
                    mostrar_menu();
                    break;
            }
        }
    }
    printf("Saliendo del programa\n");
    return 0;
}

