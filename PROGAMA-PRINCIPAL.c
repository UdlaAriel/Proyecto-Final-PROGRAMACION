#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define MAX 50

typedef struct informacionPersonal{
    char ID[MAX];
    char Nombre[MAX];
    char Cargo[MAX];
};

int main ()
{
    int vflag, opc;
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
        case 1:{ //Ver información de nómina
            
        }
        case 2:{ //Modificar o actualizar la información de nómina
            
        }
        case 3:{ //Salir del programañ
            
        }
        default:
            break;
        }


    } while (vflag);    //Si vflag es igual a 0, el programa se cerrará
    
    return 0;
}