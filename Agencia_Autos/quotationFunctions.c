#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "carsFunctions.c"
#include "clientFunction.c"

/* Global Variables and constanst */
#define QUOTES 100
#define ENGAGE 0.28985507246376811594202898550725
#define INSURERS 3
const float CAT=0.16;
int totalQuotes=0;
int periods[8]={72,60,48,36,30,24,18,12};
char *dateFormat="%d-%m-%Y";
/*Struct Quotation*/
struct Insurer
{
    char insurer[15];
    float price;
}insurers[INSURERS]={{"GNP",12000},{"QUALITA",11000},{"CHUB",11600}};

typedef struct
{
    float price;
    int paymentType;
    char insurer[15];
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
    int idCar;
    int clientId;
    int idMake;
    int idModel;
    int year;
    int transmission;
    int kindOfCar;
    Price pay;
    Insurance insurance;
    char date[70];
    float totalPay;

}quotes[QUOTES];
typedef struct Quotation Quotation;

/* quote function*/
void loadQuotes()
{
    FILE *quotesBin;
    quotesBin=fopen("Cotizaciones.bin","rb");
    fread(&totalQuotes,sizeof(int),1,quotesBin);

    fread(quotes,sizeof(Quotation),QUOTES,quotesBin);
    fclose(quotesBin);
}

void saveQuotes()
{
    FILE *quotesBin;
    quotesBin=fopen("Cotizaciones.bin","wb");
    fwrite(&totalQuotes,sizeof(int),1,quotesBin);
    fclose(quotesBin);
    quotesBin=fopen("Cotizaciones.bin","ab");
    fwrite(quotes,sizeof(Quotation),QUOTES,quotesBin);
    fclose(quotesBin);
}

void quotation()
{
    time_t t=time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    strftime(quotes[totalQuotes].date,sizeof(quotes[totalQuotes].date),dateFormat,&tiempoLocal);
    int i,carro,selected=0,period,seguro,tipoPago;
    char opc;
    do
    {
        quotes[totalQuotes].id=totalQuotes+1;
        do
        { 
            system("clear");
            printf("Ingresa la clave del cliente: ");
            scanf("%d",&quotes[totalQuotes].clientId);
            for(i=0;i<totalClients;i++)
            {
                if(quotes[totalQuotes].clientId==clients[i].id)
                    break;
            }
            if(quotes[totalQuotes].clientId==clients[i].id)
                break;
            else
            {
                printf("Ingrese 1 si quiere intentar con otra clave o 2 para cancelar: ");
                scanf("%d",&i);
                if(i==2)
                    break;;
            }
        }while(1);
        int marca;
        while(quotes[totalQuotes].clientId==clients[i].id)
        {
            system("clear");
            printf("****** Menu de marcas ******\n");
            for(i=0;i<4;i++)
                printf("%d. %s\n",i+1,makes[i]);
            printf("Ingrese la marca de auto deseada: ");
            scanf("%d",&marca);
            if(marca!=1&&marca!=2&&marca!=3&&marca!=4)
            {
                printf("Favor de seleccionar una opcion del menu\n");
                system("pause");
                system("clear");
                continue;
            }
            marca--;
            break;
        }

        do
        {
            system("clear");
            printf("********** Carros Disponibles **********\n");
            printf(" ID \t Marca %5sSub-Marca  Modelo","");
            printf("   Transmision   Estado del Vehiculo\n");
            for(i=0;i<totalCars;i++)
            {
                if((cars[i].status)&&(cars[i].idMake==marca))
                {
                    printf("%04d\t %-10s ",cars[i].id,makes[cars[i].idMake]);
                    printf("%-10s  %4d",models[cars[i].idMake][cars[i].idModel],cars[i].year);
                    printf("     ");(cars[i].transmission==1)?printf("Estandar  "):printf("Automatico");
                    printf("   %5s","");(cars[i].kidOfCar==1)?printf("Nuevo     \n"):printf("Semi-Usado\n");
                }
            }
            printf("\nIngrese el Id del auto deseado: ");
            scanf("%d",&carro);
            for(i=0;i<totalCars;i++)
            {
                if((cars[i].status)&&(cars[i].idMake==marca)&&(cars[i].id==carro))
                {
                    selected=i;
                    quotes[totalQuotes].idCar=carro;
                    quotes[totalQuotes].idMake=marca;
                    quotes[totalQuotes].idModel=cars[selected].idModel;
                    quotes[totalQuotes].kindOfCar=cars[selected].kidOfCar;
                    quotes[totalQuotes].year=cars[selected].year;
                    quotes[totalQuotes].transmission=cars[selected].transmission;
                    break;
                }
            }
            if((cars[selected].status)&&(cars[selected].idMake==marca)&&(cars[selected].id==carro))
                break;
            printf("Opcion invalida...\n");
            system("pause");
            system("clear");
        }while(1);
        
        quotes[totalQuotes].pay.engage=cars[selected].listprice*ENGAGE;
        quotes[totalQuotes].pay.restPrice=cars[selected].listprice-quotes[totalQuotes].pay.engage;
        printf("Enganche minimo solicitado: $%.2f\n",quotes[totalQuotes].pay.engage);
        printf("Monto a financiar: $%2.f\n",quotes[totalQuotes].pay.restPrice);
        do
        {
            printf("\tPeriodos de Pago Disponibles\n");
            for(i=0;i<8;i++)
                printf("%d. %d meses.\n",i+1,periods[i]);
            printf("Seleccione el periodo deseado: ");
            scanf("%d",&period);
            if(period<1&&period>8)
            {
                printf("Opcion invalida...\n");
                system("pause");
                system("clear");
                continue;
            }
            period--;
            quotes[totalQuotes].pay.period=periods[period];
            break;
        }while(1);
        
        do
        {
            system("clear");
            printf("******* Aseguradoras Disponibles *******\n");
            for(i=0;i<3;i++)
                printf("%d. %s $%.2f\n",(i+1),insurers[i].insurer,insurers[i].price);
            printf("Seleccione una aseguradora: ");
            scanf("%d",&seguro);
            if(seguro<1&&seguro>3)
            {
                printf("Opcion invalida...\n");
                system("pause");
                continue;
            }
            strcpy(quotes[totalQuotes].insurance.insurer,insurers[seguro-1].insurer);
            quotes[totalQuotes].insurance.price=insurers[seguro-1].price;
            break;
        }while(1);

        do
        {
            printf("1. Contado.\n2. Financiado.\nSelecciona el tipo de pago: ");
            scanf("%d",&quotes[totalQuotes].insurance.paymentType);
            if(quotes[totalQuotes].insurance.paymentType!=1&&quotes[totalQuotes].insurance.paymentType!=2)
            {
                printf("Ocpion invalida\n");
                system("pause");
                system("clear");
                continue;
            }
            break;
        }while(1);

        system("clear");
        quotes[totalQuotes].totalPay=quotes[totalQuotes].pay.restPrice;
        if(quotes[totalQuotes].insurance.paymentType==2)
            quotes[totalQuotes].totalPay+=quotes[totalQuotes].insurance.price;
        printf("Monto toal a financiar: %.2f\n",quotes[totalQuotes].totalPay);
        printf("Presione 1 para confirmar o 2 para modificar: ");
        fflush(stdin);
        scanf("%c",&opc);
        if(opc=='1')
            break;
        system("clear");
        continue;
    }while(1);
    totalQuotes++;
    saveQuotes();
    system("pause");
}

void quotationReport(int id)
{
    id--;
    float saldoRestante,mensualidad,interes,iva;
    printf("Cotizacion:        %0.5d\n",quotes[id].id);
    printf("Cliente:           %0.5d\t\t    %s %s\n"
    ,quotes[id].clientId,clients[quotes[id].clientId-1].name,clients[quotes[id].clientId-1].lastname);
    printf("Marca Vehiculo:    %s\t\t    Submarca: %s\n",
    makes[quotes[id].idMake],models[quotes[id].idMake][quotes[id].idModel]);
    printf("Antiguedad:        ");
    (cars[quotes[id].idCar-1].kidOfCar==1)?printf("Nuevo     \t "):printf("Semi-Usado\t ");
    printf("\t    Modelo:   %d\n",quotes[id].year);
    printf("Precio Lista:      $%.2f\n",(quotes[id].pay.restPrice+quotes[id].pay.engage));
    printf("Enganche:          $%.2f  %.2f%c\t    ",quotes[id].pay.engage,ENGAGE*100,37);
    printf("Plazo:    %0.2d meses\n",quotes[id].pay.period);
    printf("Monto a Financiar: $%.2f\n\n",quotes[id].totalPay);
    saldoRestante=quotes[id].totalPay;
    mensualidad=(quotes[id].totalPay/quotes[id].pay.period);
    
    printf("Pago  Saldo Auto   Mensualidad  \tInteres      IVA\t");
    printf("Monto a Pagar\n");
    for(i=0;i<80;i++)
        printf("%c",196);
    printf("\n");
    for (i=1;i<=quotes[id].pay.period;i++)
    {
        interes=((saldoRestante*CAT)/12);
        iva=interes*0.16;
        printf("%4d  $  %9.2f   $ %9.2f   ",i,saldoRestante,mensualidad);
        printf("$ %9.2f   $%9.2f\t",interes,iva);
        printf("%9.2f\n",mensualidad+interes+iva);
        saldoRestante-=mensualidad;
    }
    
}