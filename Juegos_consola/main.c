#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "ahorcado.c"

int numeroPalabra;

int main()
{
    numeroPalabra=seleccion();
    palabra_();
    int longPalabra=strlen(palabra_adivinada);
    adivinar(longPalabra); 
    return 0;
}