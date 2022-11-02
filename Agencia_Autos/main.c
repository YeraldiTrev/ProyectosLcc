/* Liraries and files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usersFunction.c"


/* Constants and global variables */
#define USERS 3
#define TRIES 3

int main()
{
    int validation;
    char opc='a';
    system("clear");
    loadUsers();
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
                printf("a) Alta.\nb) Baja.\nSelecciona una opcion: ");
                fflush(stdin);
                scanf("%c",&opc);
                if(opc!='a'&&opc!='b'&&opc!='A'&&opc!='B')
                {
                    printf("Opcion no valida...\n");
                    system("pause");
                    system("clear");
                    continue;
                }
                break;
            }while(1);
            break;
        case '2':
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
    printf("Gracias por usar el software de agencias Yera :D\n");

    
    return 0;
}