#include <stdio.h>
#include <stdlib.h>

/* Constants and global variables */
#define CARS 100

int totalCars=0,i;
/* Makes and Models Cars */
char makes[4][120]={"Honda","Nissan","Ford","Chevrolet"};
char models[4][4][120]={
    {"CR-v","Pilot","Civic","Accord"},
    {"Xtrail","Sentra","Frontier","Altima"},
    {"Mustang","Explorer","Expedition","Lobo"},
    {"Suburban","Tahoe","Aveo","Cavalier"}
};

struct Cars
{
    int id; /* totalCars+1 */
    int idMake;
    int idModel;
    int kidOfCar; /*1. Nuevo. 2. Semi-usado.*/
    int year;
    float listprice;
    int transmission; /*1. Estandar 2. Automatico.*/
    int status;

}cars[CARS];
typedef struct Cars Cars;

void loadCars()
{
    FILE *carsBin;
    carsBin=fopen("Vehiculos.bin","rb");
    fread(cars,sizeof(Cars),CARS,carsBin);
    fclose(carsBin);

    carsBin=fopen("totalCars.bin","rb");
    fread(&totalCars,sizeof(int),1,carsBin);
    fclose(carsBin);
}

void newCar()
{
    /* Id del carro registrado */
    cars[totalCars].id=totalCars+1;
    /* Id de la marca */
    do
    {
        system("clear");
        printf("********* Marcas *********\n");
        for (i=0;i<4;i++)
            printf("%d.- %s.\n",i+1,makes[i]);
        printf("Seleccione la marca del vehiculo: ");
        scanf("%d",&cars[totalCars].idMake);
        if(cars[totalCars].idMake<1||cars[totalCars].idMake>4)
        {
            printf("No se encontro id de la marca...\n");
            system("pause");
            continue;
        }
        cars[totalCars].idMake--;
        break;
    }while(1);
    /* id de la sub-marca*/
    do
    {
        system("clear");
        printf("********* Sub-Marcas de %s *********\n",makes[cars[totalCars].idMake]);
        for (i=0;i<4;i++)
            printf("%d.- %s.\n",i+1,models[cars[totalCars].idMake][i]);
        printf("Seleccione la sub-marca del vehiculo: ");
        scanf("%d",&cars[totalCars].idModel);
        if(cars[totalCars].idModel<1||cars[totalCars].idModel>4)
        {
            printf("No se encontro id de la marca...\n");
            system("pause");
            continue;
        }
        cars[totalCars].idModel--;
        break;
    }while(1);
    /* Tipo de auto */
    do
    {
        system("clear");
        printf("********** Tipo de Auto **********\n1. Nuevo.\n2. Semi-Usado.\n");
        printf("Ingrese el tipo de auto: ");
        scanf("%d",&cars[totalCars].kidOfCar);
        if(cars[totalCars].kidOfCar!=1&&cars[totalCars].kidOfCar!=2)
        {
            printf("Tipo de carro no valido...\n");
            system("pause");
            continue;
        }
        break;
    }while(1);
    /* Modelo del carro */
    printf("Ingrese el modelo (a%co) del carro: ",164);
    scanf("%d",&cars[totalCars].year);
    /* Precio de lista */
    printf("Ingrese el precio de lista del vehiculo: ");
    scanf("%f",&cars[totalCars].listprice);
    /* Transmisión del carro */
    do
    {
        system("clear");
        printf("********** Tipo de transmision **********\n1. Estandar.\n2. Automatico.\n");
        printf("Ingrese el tipo de transimision: ");
        scanf("%d",&cars[totalCars].transmission);
        if(cars[totalCars].transmission!=1&&cars[totalCars].transmission!=2)
        {
            printf("Tipo de carro no valido...\n");
            system("pause");
            continue;
        }
        break;
    }while(1);
    /*Estatus del carro por defecto es activo (1)*/
    cars[totalCars].status=1;
    totalCars++;
}

void loadCarsToFile()
{
    FILE *carsBin;
    carsBin=fopen("Vehiculos.bin","wb");
    fwrite(cars,sizeof(Cars),CARS,carsBin);
    fclose(carsBin);

    carsBin=fopen("totalCars.bin","wb");
    fwrite(&totalCars,sizeof(int),1,carsBin);
    fclose(carsBin);
}

void carsList()
{
    printf("Total de Carros: %d\n",totalCars);
    for(i=0;i<totalCars;i++)
    {
        printf("*************** ID: %05d ***************\n",cars[i].id);
        printf("ID y marca: %d %s\n",cars[i].idMake,makes[cars[i].idMake]);
        printf("ID y sub-marca: %d %s\n",cars[i].idModel,models[cars[i].idMake][cars[i].idModel]);
        printf("Tipo de carro: ");(cars[i].kidOfCar==1)?printf("Nuevo\n"):printf("Semi-Usado\n");
        printf("Modelo: %4d\n",cars[i].year);
        printf("Precio de lista : $%.2f\n",cars[i].listprice);
        printf("Tipo de Transmision: ");(cars[i].transmission==1)?printf("Estandar\n"):printf("Automatico\n");
        printf("Estatus :%d\n",cars[i].status);
    }
    system("pause");
    system("clear");
}