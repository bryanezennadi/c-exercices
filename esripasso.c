#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int SizeArray = 20;
void visualizzaArray(int array[], int direzione)
{
    if (direzione == 0)
    {
        printf("il contenuto dell'array è: \n");
        for (int i = 0; i < SizeArray; i++)
        {
            printf("%d\n", array[i]);
        }
    }
    else if (direzione == 1)
    {
        printf("il contenuto dell'array al contrario è: \n");
        for (int i = SizeArray - 1; i >= 0; i--)
        {
            printf("%d\n", array[i]);
        }
    }
}
int Somma(int array[])
{
    int somma = 0;
    for (int i = 0; i < SizeArray; i++)
    {
        somma = somma + array[i];
    }
    return somma;
}
void visualizzaPariDispari(int array[], int pari)
{
    if (pari == 1)
    {
        for (int i = 0; i < SizeArray; i++)
        {
            if (array[i] % 2 == 0)
            {
                printf("%d\n", array[i]);
            }
        }
    }
    else if (pari == 0)
    {
        for (int i = 0; i < SizeArray; i++)
        {
            if (array[i] % 2 != 0)
            {
                printf("%d\n", array[i]);
            }
        }
    }
}
void ricerca(int array[], int ricercato)
{
    int ricercaFinita = 0;
    for (int i = 0; i < SizeArray; i++)
    {
        if (array[i] == ricercato)
        {
            printf("numero trovato");
            ricercaFinita = 1;
        }
    }
    if (ricercaFinita != 1)
    {
        printf("numero non trovato\n");
    }
}
void rimuoviNumero(int arr[], int numero)
{
    int i, j;
    for (i = 0; i < SizeArray; i++)
    {
        if (arr[i] == numero)
        {
            // Sposta gli elementi a sinistra per "rimuovere" l'elemento
            for (j = i; j < SizeArray - 1; j++)
            {
                arr[j] = arr[j + 1];
            }
            (SizeArray)--; // Decrementa la dimensione dell'array
            i--;           // Resta sulla stessa posizione per controllare il nuovo valore
        }
    }
    visualizzaArray(arr, 0);
}
void ordinaArray(int arr[])
{ // ordino con bubble sort
    int i, j, temp;
    for (i = 0; i < SizeArray - 1; i++)
    {
        for (j = 0; j < SizeArray - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // Scambia gli elementi
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    visualizzaArray(arr, 0);
}

void main(int argc, char *argv)
{

    int array[SizeArray];
    srand(time(NULL));

    for (int i = 0; i < SizeArray; i++)
    {

        array[i] = rand() % 101;
    }
    int scelta;
    do
    {
        printf("---------------\nmenù di interazione con un array\n1) visualizzare l'array in modo ordinario\n2) visualizzare l'array al contrario\n3) visualizzare la somma dei numeri e la media\n4) visualizzare i numeri pari\n5) visualizzare i numeri dispari\n6) ricercare un numero a propria scelta\n7) eliminare un numero dall'array\n9) ordinare l'array in modo crescente\n0) uscire dal programma\n---------------\n");
        printf("qual'è la tua scelta?\n");
        scanf("%d", &scelta);
        switch (scelta)
        {
        case 1:
            visualizzaArray(array, 0);
            break;
        case 2:
            visualizzaArray(array, 1);
            break;
        case 3:
            int somma = Somma(array);
            printf("la somma è = %d \n", somma);
            printf("la media è = %d \n", somma / SizeArray);
            break;
        case 4:
            visualizzaPariDispari(array, 1);
            break;
        case 5:
            visualizzaPariDispari(array, 0);
            break;
        case 6:
            printf("inserisci numero da ricercare\n");
            int ricercato;
            scanf("%d", &ricercato);
            ricerca(array, ricercato);
            break;
        case 7:
            printf("inserisci il numero da eliminare");
            int numero;
            scanf("%d", &numero);
            rimuoviNumero(array, numero);
            break;
        case 9:
            ordinaArray(array);
            break;
        }
    } while (scelta != 0);
}