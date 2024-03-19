#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definición de la estructura
struct turno {
    int identificación;
    char apellidos[30];
    char nombre[30];
    int edad;
    char sexo;
    int celular;
    char fecha[10];
    struct turno *siguiente;
};

//Funcione para verificar si la cola esta vacia
int vacia(struct turno *cabeza){
    if (cabeza == NULL){
        return 1; //La cola esta vacia
    } else {
        return 0; //La cola no esta vacia
    }
}

//Función para ingresar los datos de la cola
void ingresar_persona(struct turno **cabeza, struct turno **cola, int id, char apellidos[], char nombre[], int edad, char sexo, int celular, char fecha[]) {
    //Se crea un nuevo nodo
    struct turno *nuevo;
    //Se reserva memoria para el nuevo nodo
    nuevo = malloc(sizeof(struct turno));
    //Se asignan los valores al nuevo nodo
    strcpy(nuevo->apellidos, apellidos);
    nuevo->celular = celular;
    nuevo->edad = edad;
    strcpy(nuevo->fecha, fecha);
    nuevo->identificación = id;
    strcpy(nuevo->nombre, nombre);
    nuevo->sexo = sexo;
    nuevo->siguiente = NULL;
    //Se verifica si la cola esta vacia
    if (vacia(*cabeza) == 1){
        //Si la cola esta vacia, el nuevo nodo es el primer y último nodo de la cola
        *cabeza = nuevo;
        *cola = nuevo;
    } else {
        //Se enlaza el nuevo nodo con el último nodo de la cola
        (*cola)->siguiente = nuevo;
        *cola = nuevo;
    } 
}

//Función para agregar un usuario a la pila de atendidos
void usuario_atendido(struct turno **cabeza, int id, char apellidos[], char nombre[], int edad, char sexo, int celular, char fecha[]){
    //Se crea un nuevo nodo
    struct turno *nuevo;
    nuevo = malloc(sizeof(struct turno));
    strcpy(nuevo->apellidos, apellidos);
    nuevo->celular = celular;
    nuevo->edad = edad;
    strcpy(nuevo->fecha, fecha);
    nuevo->identificación = id;
    strcpy(nuevo->nombre, nombre);
    nuevo->sexo = sexo;
    //Se verifica si la pila esta vacia
    if (vacia(*cabeza) == 1){
        //Si la pila esta vacia, el nuevo nodo es el primer nodo de la pila
        nuevo->siguiente = NULL;
        *cabeza = nuevo;
    } else {
        //Se enlaza el nuevo nodo con el primer nodo de la pila
        nuevo->siguiente = *cabeza;
        *cabeza = nuevo;
    }
}

//Función para pedir los datos de la cola
void datos(struct turno **prioridad1_cabeza, struct turno **prioridad1_cola, struct turno **prioridad2_cabeza, struct turno **prioridad2_cola, struct turno **prioridad3_cabeza, struct turno **prioridad3_cola){
    //Se piden los datos de la persona
    int id = 0;
    char apellidos[30];
    char nombre[30];
    int edad = 0;
    char sexo;
    int celular = 0;;
    char fecha[10];
    int op = 0;
    printf("Ingrese su ID:\n");
    scanf("%d", &id);
    fflush(stdin);
    printf("Ingrese su apellido:\n");
    fgets(apellidos, 30, stdin);
    apellidos[strcspn(apellidos, "\n")] = 0;
    printf("Ingrese su nombre:\n");
    fgets(nombre, 30, stdin);
    nombre[strcspn(nombre, "\n")] = 0;
    fflush(stdin);
    printf("Ingrese su edad:\n");
    scanf("%d", &edad);
    do {
        printf("Ingrese su sexo:\n");
        printf("->1. Hombre\n");
        printf("->2. Mujer\n");
        scanf("%d", &op);
        if (op != 1 && op != 2){
            printf("\nIntente otra vez\n\n");
        }
    } while(op != 1 && op != 2);
    if (op == 1){
        sexo = 'H';
    } else {
        sexo = 'F';
    }
    printf("Ingrese su numero celular:\n");
    scanf("%d", &celular);
    fflush(stdin);
    printf("Ingrese la fecha (DD/MM/AAAA):\n");
    fgets(fecha, 10, stdin);
    fecha[strcspn(fecha, "\n")] = 0;
    fflush(stdin);
    //Se verifica la edad de la persona para ingresarla a la cola correspondiente
    if (edad > 55){
        ingresar_persona(prioridad1_cabeza, prioridad1_cola, id, apellidos, nombre, edad, sexo, celular, fecha);
    } else if (edad > 40 && edad <= 55){
        ingresar_persona(prioridad2_cabeza, prioridad2_cola, id, apellidos, nombre, edad, sexo, celular, fecha);
    } else if (edad <= 40){
        ingresar_persona(prioridad3_cabeza, prioridad3_cola, id, apellidos, nombre, edad, sexo, celular, fecha);
    }
}
 
//Función para mostrar los datos de la persona
void mostrar_datos(int id, char apellidos[], char nombre[], int edad, char sexo, int celular, char fecha[]){
    printf("=> ID: %d\n", id);
    printf("=> Apellidos: %s\n", apellidos);
    printf("=> Nombre: %s\n", nombre);
    printf("=> Edad: %d\n", edad);
    printf("=> Sexo: %c\n", sexo);
    printf("=> Celular: %d\n", celular);
    printf("=> Fecha: %s\n", fecha);
}

//Función para mostrar los datos de la persona atendida y agregarla a la pila de atendidos
void personas_atendidas(struct turno **cabeza, struct turno **atendidos){
    //Se toman los datos de la persona
    int id = 0;
    char apellidos[30];
    char nombre[30];
    int edad = 0;
    char sexo;
    int celular = 0;;
    char fecha[10];
    strcpy(apellidos, (*cabeza)->apellidos);
    celular = (*cabeza)->celular;
    edad = (*cabeza)->edad;
    strcpy(fecha, (*cabeza)->fecha);
    id = (*cabeza)->identificación;
    strcpy(nombre, (*cabeza)->nombre);
    sexo = (*cabeza)->sexo;
    //Se muestran los datos de la persona
    mostrar_datos(id, apellidos, nombre, edad, sexo, celular, fecha);
    //Se agregan los datos de la persona a la pila de atendidos
    usuario_atendido(atendidos, id, apellidos, nombre, edad, sexo, celular, fecha);
    //Se elimina la persona de la cola
    struct turno *temp = *cabeza;
    *cabeza = (*cabeza)->siguiente;
    free(temp);
}

//Verificacion colas
int colas_vacias(struct turno *prioridad1_cabeza, struct turno *prioridad2_cabeza, struct turno *prioridad3_cabeza){
    if (vacia(prioridad1_cabeza) == 1 && vacia(prioridad2_cabeza) == 1 && vacia(prioridad3_cabeza) == 1) {
        return 1;
    }
    else {
        return 0;
    }
}

//Función para atender a la persona
void atender(struct turno **prioridad1_cabeza, struct turno **prioridad2_cabeza, struct turno **prioridad3_cabeza, struct turno **atendidos, int *atender_siguiente, int *conteo){
    // Verificar si hay personas esperando a ser atendidas
    if (*atender_siguiente == 1) {
        // Atiende a las personas en la cola de prioridad 1
        if (*conteo < 3 && *prioridad1_cabeza != NULL) {
            personas_atendidas(prioridad1_cabeza, atendidos);
            printf("Usuario atendido\n");
            (*conteo)++;
        } else {
            *conteo = 0;
            *atender_siguiente = 2;
            }
    } 
    if (*atender_siguiente == 2) {
        // Atiende a las personas en la cola de prioridad 2
        if (*conteo < 1 && *prioridad2_cabeza != NULL) {
            personas_atendidas(prioridad2_cabeza, atendidos);
            printf("Usuario atendido\n");
            (*conteo)++;
        } else {
            *conteo = 0;
            *atender_siguiente = 3;
        }
    } 
    if (*atender_siguiente == 3) {
        // Atiende a las personas en la cola de prioridad 3
        if (*conteo < 1 && *prioridad3_cabeza != NULL) {
            personas_atendidas(prioridad3_cabeza, atendidos);
            printf("Usuario atendido\n");
            (*conteo)++;
        } else {
            *conteo = 0;
            *atender_siguiente = 1;
        }
    }
    if (colas_vacias( *prioridad1_cabeza, *prioridad2_cabeza, *prioridad3_cabeza) != 0) {
        printf("No hay personas por atender\n");
    }
}


//Función para consultar las personas atendidas
void consultar_atendidos(struct turno **atendidos){
    //Se define una pila temporal y un nodo para borrar
    struct turno *temp = NULL;
    struct turno *borrar = NULL;
    //Se toman los datos de la persona atendida y se agregan a la cola temporal
    int id = 0;
    char apellidos[30];
    char nombre[30];
    int edad = 0;
    char sexo;
    int celular = 0;
    char fecha[10];
    //Se verifica si la pila esta vacia
    if (vacia(*atendidos) == 1){
        printf("No se ha atendido ha nadie\n");
    } else {
        //Se toman los datos de la persona atendida y se agregan a la cola temporal
        while (vacia(*atendidos) != 1){
            strcpy(apellidos, (*atendidos)->apellidos);
            celular = (*atendidos)->celular;
            edad = (*atendidos)->edad;
            strcpy(fecha, (*atendidos)->fecha);
            id = (*atendidos)->identificación;
            strcpy(nombre, (*atendidos)->nombre);
            sexo = (*atendidos)->sexo;
            mostrar_datos(id, apellidos, nombre, edad, sexo, celular, fecha);
            printf("\n---------------------------\n");
            usuario_atendido(&temp, id, apellidos, nombre, edad, sexo, celular, fecha);
            //Se elimina la persona de la pila de atendidos
            borrar = *atendidos;
            *atendidos = (*atendidos)->siguiente;
            free(borrar);
        }
        //Se regresan los datos a la pila de atendidos
        borrar = temp;
        while (vacia(temp) != 1){
            //Se toman los datos de la persona atendida y se agregan a la pila de atendidos
            strcpy(apellidos, temp->apellidos);
            celular = temp->celular;
            edad = temp->edad;
            strcpy(fecha, temp->fecha);
            id = temp->identificación;
            strcpy(nombre, temp->nombre);
            sexo = temp->sexo;
            usuario_atendido(atendidos, id, apellidos, nombre, edad, sexo, celular, fecha);
            //Se elimina la persona de la pila de atendidos temporal
            borrar = temp;
            temp = temp->siguiente;
            free(borrar);
        }
    }
}

//Función para eliminar a una persona de la cola
void eliminar_usuario(struct turno **prioridad1_cabeza, struct turno **prioridad1_cola, struct turno **prioridad2_cabeza, struct turno **prioridad2_cola, struct turno **prioridad3_cabeza, struct turno **prioridad3_cola, struct turno **atendidos){
    //Se definen las colas temporales y un nodo para borrar
    struct turno *temp = NULL;
    struct turno *borrar = *prioridad1_cabeza;
    //Se toman los datos de la persona a eliminar
    int id = 0, id_temp = 0, encontrado = 0, prioridad = 0;;
    char apellidos[30];
    char nombre[30];
    int edad = 0;
    char sexo;
    int celular = 0;
    char fecha[10];
    printf("Ingrese la id del usuario que desea eliminar:\n");
    scanf("%d", &id_temp);
    if (*prioridad1_cabeza == NULL && *prioridad2_cabeza == NULL && *prioridad3_cabeza == NULL){
        printf("No hay personas en espera\n");
        return;
    }
    //Se busca a la persona en la cola
    while(vacia(*prioridad1_cabeza) != 1 && encontrado == 0){
        strcpy(apellidos, (*prioridad1_cabeza)->apellidos);
        celular = (*prioridad1_cabeza)->celular;
        edad = (*prioridad1_cabeza)->edad;
        strcpy(fecha, (*prioridad1_cabeza)->fecha);
        id = (*prioridad1_cabeza)->identificación;
        strcpy(nombre, (*prioridad1_cabeza)->nombre);
        sexo = (*prioridad1_cabeza)->sexo;
        //Se verifica si la persona se encuentra en la cola
        if (id_temp == id){
            //Se registra que la persona se encuentra en la cola
            encontrado = 1;
            prioridad = 1;
            break;
        }
        //Se agrega la persona a la cola temporal y se elimina de la cola original, si no es la persona a eliminar
        borrar = *prioridad1_cabeza;
        ingresar_persona(&temp, prioridad1_cola, id, apellidos, nombre, edad, sexo, celular, fecha);
        *prioridad1_cabeza = (*prioridad1_cabeza) ->siguiente; 
        free(borrar);
    }
    //Se verifica si la persona se encuentra en la cola
    if (encontrado == 1 && prioridad == 1){
        //Se eliminan las personas de la cola
        personas_atendidas(prioridad1_cabeza, atendidos);
    }
    //Se verifica si se encontró a la persona
    if (encontrado == 1 && prioridad == 1){
        //Se termina de pasar a la cola temporal y se vueve la cola original
        while (vacia(*prioridad1_cabeza) != 1){
            strcpy((*prioridad1_cabeza)->apellidos, apellidos);
            celular = (*prioridad1_cabeza)->celular;
            edad = (*prioridad1_cabeza)->edad;
            strcpy(fecha, (*prioridad1_cabeza)->fecha);
            id = (*prioridad1_cabeza)->identificación;
            strcpy(nombre, (*prioridad1_cabeza)->nombre);
            sexo = (*prioridad1_cabeza)->sexo;
            borrar = *prioridad1_cabeza;
            ingresar_persona(&temp, prioridad1_cola, id, apellidos, nombre, edad, sexo, celular, fecha);
        }
        *prioridad1_cabeza = temp;
        printf("\nUsuario atendido con prioridad\n");
        return;
    }
    temp = NULL;
    //Se busca a la persona en la cola en la siguiente prioridad y se repite el proceso anterior
    while(vacia(*prioridad2_cabeza) != 1 && encontrado == 0){
        strcpy(apellidos, (*prioridad2_cabeza)->apellidos);
        celular = (*prioridad2_cabeza)->celular;
        edad = (*prioridad2_cabeza)->edad;
        strcpy(fecha, (*prioridad2_cabeza)->fecha);
        id = (*prioridad2_cabeza)->identificación;
        strcpy(nombre, (*prioridad2_cabeza)->nombre);
        sexo = (*prioridad2_cabeza)->sexo;
        if (id_temp == id){
            encontrado = 1;
            prioridad = 2;
            break;
        }
        borrar = *prioridad2_cabeza;
        ingresar_persona(&temp, prioridad2_cola, id, apellidos, nombre, edad, sexo, celular, fecha);
        *prioridad2_cabeza = (*prioridad2_cabeza) ->siguiente; 
        free(borrar);
    }
    if (encontrado == 1 && prioridad == 2){
        personas_atendidas(prioridad2_cabeza, atendidos);
    }
    if (encontrado == 1 && prioridad == 2){
        while (vacia(*prioridad2_cabeza) != 1){
            strcpy(apellidos, (*prioridad2_cabeza)->apellidos);
            celular = (*prioridad2_cabeza)->celular;
            edad = (*prioridad2_cabeza)->edad;
            strcpy(fecha, (*prioridad2_cabeza)->fecha);
            id = (*prioridad2_cabeza)->identificación;
            strcpy(nombre, (*prioridad2_cabeza)->nombre);
            sexo = (*prioridad2_cabeza)->sexo;
            borrar = *prioridad2_cabeza;
            ingresar_persona(&temp, prioridad2_cola, id, apellidos, nombre, edad, sexo, celular, fecha);
        }
        *prioridad2_cabeza = temp;
        printf("\nUsuario atendido con prioridad\n");
        return;
    }
    temp = NULL;
    while(vacia(*prioridad3_cabeza) != 1 && encontrado == 0){
        strcpy(apellidos,(*prioridad3_cabeza)->apellidos);
        celular = (*prioridad3_cabeza)->celular;
        edad = (*prioridad3_cabeza)->edad;
        strcpy(fecha, (*prioridad3_cabeza)->fecha);
        id = (*prioridad3_cabeza)->identificación;
        strcpy(nombre, (*prioridad3_cabeza)->nombre);
        sexo = (*prioridad3_cabeza)->sexo;
        if (id_temp == id){
            encontrado = 1;
            prioridad = 3;
            break;
        }
        borrar = *prioridad3_cabeza;
        *prioridad3_cabeza = (*prioridad3_cabeza)->siguiente; 
        ingresar_persona(&temp, prioridad3_cola, id, apellidos, nombre, edad, sexo, celular, fecha);
        
        free(borrar);
    }
    if (encontrado == 1 && prioridad == 3){
        personas_atendidas(prioridad3_cabeza, atendidos);
    }
    if (encontrado == 1 && prioridad == 3){
        while (vacia(*prioridad3_cabeza) != 1){
            strcpy(apellidos, (*prioridad3_cabeza)->apellidos);
            celular = (*prioridad3_cabeza)->celular;
            edad = (*prioridad3_cabeza)->edad;
            strcpy(fecha, (*prioridad3_cabeza)->fecha);
            id = (*prioridad3_cabeza)->identificación;
            strcpy(nombre, (*prioridad3_cabeza)->nombre);
            sexo = (*prioridad3_cabeza)->sexo;
            borrar = *prioridad3_cabeza;
            ingresar_persona(&temp, prioridad3_cola, id, apellidos, nombre, edad, sexo, celular, fecha);
        }
        *prioridad3_cabeza = temp;
        printf("\nUsuario atendido con prioridad\n");
        return;
    }
    if (encontrado == 0){
        printf("El usuario no se encuentra\n");
    }
}

//Función para archivar los datos de las personas atendidas
void guardar_archivo(struct turno **atendidos){
    //Se define un nodo temporal y se abre el archivo
    struct turno *temp = NULL;
    FILE *archivo;
    archivo = fopen("atendidos.bin", "wb");
    if (archivo == NULL){
        printf("Error al abrir el archivo\n");
    }
    //Se toman los datos de la pila de atendidos y se guardan en el archivo
    while(*atendidos != NULL){
        struct turno archivar;
        archivar.identificación = (*atendidos)->identificación;
        strcpy(archivar.nombre, (*atendidos)->nombre);
        strcpy(archivar.apellidos, (*atendidos)->apellidos);
        archivar.edad = (*atendidos)->edad;
        archivar.sexo = (*atendidos)->sexo;
        archivar.celular = (*atendidos)->celular;
        strcpy(archivar.fecha, (*atendidos)->fecha);
        archivar.siguiente = NULL;
        fwrite(&archivar, sizeof(archivar), 1, archivo);
        //Se elimina la persona de la pila de atendidos
        temp = *atendidos;
        *atendidos = (*atendidos)->siguiente;
        free(temp);
    }

    printf("Datos guardados correctamnte\n");

    fclose(archivo);
}

//Función para recuperar los datos de las personas atendidas
void recuperar_datos(struct turno **atendidos){
    //Se abre el archivo
    FILE *archivo;
    archivo = fopen("atendidos.bin", "rb");
    if (archivo == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }
    //Se toman los datos del archivo y se agregan a la pila de atendidos
    struct turno archivado;
    while (fread(&archivado, sizeof(struct turno),1,archivo) == 1){
        struct turno *usuario = malloc(sizeof(struct turno));
        if (usuario == NULL){
            printf("No hay datos en el archivo\n");
            fclose(archivo);
            return;
        }
        usuario ->identificación = archivado.identificación;
        strcpy(usuario->nombre,archivado.nombre);
        strcpy(usuario->apellidos, archivado.apellidos);
        usuario->edad = archivado.edad;
        usuario->sexo = archivado.sexo;
        usuario->celular = archivado.celular;
        strcpy(usuario->fecha, archivado.fecha);
        usuario->siguiente = NULL;
        if (*atendidos== NULL){
            *atendidos = usuario;
        }
        else{
            struct turno *temp = *atendidos;
            while (temp->siguiente != NULL){
                temp = temp->siguiente;
            }
            temp ->siguiente = usuario;
        }
    }

    printf("Datos recuperados\n");

    fclose(archivo);
}

//Función principal
int main(){
    //Se definen las colas y la pila
    struct turno *prioridad1_cabeza = NULL;
    struct turno *prioridad1_cola = NULL;
    struct turno *prioridad2_cabeza = NULL;
    struct turno *prioridad2_cola = NULL;
    struct turno *prioridad3_cabeza = NULL;
    struct turno *prioridad3_cola = NULL;
    struct turno *atendidos = NULL;
    //Se definen las variables para el menú
    int op = 0, atender_siguiente = 1, conteo = 0;
    printf("Desea consultar si hay datos archivados?\n");
    printf("->1. Si \n->2. No\n");
    scanf("%d", &op);
    if (op == 1){
        recuperar_datos(&atendidos);
    }
    do {
        //Se muestra el menú
        printf("***************************************\n");
        printf("\t\tMenu\t\n");
        printf("***************************************\n");
        printf("-> 1. Registrar persona\n");
        printf("-> 2. Siguiente persona\n");
        printf("-> 3. Eliminar persona\n");
        printf("-> 4. Consultar personas atendidas\n");
        printf("-> 5. Salir\n");
        printf("Seleccione:\n");
        scanf("%d", &op);
        //Se ejecuta la opción seleccionada
        switch (op) {
            case 1:
                printf("***************************************\n");
                datos(&prioridad1_cabeza, &prioridad1_cola, &prioridad2_cabeza, &prioridad2_cola, &prioridad3_cabeza, &prioridad3_cola);
                printf("Usuario registrado correctamente\n");
                break;
            case 2:
                printf("***************************************\n");
                atender(&prioridad1_cabeza, &prioridad2_cabeza, &prioridad3_cabeza, &atendidos, &atender_siguiente, &conteo);
                break;
            case 3:
                printf("***************************************\n");
                eliminar_usuario(&prioridad1_cabeza, &prioridad1_cola, &prioridad2_cabeza, &prioridad2_cola, &prioridad3_cabeza, &prioridad3_cola, &atendidos);
                break;
            case 4:
                printf("***************************************\n");
                consultar_atendidos(&atendidos);
                break;
            case 5:
                printf("***************************************\n");
                if (colas_vacias(prioridad1_cabeza, prioridad2_cabeza, prioridad3_cabeza) != 1){
                    printf("Todavia hay personas en espera\n");
                    op = 0;
                } else {
                    printf("Se archivaran los usuarios atendidos\n");
                    guardar_archivo(&atendidos);
                    printf("Cerrando el programa...");
                }
                break;
            default:
                printf("***************************************\n");
                printf("Error...\n");
                break;
        }
    } while (op != 5);
    return 0;
}
