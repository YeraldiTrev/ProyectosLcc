#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
/* CONSTANTES PARA DEFINICION DE CANTIDAD DE PALABRAS */
#define MIN 0
#define MAX 6

int numeroPalabra;
char palabras[7][120]={"gato","el perro camina", "computadora", "el asesino asesina", "java", "hola mundo"};
char palabra_adivinada[120];

/* 5 intentos para frase y 3 para palabra */
int intentos[2]={5,3},maxIntentos,i,aux;
char letra;

int seleccion()
{
    srand(time(NULL));
    int num,i;
    num=rand()%(MAX-MIN)+MIN;
    if(num>MAX) seleccion();
    return num;
}

void palabra_()
{
    int i,longitud=strlen(palabras[numeroPalabra]);
    for(i=0;i<longitud;i++)
    {
        if(palabras[numeroPalabra][i]==' ')
        {
            palabra_adivinada[i]=' ';
            maxIntentos=0;
        }
        else
        {
            palabra_adivinada[i]='_';
            maxIntentos=1;
        }
    }
}

void adivinar(int longPalabra)
{
    do
    {
        system("clear");
        aux=0;
        /* Palabra en guiones, y con letras adivinadas */
        puts(palabra_adivinada);

        /* Entrada de datos con conversion a minusculas */
        printf("\nIntentos restantes: %d \nIngrese una letra: ",intentos[maxIntentos]);
        scanf("%c",&letra);
        letra=tolower(letra);
        fflush(stdin);

        /* Verificacion de la letras en la palabra deseada */
        for(i=0;i<longPalabra;i++)
        {
            if(letra==palabra_adivinada[i])
            {
                printf("La letra ingresada ya fue encontrada...\n\n");
                system("pause");
                aux=1;
                break;
            }

            if(letra==palabras[numeroPalabra][i])
            {
                palabra_adivinada[i]=letra;
                aux=1;
            }
        }

        /* Verificacion de error o perdida de la partida */
        if(aux==0)
        {
            printf("\nLa letra no esta en la palabra o frase...\n");
            intentos[maxIntentos]-=1;
            system("pause");
            if(intentos[maxIntentos]<1)
            {
                printf("\nIntentos Agotados. Has perdido...\nLa palabra/frase era: ");
                puts(palabras[numeroPalabra]);
                return;
            }
            continue;
        }

        /* verificacion de victoria */
        for(i=0;i<longPalabra;i++)
        {
            if(palabra_adivinada[i]=='_')
                break;
        }
        if(palabra_adivinada[i]!='_')
        {
            system("clear");
            printf("La palabra/frase es: ");
            puts(palabra_adivinada);
            printf("\n***** HAS GANADO!!!!!! :D *****\n");
            break;
        }
    }while(1);
    
    return ;
}