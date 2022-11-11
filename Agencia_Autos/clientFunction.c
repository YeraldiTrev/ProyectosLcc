/* Liraries and files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Global variables and constants */
#define CLIENTS 100
int totalClients=0,i;

/* Strctures */

typedef struct
{
    char calle[60];
    char colonia[60];
    int numero;
    int cp;
}Domicilio;

struct Client
{
    int id;
    char name[60];
    char lastname[60];
    char email[40];
    char phoneNum[10];
    Domicilio home;
    int status;
}clients[CLIENTS];
typedef struct Client Client;


void loadClients()
{
    FILE *clientsBin;
    clientsBin=fopen("Clientes.bin","rb");
    fread(&totalClients,sizeof(int),1,clientsBin);
    fread(clients,sizeof(Client),CLIENTS,clientsBin);
    fclose(clientsBin);
}

void saveClients()
{
    FILE *clientsBin;
    clientsBin=fopen("Clientes.bin","wb");
    fwrite(&totalClients,sizeof(int),1,clientsBin);
    fclose(clientsBin);
    clientsBin=fopen("Clientes.bin","ab");
    fwrite(clients,sizeof(Client),CLIENTS,clientsBin);
    fclose(clientsBin);
}

void newClient()
{
    system("clear");
    clients[totalClients].id=totalClients+1;
    fflush(stdin);
    printf("Ingresa el nombre completo: ");
    scanf("%s %s",clients[totalClients].name,clients[totalClients].lastname);
    fflush(stdin);
    printf("Ingresa el correo: ");
    scanf("%s",clients[totalClients].email);
    fflush(stdin);
    printf("Ingresa el telefono: ");
    scanf("%s",clients[totalClients].phoneNum);
    fflush(stdin);
    printf("\tDireccion...\n");
    printf("\tIngresa la calle: ");
    gets(clients[totalClients].home.calle);
    fflush(stdin);
    printf("\tIngresa la colonia: ");
    gets(clients[totalClients].home.colonia);
    fflush(stdin);
    printf("\tIngresa el numero: ");
    scanf("%d",&clients[totalClients].home.numero);
    fflush(stdin);
    printf("\tIngresa el codigo postal: ");
    scanf("%d",&clients[totalClients].home.cp);
    fflush(stdin);
    clients[totalClients].status=1;
    totalClients++;
    saveClients();
}

/* Disable client */
void disableClient()
{
    char name[60];
    char lastname[60];
    int id,finded=0;
    system("clear");
    printf("Ingrese el nombre y/o apellido ");
    printf("(Ingrese un espacio y punto si solo ingresa uno de los 2): ");
    scanf("%s %s",name,lastname);
    for(i=0;i<totalClients;i++)
    {
        if(strcmp(name,clients[i].name)==0)
        {
            printf("%04d\t%s %s\n",clients[i].id,clients[i].name,clients[i].lastname);
            finded++;
        }
        else if(strcmp(lastname,clients[i].lastname)==0)
        {
            printf("%04d\t%s %s\n",clients[i].id,clients[i].name,clients[i].lastname);
            finded++;

        }
        else if(strcmp(name,clients[i].lastname)==0)
        {
            printf("%04d\t%s %s\n",clients[i].id,clients[i].name,clients[i].lastname);
            finded++;
        }
        else if(strcmp(lastname,clients[i].name)==0)
        {
            printf("%04d\t%s %s\n",clients[i].id,clients[i].name,clients[i].lastname);
            finded++;
        }
    }

    if(finded>0)
    {
        printf("\nIngresa el Id: ");
        scanf("%d",&id);
        for(i=0;i<totalClients;i++)
        {
            if(id==clients[i].id)
            {
                if(clients[i].status==0)
                {
                    printf("El cliente ya estaba deshabilitado...\n");
                    system("pause");
                    system("clear");
                }
                else
                {
                    clients[i].status=0;
                    printf("Cliente deshabilitado...\n");
                    system("pause");
                    system("clear");
                }
            }
        }
    }
    else
    {
        printf("\nNo se encontraron coincidencias...\n");
        system("pause");
        system("clear");
    }
    saveClients();
}

void clientsLists()
{
    printf(" ID \t    Nombre \t  Correo   \t\t Telefono\n");
    for(i=0;i<totalClients;i++)
    {
        if(clients[i].status)
        {
            printf("%04d \t%s %s  ",clients[i].id,clients[i].name,clients[i].lastname);
            printf("%s\t%s\n",clients[i].email,clients[i].phoneNum);
        }
    }
    printf("\n");
    system("pause");
    system("clear");
}

void ableClient(int clientId)
{
    clients[clientId].status=1;
}