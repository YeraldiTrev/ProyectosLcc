/* Liraries and files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "usersFunction.c"
#include "menuFunctions.c"
#include "quotationFunctions.c"
/*#include "clientFunction.c"
#include "carsFunctions.c"*/


/* Constants and global variables */
#define USERS 4
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
    loadQuotes();
    /* Login */
    validation = userValidation(TRIES);

    while(opc!='6'&& validation)
    {
        fflush(stdin);
        system("clear");
        printf("1. Clientes.\n2. Autos.\n3. Cotizacion.\n");
        printf("4. Reportes.\n5. Reactivar usuario.\n");
        printf("6. Salir.\nSelecciona una opcion: ");
        scanf("%c",&opc);
        fflush(stdin);
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
                    else if (opc=='2')
                        disableCar();
                    else
                        break;
                }while(1);
                break;
            case '3':
                quotation();
                break;
            case '4':
                do
                {
                    system("clear");
                    fflush(stdin);
                    printf("1. Listado de clientes.\n2. Listado de Vehiculos.\n");
                    printf("3. Reimprimir Cotizacion.\n4. Regresar al menu principal.\n");
                    printf("Selecciona una opcion: ");
                    scanf("%c",&opc);
                    fflush(stdin);
                    opc=tolower(opc);
                    switch (opc)
                    {
                        case '1':clientsQuotes();break;
                        case '2':
                            do
                            {
                                system("clear");
                                printf("=========== Tipo de Busqueda ===========\n");
                                printf("1. Todos los registos.\n2. Marca\n3. Modelo.\n");
                                printf("Selecciona una opcion: ");
                                scanf("%c",&opc);
                                
                                switch(opc)
                                {
                                    case '1':carsList();break;
                                    case '2':carsFilterMakeList();break;
                                    case '3':carsFilterModelList();break;
                                    default:
                                        printf("Opcion no valida...\n");
                                        system("pause");
                                        continue;
                                }
                                break;
                            }while(1);
                            break;
                        case '3':quotesList();break;
                        case '4':break;
                        default:
                            printf("Favor de ingresar una opcion del menu...\n");
                            system("pause");
                            system("clear");
                            break;
                    }
                }while(opc!='4');
                break;
            case '5':activateUser();break;
            case '6':system("clear");break;
            default:
                printf("Opcion no valida. Intente de nuevo...\n");
                system("pause");
                break;
        }
    }
    printf("Gracias por usar el software de agencias Yera :D\n"); 
    return 0;
}