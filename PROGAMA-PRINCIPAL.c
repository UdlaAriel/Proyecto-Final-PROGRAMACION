#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define MAX 100
#define MEDIUM 50
#define MIN 25

int funcionConsulta (); //Lee los datos dentro del fichero y los imprime en pantalla
int funcionActualizacion (); //Permite cambiar o acutalizar los datos del fichero
void cantidadNomina (int *pointer); //Devuelve la cantidad de personas dentro de la nómina

int filas = 0; //numero de filas
char archivo[] = "BASE_DE_DATOS.csv"; //Nombre de archivo que va a ser utilizado
typedef struct{ //Estructura que almacenará la información de cada persona en nómina
    char infoNomina[MAX];
    char ID[MEDIUM];
    char Nombre[MEDIUM];
    char Cargo[MEDIUM];
    int Salario[MIN];
    int SalarioTOTAL[MIN];
}informacion;

int main ()
{
    int *pointer = &filas; 
    int vflag = 1, opc = 0;
    char *opciones[3] = {
        "1. Ver informacion de nomina",
        "2. Actualizar nomina",
        "3. Salir"
    };

    printf("\n\nIniciando..");
    Sleep(200);

    while (vflag != 0){

        cantidadNomina(pointer);
        printf("Cantidad de personas en nomina %d", filas);
        printf("\nPROGRAMA DE MANEJO DE DATOS\n%s\n%s\n%s\nA continuacion digita la opcion que desee ejecutar >> ",opciones[0],opciones[1],opciones[2]);
        scanf("%d",&opc);
        
        switch (opc)
        {
        case 1: funcionConsulta(); break; //Ver información de nómina
        case 2: funcionActualizacion(); break; //Modificar o actualizar la información de nómina          
        case 3: vflag = 0; break;//Salir del programa
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

void cantidadNomina (int *pointer){ //Funcion para determinar la cantidad de personas en nomina leyendo cada caracter de salto de linea
    FILE *archivoBASE;
    if((archivoBASE = fopen(archivo,"r"))==NULL) printf("\nLo sentimos, existe un error al abrir el archivo %s",archivo);
    else printf("\nArchivo abierto correctamente.\n");

    while (!feof(archivoBASE)){
        if(fgetc(archivoBASE)=='\n') 
            ++*pointer;
    }
    *pointer -= 1;
    fclose(archivoBASE);
}

int funcionConsulta (){
    informacion *SIZE;  //Definición de struct para almacenar la información de cadad miembro dentro de la nómina
    SIZE = (informacion*) malloc(filas * sizeof(informacion));

    if(SIZE==NULL){ //Comprobación de 
        printf("\nError al asignar memoria dinamicamente.\n");
        return 1;
    }

    FILE *archivoBASE;
    
    system("cls");
    if((archivoBASE = fopen(archivo,"r"))==NULL) printf("Lo sentimos, existe un error al abrir el archivo %s",archivo);
    else printf("Archivo abierto correctamente.");

    printf("\nID\tNOMBRE\tPUESTO\tSALARIO MENSUAL\tH.E MENSUALES\tSALARIO TOTAL\n");

    while (!feof(archivoBASE)){
        for (int i = 0; i < filas; i++){
            if(fgetc(archivoBASE)!=('\n' || ',')){
                
            }
        }
    }
    

    fclose(archivoBASE);
}

int funcionActualizacion (){

}

