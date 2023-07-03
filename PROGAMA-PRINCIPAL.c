#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define MAX 100
#define MEDIUM 50
#define MIN 25

char archivo[] = "BASE_DE_DATOS.csv"; //Nombre de archivo que va a ser utilizado
typedef struct NOMINA{ //Estructura que almacenará la información de cada persona en nómina
    char ID[MEDIUM];
    char Nombre[MEDIUM];
    char Cargo[MEDIUM];
    int Salario[MIN];
    int SalarioTOTAL[MIN];
}informacion;

int funcionActualizacion (); //Permite cambiar o acutalizar los datos del fichero
void funcionConsulta (int personasNomina); //Lee los datos dentro del fichero y los imprime en pantalla
void cantidadNomina (int *pointer1); //Devuelve la cantidad de personas dentro de la nómina, además de idenficar el numero de secciones

int main ()
{
    int vflag = 1, opc = 0;
    char *opciones[3] = {
        "1. Ver informacion de nomina",
        "2. Actualizar nomina",
        "3. Salir"
    };

    printf("\n\nIniciando..");
    //Sleep(200);

    while (vflag != 0){
        int personasNomina = 0; //numero de personas en nómina
        int *pointer1 = &personasNomina; //Puntero que modifica de forma dinámica el número de personas en nómina

        informacion *DATA;  //Definición de struct para almacenar la información de cadad miembro dentro de la nómina
        DATA = (informacion*) malloc(personasNomina * sizeof(informacion));
    
        if(DATA==NULL){ //Comprobación de asignación de memoria al puntero SIZE de tipo informacion
            printf("\nError al asignar memoria dinamicamente.\n");
            return 1;
        }

        cantidadNomina(pointer1);
        printf("Cantidad de personas en NOMINA %d", personasNomina);
        printf("\n\nPROGRAMA DE MANEJO DE DATOS\n%s\n%s\n%s\nA continuacion digita la opcion que desee ejecutar >> ",opciones[0],opciones[1],opciones[2]);
        scanf("%d",&opc);
        
        switch (opc)
        {
        case 1: funcionConsulta(personasNomina); break;//Ver información de nómina
        case 2: funcionActualizacion(); break; //Modificar o actualizar la información de nómina          
        case 3: system("cls"); vflag = 0; break;//Salir del programa
        default: {
            printf("Ingrese una opción valida.\n"); 
            scanf("%d", &opc); 
            break;
            }
        }
    }   //Si vflag es igual a 0, el programa se cerrará
    printf("\nHa cerrado el programa.");
    return 0;
}

void cantidadNomina (int *pointer1){ //Funcion para determinar la cantidad de personas en nomina leyendo cada caracter de salto de linea
    FILE *archivoBASE;
    if((archivoBASE = fopen(archivo,"r"))==NULL) printf("\nLo sentimos, existe un error al abrir el archivo %s",archivo);
    else printf("\nArchivo abierto correctamente.\n");

    while (!feof(archivoBASE)){
        if(fgetc(archivoBASE)=='\n') ++*pointer1;
    }
    
    *pointer1 -= 1; //Asigna el valor del total de personas dentro de nomina a la variable global filas
    fclose(archivoBASE);
}

void funcionConsulta (int personasNomina){
    system("cls");

    char linea[1000], *token;
    FILE *archivoBASE_Lectura;
    if((archivoBASE_Lectura = fopen(archivo,"rt"))==NULL) printf("Lo sentimos, existe un error al abrir el archivo %s",archivo);
    else printf("Archivo abierto correctamente.");

    printf("\nID\tNOMBRE\tPUESTO\tSALARIO MENSUAL\tH.E MENSUALES\tSALARIO TOTAL");
    fgets(linea,sizeof(linea),archivoBASE_Lectura);

    for(int i=0;i<personasNomina;i++){
        fgets(linea,sizeof(linea),archivoBASE_Lectura);
        printf("%s", linea);

        token = strtok(linea,",");


    }
    
    fclose(archivoBASE_Lectura);
}


int funcionActualizacion (){

}

