/*

--------------------------------------------------------------------------
|                               Podujatia 2                              |
|                               Martin Szabo                             |
|                                  116304                                |
--------------------------------------------------------------------------

*/

// Program bol naprogramovaný v Visual Studio Code s GCC kompilátorom

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VELKOST_BUFFERA 200

typedef struct menoAutora{
    char* meno;
    char* priezvisko;
} MENO_AUTORA;

typedef struct podujatie{
    int ID;
    char* nazovPrispevku;
    MENO_AUTORA menaAutorov; // TODO spravit z tohto array
    char* typPrezentovania;
    int casPrezentovania;
    int datum;
    struct podujatie* dalsi;
    struct podujatie* predchadzajuci;
} PODUJATIE;

// Pomocne funkcie
void vypisSpajany(PODUJATIE* hlavicka);

// Hlavne funkcie
void n(PODUJATIE** zoznam);
void v(PODUJATIE* hlavicka);

int main () {
    PODUJATIE* zoznamPodujatii = NULL;

    n(&zoznamPodujatii);
    v(zoznamPodujatii);

    return 0;
}

void n(PODUJATIE** hlavicka){

    PODUJATIE* aktualny = NULL;
    FILE* subor = fopen("OrganizacnePodujatia2.txt", "r");
    char riadok[VELKOST_BUFFERA];
    int pocetZaznamov = 0;

    // TODO pokial uz je vytvoreny zoznam, uvolni ho.

    if(!subor){
        printf("Zaznamy neboli nacitane!\n");
        return;
    }

    for(int i = 0; fgets(riadok, VELKOST_BUFFERA, subor); i++) {
        if(strcmp(riadok, "$$$\n") == 0){ // V tomto bode treba vytvorit novy uzol
            PODUJATIE* temp = aktualny; // Ulozim si aktualny
            
            if(aktualny){ // Pokial existuje aktualny tak sa posuniem o jeden uzol dopredu
                aktualny = (aktualny)->dalsi;
            }
            
            aktualny = (PODUJATIE*) malloc(sizeof(PODUJATIE)); // Alokujem novy uzol
            aktualny->predchadzajuci = temp; // Nastavim predchadzajuci na moj stary aktualny uzol
            
            if(!temp){ // Pokial neexistuje stary predchadzajuci uzol tak som na zaciatku...
                *hlavicka = aktualny; // ...tym padom nastavim hlavicku na aktualny uzol
            }
            else{
                temp->dalsi = aktualny; // Inak na starom uzly nastavim moj novy uzol ako dalsi v poradi
            }
            pocetZaznamov++;
            continue; // Pokracujem na dalsiu iteraciu
        }
        switch (i){
            case 1:
                aktualny->ID = atoi(riadok);
                //printf("ID: %s", riadok); // TODO delete this
                break;
            case 2:
                aktualny->nazovPrispevku = (char*) calloc(strlen(riadok)+1, sizeof(char));
                strcpy(aktualny->nazovPrispevku, riadok);
                //printf("Nazov prispevku: %s", riadok); // TODO delete this
                break;
            case 3:

                // TODO Rozsekat meno podla # a potom podla toho co je meno a co priezvisko.
                //? Bolo by vhodne si spravit z menaAutorov pole mien autorov. To potom dynamicky naplnit
                //? Taktiez niektore ukony s stringami si hod do extra funkcii lebo sa s toho fakt nevysomaris
                //? Vid kod nizsie...

                //! Scrap code
                /*
                    char* temp = (char*) calloc(strlen(riadok)+1, sizeof(char));
                    size_t pocetMien = 0;
                    strcpy(temp, riadok);
                    
                    char* token = strtok(temp, "#");

                    aktualny->menaAutorov = NULL;

                    while(token){
                        pocetMien++;
                        if(!aktualny->menaAutorov){
                            aktualny->menaAutorov = (MENO_AUTORA*) malloc(sizeof(MENO_AUTORA));
                        }
                        else{
                            aktualny->menaAutorov = (MENO_AUTORA*) realloc(aktualny->menaAutorov, pocetMien*sizeof(MENO_AUTORA));
                        }

                        (aktualny->menaAutorov[pocetMien-1]).meno = NULL;
                        (aktualny->menaAutorov[pocetMien-1]).priezvisko = NULL;
                        char* token2 = strtok(token, " ");

                        for(int j = 0; token2; j++){
                            if(j == 0){
                                (aktualny->menaAutorov[pocetMien-1]).meno = (char*) calloc(strlen(token2)+1, sizeof(char));
                                strcpy((aktualny->menaAutorov[pocetMien-1]).meno, token2);
                            }
                            else{
                                if(!(aktualny->menaAutorov[pocetMien-1]).priezvisko){
                                    (aktualny->menaAutorov[pocetMien-1]).priezvisko = (char*) calloc(strlen(token2)+1, sizeof(char));
                                    strcpy((aktualny->menaAutorov[pocetMien-1]).priezvisko, token2);
                                }
                                else{
                                    (aktualny->menaAutorov[pocetMien-1]).priezvisko = (char*) realloc((aktualny->menaAutorov[pocetMien-1]).priezvisko , strlen(token2)+strlen((aktualny->menaAutorov[pocetMien-1]).priezvisko)+2);
                                    strcat((aktualny->menaAutorov[pocetMien-1]).priezvisko, " ");
                                    strcat((aktualny->menaAutorov[pocetMien-1]).priezvisko, token2);
                                }
                            }
                            token2 = strtok(NULL, " ");
                        }
                        token = strtok(NULL, "#");
                    }


                    printf("Mena autorov: %s", aktualny->menaAutorov[0].meno);
                    if(aktualny->menaAutorov[1].meno){
                        printf(" a %s", aktualny->menaAutorov[1].meno);
                    }
                    printf("\n");
                */
                
                aktualny->menaAutorov.meno = (char*) calloc(strlen(riadok)+1, sizeof(char));
                strcpy(aktualny->menaAutorov.meno, riadok);
                break;
            case 4:
                aktualny->typPrezentovania = (char*) calloc(strlen(riadok)+1, sizeof(char));
                strcpy(aktualny->typPrezentovania, riadok);
                //printf("Typ prezentovania: %s", riadok);
                break;
            case 5:
                aktualny->casPrezentovania = atoi(riadok);
                //printf("Cas prezentovania:  %s", riadok);
                break;
            case 6:
                aktualny->datum = atoi(riadok);
                aktualny->dalsi = NULL;
                i = -1; // O jeden menej lebo for loop tuto premennu inkrementuje na 0
                break;
            default:
                printf("Error");
        }
    }
    
    printf("Nacitalo sa %d zaznamov\n", pocetZaznamov);
    fclose(subor);
}

void v(PODUJATIE* hlavicka){
    /*
        1.
        ID cislo : 15
        Nazov prispevku: Deep learning
        Mena autorov:
        1: Jozko Mrkvicka
        Typ prezentovania: UP
        Cas prezentovania: 1120
        Datum: 20200405
     */

    PODUJATIE* aktualny = hlavicka;

    for(int i = 1; aktualny; i++){
        printf("%d\n", i);
        printf("ID cislo : %d\n", aktualny->ID);
        printf("Nazov prispevku: %s", aktualny->nazovPrispevku);
        printf("Mena autorov: %s", aktualny->menaAutorov.meno);
            // TODO prerobit na array mien
        printf("Typ prezentovania: %s", aktualny->typPrezentovania);
        printf("Cas prezentovania: %d\n", aktualny->casPrezentovania);
        printf("Datum: %d\n", aktualny->datum);
        aktualny = aktualny->dalsi;
    }
}

// TODO uprav alebo zmaz tuto funkciu
void vypisSpajany(PODUJATIE* hlavicka){
    PODUJATIE* aktualny = hlavicka;

    while(aktualny){
        printf("ID: %d\n", aktualny->ID);
        printf("Nazov prispevku: %s", aktualny->nazovPrispevku);
        printf("Meno Autora: %s", aktualny->menaAutorov.meno);
        printf("Typ prezentovania: %s", aktualny->typPrezentovania);
        printf("Cas prezentovania: %d\n", aktualny->casPrezentovania);
        printf("Datum: %d\n", aktualny->datum);
        if(aktualny->dalsi){
            aktualny = aktualny->dalsi;
        }
        else{ break; }
    }

    printf("\n\nA teraz odzadu\n\n");

    while(aktualny){
        printf("ID: %d\n", aktualny->ID);
        printf("Nazov prispevku: %s", aktualny->nazovPrispevku);
        printf("Meno Autora: %s", aktualny->menaAutorov.meno);
        printf("Typ prezentovania: %s", aktualny->typPrezentovania);
        printf("Cas prezentovania: %d\n", aktualny->casPrezentovania);
        printf("Datum: %d\n", aktualny->datum);
        if(aktualny->predchadzajuci){
            aktualny = aktualny->predchadzajuci;
        }
        else{ break; }
    }
}