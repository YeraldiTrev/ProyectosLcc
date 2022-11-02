/* Liraries and files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Global variables and constants */
#define CLIENTS 100
int totalClients=0;

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
    char name[120];
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
    fread(clients,sizeof(Client),CLIENTS,clientsBin);
    fclose(clientsBin);

    clientsBin=fopen("totalClientes.bin","rb");
    fread(&totalClients,sizeof(int),1,clientsBin);
    fclose(clientsBin);
}

void newClient()
{
    system("clear");
    clients[totalClients].id=totalClients+1;
    fflush(stdin);
    printf("Ingresa el nombre completo: ");
    gets(clients[totalClients].name);
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
    totalClients++;
}

void loadToFileClients()
{
    FILE *clientsBin;
    clientsBin=fopen("Clientes.bin","wb");
    fwrite(clients,sizeof(Client),CLIENTS,clientsBin);
    fclose(clientsBin);

    clientsBin=fopen("totalClientes.bin","wb");
    fwrite(&totalClients,sizeof(int),1,clientsBin);
    fclose(clientsBin);
}