#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "carsFunctions.c"
#include "clientFunction.c"

/* Global Variables and constanst */
#define QUOTES 100
#define ENGAGE 0.30
#define INSURERS 3
int totalQuotes=0;

/*Struct Quotation*/
struct Insurer
{
    char insurance[15];
    float price;
}insurers[INSURERS]={{"GNP",12000},{"QUALITA",11000},{"CHUB",11600}};

typedef struct
{
    float price;
    int paymentType;
    struct Insurer insurer;
}Insurance;

typedef struct Price
{
    float engage;
    float restPrice;
    int period;
}Price;

struct Quotation
{
    int id;
    int clientId;
    int idMake;
    int idModel;
    int year;
    Price pay;
    Insurance insurance;

}quotes[QUOTES];
typedef struct Quotation Quotation;

/* quote function*/
void loadQuotes()
{
    FILE *quotesBin;
    quotesBin=fopen("Cotizaciones.bin","rb");
    fread(&totalQuotes,sizeof(int),1,quotesBin);    
    fclose(quotesBin);

    quotesBin=fopen("Cotizaciones.bin","ab");
    fread(quotes,sizeof(Quotation),QUOTES,quotesBin);
    fclose(quotesBin);
}

void loadQuotesToFile()
{
    FILE *quotesBin;
    quotesBin=fopen("Cotizaciones.bin","wb");
    fwrite(quotes,sizeof(Quotation),QUOTES,quotesBin);
    fclose(quotesBin);

    quotesBin=fopen("totalCotizaciones.bin","wb");
    fwrite(&totalQuotes,sizeof(int),1,quotesBin);
    fclose(quotesBin);
}

void quotation()
{
    quotes[totalQuotes].id=totalQuotes+1;
    do
    {
        printf("Ingresa la clave del cliente:");
    }while(1);
    
}