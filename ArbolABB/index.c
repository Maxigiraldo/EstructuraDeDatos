#include <stdio.h> // Incluimos la libreria stdio.h para poder utilizar las funciones de entrada y salida
#include <stdlib.h> // Incluimos la libreria stdlib.h para poder utilizar las funciones de memoria dinamica
#include <conio.h> // Incluimos la libreria conio.h para poder utilizar las funciones de entrada y salida de consola
#include <windows.h> // Incluimos la libreria windows.h para poder utilizar las funciones de la API de Windows
#include <string.h> // Incluimos la libreria string.h para poder utilizar las funciones de cadenas de texto

struct sinonimos { // Estructura para los sinonimos
    char sinonimo[50]; // Sinonimo de la palabra
    struct sinonimos *siguiente; // Puntero al siguiente nodo
};

struct nodoABB {
    char palabra[50]; // Palabra a almacenar
    char significado[80]; // Significado de la palabra
    char categoria[50]; // Categoria de la palabra
    struct sinonimos *sinonimos; // Lista de sinonimos
    struct nodoABB *izquierda;
    struct nodoABB *derecha;
};

void menu_categorias(int opcion) { // Funcion para mostrar el menu de categorias
    system("cls");  
    if (opcion == 0) {
        printf(">> Sustantivo\n");
    } else if (opcion == 1) {
        printf(">> Adjetivo\n");
    } else if (opcion == 2) {
        printf(">> Articulo\n");
    } else if (opcion == 3) {
        printf(">> Pronombre\n");
    } else if (opcion == 4) {
        printf(">> Verbo\n");
    } else if (opcion == 5) {
        printf(">> Adverbio\n");
    } else if (opcion == 6) {
        printf(">> Interjeccion\n");
    } else if (opcion == 7) {
        printf(">> Preposicion\n");
    } else {
        printf(">> Conjuncion\n");
    }
}

int moverse_menu_categoria(){ // Funcion para moverse en el menu de categorias
    printf("Ingrese la categoria\n");
    int opcion = 0;
    do { // Mostrar el menu de opciones
        Sleep(1000);
        char ch;
        opcion = 0;
        printf("Seleccione una opcion:\n");
        Sleep(1000);
        do { // Mostrar el menu de categorias
            menu_categorias(opcion);
            ch = getch(); // Leer la tecla presionada

            if (ch == 72){ // 72 es el codigo ASCII para la tecla de flecha arriba
                opcion = (opcion - 1 + 9) % 9; // 9 es el numero de opciones
            } else if (ch == 80){ // 80 es el codigo ASCII para la tecla de flecha abajo
                opcion = (opcion + 1) % 9; 
            }
        } while (ch != 13);  // 13 es el codigo ASCII para la tecla Enter

        system("cls");

    } while (opcion != 0 && opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4 && opcion != 5 && opcion != 6 && opcion != 7 && opcion != 8); 

    return opcion; // Retornar la opcion seleccionada
}
 
void categoria_palabra(struct nodoABB **raiz) { // Funcion para agregar la categoria de la palabra
    int opcion = 0;
    opcion = moverse_menu_categoria(); // Moverse en el menu de categorias
        switch (opcion) {
            case 0:
                strcpy((*raiz)->categoria, "Sustantivo");
                break;
            case 1:
                strcpy((*raiz)->categoria, "Adjetivo");
                break;
            case 2:
                strcpy((*raiz)->categoria, "Articulo");
                break;
            case 3:
                strcpy((*raiz)->categoria, "Pronombre");
                break;
            case 4:
                strcpy((*raiz)->categoria, "Verbo");
                break;
            case 5:
                strcpy((*raiz)->categoria, "Adverbio");
                break;
            case 6:
                strcpy((*raiz)->categoria, "Interjeccion");                
                break;
            case 7:
                strcpy((*raiz)->categoria, "Preposicion");
                break;
            case 8:
                strcpy((*raiz)->categoria, "Conjuncion");
                break;
        } 
}

void agregar_sinonimo(struct sinonimos **sinonimos) { // Funcion para agregar un sinonimo
    struct sinonimos *nuevo = malloc(sizeof(struct sinonimos)); // Asignar memoria para el nuevo nodo
    if (nuevo == NULL) { // Verificar si se pudo asignar memoria
        printf("No se pudo asignar memoria\n");
        return;
    }
    printf("Ingrese el sinonimo: "); // Pedir el sinonimo
    fgets(nuevo->sinonimo, 50, stdin); 
    nuevo->sinonimo[strcspn(nuevo->sinonimo, "\n")] = 0; // Eliminar el salto de linea
    nuevo->siguiente = *sinonimos; // El nuevo nodo apunta al primer nodo en la lista
    *sinonimos = nuevo; // El puntero a la cabeza de la lista ahora apunta al nuevo nodo
    printf("Sinonimo agregado correctamente\n");
    printf("Presione ESC para terminar\n");
    printf("Presione ENTER para ingresar otro sinonimo\n");
    char ch;
    ch = getch(); // Leer la tecla presionada
    if (ch == 13) { // 13 es el codigo ASCII para la tecla Enter
        system("cls");
        agregar_sinonimo(sinonimos); // Agregar otro sinonimo
    } else if (ch == 27) { // 27 es el codigo ASCII para la tecla ESC
        return; // Terminar
    }
    
}

void eliminar_sinonimo(struct sinonimos **sinonimos) { // Funcion para eliminar un sinonimo
    char sinonimo[50]; // Sinonimo a eliminar
    printf("Ingrese el sinonimo a eliminar: "); // Pedir el sinonimo
    fgets(sinonimo, 50, stdin); 
    sinonimo[strcspn(sinonimo, "\n")] = 0; // Eliminar el salto de linea
    struct sinonimos *actual = *sinonimos; // Nodo actual
    struct sinonimos *anterior = NULL; // Nodo anterior
    while (actual != NULL) { // Recorrer la lista de sinonimos
        if (strcmp(sinonimo, actual->sinonimo) == 0) { // Verificar si el sinonimo es igual al actual
            if (anterior == NULL) { // Verificar si el nodo anterior es nulo
                *sinonimos = actual->siguiente; // El puntero a la cabeza de la lista ahora apunta al siguiente nodo
            } else {
                anterior->siguiente = actual->siguiente; // El nodo anterior apunta al siguiente nodo
            }
            free(actual); // Liberar la memoria del nodo actual
            printf("Sinonimo eliminado correctamente\n"); // Mensaje de exito
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    printf("Sinonimo no encontrado\n");
}

void significado_palabra(struct nodoABB **raiz) { // Funcion para agregar el significado de la palabra
    printf("Ingrese el significado: "); // Pedir el significado
    fgets((*raiz)->significado, 80, stdin); 
    (*raiz)->significado[strcspn((*raiz)->significado, "\n")] = 0; // Eliminar el salto de linea
}

void agregar_palabra(struct nodoABB **raiz) { // Funcion para agregar una palabra
    struct nodoABB *nuevo = NULL; // Nuevo nodo
    nuevo = malloc(sizeof(struct nodoABB)); // Asignar memoria para el nuevo nodo
    if (nuevo == NULL) { // Verificar si se pudo asignar memoria
        printf("No se pudo asignar memoria\n");
        return;
    }
    printf("Ingrese la palabra: "); // Pedir la palabra
    fgets(nuevo->palabra, 50, stdin);
    nuevo->palabra[strcspn(nuevo->palabra, "\n")] = 0; // Eliminar el salto de linea
    significado_palabra(&nuevo); // Agregar el significado de la palabra
    categoria_palabra(&nuevo); // Agregar la categoria de la palabra
    nuevo->sinonimos = NULL; // Inicializar la lista de sinonimos
    agregar_sinonimo(&nuevo->sinonimos); // Agregar sinonimos
    nuevo->izquierda = NULL; // Inicializar el puntero izquierdo
    nuevo->derecha = NULL;  // Inicializar el puntero derecho
    if (*raiz == NULL) { // Verificar si la raiz es nula
        *raiz = nuevo;
    } else { // Si no es nula
        struct nodoABB *padre = NULL; // Nodo padre
        struct nodoABB *actual = *raiz; // Nodo actual
        while (actual != NULL) { // Recorrer el arbol
            padre = actual; // El padre es el actual
            if (strcmp(nuevo->palabra, actual->palabra) < 0) { // Verificar si la palabra es menor al actual
                actual = actual->izquierda; // El actual es el izquierdo
            } else { // Si no
                actual = actual->derecha; // El actual es el derecho
            }
        }
        if (strcmp(nuevo->palabra, padre->palabra) < 0) { // Verificar si la palabra es menor al padre
            padre->izquierda = nuevo; // El izquierdo del padre es el nuevo nodo
        } else { // Si no
            padre->derecha = nuevo; // El derecho del padre es el nuevo nodo
        }
    }
    printf("Palabra agregada correctamente\n"); // Mensaje de exito
}

void modificar_elemento(struct nodoABB **raiz) { // Funcion para modificar un elemento de la palabra
    if (*raiz == NULL) { // Verificar si la raiz es nula
        printf("No hay palabras en el diccionario\n");
        return;
    }
    char palabra[50]; // Palabra a modificar
    printf("Ingrese la palabra a modificar: "); // Pedir la palabra
    fgets(palabra, 50, stdin);
    palabra[strcspn(palabra, "\n")] = 0; // Eliminar el salto de linea
    struct nodoABB *actual = *raiz; // Nodo actual
    while (actual != NULL) { // Recorrer el arbol
        if (strcmp(palabra, actual->palabra) == 0) { // Verificar si la palabra es igual al actual
            printf("Palabra encontrada\n"); // Mensaje de exito
            printf("Que elemento desea modificar?\n"); // Preguntar que elemento desea modificar
            printf("1. Significado\n");
            printf("2. Categoria\n");
            printf("3. Sinonimos\n");
            int opcion = 0; // Opcion seleccionada
            while (opcion != 1 && opcion != 2 && opcion != 3) { 
                scanf("%d", &opcion); // Leer la opcion seleccionada
                getchar(); // Leer el salto de linea
                if (opcion == 1) { // Si la opcion es 1
                    significado_palabra(&actual); // Modificar el significado
                } else if (opcion == 2) { // Si la opcion es 2
                    categoria_palabra(&actual); // Modificar la categoria
                } else if (opcion == 3) { // Si la opcion es 3
                    int opcion_sinonimo = 0; // Opcion de sinonimo seleccionada
                    while(opcion_sinonimo != 1 && opcion_sinonimo != 2){ 
                        printf("Desea agregar algun sinonimo o eliminar algun sinonimo?\n"); // Preguntar si desea agregar o eliminar un sinonimo
                        printf("1. Agregar sinonimo\n");
                        printf("2. Eliminar sinonimo\n");
                        scanf("%d", &opcion_sinonimo); // Leer la opcion seleccionada
                        getchar();
                        if (opcion_sinonimo == 1) { // Si la opcion es 1
                            agregar_sinonimo(&actual->sinonimos); // Agregar sinonimos
                        } else if (opcion_sinonimo == 2) {
                            eliminar_sinonimo(&actual->sinonimos); // Eliminar un sinonimo
                        } else {
                            printf("Opcion no valida\n"); // Mensaje de error   
                        } 
                    }                   
                } else {
                    printf("Opcion no valida\n"); // Mensaje de error
                }
            }
            printf("Palabra modificada correctamente\n"); // Mensaje de exito
            return; // Terminar
        } else if (strcmp(palabra, actual->palabra) < 0) { // Si la palabra es menor al actual
            actual = actual->izquierda; // El actual es el izquierdo
        } else { // Si no
            actual = actual->derecha; // El actual es el derecho
        }
    }
    printf("Palabra no encontrada\n"); // Mensaje de error
}

struct nodoABB *encontrarMinimo(struct nodoABB **nodo) { // Funcion para encontrar el minimo
    struct nodoABB *actual = *nodo; // Nodo actual
    while (actual->izquierda != NULL) { // Mientras el izquierdo del actual no sea nulo
        actual = actual->izquierda; // El actual es el izquierdo
    }
    return actual; // Retornar el actual
}

void borrar_sinonimos(struct sinonimos **sinonimos) { // Funcion para borrar los sinonimos
    struct sinonimos *actual = *sinonimos; // Nodo actual
    while (actual != NULL) { // Mientras el actual no sea nulo
        struct sinonimos *temp = actual; // Nodo temporal
        actual = actual->siguiente; // El actual es el siguiente
        free(temp); // Liberar la memoria del temporal
    }
    *sinonimos = NULL; // El puntero a la cabeza de la lista ahora apunta a nulo
}

struct nodoABB *eliminar_palabra(struct nodoABB **raiz, char palabra[50]) { // Funcion para eliminar una palabra
    if (*raiz == NULL) { // Verificar si la raiz es nula
        return *raiz;
    }
    if (strcmp(palabra, (*raiz)->palabra) < 0) { // Verificar si la palabra es menor al actual
        (*raiz)->izquierda = eliminar_palabra(&(*raiz)->izquierda, palabra); // El izquierdo del actual es la eliminacion de la palabra
    } else if (strcmp(palabra, (*raiz)->palabra) > 0) { // Si no
        (*raiz)->derecha = eliminar_palabra(&(*raiz)->derecha, palabra); // El derecho del actual es la eliminacion de la palabra
    } else { // Si no
        if ((*raiz)->izquierda == NULL) { // Verificar si el izquierdo del actual es nulo
            struct nodoABB *temp = (*raiz)->derecha; // Nodo temporal
            borrar_sinonimos(&(*raiz)->sinonimos); // Borrar los sinonimos
            free((*raiz)); // Liberar la memoria del actual
            return temp; // Retornar el temporal
        } else if ((*raiz)->derecha == NULL) { // Si no
            struct nodoABB *temp = (*raiz)->izquierda; // Nodo temporal
            borrar_sinonimos(&(*raiz)->sinonimos); // Borrar los sinonimos
            free((*raiz)); // Liberar la memoria del actual
            return temp; // Retornar el temporal
        }
        
        struct nodoABB *temp = encontrarMinimo(&(*raiz)->derecha); // Nodo temporal
        strcpy((*raiz)->palabra, temp->palabra); // Copiar la palabra del temporal al actual
        strcpy((*raiz)->significado, temp->significado); // Copiar el significado del temporal al actual
        strcpy((*raiz)->categoria, temp->categoria); // Copiar la categoria del temporal al actual
        (*raiz)->sinonimos = temp->sinonimos; // Los sinonimos del actual son los del temporal
        (*raiz)->izquierda = temp->izquierda; // El izquierdo del actual es el izquierdo del temporal
        (*raiz)->derecha = temp->derecha; // El derecho del actual es el derecho del temporal
        (*raiz)->derecha = eliminar_palabra(&(*raiz)->derecha, temp->palabra); // El derecho del actual es la eliminacion de la palabra
    }
    return *raiz; // Retornar la raiz
}

void mostrar_palabras_elementos(struct nodoABB **raiz) { // Funcion para mostrar las palabras y sus elementos
    printf("Palabra:\n"); 
    printf("\t> %s\n", (*raiz)->palabra);
    printf("Significado:\n");
    printf("\t> %s\n", (*raiz)->significado);
    printf("Categoria:\n");
    printf("\t> %s\n", (*raiz)->categoria);
    printf("Sinonimos:\n");
    struct sinonimos *actual = (*raiz)->sinonimos;
    while (actual != NULL) { // Recorrer la lista de sinonimos
        printf("\t> %s\n", actual->sinonimo); // Mostrar el sinonimo
        actual = actual->siguiente; // El actual es el siguiente
    }
    printf("\n");
}

void mostrar_palabra(struct nodoABB **raiz) { // Funcion para mostrar la palabra
    printf("Palabra: %s\n", (*raiz)->palabra); 
}

void mostrar_elementos(struct nodoABB **raiz) { // Funcion para mostrar los elementos de la palabra
    if (*raiz == NULL) { // Verificar si la raiz es nula
        printf("No hay palabras en el diccionario\n");
        return;
    }
    struct nodoABB *actual = *raiz; // Nodo actual
    printf("Ingrese la palabra a mostrar: "); // Pedir la palabra
    char palabra[50];
    char ch;
    fgets(palabra, 50, stdin); 
    palabra[strcspn(palabra, "\n")] = 0; // Eliminar el salto de linea
    while (actual != NULL) { // Recorrer el arbol
        if (strcmp(palabra, actual->palabra) == 0) { // Verificar si la palabra es igual al actual
            mostrar_palabras_elementos(&actual); // Mostrar los elementos de la palabra
            Sleep(2000);
            printf("\nPresione cualquier tecla para continuar\n");
            ch = getch();
            return;
        } else if (strcmp(palabra, actual->palabra) < 0) { // Si la palabra es menor al actual
            actual = actual->izquierda; // El actual es el izquierdo
        } else {
            actual = actual->derecha; // El actual es el derecho
        }
    }
    printf("Palabra no encontrada\n");
}

void recorrer_arbol(struct nodoABB **raiz, char categoria[50], char letra, int general) { // Funcion para recorrer el arbol
    if (*raiz == NULL) { // Verificar si la raiz es nula
        return;
    }
    recorrer_arbol(&(*raiz)->izquierda, categoria, letra, general); // Recorrer el arbol
    if (strcmp((*raiz)->categoria, categoria) == 0 || letra == (*raiz)->palabra[0]) { // Verificar si la categoria es igual a la categoria del actual o la letra es igual a la primera letra de la palabra
        mostrar_palabras_elementos(raiz); // Mostrar los elementos de la palabra
    } else if (general == 1) { // Si no
        mostrar_palabra(raiz); // Mostrar la palabra
    }
    recorrer_arbol(&(*raiz)->derecha, categoria, letra, general); // Recorrer el arbol
}

void listado_categoria(struct nodoABB **raiz) { // Funcion para mostrar el listado de palabras por categoria
    if (*raiz == NULL) { // Verificar si la raiz es nula
        printf("No hay palabras en el diccionario\n");
        return;
    }
    struct nodoABB *actual = *raiz; // Nodo actual
    int opcion = 0; // Opcion seleccionada
    opcion = moverse_menu_categoria(); // Moverse en el menu de categorias
    char categoria[50];
    switch (opcion) {
        case 0:
            strcpy(categoria, "Sustantivo");
            break;
        case 1:
            strcpy(categoria, "Adjetivo");
            break;
        case 2:
            strcpy(categoria, "Articulo");
            break;
        case 3:
            strcpy(categoria, "Pronombre");
            break;
        case 4:
            strcpy(categoria, "Verbo");
            break;
        case 5:
            strcpy(categoria, "Adverbio");
            break;
        case 6:
            strcpy(categoria, "Interjeccion");                
            break;
        case 7:
            strcpy(categoria, "Preposicion");
            break;
        case 8:
            strcpy(categoria, "Conjuncion");
            break;
    }
    recorrer_arbol(&actual, categoria, '\n', 0); // Recorrer el arbol
    Sleep(2000);
    char ch;
    printf("\nPresione cualquier tecla para continuar\n"); // Mensaje de continuar
    ch = getch(); // Leer la tecla presionada
}

void listado_letra(struct nodoABB **raiz) { // Funcion para mostrar el listado de palabras por letra
    if (*raiz == NULL) { // Verificar si la raiz es nula
        printf("No hay palabras en el diccionario\n");
        return;
    }
    struct nodoABB *actual = *raiz; // Nodo actual
    char letra;
    printf("Ingrese la letra: "); // Pedir la letra
    scanf("%c", &letra);
    char nada[50] = "NULL"; 
    recorrer_arbol(&actual, nada, letra, 0); // Recorrer el arbol
    Sleep(2000);
    char ch;
    printf("\nPresione cualquier tecla para continuar\n");
    ch = getch();
}

void listado_alfabeticamente(struct nodoABB **raiz) { // Funcion para mostrar el listado general de palabras
    if (*raiz == NULL) { // Verificar si la raiz es nula
        printf("No hay palabras en el diccionario\n");
        return;
    }
    char nada[50] = "NULL"; 
    recorrer_arbol(raiz, nada, '\n', 1); // Recorrer el arbol
    Sleep(2000);
    char ch;
    printf("\nPresione cualquier tecla para continuar\n");
    ch = getch();
}

void menu_opciones(int opcion) { // Funcion para mostrar el menu de opciones
    system("cls");  
    if (opcion == 0) {
        printf(">> Agregar Palabra\n");
    } else if (opcion == 1) {
        printf(">> Modificar elementos\n");
    } else if (opcion == 2) {
        printf(">> Eliminar palabra\n");
    } else if (opcion == 3) {
        printf(">> Mostrar elementos\n");
    } else if (opcion == 4) {
        printf(">> Listado de palabras por categoria\n");
    } else if (opcion == 5) {
        printf(">> Listado de palabras por letra\n");
    } else if (opcion == 6) {
        printf(">> Listado de general de palabras\n");
    } else {
        printf(">> Salir\n");
    }
}

int main() { // Funcion principal
    struct nodoABB *raiz = NULL;
    int opcion = 0;
    do { // Mostrar el menu de opciones
        printf("Bienvenido al diccionario\n");
        Sleep(1000);
        char ch;
        printf("Seleccione una opcion:\n");
        Sleep(1000);
        do { // Mostrar el menu de opciones
            menu_opciones(opcion); 
            ch = getch(); // Leer la tecla presionada

            if (ch == 72){ // 72 es el codigo ASCII para la tecla de flecha arriba
                opcion = (opcion - 1 + 8) % 8; // 8 es el numero de opciones
            } else if (ch == 80){ // 80 es el codigo ASCII para la tecla de flecha abajo
                opcion = (opcion + 1) % 8; 
            }
        } while (ch != 13);  // 13 es el codigo ASCII para la tecla Enter

        switch (opcion) { // Seleccionar la opcion
            case 0:
                agregar_palabra(&raiz); // Agregar palabra
                Sleep(1000);
                system("cls");
                break;
            case 1:
                modificar_elemento(&raiz); // Modificar elemento
                Sleep(1000);
                system("cls");
                break;
            case 2:
                char palabra[50];
                printf("Ingrese la palabra a eliminar: ");
                fgets(palabra, 50, stdin);
                palabra[strcspn(palabra, "\n")] = 0; // Eliminar el salto de linea
                raiz = eliminar_palabra(&raiz, palabra); // Eliminar palabra
                printf("Palabra eliminada correctamente\n");
                Sleep(1000);
                system("cls");
                break;
            case 3:
                mostrar_elementos(&raiz); // Mostrar elementos
                Sleep(1000);
                system("cls");
                break;
            case 4:
                listado_categoria(&raiz); // Listado por categoria
                Sleep(1000);
                system("cls");
                break;
            case 5:
                listado_letra(&raiz); // Listado por letra
                Sleep(1000);
                system("cls");
                getchar();
                break;
            case 6:
                listado_alfabeticamente(&raiz); // Listado general
                Sleep(1000);
                system("cls");
                break;
            case 7:
                system("cls");
                printf("Cerrando...\n"); // Salir
                Sleep(1000);
                break;
        }
    } while (opcion != 7); // 7 es la opción para salir
    return 0;
}
