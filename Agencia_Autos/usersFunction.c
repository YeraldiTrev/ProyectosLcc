/* Libraries and files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Global variables and constants */
#define USERS 4
int i,j;

/* Users structure */
struct Users
{
    int id;
    char userName[30];
    char password[30];
    int status;
}users[USERS];
typedef struct Users Users;

/* Load users from bin file */
void loadUsers()
{
    FILE *usersBin;
    usersBin=fopen("Usuarios.bin","rb");
    fread(users,sizeof(Users),USERS,usersBin);
    fclose(usersBin);
}

/* User and password validation */
int userValidation(int tries)
{
    FILE *usersBin;
    char user[30],pass[30];

    while(tries>0)
    {
        /* User and password input */
        printf("Usuario: ");
        scanf("%s",user);
        fflush(stdin);
        printf("Contrase%ca: ",164);
        scanf("%s", pass);

        /* User validation */
        for(j=0;j<USERS;j++)
        {
            if(strcmp(user,users[j].userName)==0)   
                break;
        }

        /* Password and status validation */
        if(strcmp(pass,users[j].password)==0)
        {
            if(users[j].status)
                return 1;
            else
            {
                printf("El usuario esta inactivo...\n");
                system("pause");
                continue;
            }
        }   
        else
        {
            tries--;
            printf("\nContrase%ca o usuario incorrecto...\n",164);
            system("pause");
            system("clear");
            if(tries<=0)
            {
                /* disable user */
                printf("Usuario bloqueado. Favor de contactar a soporte tecnio...\n");
                users[j].status=0;
                usersBin=fopen("Usuarios.bin","wb");
                fwrite(users,sizeof(Users),USERS,usersBin);
                fclose(usersBin);
                return 0;
            }
            continue; 
        }
    }
    return 1;
}

void activateUser()
{
    char username[30];
    do
    {
        system("clear");
        printf("Usuario a activar: ");
        scanf("%s",username);
        for(i=0;i<USERS;i++)
        {
            if(strcmp(username,users[i].userName)==0)
            {
                users[i].status=1;
                FILE *usersBin;
                usersBin=fopen("Usuarios.bin","wb");
                fwrite(users,sizeof(Users),USERS,usersBin);
                fclose(usersBin);
                break;
            }
        }
        if(strcmp(username,users[i].userName)!=0)
        {
            printf("El usuario no existe...\n");
            system("pause");
            system("clear");
            continue;
        }
        printf("Usuario activado...\n");
        system("pause");
        system("clear");
        break;
    }while(1);
}

/*
    System users register.

    Users users[USERS]={{1000,"Admin","Admin123456",1},
    {1001,"Yeraldi01","Yath2079052",1},{1002,"Reyna02","Rgcm123456",1}};

    usersBin=fopen("Usuarios.bin","wb");
    fwrite(users,sizeof(Users),USERS,usersBin);
    fclose(usersBin);
*/