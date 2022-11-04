/* Liraries and files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "usersFunction.c"
#include "menuFunctions.c"
#include "clientFunction.c"
#include "carsFunctions.c"


/* Constants and global variables */
#define USERS 3
#define TRIES 3

int main()
{
    int validation,i;
    char opc=' ';
    system("clear");
    /* Load information files */
    loadUsers();
    loadClients();
    loadCars();
    validation = userValidation(TRIES);

    while(opc!='6'&& validation)
    {
        system("clear");
        printf("1. Clientes.\n2. Autos.\n3. Cotizacion.\n");
        printf("4. Reportes.\n5. Reactivar usuario.\n");
        printf("6. Salir.\nSelecciona una opcion: ");
        fflush(stdin);
        scanf("%c",&opc);
        switch (opc)
        {
        case '1':
            do
            {
                system("clear");
                opc=tolower(subMenu());
                if(opc=='1')
                    newClient();
                else if(opc=='2')
                    disableClient();
                else
                    break;
            }while(1);
            break;
        case '2':
            do
            {
                opc=tolower(subMenu());
                if(opc=='1')
                    newCar();
                else
                    break;
            }while(1);
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            activateUser();
            break;
        case '6':
            system("clear");
            break;
        default:
            printf("Opcion no valida. Intente de nuevo...\n");
            system("pause");
            break;
        }
    }
    loadToFileClients();
    loadCarsToFile();
    printf("Gracias por usar el software de agencias Yera :D\n"); 
    return 0;
}