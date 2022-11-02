/* Liraries and files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "usersFunction.c"
#include "menuFunctions.c"
#include "clientFunction.c"


/* Constants and global variables */
#define USERS 3
#define TRIES 3

int main()
{
    int validation,i;
    char opc='a';
    system("clear");
    /* Load information files */
    loadUsers();
    loadClients();

    printf("Total clientes: %d\n",totalClients);
    for(i=0;i<totalClients;i++)
    {
        printf("ID: %d\n",clients[i].id);
        printf("Nombre: %s\n",clients[i].name);
        printf("Correo: %s\n",clients[i].email);

    }
    system("pause");
    system("clear");
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
                opc=tolower(subMenu());
                if(opc=='1')
                    newClient();
                else
                    break;
            }while(1);
            break;
        case '2':
            do
            {
                opc=tolower(subMenu());
                if(opc=='1')
                    break;
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
    printf("Gracias por usar el software de agencias Yera :D\n");

    
    return 0;
}