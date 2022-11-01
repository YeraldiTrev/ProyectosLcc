#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    char userName[30];
    char password[30];
    int status;
}Users;

int main()
{
    system("clear");
    char fileName[30]="Usuarios.bin";
    Users user1={1001,"Yeraldi13","Lcc-2079052",1};
    return 0;
}