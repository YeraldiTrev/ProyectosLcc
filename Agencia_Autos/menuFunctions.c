#include <stdio.h>
#include <stdlib.h>


char subMenu()
{
    char opc;
    system("clear");
    printf("1) Alta.\n2) Baja.\n3) Volver al menu anterior.\nSelecciona una opcion: ");
    fflush(stdin);
    scanf("%c",&opc);
    if(opc!='1'&&opc!='2'&&opc!='3')
    {
        printf("Opcion no valida...\n");
        system("pause");
        system("clear");
        subMenu();
    }
    return opc;
}