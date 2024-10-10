#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIBRI 40
#define MAX_LENGTH 100

struct libro
{
    char titolo[MAX_LENGTH];
    char autore[MAX_LENGTH];
    int annoPubblicazione;
    float prezzo;
    char categoria[MAX_LENGTH];
};

void leggiCSV(const char *filename, struct libro *libri, int *count)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Errore nell'apertura del file");
        return;
    }

    char line[MAX_LENGTH];
    *count = 0; // Inizializza il contatore

    // Salta la prima riga (intestazione)
    fgets(line, sizeof(line), file);

    // Leggi ogni riga del file
    while (fgets(line, sizeof(line), file) && *count < MAX_LIBRI)
    {
        sscanf(line, "%[^,],%[^,],%d,%f,%[^,\n]",
               libri[*count].titolo,
               libri[*count].autore,
               &libri[*count].annoPubblicazione,
               &libri[*count].prezzo,
               libri[*count].categoria);
        (*count)++;
    }

    fclose(file);
}
// stampare tutti i libri
void stampaLibri(const struct libro *libri, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("Titolo: %s\n", libri[i].titolo);
        printf("Autore: %s\n", libri[i].autore);
        printf("Anno di pubblicazione: %d\n", libri[i].annoPubblicazione);
        printf("Prezzo: %.2f\n", libri[i].prezzo);
        printf("Categoria: %s\n\n", libri[i].categoria);
    }
}
// stampare i libri di solo 1 categoria o di tutte tra quelle non specificate
void stampaCategoria(const struct libro *libri, int count, char categoria[], int categoriaselezionata)
{
    const char *categorieEscludibili[] = {
        "romanzo storico",
        "romanzo di formazione",
        "poesia epica",
        "romanzo psicologico",
        "romanzo esistenziale",
        "romanzo gotico",
        "fantastico",
        "avventura"};
    int numCategorie = sizeof(categorieEscludibili) / sizeof(categorieEscludibili[0]);

    for (int i = 0; i < count; i++)
    {
        int isEscluso = 0; // Flag per tenere traccia se la categoria è esclusa

        // se il libro appartiene ad una categoria che non è tra quelle specificate, il flag viene impostato ad 1
        for (int j = 0; j < numCategorie; j++)
        {
            if (strcmp(libri[i].categoria, categorieEscludibili[j]) == 0)
            {
                isEscluso = 1; // Categoria esclusa
                break;
            }
        }

        // se si vuole visualizare i libri che non appartengono alle categorie specificate
        if (categoriaselezionata == 1 && !isEscluso)
        {
            printf("Titolo: %s\n", libri[i].titolo);
            printf("Autore: %s\n", libri[i].autore);
            printf("Anno di pubblicazione: %d\n", libri[i].annoPubblicazione);
            printf("Prezzo: %.2f\n", libri[i].prezzo);
            printf("Categoria: %s\n\n", libri[i].categoria);
        }
        // se si vuole vedere i libri di una categoria specificata
        else if (categoriaselezionata == 0 && strcmp(libri[i].categoria, categoria) == 0)
        {
            printf("Titolo: %s\n", libri[i].titolo);
            printf("Autore: %s\n", libri[i].autore);
            printf("Anno di pubblicazione: %d\n", libri[i].annoPubblicazione);
            printf("Prezzo: %.2f\n", libri[i].prezzo);
            printf("Categoria: %s\n\n", libri[i].categoria);
        }
    }
}
// ricercare il libro attraverso l'inserimento di un titolo
void ricercatitolo(const struct libro *libri, int count, char titolo[])
{
    int trovato = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(libri[i].titolo, titolo) == 0)
        {
            printf("Titolo: %s\n", libri[i].titolo);
            printf("Autore: %s\n", libri[i].autore);
            printf("Anno di pubblicazione: %d\n", libri[i].annoPubblicazione);
            printf("Prezzo: %.2f\n", libri[i].prezzo);
            printf("Categoria: %s\n\n", libri[i].categoria);
            trovato = 1;
        }
    }
    if (trovato == 0)
    {
        printf("libro non trovato\n");
    }
}

void main()
{
    struct libro libri[MAX_LIBRI];
    int count;
    leggiCSV("libreria.csv", libri, &count);
    int scelta;
    do
    {
        printf("seleziona cosa vuoi fare:\n1)visualizza tutti i libri\n2)visualizza i libri di solo una categoria\n3)ricerca un libro attraverso il titolo\n0)esci\n");
        scanf("%d", &scelta);
        switch (scelta)
        {
        case 1:
            stampaLibri(libri, count);
            break;
        case 2:
            printf("seleziona la categoria: \n1)romanzo storico \n2)romanzo di formazione \n3)poesia epica \n4)romanzo psicologico \n5)romanzo esistenziale \n6)romanzo gotico \n7)fantastico \n8)avventura \n9)altro\n");
            int sceltacategoria;
            scanf("%d", &sceltacategoria);
            switch (sceltacategoria)
            {
            case 1:
                stampaCategoria(libri, count, "romanzo storico", 0);
                break;
            case 2:
                stampaCategoria(libri, count, "romanzo di formazione", 0);
                break;
            case 3:
                stampaCategoria(libri, count, "poesia epica", 0);
                break;
            case 4:
                stampaCategoria(libri, count, "romanzo psicologico", 0);
                break;
            case 5:
                stampaCategoria(libri, count, "romanzo esistenziale", 0);
                break;
            case 6:
                stampaCategoria(libri, count, "romanzo gotico", 0);
                break;
            case 7:
                stampaCategoria(libri, count, "fantastico", 0);
                break;
            case 8:
                stampaCategoria(libri, count, "avventura", 0);
                break;
            case 9:
                stampaCategoria(libri, count, "altro", 1);
                break;
            }
            break;
        case 3:
            printf("Inserisci il titolo:\n");
            char titolo[MAX_LENGTH];
            getchar();                        // Consuma il carattere di nuova linea per non creare errori con l'fgets
            fgets(titolo, MAX_LENGTH, stdin); // uso l'fgets perchè lo scanf non legge gli spazi
            ricercatitolo(libri, count, titolo);
            break;
        }
    } while (scelta != 0);
}
