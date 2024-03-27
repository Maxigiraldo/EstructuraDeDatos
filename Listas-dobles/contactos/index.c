// Autor: Maximiliano Giraldo Ocampo
#include <stdio.h> // Incluye la biblioteca estándar de E/S
#include <stdlib.h> // Incluye la biblioteca estándar
#include <string.h> // Incluye la biblioteca de cadenas
#include <conio.h> // Incluye la biblioteca de entrada/salida
#include <windows.h> // Incluye la biblioteca de Windows
#include <ctype.h> // Incluye la biblioteca de caracteres

struct contacto { // Estructura de un contacto
    char nombre[50];
    char apellido[50];
    char telefono[20];
    char whatsapp[20];
    char email[50];
    char estado;
    struct contacto *siguiente;
    struct contacto *anterior;
};

void mayus(char *cadena) { // Función para convertir la primera letra de una cadena a mayusculas
    // Verifica si la cadena es vacía
    if (*cadena != '\0') {
        // Si el primer caracter es una letra minuscula, cambiarla a mayuscula
        if (islower(*cadena)) {
            *cadena = toupper(*cadena);
        }
    }
}

void verificar_posicion(struct contacto **inicio, struct contacto **final, struct contacto *nuevo) { // Función para verificar la posición de un contacto
    struct contacto *actual = *inicio;
    while (actual != NULL) { // Mientras el contacto actual no sea vacio
        if(strcmp(nuevo->apellido, actual->apellido) < 0){
            if(actual == *inicio){
                nuevo->siguiente = *inicio;
                (*inicio)->anterior = nuevo;
                *inicio = nuevo;
                break;
            } else { // Si el contacto actual no es el primero
                nuevo->siguiente = actual;
                nuevo->anterior = actual->anterior;
                actual->anterior->siguiente = nuevo;
                actual->anterior = nuevo;
                break;
            }
        } else if (actual == *final) { // Si el contacto actual es el ultimo
            (*final)->siguiente = nuevo;
            nuevo->anterior = *final;
            *final = nuevo;
            break;
        }
        actual = actual->siguiente; // Pasar al siguiente contacto
    }
}

void agregar_contacto(struct contacto **inicio, struct contacto **final){ // Función para agregar un contacto
    struct contacto *nuevo; // Crear un nuevo contacto
    nuevo = malloc(sizeof(struct contacto)); // Asignar memoria al nuevo contacto
    printf("Ingrese el nombre: "); // Solicitar el nombre del contacto
    fgets(nuevo->nombre, 50, stdin); // Leer el nombre del contacto
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = 0; // Eliminar el salto de linea
    mayus(nuevo->nombre); // Convertir la primera letra del nombre a mayuscula
    printf("Ingrese el apellido: "); // Solicitar el apellido del contacto
    fgets(nuevo->apellido, 50, stdin); // Leer el apellido del contacto
    nuevo->apellido[strcspn(nuevo->apellido, "\n")] = 0; // Eliminar el salto de linea
    mayus(nuevo->apellido); // Convertir la primera letra del apellido a mayuscula
    printf("Ingrese el telefono: "); // Solicitar el telefono del contacto
    fgets(nuevo->telefono, 20, stdin); // Leer el telefono del contacto
    nuevo->telefono[strcspn(nuevo->telefono, "\n")] = 0; // Eliminar el salto de linea
    printf("Ingrese el whatsapp: "); // Solicitar el whatsapp del contacto
    fgets(nuevo->whatsapp, 20, stdin); // Leer el whatsapp del contacto
    nuevo->whatsapp[strcspn(nuevo->whatsapp, "\n")] = 0; // Eliminar el salto de linea
    printf("Ingrese el email: "); // Solicitar el email del contacto
    fgets(nuevo->email, 50, stdin); // Leer el email del contacto
    nuevo->email[strcspn(nuevo->email, "\n")] = 0; // Eliminar el salto de linea
    nuevo->estado = 'A'; // Establecer el estado del contacto como activo
    nuevo->siguiente = NULL; // Establecer el siguiente contacto como vacio
    nuevo->anterior = NULL; // Establecer el contacto anterior como vacio
    if (*inicio == NULL) { // Si el contacto es el primero
        *inicio = nuevo; // Establecer el contacto como el primero
        *final = nuevo; // Establecer el contacto como el ultimo
    } else {
        verificar_posicion(inicio, final, nuevo);
    }
    printf("Contacto agregado correctamente\n"); // Mostrar mensaje de contacto agregado
    Sleep(1000); // Esperar 1 segundo
    system("cls"); // Limpiar la pantalla
}

void ver_contacto(struct contacto *contacto) { // Función para ver un contacto
    printf("Contacto:\n\n"); // Mostrar contacto
    printf("\tNombre: %s\n", contacto->nombre); 
    printf("\tApellido: %s\n", contacto->apellido);
    printf("\tTelefono: %s\n", contacto->telefono);
    printf("\tWhatsapp: %s\n", contacto->whatsapp);
    printf("\tEmail: %s\n", contacto->email);
    printf("\tEstado: %c\n\n", contacto->estado);
}

void opciones_consulta(){ // Función para mostrar las opciones de consulta
    printf("Ver siguiente contacto (^/>)\n"); // Mostrar opciones de consulta
    printf("Ver anterior contacto (v/<)\n");
    printf("Salir (ESC)\n");
    printf("Borrar contacto (ENTER)\n");
}


void confirmacion(int op){ // Función para mostrar la confirmación
    system("cls");  
    if (op == 0) { 
        printf(">> Si\n");
        printf("   No\n");
    } else {
        printf("   Si\n");
        printf(">> No\n");
    }
}

void consulta(struct contacto **inicio, struct contacto **final){ // Función para consultar un contacto
    struct contacto *actual = *inicio; // Establecer el contacto actual como el primero
    char ch;
    int opcion = 0;
    do {
        system("cls");
        if(actual != NULL){ 
            if (actual->anterior == NULL) { // Si el contacto actual es el primero
                printf("------Primer contacto--------\n\n");
            } else if (actual->siguiente == NULL) {
                printf("------Ultimo contacto--------\n\n");
            }
            ver_contacto(actual); // Mostrar el contacto actual
        } else {
            printf("No hay mas contactos\n"); 
            Sleep(1000);
            break;
        }
        opciones_consulta(); // Mostrar las opciones de consulta
        ch = getch();
        if (ch == 0 || ch == 224) {
            switch (getch()) {
                case 72:  // Flecha arriba
                    if (actual->siguiente != NULL) {
                        actual = actual->siguiente;
                    }
                    break;
                case 75:  // Flecha izquierda
                    if (actual->anterior != NULL) {
                        actual = actual->anterior;
                    }
                    break;
                case 77:  // Flecha derecha
                    if (actual->siguiente != NULL) {
                        actual = actual->siguiente;
                    }
                    break;
                case 80:  // Flecha abajo
                    if (actual->anterior != NULL) {
                        actual = actual->anterior;
                    }
                    break;
            }
        } else if (ch == 13) { // Si se presiona Enter
            if (actual->estado == 'A') {
                printf("Contacto activo\n");
                printf("Desea borrar el contacto?\n");
                Sleep(1000);
                do {
                    confirmacion(opcion);
                    ch = getch();
                    if (ch == 0 || ch == 224) {
                        switch (getch()) {
                            case 72:  // Flecha arriba
                                opcion = (opcion - 1 + 2) % 2;
                                break;
                            case 80:  // Flecha abajo
                                opcion = (opcion + 1) % 2;
                                break;
                        }
                    }
                } while (ch != 13);
                if (opcion == 0){
                    actual->estado = 'B';
                } else {
                    printf("Contacto no borrado\n");
                    Sleep(1000);
                }
                Sleep(1000);
            } else {
                printf("Contacto ya borrado\n");
                printf("Desea activar el contacto?\n");
                Sleep(1000);
                do {
                    confirmacion(opcion);
                    ch = getch();
                    if (ch == 0 || ch == 224) {
                        switch (getch()) {
                            case 72:  // Flecha arriba
                                opcion = (opcion - 1 + 2) % 2;
                                break;
                            case 80:  // Flecha abajo
                                opcion = (opcion + 1) % 2;
                                break;
                        }
                    }
                } while (ch != 13);
                if (opcion == 0){
                    actual->estado = 'A';
                } else {
                    printf("Contacto no activado\n");
                    Sleep(1000);
                }

                Sleep(1000);
            }
            break;
        }
    } while (ch != 27);

}

void menu_modificar(int opcion) { // Función para mostrar el menú de modificar
    system("cls");  
    if (opcion == 0) {
        printf(">> Telefono\n");
        printf("   Whatsapp\n");
        printf("   Email\n");
        printf("   Salir\n");
    } else if (opcion == 1) {
        printf("   Telefono\n");
        printf(">> Whatsapp\n");
        printf("   Email\n");
        printf("   Salir\n");
    } else if (opcion == 2) {
        printf("   Telefono\n");
        printf("   Whatsapp\n");
        printf(">> Email\n");
        printf("   Salir\n");
    } else {
        printf("   Telefono\n");
        printf("   Whatsapp\n");
        printf("   Email\n");
        printf(">> Salir\n");
    }
}



void cambio(struct contacto **inicio, char busqueda[]){ // Función para modificar un contacto
    struct contacto *actual = *inicio;
    while (actual != NULL){ // Mientras el contacto actual no sea vacio
        if ((strcmp(busqueda, actual->nombre) == 0) || (strcmp(busqueda, actual->apellido) == 0)){ // Si el contacto actual es el contacto a modificar
            printf("Contacto encontrado\n");
            Sleep(1000);
            system("cls"); 
            printf("Contacto:\n\n"); // Mostrar el contacto actual
            printf("\tNombre: %s\n", actual->nombre);
            printf("\tApellido: %s\n", actual->apellido);
            printf("\tTelefono: %s\n", actual->telefono);
            printf("\tWhatsapp: %s\n", actual->whatsapp);
            printf("\tEmail: %s\n", actual->email);
            printf("\tEstado: %c\n\n", actual->estado);
            printf("Desea modificar el contacto?\n");
            Sleep(2000);
            int opcion = 0;
            char ch;
            do { 
                confirmacion(opcion); // Mostrar la confirmación
                ch = getch();
                if (ch == 0 || ch == 224) {
                    switch (getch()) {
                        case 72:  // Flecha arriba
                            opcion = (opcion - 1 + 2) % 2;
                            break;
                        case 80:  // Flecha abajo
                            opcion = (opcion + 1) % 2;
                            break;
                    }
                }
            } while (ch != 13);
            if (opcion == 0){
                printf("Que desea modificar?\n");
                do {
                    menu_modificar(opcion); // Mostrar el menú de modificar
                    ch = getch();
                    if (ch == 0 || ch == 224) {
                        switch (getch()) {
                            case 72:  // Flecha arriba
                                opcion = (opcion - 1 + 4) % 4;
                                break;
                            case 80:  // Flecha abajo
                                opcion = (opcion + 1) % 4;
                                break;
                        }
                    }
                } while (ch != 13);
                system("cls");
                if (opcion == 0){ // Si se selecciona el telefono
                    printf("Ingrese el nuevo telefono: ");
                    fgets(actual->telefono, 20, stdin);
                    actual->telefono[strcspn(actual->telefono, "\n")] = 0;
                    Sleep(1000);
                    printf("Contacto modificado correctamente\n");
                } else if (opcion == 1){ // Si se selecciona el whatsapp
                    printf("Ingrese el nuevo whatsapp: ");
                    fgets(actual->whatsapp, 20, stdin);
                    actual->whatsapp[strcspn(actual->whatsapp, "\n")] = 0;
                    Sleep(1000);
                    printf("Contacto modificado correctamente\n");
                } else if (opcion == 2){ // Si se selecciona el email
                    printf("Ingrese el nuevo email: ");
                    fgets(actual->email, 50, stdin);
                    actual->email[strcspn(actual->email, "\n")] = 0;
                    Sleep(1000);
                    printf("Contacto modificado correctamente\n");
                } else { // Si se selecciona salir
                    printf("Regresando...\n");
                }
                Sleep(1000);
                system("cls");
                return;
            } else { // Si no se desea modificar el contacto
                printf("Contacto no modificado\n");
                Sleep(1000);
                system("cls");
                return;
            }
        } else { // Si el contacto actual no es el contacto a modificar
            actual = actual->siguiente;
        }    
    }
    if (actual == NULL){ // Si el contacto no se encuentra
        printf("Contacto no encontrado\n");
        Sleep(1000);
        system("cls");
        return;
    }
}

void forma_busqueda(int op) { // Función para mostrar la forma de búsqueda
    system("cls");  
    if (op == 0) {
        printf(">> Buscar\n");
        printf("   Salir\n");
    }  else {
        printf("   Buscar\n");
        printf(">> Salir\n");
    }

}

void modificar_contacto(struct contacto **inicio){ // Función para modificar un contacto
    char ch;
    int opcion = 0;
    char busqueda[50];
    if (*inicio == NULL) {
        printf("No hay contactos\n");
        Sleep(1000);
        return;
    }
    printf("Desea buscar contacto?\n");
    Sleep(1000);
    system("cls");
    do { 
        forma_busqueda(opcion); // Mostrar la forma de búsqueda
        ch = getch();
        if (ch == 0 || ch == 224) {
            switch (getch()) {
                case 72:  // Flecha arriba
                    opcion = (opcion - 1 + 2) % 2;
                    break;
                case 80:  // Flecha abajo
                    opcion = (opcion + 1) % 2;
                    break;
            }
        }
    }   while (ch != 13);
    
    system("cls");

    switch (opcion) {
        case 0:
            printf("Ingrese el nombre o el apellido: ");
            fgets(busqueda, 50, stdin);
            busqueda[strcspn(busqueda, "\n")] = 0;
            cambio(inicio, busqueda);
            break;
        case 1:
            printf("Regresando...\n");
            Sleep(1000);
            break;
    }

}
   

void menu_opciones(int opcion) { // Función para mostrar el menú de opciones
    system("cls");  
    if (opcion == 0) {
        printf(">> Agregar Contacto\n");
        printf("   Consultar Contacto\n");
        printf("   Modificar Contacto\n");
        printf("   Salir\n");
    } else if (opcion == 1) {
        printf("   Agregar Contacto\n");
        printf(">> Consultar Contacto\n");
        printf("   Modificar Contacto\n");
        printf("   Salir\n");
    } else if (opcion == 2) {
        printf("   Agregar Contacto\n");
        printf("   Consultar Contacto\n");
        printf(">> Modificar Contacto\n");
        printf("   Salir\n");
    } else {
        printf("   Agregar Contacto\n");
        printf("   Consultar Contacto\n");
        printf("   Modificar Contacto\n");
        printf(">> Salir\n");
    }
}

int main(){ // Función principal
    struct contacto *inicio = NULL;
    struct contacto *fin = NULL;
    int opcion = 0;
    do {
        printf("-------Bienvenido a la agenda de contactos--------\n\n");
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
                        opcion = (opcion - 1 + 4) % 4;
                        break;
                    case 80:  // Flecha abajo
                        opcion = (opcion + 1) % 4;
                        break;
                }
            }
        } while (ch != 13);  // 13 es el código ASCII para la tecla Enter

        system("cls"); 

        switch (opcion) {
            case 0:
                agregar_contacto(&inicio, &fin);
                break;
            case 1:
                consulta(&inicio, &fin);
                break;
            case 2:
                modificar_contacto(&inicio);
                break;
            case 3:
                printf("Cerrando...\n");
                break;
        }
    } while (opcion != 3);
    return 0;
}
