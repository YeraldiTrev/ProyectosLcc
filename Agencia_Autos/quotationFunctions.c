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
void quotationReport(int id);

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
    int i,carro,selected=0,period,seguro,tipoPago,cliente;
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
                if((quotes[totalQuotes].clientId==clients[i].id)&&(clients[i].status))
                    break;
            }
            if((quotes[totalQuotes].clientId==clients[i].id)&&(clients[i].status))
                break;
            else
            {
                printf("Cliente no encontrado o deshabiltado\n");
                printf("Presiona 1 para intentar con otra clave y 2 para cancelar: ");
                scanf("%d",&i);
                if(i==2)
                    break;
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
        int findedCars=0;
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
                    findedCars++;
                    printf("%04d\t %-10s ",cars[i].id,makes[cars[i].idMake]);
                    printf("%-10s  %4d",models[cars[i].idMake][cars[i].idModel],cars[i].year);
                    printf("     ");(cars[i].transmission==1)?printf("Estandar  "):printf("Automatico");
                    printf("   %5s","");(cars[i].kidOfCar==1)?printf("Nuevo     \n"):printf("Semi-Usado\n");
                }
            }
            if(findedCars<=0)
            {
                system("clear");
                printf("\nNo se encontraron autos de esta marca...\n");
                system("pause");
                system("clear");
                return;
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
        printf("Monto a financiar: $%.2f\n",quotes[totalQuotes].pay.restPrice);
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
        printf("Monto total a financiar: $%.2f\n",quotes[totalQuotes].totalPay);
        printf("Presione 1 para confirmar o 2 para modificar: ");
        fflush(stdin);
        scanf("%c",&opc);
        if(opc=='1')
            break;
        system("clear");
        continue;
    }while(1);
    totalQuotes++;
    quotationReport(totalQuotes);
    saveQuotes();
}

void quotationReport(int id)
{
    id--;
    float totalPagar=0;
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
        printf("$%9.2f\n",mensualidad+interes+iva);
        saldoRestante-=mensualidad;
        totalPagar+=(mensualidad+interes+iva);
    }
    printf("\t\t\t\t\t\tTotal a pagar:  $%9.2f\n",totalPagar);
    system("pause");
}

void clientsQuotes()
{
    char name[60];
    char lastname[60],opc;
    int id,finded=0;
    do
    {
        system("clear");
        fflush(stdin);
        printf("1. Mostrar todos los clientes\n2. Buscar por nombre u apellido.\n");
        printf("Seleccione una opcion: ");
        fflush(stdin);
        scanf("%c",&opc);
        if(opc!='1'&&opc!='2')
        {
            printf("Opcion no valida...\n");
            system("pause");
            continue;
        }
        break;
    }
    while(1);

    system("clear");
    if(opc=='1')
        clientsLists();
    else if(opc=='2')
    {
        printf("Ingrese el nombre y/o apellido ");
        printf("(Ingrese un espacio y punto si solo ingresa uno de los 2): ");
        scanf("%s %s",name,lastname);
        for(i=0;i<totalClients;i++)
        {
            if((strcmp(name,clients[i].name)==0)&&(clients[i].status))
            {
                printf("%04d\t%s %s\n",clients[i].id,clients[i].name,clients[i].lastname);
                finded++;
            }
            else if((strcmp(lastname,clients[i].lastname)==0)&&(clients[i].status))
            {
                printf("%04d\t%s %s\n",clients[i].id,clients[i].name,clients[i].lastname);
                finded++;

            }
            else if((strcmp(name,clients[i].lastname)==0)&&(clients[i].status))
            {
                printf("%04d\t%s %s\n",clients[i].id,clients[i].name,clients[i].lastname);
                finded++;
            }
            else if((strcmp(lastname,clients[i].name)==0)&&(clients[i].status))
            {
                printf("%04d\t%s %s\n",clients[i].id,clients[i].name,clients[i].lastname);
                finded++;
            }
        }
    }
    
    if(finded>0||opc=='1')
    {
        printf("\nIngresa el Id: ");
        scanf("%d",&id);
        system("clear");
        for(i=0;i<totalClients;i++)
        {
            if(id==clients[i].id)
            {
                if(clients[i].status==1)
                {
                    printf("Clave Cliente: %0.5d\n",clients[id-1].id);
                    printf("Nombre:        %s %s\n",clients[id-1].name,clients[id-1].lastname);
                    printf("Correo:        %s\t Telefono: %s\n",clients[id-1].email,clients[id-1].phoneNum);
                    printf("Direccion:     %s ",clients[id-1].home.calle);
                    printf("%d, %s, CP. ",clients[id-1].home.numero,clients[id-1].home.colonia);
                    printf("%d\n\n",clients[id-1].home.cp);
                    printf("\t Cotizaciones\n");
                    printf("Id Cotizacion   Descripcion Vehiculo\t        Monto a Financiar   ");
                    printf("Plazo Total a Pagar\n");
                    for(j=0;j<totalQuotes;j++)
                    {
                        if(clients[id-1].id==quotes[j].clientId)
                        {
                            printf("    %0.5d\t",quotes[j].id);
                            printf("%-10s %-10s ",
                            makes[quotes[j].idMake],models[quotes[j].idMake][quotes[j].idModel]);
                            printf("%4d \t",quotes[j].year);
                            printf("  $ %9.2f\t\t %d meses\n",quotes[j].totalPay,quotes[j].pay.period);
                        }
                    }
                    
                }
                else
                {
                    printf("El cliente esta deshabilitado...\n");
                    break;
                }
            }
        }
        system("pause");
        /*
        printf("Ingresa el id de la cotizacion a mostrar: ");
        scanf("%d",&id);
        system("clear");
        quotationReport(id);
        */
    }
    else
    {
        printf("\nNo se encontraron coincidencias...\n");
        system("pause");
        system("clear");
    }
}

/* Disable client esta aqui ya que da error por duplicacion y falta de variables */
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
                    for(j=0;j<totalQuotes;j++)
                    {
                        if(id==quotes[j].clientId)
                        {
                            printf("\nEl cliente tiene cotizaciones activas");
                            printf(", no se puede deshabilitar...\n");
                            system("pause");
                            break;
                        }
                        else
                        {
                            clients[i].status=0;
                            printf("Cliente deshabilitado...\n");
                            system("pause");
                            system("clear");
                            break;
                        }
                    }
                }
                break;
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

void quotesList()
{
    int idcot;
    do
    {
        system("clear");
        printf("\t\t Cotizaciones\n\n");
        printf("Cotizacion    Marca      Sub-Marca    Modelo   Cliente\n");
        for(i=0;i<totalQuotes;i++)
        {
            printf("   %05d      %-10s %-10s    ",
            quotes[i].id,makes[quotes[i].idMake],models[quotes[i].idMake][quotes[i].idModel]);
            printf("%4d    ",quotes[i].year);
            printf("%s %s\n",clients[quotes[i].clientId-1].name,clients[quotes[i].clientId-1].lastname);
        }
        printf("Id cotizacion: ");
        scanf("%d",&idcot);
        if((idcot<1)||(idcot>(totalQuotes)))
        {
            printf("Cotizacion no encontrada...\n");
            system("pause");
            continue;
        }
        break;
    }while(1);
    system("clear");
    quotationReport(idcot);
}