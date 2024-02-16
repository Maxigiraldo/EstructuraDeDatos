//Presentado por: Maximiliano Giraldo Ocampo
#include <stdio.h>
#include <string.h>

//Creacion de la estructura en la forma en que guardaremos los datos de cada vehiculo
struct Vehiculo{
    char marca[20];
    char modelo[20];
    char placa[20];
    int año;
    char color[20];
    int valor;
    char estado;
    char tipo;
 }; 

//funcion para registrar los vehiulos
void registrarVehiculo(){

    //Creacion de variables y la estructura que usaremos en esta funcion
    struct Vehiculo vehiculo;
    int op = 0;
    int condicion = 0;

    //Se toman los datos de los vehiculos
    getchar();
    printf("Ingrese la marca del vehiculo:\n");
    fgets(vehiculo.marca, 20, stdin);
    printf("Ingrese el modelo del vehiculo:\n");
    fgets(vehiculo.modelo, 20, stdin);
    do {
        printf("Ingrese la placa del vehiculo\n");
        fgets(vehiculo.placa, 20, stdin);

        // Abrir archivo para lectura
        FILE *vehiculos;
        vehiculos = fopen("vehiculos.bin", "rb");
        if (vehiculos == NULL) {
            printf("Error al abrir el archivo.");
            return;
        }

        // Verificar si la placa ya existe
        struct Vehiculo temp;
        while (fread(&temp, sizeof(temp), 1, vehiculos) == 1) {
            if (strcmp(vehiculo.placa, temp.placa) == 0) {
                printf("La placa ya existe en la base de datos. Ingrese otra placa.\n");
                condicion = 0;
                break;
            } else {
                condicion = 1;
            }
        }
        fclose(vehiculos);
    } while (!condicion);
    printf("Ingrese el año del vehiculo:\n");
    scanf("%d", &vehiculo.año);
    getchar();
    printf("Ingrese el color del vehiculo:\n");
    fgets(vehiculo.color, 20, stdin);
    printf("Ingrese el valor del vehiculo:\n");
    scanf("%d", &vehiculo.valor);
    getchar();
    vehiculo.estado = 'A';
    
    //Este bucle se encarga de que el usuario ingrese correctamente el tipo del vehiculo y hasta que no ingrese alguno de los dos no continuara el programa
    do{
        printf("Elija el tipo del vehiculo:\n");
        printf("1. Propio\n");
        printf("2. Consignado\n");
        scanf("%d", &op);
        if (op == 1){
            vehiculo.tipo = 'P';
            condicion = 1;
        }
        else if (op == 2){
            vehiculo.tipo = 'C';
            condicion = 1;
        }
        else {
            printf("Opcion invalida");
        }
    } while (!condicion); 
    
    //Abre o crea el archivo binario en modo para añadir
    FILE *vehiculos;
    vehiculos = fopen("vehiculos.bin", "ab"); 

    //Se asegura que no vayan a haber errores en ejecucion. verifica que se haya abierto correctamente
    if (vehiculos == NULL) {
        printf("Error al abrir el archivo.");
        return;
    }
    
    //Adiciona los nuevos datos
    fwrite(&vehiculo, sizeof(vehiculo), 1, vehiculos); 

    //Cierra el archivo, cada que acabemos un proceso debe cerrarse para evitar problemas
    fclose(vehiculos); 

    printf("Vehiculo ingresado con exito");   
} 

//funcion para consultar los vehiculos
void consultarVehiculos(){

    //Creacion de variables y la estructura que usaremos en esta funcion
    struct Vehiculo vehiculo;
    int op = 0, min = 0, max = 0, op_sec = 0;
    char ingreso_marca[20];

    //Abre el archivo binario en modo de lectura
    FILE *vehiculos;
    vehiculos = fopen("vehiculos.bin", "rb"); 
    if (vehiculos == NULL) {
        printf("Error al abrir el archivo.");
        return;
    }

    //El siguiente bloque se encarga de ir mostrando los datos de cada vehiculo mientras este activado en el sistema, y cumpla el requisito pedido, mientras reciba datos lo mostrara, en el momento en el que ya no reciba algun dato. se detiene
    printf("Como desea consultar:\n");
    printf("1.Marca\n");
    printf("2.Rango de precio\n");
    printf("3.Tipo\n");
    scanf("%d", &op);
    switch(op){
        case 1:
            printf("Ingrese la marca que desea consultar:\n");
            getchar();
            fgets(ingreso_marca, 20, stdin);
            printf("Se mostraran los vehiculos activos que cumplan los requisitos\n");
            while (fread(&vehiculo, sizeof(vehiculo), 1, vehiculos) == 1){
                if ((strcmp(ingreso_marca, vehiculo.marca) == 0) && ('A' == vehiculo.estado)){
                    printf("MODELO: %s", vehiculo.modelo);
                    printf("\n");
                }
            }
            break;
        case 2:
            printf("Ingrese el minimo de precio:\n");
            scanf("%d", &min);
            printf("Ingrese el maximo de precio:\n");
            scanf("%d", &max);
            printf("Se mostraran los vehiculos activos que cumplan los requisitos\n");
            while (fread(&vehiculo, sizeof(vehiculo), 1, vehiculos) == 1){
                if ((vehiculo.valor >= min) && (vehiculo.valor <= max) && ('A' == vehiculo.estado)){
                    printf("MARCA: %s", vehiculo.marca);
                    printf("MODELO: %s", vehiculo.modelo);
                    printf("PRECIO: %d\n", vehiculo.valor);
                    printf("TIPO: %c\n", vehiculo.tipo);
                    printf("AÑO: %d\n", vehiculo.año);
                    printf("PLACA: %s", vehiculo.placa);
                    printf("COLOR: %s", vehiculo.color);
                    printf("\n");
                }
            }
            break;
        case 3:
            printf("Ingrese el tipo del vehiculo:\n");
            printf("1. Propio\n");
            printf("2. Consignado\n");
            scanf("%d", &op_sec);
            if (op_sec == 1){
                printf("Se mostraran los vehiculos activos que cumplan los requisitos\n");
                while (fread(&vehiculo, sizeof(vehiculo), 1, vehiculos) == 1){
                    if ((vehiculo.tipo == 'P') && ('A' == vehiculo.estado)){
                        printf("MARCA: %s", vehiculo.marca);
                        printf("MODELO: %s", vehiculo.modelo);
                        printf("PRECIO: %d\n", vehiculo.valor);
                        printf("TIPO: %c\n", vehiculo.tipo);
                        printf("AÑO: %d\n", vehiculo.año);
                        printf("PLACA: %s", vehiculo.placa);
                        printf("COLOR: %s", vehiculo.color);
                        printf("\n");
                    }
                }
            }
            else if (op_sec == 2){
                printf("Se mostraran los vehiculos activos que cumplan los requisitos\n");
                while (fread(&vehiculo, sizeof(vehiculo), 1, vehiculos) == 1){
                    if ((vehiculo.tipo == 'C') && ('A' == vehiculo.estado)){
                        printf("MARCA: %s", vehiculo.marca);
                        printf("MODELO: %s", vehiculo.modelo);
                        printf("PRECIO: %d\n", vehiculo.valor);
                        printf("TIPO: %c\n", vehiculo.tipo);
                        printf("AÑO: %d\n", vehiculo.año);
                        printf("PLACA: %s\n", vehiculo.placa);
                        printf("COLOR: %s\n", vehiculo.color);
                        printf("\n");
                    }
                }
            }
            else {
                printf("Opcion invalida\n");
                break;
            }
            break;
    }

    //Cerrar el archivo
    fclose(vehiculos);
}

void actualizarVehiculos(){

    //Creacion de variables y la estructura que usaremos en esta funcion
    struct Vehiculo vehiculo;
    char placa[20];
    int op = 0;
    int condicion = 0;
    long int size = sizeof(struct Vehiculo); 

    //Abre el archivo binario en modo de lectura y escritura para añadir datos
    FILE *vehiculos;
    vehiculos = fopen("vehiculos.bin", "rb+"); 
    if (vehiculos == NULL) {
        printf("Error al abrir el archivo.");
        return;
    }

    //Imprime en pantalla los vehiculos que se encuentran actualmente en el archivo
    while (fread(&vehiculo, sizeof(vehiculo), 1, vehiculos) == 1){
        printf("PLACA: %s", vehiculo.placa);
        printf("\n");
    } 

    //Ingreso de la placa del vehiculo que se desea actualizar
    printf("Ingrese la placa del vehiculo que desea actualizar:\n");
    getchar();
    fgets(placa, 20, stdin);
    fflush(stdin);
    printf("\n"); 

    //Esta linea lo que hace es regresar al inicio del archivo, la razon de hacer esto es debido a que al mostrar las placas anteriormente se reccorio el archivo y el puntero se encuentra al final del archivo
    fseek(vehiculos, 0, SEEK_SET); 

    //Muestra los datos del vehiculo, con el fin de mostrar en pantalla el carro que se eligio junto a los datos que se actualizaran
    while (fread(&vehiculo, sizeof(vehiculo), 1, vehiculos) == 1){
        if (strcmp(placa, vehiculo.placa) == 0){
            printf("MARCA: %s", vehiculo.marca);
            printf("MODELO: %s", vehiculo.modelo);
            printf("PRECIO: %d\n", vehiculo.valor);
            printf("TIPO: %c\n", vehiculo.tipo);
            printf("\n"); 
            do{
                //Se muestran los datos que pueden ser actualizados
                printf("Que desea actualizar?\n");
                printf("1. Valor\n");
                printf("2. Tipo\n");

                //Actualizacion de los datos 
                scanf("%d", &op);
                if (op == 1){
                    printf("Ingrese el nuevo valor:\n");
                    scanf("%d", &vehiculo.valor);

                    //Esta linea, al ser ejecutada lo que hace es regresar atras la cantidad igual al tamaño de la estructura Vehiculo, al usarse de esta manera, lo que se hara es tomarse desde el punto actual en el que se encuentre el puntero y se devolvera al ultimo objeto que se encuentra en la estructura
                    fseek(vehiculos, -size, SEEK_CUR); 

                    //Se reescribe el dato actualizado en el archivo
                    fwrite(&vehiculo, sizeof(struct Vehiculo), 1, vehiculos);
                    fflush(vehiculos);
                    condicion = 1;
                }
                else if (op == 2){
                    op = 0;
                    printf("Elija el tipo del vehiculo:\n");
                    printf("1. Propio\n");
                    printf("2. Consignado\n");
                    scanf("%d", &op);
                    if (op == 1 || op == 2) {
                        vehiculo.tipo = (op == 1) ? 'P' : 'C';
                        fseek(vehiculos, -size, SEEK_CUR);
                        fwrite(&vehiculo, sizeof(struct Vehiculo), 1, vehiculos);
                        fflush(vehiculos);
                        condicion = 1;
                    }
                    else {
                        printf("Opcion invalida\n");
                    }
                }
                else {
                    printf("Opcion invalida");
                }
            } while (!condicion);
            break;
        }
    }

    //Cerrar el archivo
    fclose(vehiculos);
}

void eliminarVehiculos(){

    //Creacion de variables y la estructura que usaremos en esta funcion
    struct Vehiculo vehiculo;
    char placa[20];
    int op = 0;
    int condicion = 0;
    long int size = sizeof(struct Vehiculo);

    //Abre el archivo binario en modo de lectura y escritura para añadir datos
    FILE *vehiculos;
    vehiculos = fopen("vehiculos.bin", "rb+"); 
    if (vehiculos == NULL) {
        printf("Error al abrir el archivo.");
        return;
    }

    //Imprime en pantalla los vehiculos que se encuentran actualmente en el archivo y el estado en que se encuentran
    while (fread(&vehiculo, sizeof(vehiculo), 1, vehiculos) == 1){
        printf("PLACA: %s", vehiculo.placa);
        printf("ESTADO: %c\n", vehiculo.estado);
        printf("\n");
    }

    //Ingreso de la placa del vehiculo que se desea actualizar
    printf("Ingrese la placa del vehiculo que desea actualizar:\n");
    getchar();
    fgets(placa, 20, stdin);
    fflush(stdin);
    printf("\n");

    //Regresando el cursor al inicio
    fseek(vehiculos, 0, SEEK_SET);

    //Busqueda del vehiculo y cambio en el estado ya sea que se elimine o active
    while (fread(&vehiculo, sizeof(vehiculo), 1, vehiculos) == 1){
        if (strcmp(placa, vehiculo.placa) == 0){
            printf("MARCA: %s", vehiculo.marca);
            printf("MODELO: %s", vehiculo.modelo);
            printf("PRECIO: %d\n", vehiculo.valor);
            printf("ESTADO: %c\n", vehiculo.estado);
            printf("\n");
            do{
                printf("Que desea realizar?\n");
                printf("1. Eliminar\n");
                printf("2. Activar\n");
                scanf("%d", &op);
                if (op == 1 || op == 2){
                    vehiculo.estado = (op == 1) ? 'E' : 'A';
                    fseek(vehiculos, -size, SEEK_CUR);
                    fwrite(&vehiculo, sizeof(struct Vehiculo), 1, vehiculos);
                    fflush(vehiculos);
                    condicion = 1;
                }
                else{
                    printf("Opcion invalida\n");
                }
            } while (!condicion);
            break;
        }
    }
    //Cerrar el archivo
    fclose(vehiculos); 
}

//funcion principal
void main(){
    int op = 0;
    do{
        printf("Elija una opcion:\n");
        printf("1. Registrar vehiculo\n");
        printf("2. Mostrar vehiculos\n");
        printf("3. Actualizar vehiculo\n");
        printf("4. Eliminar o activar vehiculo\n");
        printf("5. Salir\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            registrarVehiculo();
            printf("\n");
            break;
        case 2:
            consultarVehiculos();
            break;
        case 3:
            actualizarVehiculos();
            printf("\n");
            break;
        case 4:
            eliminarVehiculos();
            printf("\n");
            break;
        case 5:
            printf("Ha salido del programa");
            printf("\n");
            break;
        }
    } while (op != 5);
}
