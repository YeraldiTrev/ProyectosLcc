#include <stdio.h>
#include <stdlib.h>
#include "usersFunction.c"
#include "clientFunction.c"
#include "carsFunctions.c"


int main()
{   
    /* Modificar o agregar nuevo usuario despues de cambiar el valor de la constante USERS */
    Users users[USERS]={{1000,"Admin","Admin123456",1},
    {1001,"Yeraldi01","Yath2079052",1},
    {1002,"Reyna02","Rgcm123456",1},
    {1003,"Usuario","Usr123456",1}};

    /*NO MODIFICAR LAS SIGUIENTES LINEAS DE CÓDIGO*/
    FILE *usersBin;
    usersBin=fopen("Usuarios.bin","wb");
    fwrite(users,sizeof(Users),USERS,usersBin);
    fclose(usersBin);
    return 0;
}