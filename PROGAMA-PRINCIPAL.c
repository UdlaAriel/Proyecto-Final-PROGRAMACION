#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define MAX 100
#define MIN 50

/*Programa que permite un manejo de Base de Datos
NOMBRE: Jarvis*/

char archivoCSV[] = "BASE_DE_DATOS.csv"; //Nombre de archivo que va a ser utilizado

typedef struct{ //Estructura que almacenará la información de cada persona en nómina
    char ID[MIN];
    char Nombre[MIN];
    char Cargo[MAX];
    int HorasExtra;
    int Salario;
    int SalarioTOTAL;
}persona;

int verify                  (int numeroIngresado);
int verifyStrings           (char *cadena);
void cleanbuffer            (); // Limpia la entrada del buffer
void inicio                 (int cantidad, persona *DATA); //Inicia el registro de todas las personas dentro del nómina
void actualizar             (int personasNomina, persona *DATA); //Actualiza los datos del fichero
void funcionConsulta        (int personasNomina, persona *DATA); //Lee los datos dentro del fichero y los imprime en pantalla
void funcionModificar       (int personasNomina, persona *DATA); //Permite cambiar o acutalizar los datos del fichero
void funcionAniadir         (int personasNomina, persona *DATA);
void funcionBorrar          (int personasNomina, persona *DATA); //Elimina el registro de una persona identificando su ID
int cantidadNomina (); //Devuelve la cantidad de personas dentro de la nómina, además de idenficar el numero de secciones

int main ()
{
    int opc = 0;
    while (1){
        int personasNomina = cantidadNomina(); //numero de personas en nómina
        personasNomina++; //Para contar a la última persona ingresada

        persona *DATA = calloc(personasNomina, sizeof(persona));  //Definición de struct para almacenar la información de cadad miembro dentro de la nómina
    
        if(!DATA){ //Comprobación de asignación de memoria al puntero SIZE de tipo informacion
            printf("\nError al asignar memoria dinamicamente.\n");
            return 1;
        }
    
        inicio(personasNomina, DATA); //Función para inicializar las variables

        printf("Cantidad de personas en NOMINA %d", personasNomina-1);
        printf("\n\nPROGRAMA DE MANEJO DE DATOS\n1. Ver informacion de nomina\n2. Modificar nomina\n3. A%cadir personas a la nomina\n4. Borrar\n5. Salir\nA continuacion digite la opcion que desee ejecutar >> ",164);
        opc = verify(opc);

        switch (opc)
        {
        case 1: funcionConsulta     (personasNomina, DATA); break; //Ver información de nómina
        case 2: funcionModificar    (personasNomina, DATA); break; //Modificar o actualizar la información de nómina   
        case 3: funcionAniadir      (personasNomina, DATA); break; //Añadir nuevas personas al registro     
        case 4: funcionBorrar       (personasNomina, DATA); break; //Eliminar el registro de una persona ingresando su ID
        case 5: system ("cls"); printf("Ha cerrado el programa.\nPRESIONE ENTER para finalizar."); getche(); return 0;//Salir del programa
        default: system("cls"); break;
        }
        
        free(DATA);
    }   //Si vflag es igual a 0, el programa se cerrará
    return 0;
}

void inicio(int cantidad, persona *DATA){

    FILE *archivo; //Puntero de tipo FILE para abrir el fichero
    if((archivo = fopen(archivoCSV,"r"))==NULL) printf("\nLo sentimos, existe un error al abrir el archivo %s",archivoCSV);
    else printf("\nArchivo abierto correctamente.\n");

    char linea[100];

    for (int i = 0; i < cantidad; i++) {
        if (fgets(linea, sizeof(linea), archivo) != NULL) {
            char *token = strtok(linea, ","); //Definición de puntero que almacenará el resultado de la función strtok
            /*Definición de punteros temporales, para almacenar el contenido de cada TOKEN*/
            char *ID;
            char *nombre;
            char *cargo;
            char *salario;
            char *horas_extras;
            char *salariototal;

            int count = 0; //Definición de contador para guardar los TOKENS resultantes dentro de cada variable temporal.
            while (token != NULL) {
                if (count == 0) {
                    ID = token;
                    strcpy(DATA[i].ID, token); //Copiar contenido de token a los atributos de cada persona.
                } else if (count == 1) {
                    nombre = token;
                    strcpy(DATA[i].Nombre, token);
                } else if (count == 2) {
                    cargo = token;
                    strcpy(DATA[i].Cargo, token);
                } else if (count == 3) {
                    DATA[i].Salario = atoi(token); //Transformación de strings a números
                } else if (count == 4) {
                    DATA[i].HorasExtra = atoi(token); //Transformación de strings a números
                } else if (count == 5) {
                    DATA[i].SalarioTOTAL = atoi(token); //Transformación de strings a números
                }

                count++;
                token = strtok(NULL, ",");
            }
        }
    }
}

int cantidadNomina(){ //Funcion para determinar la cantidad de personas en nomina leyendo cada caracter de salto de linea
    int cantidad = 0; //Inicializar el valor de la variable que almacena el valor de personas en nomina
    FILE *archivo;

    // Abre el archivo CSV en modo de lectura
    if((archivo = fopen(archivoCSV,"r"))==NULL) printf("\nLo sentimos, existe un error al abrir el archivo %s",archivoCSV);

    while (!feof(archivo)){
        if(fgetc(archivo)=='\n') cantidad++;
    }
     //Asigna el valor del total de personas dentro de nomina a la variable global filas
    fclose(archivo);

    return cantidad;
}

void funcionConsulta (int personasNomina, persona *DATA){

    //Impresión del contenido del fichero
    printf("\nID\tNOMBRE\t\t\tPUESTO\t\t\t\t\tSALARIO\t\tH.E\tSALARIO TOTAL\n");
    for(int i=1;i<personasNomina;i++){

        printf("%s\t", DATA[i].ID);

        //Separación por tabulación según la longitud de la cadena que se va a imprimir
        if (strlen(DATA[i].Nombre)<8) printf("%s\t\t\t", DATA[i].Nombre);
        else if(strlen(DATA[i].Nombre)<16) printf("%s\t\t", DATA[i].Nombre);
             else printf("%s\t", DATA[i].Nombre);
        
        //Separación por tabulación según la longitud de la cadena que se va a imprimir
        if(strlen(DATA[i].Cargo)<8) printf("%s\t\t\t\t\t", DATA[i].Cargo);
        else if (strlen(DATA[i].Cargo)<16) printf("%s\t\t\t\t", DATA[i].Cargo);
            else if(strlen(DATA[i].Cargo)<24) printf("%s\t\t\t", DATA[i].Cargo);
                else if(strlen(DATA[i].Cargo)<32) printf("%s\t\t", DATA[i].Cargo);
                        else if (strlen(DATA[i].Cargo)<40) printf("%s\t", DATA[i].Cargo);
    
        printf("$%d\t\t", DATA[i].Salario);
        printf("%d\t", DATA[i].HorasExtra);
        printf("$%d\n", DATA[i].SalarioTOTAL);
    }
}

void funcionModificar (int personasNomina, persona *DATA){
    
    system("cls"); //Limpieza de cadenas
    int vflag = 1, i; //Definición de bandera para bucle while
    char ID[10], confirmacion;
 
    do{
        printf("Recuerde ingresar IDs EXISTENTES.\n");
        printf("Ingrese el ID de la persona que desea modificar los datos, e.g(A001): ");
        scanf("%s",&ID); //Definición de variable temporal que almacenará el ID que se desea consultar

        i = 0; //Asignación de valor 0 cada que se reinicia el bucle

        int longitud = strlen(ID); //Mide la longitud de la cadena ID ingresada
        char numeros[longitud];
        int indice_numeros = 0;

        for (i = 0; i < longitud; i++) { //Se asignan aquellos caracteres que sean numeros dentro de numeros[]
            if (isdigit(ID[i])) {
                numeros[indice_numeros] = ID[i];
                indice_numeros++;
            }
        }

        numeros[indice_numeros] = '\0'; // Agrega el carácter nulo al final de la cadena de números
        i = atoi(numeros); // Convierte la cadena de números en un entero y lo asigna a la variable 'i'*/

    }while(i>=personasNomina);
    

    while (vflag == 1){

        int opc = 0;
        //system("cls"); //Limpieza de cadenas
        printf("\n\nATRIBUTOS. %s\nQue desea modificar\n1. Nombre\n2. Cargo\n3. Salario\n4. Horas Extra\n5. Regresar al menu principal\n\nIngrese la opcion: ",ID);
        opc = verify(opc); //Verificación de la opción ingresada
        
        switch (opc)
        {
        case 1: {
            char *nombre = calloc(50,sizeof(char));
            fflush(stdin); //Limpieza de buffer

            printf("Nombre: "); 
            fgets(nombre,50,stdin); //Ingreso de datos

            if(verifyStrings(nombre)){
            nombre[strcspn(nombre, "\n")] = '\0'; // Asegura que la cadena termina en nulo  
            strncpy(DATA[i].Nombre, nombre, sizeof(DATA[i].Nombre) - 1); //Copia la cadena excluyendo el caracter '\n'
            }
            else printf("El nombre ingresado contiene caracteres no válidos.\n");

            free(nombre); //libera memoria
            break;
        }
        case 2: {
            char *cargo = calloc(50,sizeof(char));
            int valid = 1;

            fflush(stdin); //Limpieza de buffer;

            printf("Cargo: ");
            fgets(cargo,50,stdin); //Ingreso de datos

            if(verifyStrings(cargo)){
                cargo[strcspn(cargo, "\n")] = '\0'; // Asegura que la cadena termina en nulo  
                strncpy(DATA[i].Cargo, cargo, sizeof(DATA[i].Cargo) - 1); //Copia la cadena excluyendo el caracter '\n'
            }
            else printf("El nombre ingresado contiene caracteres no válidos.\n");

            free(cargo); //libera memoria
            break;
        }
        case 3: {
            int salario; 
            printf("Salario: ");
            scanf("%d",&salario); 
            DATA[i].Salario = salario; //Asignación del valor salario a la persona[i]
            break;
        }
        case 4: {
            int horas_extra;
            printf("Horas extra trabajadas: ");
            scanf("%d",&horas_extra); 
            DATA[i].HorasExtra = horas_extra; //Asignación de valor a la cantidad de horas extra de la persona[i]
            break;
        }
        case 5: vflag = 0; break;
        default: break;
        }
    }

    DATA[i].SalarioTOTAL = DATA[i].Salario + (DATA[i].HorasExtra * 5); //Salario total en base a las horas extras trabajdas más el salario mensual

    actualizar(personasNomina, DATA);
}

void funcionAniadir(int personasNomina, persona *DATA){

    system("cls"); //Limpieza de cadenas

    FILE *archivo;
    char linea[100];
    char *nombre = calloc(50,sizeof(char)); //Asignación de memoria dinámica
    char *cargo = calloc(50,sizeof(char)); //Asignación de memoria dinámica
    char *salario = calloc(10,sizeof(char)); //Asignación de memoria dinámica
    char *horas_extra = calloc(5,sizeof(char)); //Asignación de memoria dinámica
    char *salariototal = calloc(10,sizeof(char)); //Asignación de memoria dinámica


    // Abrir el archivo en modo append
    archivo = fopen(archivoCSV, "a");
    
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
    }

    // Definir el prefijo de ID
    char ID[10] = "A0";
    char cadena[10];

    snprintf(cadena, sizeof(cadena), "%d", personasNomina);  // Convierte el entero a cadena

    if(personasNomina < 10){
        strcat(ID,"0");
        strcat(ID,cadena);
    }
    else strcat(ID,cadena); // Une la cadena ID con el número auto-generado
    
    // Impresión de cadena auto-generada
    printf("ID AUTO-GENERADO: %s\n", ID);
    // Vacía la secuencia stream
    fflush(stdin);

    printf("Nueva persona\nRECORDATORIO: Ingresar unicamente numeros enteros**\n");
    printf("Nombre: ");
    fgets(nombre,50,stdin); //Lectura de cadena nombre
    printf("Cargo: ");
    fgets(cargo,50,stdin); //Lectura de cadena cargo
    printf("Salario: ");
    fgets(salario,10,stdin); //Lectura de cadena salario
    printf("Horas extra trabajadas: ");
    fgets(horas_extra,5,stdin); //Lectura de cadena horas_extra

    //Asignación de caracter \0 al final de cada cadena
    nombre[strcspn(nombre, "\n")] = '\0'; 
    cargo[strcspn(cargo, "\n")] = '\0';
    salario[strcspn(salario, "\n")] = '\0';
    horas_extra[strcspn(horas_extra, "\n")] = '\0';

    //Calculo de salario total
    int NumSalario = atoi(salario);
    int NumHoras_extra = atoi(horas_extra);
    int NumSalarioTotal = NumSalario + (NumHoras_extra * 5);
    
    //Conversión del numero conseguido a una cadena de caracteres
    sprintf(salariototal, "%d", NumSalarioTotal);  // Convierte el entero a cadena y lo almacena en 'cadena'

    //Concatenación de todas las cadenas dentro de una sola
    strcat(linea,ID);
    strcat(linea,",");
    strcat(linea,nombre);
    strcat(linea,",");
    strcat(linea,cargo);
    strcat(linea,",");
    strcat(linea,salario);
    strcat(linea,",");
    strcat(linea,horas_extra);
    strcat(linea,",");
    strcat(linea,salariototal);
    
    //Impresión de la nueva cadena al final del fichero .csv
    fprintf(archivo,"\n%s",linea);
    // Cerrar el archivo
    fclose(archivo);

    free(nombre);
    free(cargo);
    free(salario);
    free(horas_extra);
    free(salariototal);
    
    printf("Los cambios se han a%cadido correctamente.\n",164);
}

void funcionBorrar(int personasNomina, persona *DATA){

    system("cls");

    char ID[10];
    int filaEliminar = 0;

    printf("Ingrese el ID de la persona que desea eliminar los datos, e.g(A001): ");
    scanf("%s",&ID); //Definición de variable temporal que almacenará el ID que se desea consultar

    int i = 0;
    int longitud = strlen(ID);
    char numeros[longitud];
    int indice_numeros = 0;

    for (i = 0; i < longitud; i++) {
        if (isdigit(ID[i])) {
            numeros[indice_numeros] = ID[i];
            indice_numeros++;
        }
    }

    numeros[indice_numeros] = '\0'; // Agrega el carácter nulo al final de la cadena de números

    i = atoi(numeros); // Convierte la cadena de números en un entero y lo asigna a la variable 'i'*/

    //Modificación y eliminación de la información del ID seleccionado
    strncpy(DATA[i].Nombre,"-VACIO-",8);
    strncpy(DATA[i].Cargo,"-VACIO-",8);
    DATA[i].Salario = 0;
    DATA[i].HorasExtra = 0;
    DATA[i].SalarioTOTAL = 0;

    actualizar(personasNomina, DATA);
    printf("\nLos cambios se han a%ciadidos correctamente.\n",164);
}

void actualizar(int personasNomina, persona *DATA){
    
    FILE *archivo;
    if((archivo = fopen(archivoCSV,"w"))==NULL) printf("\nLo sentimos, existe un error al abrir el archivo %s",archivoCSV);
    
    fprintf(archivo,"ID,NOMBRE,PUESTO,SALARIO,H.E MENSUALES,SALARIO TOTAL");
    for(int i=1;i<personasNomina;i++){
        fprintf(archivo,"\n%s,%s,%s,%d,%d,%d",DATA[i].ID,DATA[i].Nombre,DATA[i].Cargo,DATA[i].Salario,DATA[i].HorasExtra,DATA[i].SalarioTOTAL);
    }

    fclose(archivo);
}

int verifyStrings(char *cadena){
    //Validación de datos ingresados
    int valid = 1;
    for (int j = 0; j < strlen(cadena) - 1; j++) {
        if (!isalpha(cadena[j])) {
            if(cadena[j]!=' ')
                valid = 0;
                break;
        }
    }
    return valid;       
}

int verify(int numeroIngresado) // FUNCION QUE VALIDA QUE EL VALOR INGRESADO SEA UN NUMERO
{
	int res = 0;
    do{
        if(scanf("%d", &numeroIngresado) != 1){ // Mensaje de error en la pantalla
            system("cls");
            printf("OPCION NO VALIDA");
            printf("\nIngrese cualquier NUMERO [6-10] para regresar al men%c: ",163);
        }
    else res = 1;

        cleanbuffer(); 

    }while (res == 0);
	
	return numeroIngresado;
}

void cleanbuffer(){
    char c;
	while((c = getchar()) != '\n' && c != EOF);// Limpia cada caracter ingresado hasta que llegue al caracter \n o EOF (End of file)
}
