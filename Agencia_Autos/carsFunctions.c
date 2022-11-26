#include <stdio.h>
#include <stdlib.h>

/* Constants and global variables */
#define CARS 100

int totalCars=0,i;
/* Makes and Models Cars */
char makes[4][10]={"Honda","Nissan","Ford","Chevrolet"};
char models[4][4][13]={
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
    fread(&totalCars,sizeof(int),1,carsBin);
    fread(cars,sizeof(Cars),CARS,carsBin);
    fclose(carsBin);
}

void saveCars()
{
    FILE *carsBin;
    carsBin=fopen("Vehiculos.bin","wb");
    fwrite(&totalCars,sizeof(int),1,carsBin);
    fclose(carsBin);

    carsBin=fopen("Vehiculos.bin","ab");
    fwrite(cars,sizeof(Cars),CARS,carsBin);
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
    saveCars();
}


void disableCar()
{
    int clvCar;
    char opc;
    do
    {
        system("clear");        
        printf("Ingrese la clave del vehiculo: ");
        scanf("%d", &clvCar);
        for(i=0;i<totalCars;i++)
        {
            if(clvCar==cars[i].id)
            {
                if(cars[i].status==1)
                {
                    do
                    {
                        printf("Presione 1 para confirmar o 0 para cancelar: ");
                        fflush(stdin);
                        scanf("%c",&opc);
                        if(opc!='1'&&opc!='0')
                        {
                            printf("Ingrese una opcion valida...\n");
                            system("pause");
                            system("clear");
                            continue;
                        }
                        break;
                    }while(1);
                    if(opc=='1')
                    {
                        cars[i].status=0;
                        printf("El vehiculo se a dado de baja...\n");
                        system("pause");
                        system("clear");
                        saveCars();
                        return;
                    }
                    else
                    {
                        printf("\nVolviendo al sub-Menu...\n");
                        system("pause");
                        system("clear");
                        return;
                    }
                }
                else
                {
                    printf("Este vehiculo ya esta dado de baja...\n");
                    system("pause");
                    system("clear");
                    return;
                }
            }
        }
        printf("Clave del vehiculo no encontrada...\n");
        printf("Ingrese 1 para intentar de nuevo o 0 para regresar al menu: ");
        fflush(stdin);
        scanf("%c",&opc);
        if(opc!='1')
            break;
    }while(1);
}

void carsList()
{
    printf("\t\tListado de Alojamiento\n\n");
    printf(" ID \t Marca %5sSub-Marca  Modelo","");
    printf("   Transmision   Estado del Vehiculo\n");
    for(i=0;i<totalCars;i++)
    {
        if(cars[i].status==0)
            continue;
        printf("%04d\t %-10s ",cars[i].id,makes[cars[i].idMake]);
        printf("%-10s  %4d",models[cars[i].idMake][cars[i].idModel],cars[i].year);
        printf("     ");(cars[i].transmission==1)?printf("Estandar  "):printf("Automatico");
        printf("   %5s","");(cars[i].kidOfCar==1)?printf("Nuevo     \n"):printf("Semi-Usado\n");
    }
    system("pause");
}


void carsFilterMakeList()
{
    int marca;
    do
    {
        system("clear");
        printf("********* Marcas *********\n");
        for (i=0;i<4;i++)
            printf("%d.- %s.\n",i+1,makes[i]);
        printf("Seleccione la marca del vehiculo: ");
        scanf("%d",&marca);
        if(marca<1&&marca>4)
        {
            printf("Marca no valida...\n");
            system("pause");
            continue;
        }
        break;
    }while(1);
    system("clear");
    marca--;
    printf("\t\t Listado de Alojamiento.\n");
    printf("Marca: %s\n",makes[marca]);
    printf(" ID    Submarca    Modelo   Transmision   Antiguedad\n");
    for(i=0;i<totalCars;i++)
    {
        if(cars[i].idMake==(marca))
        {
            printf("%04d   %-10s   %4d ",cars[i].id,models[cars[i].idMake][cars[i].idModel],cars[i].year);
            printf("    ");(cars[i].transmission==1)?printf("Estandar  "):printf("Automatico");
            printf("%4s","");(cars[i].kidOfCar==1)?printf("Nuevo\n"):printf("Semi-Usado\n");
        }
    }
    system("pause");
}

void carsFilterModelList()
{
    int year;
    do
    {
        system("clear");
        printf("Ingresa el a%co de consulta: ",164);
        scanf("%d",&year);
        if(year<1980&&year>2023)
        {
            printf("Ingresa un modelo valido...\n");
            system("pause");
            continue;
        }
        break;
    }while(1);
    system("clear");
    printf("\t\t Automoviles Modelo %d\n\n",year);
    printf(" ID \t Marca %5sSub-Marca  Modelo","");
    printf("   Transmision   Estado del Vehiculo\n");
    for(i=0;i<totalCars;i++)
    {
        if((year==cars[i].year)&&(cars[i].status))
        {
            printf("%04d     %-10s %-10s  %4d ",cars[i].id,
            makes[cars[i].idMake],models[cars[i].idMake][cars[i].idModel],cars[i].year);
            printf("    ");(cars[i].transmission==1)?printf("Estandar  "):printf("Automatico");
            printf("%4s","");(cars[i].kidOfCar==1)?printf("Nuevo\n"):printf("Semi-Usado\n");
        }
    }
    system("pause");
}

void ableCar(int carId)
{
    cars[carId].status=1;
    saveCars();
}