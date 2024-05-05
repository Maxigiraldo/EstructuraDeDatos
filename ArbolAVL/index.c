#include <stdio.h> // Incluimos la libreria stdio.h para poder utilizar las funciones de entrada y salida
#include <stdlib.h> // Incluimos la libreria stdlib.h para poder utilizar las funciones de memoria dinamica
#include <conio.h> // Incluimos la libreria conio.h para poder utilizar las funciones de entrada y salida de consola
#include <windows.h> // Incluimos la libreria windows.h para poder utilizar las funciones de la API de Windows
#include <string.h> // Incluimos la libreria string.h para poder utilizar las funciones de cadenas de texto

// Estructura para los sinonimos
struct sinonimos { 
    char sinonimo[50]; // Sinonimo de la palabra
    struct sinonimos *siguiente; // Puntero al siguiente nodo
};

// Estructura para los nodos del arbol AVL
struct nodoAVL {
    char palabra[50]; // Palabra a almacenar
    char significado[80]; // Significado de la palabra
    char categoria[50]; // Categoria de la palabra
    int altura; // Altura del nodo
    struct sinonimos *sinonimos; // Lista de sinonimos
    struct nodoAVL *izquierda;
    struct nodoAVL *derecha;
};

// Funcion para mostrar el menu de categorias
void menu_categorias(int opcion) { 
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

// Funcion para moverse en el menu de categorias
int moverse_menu_categoria(){ 
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
 
// Funcion para agregar la categoria de la palabra
void categoria_palabra(char categoria[50]) { 
    int opcion = 0;
    opcion = moverse_menu_categoria(); // Moverse en el menu de categorias
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
}

// Funcion para agregar un sinonimo
void agregar_sinonimo(struct sinonimos **sinonimos) { 
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

// Funcion para borrar los sinonimos
void borrar_sinonimos(struct sinonimos **sinonimos) { 
    struct sinonimos *actual = *sinonimos; // Nodo actual
    while (actual != NULL) { // Mientras el actual no sea nulo
        struct sinonimos *temp = actual; // Nodo temporal
        actual = actual->siguiente; // El actual es el siguiente
        free(temp); // Liberar la memoria del temporal
    }
    *sinonimos = NULL; // El puntero a la cabeza de la lista ahora apunta a nulo
}

// Funcion para eliminar un sinonimo
void eliminar_sinonimo(struct sinonimos **sinonimos) { 
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

// Funcion para agregar el significado de la palabra
void significado_palabra(char significado[80]) { 
    printf("Ingrese el significado: "); // Pedir el significado
    fgets(significado, 80, stdin); 
    significado[strcspn(significado, "\n")] = 0; // Eliminar el salto de linea
}

// Funcion para obtener la altura de un nodo
int altura(struct nodoAVL *nodo) {
    if (nodo == NULL)
        return 0;
    return nodo->altura;
}

// Funcion para obtener el maximo de dos numeros enteros
int maximo(int a, int b) {
    return (a > b) ? a : b;
}

// Funcion para crear un nuevo nodo
struct nodoAVL *Nuevo_nodo(char palabra[50], char significado[80], char categoria[50]) {
    struct nodoAVL *nuevo = malloc(sizeof(struct nodoAVL)); // Nuevo nodo
    strcpy(nuevo->palabra, palabra); // Copiar la palabra
    strcpy(nuevo->significado, significado); // Copiar el significado
    strcpy(nuevo->categoria, categoria); // Copiar la categoria
    nuevo->sinonimos = NULL; // Inicializar la lista de sinonimos
    nuevo->izquierda = NULL; // Inicializar el puntero izquierdo
    nuevo->derecha = NULL;  // Inicializar el puntero derecho
    nuevo->altura = 1; // Inicializar la altura
    return(nuevo); // Retornar el nuevo nodo
}

// Rotacion simple a la derecha
struct nodoAVL *rotacion_derecha(struct nodoAVL *y) {
    struct nodoAVL *x = y->izquierda;
    struct nodoAVL *T2 = x->derecha;

    // Realizar rotacion
    x->derecha = y;
    y->izquierda = T2;

    // Actualizar alturas
    y->altura = maximo(altura(y->izquierda), altura(y->derecha)) + 1;
    x->altura = maximo(altura(x->izquierda), altura(x->derecha)) + 1;

    // Retornar nueva raiz
    return x;
}

// Rotacion simple a la izquierda
struct nodoAVL *rotacion_izquierda(struct nodoAVL *x) {
    struct nodoAVL *y = x->derecha;
    struct nodoAVL *T2 = y->izquierda;

    // Realizar rotacion
    y->izquierda = x;
    x->derecha = T2;

    // Actualizar alturas
    x->altura = maximo(altura(x->izquierda), altura(x->derecha)) + 1;
    y->altura = maximo(altura(y->izquierda), altura(y->derecha)) + 1;

    // Retornar nueva raiz
    return y;
}

// Obtener el factor de equilibrio de un nodo
int obtener_balance(struct nodoAVL *nodo) {
    if (nodo == NULL)
        return 0;
    return altura(nodo->izquierda) - altura(nodo->derecha);
}

// Funcion para agregar una palabra
struct nodoAVL *agregar_palabra(struct nodoAVL **raiz, char palabra[50], char significado[80], char categoria[50]) { 
    if (*raiz == NULL) { // Verificar si la raiz es nula
        return(Nuevo_nodo(palabra, significado, categoria)); // Agregar la palabra
    }
    if (strcmp(palabra, (*raiz)->palabra) < 0) { // Verificar si la palabra es menor al actual
        (*raiz)->izquierda = agregar_palabra(&(*raiz)->izquierda, palabra, significado, categoria); // Agregar la palabra al izquierdo
    } else if (strcmp(palabra, (*raiz)->palabra) > 0) { // Si no
        (*raiz)->derecha = agregar_palabra(&(*raiz)->derecha, palabra, significado, categoria); // Agregar la palabra al derecho
    } else {
        return *raiz; // Retornar la raiz
    }
    (*raiz)->altura = 1 + maximo(altura((*raiz)->izquierda), altura((*raiz)->derecha)); // Actualizar la altura
    int balance = obtener_balance(*raiz); // Obtener el factor de equilibrio

    // Caso izquierda izquierda
    if (balance > 1 && strcmp(palabra, (*raiz)->izquierda->palabra) < 0) {
        return rotacion_derecha(*raiz);
    }
    
    // Caso derecha derecha
    if (balance < -1 && strcmp(palabra, (*raiz)->derecha->palabra) > 0) {
        return rotacion_izquierda(*raiz);
    }

    // Caso izquierda derecha
    if (balance > 1 && strcmp(palabra, (*raiz)->izquierda->palabra) > 0) {
        (*raiz)->izquierda = rotacion_izquierda((*raiz)->izquierda);
        return rotacion_derecha(*raiz);
    }

    // Caso derecha izquierda
    if (balance < -1 && strcmp(palabra, (*raiz)->derecha->palabra) < 0) {
        (*raiz)->derecha = rotacion_derecha((*raiz)->derecha);
        return rotacion_izquierda(*raiz);
    }

    return *raiz; // Retornar la raiz
}

// Funcion para modificar un elemento de la palabra
void modificar_elemento(struct nodoAVL **raiz) { 
    if (*raiz == NULL) { // Verificar si la raiz es nula
        printf("No hay palabras en el diccionario\n");
        return;
    }
    char palabra[50]; // Palabra a modificar
    printf("Ingrese la palabra a modificar: "); // Pedir la palabra
    fgets(palabra, 50, stdin);
    palabra[strcspn(palabra, "\n")] = 0; // Eliminar el salto de linea
    struct nodoAVL *actual = *raiz; // Nodo actual
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
                    char significado[80]; // Significado de la palabra
                    significado_palabra(significado); // Modificar el significado
                    strcpy(actual->significado, significado); // Copiar el significado al actual
                } else if (opcion == 2) { // Si la opcion es 2
                    char categoria[50]; // Categoria de la palabra
                    categoria_palabra(categoria); // Modificar la categoria
                    strcpy(actual->categoria, categoria); // Copiar la categoria al actual
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

// Funcion para encontrar el minimo
struct nodoAVL *encontrarMinimo(struct nodoAVL **nodo) { 
    struct nodoAVL *actual = *nodo; // Nodo actual
    while (actual->izquierda != NULL) { // Mientras el izquierdo del actual no sea nulo
        actual = actual->izquierda; // El actual es el izquierdo
    }
    return actual; // Retornar el actual
}

// Funcion para eliminar una palabra
struct nodoAVL *eliminar_palabra(struct nodoAVL **raiz, char palabra[50]) { 
    if (*raiz == NULL) { // Verificar si la raiz es nula
        return *raiz; // Retornar la raiz
    }
    if (strcmp(palabra, (*raiz)->palabra) < 0) { // Verificar si la palabra es menor al actual
        (*raiz)->izquierda = eliminar_palabra(&(*raiz)->izquierda, palabra); // Eliminar la palabra del izquierdo
    } else if (strcmp(palabra, (*raiz)->palabra) > 0) { // Si no
        (*raiz)->derecha = eliminar_palabra(&(*raiz)->derecha, palabra); // Eliminar la palabra del derecho
    } else { // Si no
        if (((*raiz)->izquierda == NULL) || ((*raiz)->derecha == NULL)) { // Verificar si el izquierdo o derecho del actual es nulo
            struct nodoAVL *temp = (*raiz)->izquierda ? (*raiz)->izquierda : (*raiz)->derecha; // Nodo temporal
            if (temp == NULL) { // Verificar si el temporal es nulo
                temp = *raiz; // El temporal es la raiz
                *raiz = NULL; // La raiz es nula
            } else {
                **raiz = *temp; // La raiz es el temporal
            }
            borrar_sinonimos(&temp->sinonimos); // Borrar los sinonimos
            free(temp); // Liberar la memoria del temporal
        } else {
            struct nodoAVL *temp = encontrarMinimo(&(*raiz)->derecha); // Nodo temporal
            strcpy((*raiz)->palabra, temp->palabra); // Copiar la palabra del temporal al actual
            (*raiz)->derecha = eliminar_palabra(&(*raiz)->derecha, temp->palabra); // Eliminar la palabra del derecho
        }
    }
    if (*raiz == NULL) { // Verificar si la raiz es nula
        return *raiz; // Retornar la raiz
    }
    (*raiz)->altura = 1 + maximo(altura((*raiz)->izquierda), altura((*raiz)->derecha)); // Actualizar la altura
    int balance = obtener_balance(*raiz); // Obtener el factor de equilibrio

    // Caso izquierda izquierda
    if (balance > 1 && obtener_balance((*raiz)->izquierda) >= 0) {
        return rotacion_derecha(*raiz);
    }

    // Caso izquierda derecha
    if (balance > 1 && obtener_balance((*raiz)->izquierda) < 0) {
        (*raiz)->izquierda = rotacion_izquierda((*raiz)->izquierda);
        return rotacion_derecha(*raiz);
    }

    // Caso derecha derecha
    if (balance < -1 && obtener_balance((*raiz)->derecha) <= 0) {
        return rotacion_izquierda(*raiz);
    }

    // Caso derecha izquierda
    if (balance < -1 && obtener_balance((*raiz)->derecha) > 0) {
        (*raiz)->derecha = rotacion_derecha((*raiz)->derecha);
        return rotacion_izquierda(*raiz);
    }

    return *raiz; // Retornar la raiz
}

// Funcion para mostrar las palabras y sus elementos
void mostrar_palabras_elementos(struct nodoAVL **raiz) { 
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

// Funcion para mostrar la palabra
void mostrar_palabra(struct nodoAVL **raiz) { 
    printf("Palabra: %s\n", (*raiz)->palabra); 
}

// Funcion para mostrar los elementos de la palabra
void mostrar_elementos(struct nodoAVL **raiz) { 
    if (*raiz == NULL) { // Verificar si la raiz es nula
        printf("No hay palabras en el diccionario\n");
        return;
    }
    struct nodoAVL *actual = *raiz; // Nodo actual
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

// Funcion para recorrer el arbol
void recorrer_arbol(struct nodoAVL **raiz, char categoria[50], char letra, int general) { 
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

// Funcion para mostrar el listado de palabras por categoria
void listado_categoria(struct nodoAVL **raiz) { 
    if (*raiz == NULL) { // Verificar si la raiz es nula
        printf("No hay palabras en el diccionario\n");
        return;
    }
    struct nodoAVL *actual = *raiz; // Nodo actual
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

// Funcion para mostrar el listado de palabras por letra
void listado_letra(struct nodoAVL **raiz) { 
    if (*raiz == NULL) { // Verificar si la raiz es nula
        printf("No hay palabras en el diccionario\n");
        return;
    }
    struct nodoAVL *actual = *raiz; // Nodo actual
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

// Funcion para mostrar el listado general de palabras
void listado_alfabeticamente(struct nodoAVL **raiz) { 
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

// Funcion para mover el cursor en la consola
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Funcion para calcular la anchura del subarbol
void dibujarArbolVisual(struct nodoAVL *raiz, int x, int y) {
    if (raiz != NULL) {
        gotoxy(x, y);
        printf("%.3s", raiz->palabra);

        if (raiz->izquierda != NULL) {
            gotoxy(x - 2, y + 2);
            printf("/");
            dibujarArbolVisual(raiz->izquierda, x - 4, y + 4);
        }

        if (raiz->derecha != NULL) {
            gotoxy(x + 2, y + 2);
            printf("\\");
            dibujarArbolVisual(raiz->derecha, x + 4, y + 4);
        }
    }
}

// Funcion para mostrar el menu de opciones
void menu_opciones(int opcion) { 
    system("cls");  
    if (opcion == 0) {
        printf(">> Agregar palabra\n");
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
    } else if (opcion == 7) {
        printf(">> Ver arbol\n");
    } else {
        printf(">> Salir\n");
    }
}

// Funcion principal
int main() { 
    struct nodoAVL *raiz = NULL;
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
                opcion = (opcion - 1 + 9) % 9; // 8 es el numero de opciones
            } else if (ch == 80){ // 80 es el codigo ASCII para la tecla de flecha abajo
                opcion = (opcion + 1) % 9; 
            }
        } while (ch != 13);  // 13 es el codigo ASCII para la tecla Enter

        switch (opcion) { // Seleccionar la opcion
            case 0:
                int confirmacion = 0;
                char palabra[50], significado[80], categoria[50];
                do {
                    printf("Ingrese la palabra: "); // Pedir la palabra
                    fgets(palabra, 50, stdin);
                    palabra[strcspn(palabra, "\n")] = 0; // Eliminar el salto de linea
                    if (strcmp(palabra, "") == 0) { // Verificar si la palabra es vacia
                        printf("La palabra no puede estar vacia\n");
                        confirmacion = 0;
                    } else if (palabra[0] > 96 && palabra[0] < 123) { // Verificar si la primera letra de la palabra es minuscula
                        printf("La primera letra de la palabra debe ser mayuscula\n");
                        confirmacion = 0;
                    } else {
                        confirmacion = 1;
                        
                    }
                } while (confirmacion == 0); // Verificar si la confirmacion es igual a 0
                significado_palabra(significado); // Agregar el significado de la palabra
                categoria_palabra(categoria); // Agregar la categoria de la palabra
                raiz = agregar_palabra(&raiz, palabra, significado, categoria); // Agregar palabra
                Sleep(1000);
                system("cls");
                break;
            case 1:
                modificar_elemento(&raiz); // Modificar elemento
                Sleep(1000);
                system("cls");
                break;
            case 2:
                char palabra_eliminar[50];
                printf("Ingrese la palabra a eliminar: ");
                fgets(palabra_eliminar, 50, stdin);
                palabra_eliminar[strcspn(palabra_eliminar, "\n")] = 0; // Eliminar el salto de linea
                raiz = eliminar_palabra(&raiz, palabra_eliminar); // Eliminar palabra
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
                dibujarArbolVisual(raiz, 40, 5);
                Sleep(5000);
                system("cls");
                break;
            case 8:
                system("cls");
                printf("Cerrando...\n"); // Salir
                Sleep(1000);
                break;
        }
    } while (opcion != 8); // 8 es la opción para salir
    return 0;
}
