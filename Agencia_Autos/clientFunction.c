/* Liraries and files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Global variables and constants */
int totalClients=0,i,j,totalQuotes;
#define CLIENTS 100

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
}

void ableClient(int clientId)
{
    clients[clientId].status=1;
    saveClients();
}