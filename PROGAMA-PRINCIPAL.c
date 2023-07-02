#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define MAX 50
#define MIN 25

typedef struct informacionPersonal{
    char ID[MAX];
    char Nombre[MAX];
    char Cargo[MAX];
    char Salario[MIN];
    char SalarioTOTAL[MIN];
};

void funcionConsulta ();
void funcionActualizacion ();

int main ()
{
    int vflag = 1, opc = 0;
    char *opciones[] = {
        "1. Ver informacion de nomina",
        "2. Actualizar nomina",
        "3. Salir"
    };

    printf("\n\nIniciando..");
    Sleep(200);

    do
    {
        printf("MANEJO DE DATOS\n%s\n%s\n%s\bA continuación digite la opción que desee ejecutar >> ",*opciones[0],*opciones[1],*opciones[2]);
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

    } while (vflag);    //Si vflag es igual a 0, el programa se cerrará
    printf("Ha cerrado el programa.");
    return 0;
}