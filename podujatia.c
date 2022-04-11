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
    struct menoAutora* dalsi;
    struct menoAutora* predchadzajuci;
} MENO_AUTORA;

typedef struct podujatie{
    int ID;
    char* nazovPrispevku;
    MENO_AUTORA* menaAutorov; // TODO spravit z tohto array
    char* typPrezentovania;
    int casPrezentovania;
    int datum;
    struct podujatie* dalsi;
    struct podujatie* predchadzajuci;
} PODUJATIE;

// Pomocne funkcie
void vypisSpajany(PODUJATIE* hlavicka);

// Hlavne funkcie
void n(PODUJATIE** zoznam, int* dlzkaZoznamu);
void v(PODUJATIE* hlavicka);

int main () {

    char vyber;
    PODUJATIE* zoznamPodujatii = NULL;
    int dlzkaZoznamu = 0;

    do{

        //*----------------------------------------------- Inicializácia ----------------------------------------------
                
        scanf(" %c", &vyber);
        getchar();

        //*---------------------------------------------- Výber možnosti ----------------------------------------------
        
        switch (vyber){
            case 'n':
                // TODO FIXME random crashe ked spustim cez code runner
                n(&zoznamPodujatii, &dlzkaZoznamu);
                break;
            case 'v':
                v(zoznamPodujatii);
                break;
            case 'p':
                break;
            case 'z':
                break;
            case 'h':
                break;
            case 'a':
                break;
            case 'r':
                break;
            case 'k':
                break;
            default:
                break;
        }
    } while (vyber != 'k');
    return 0;
}

int pocetTokenov(char* token, const char* delimiter){
    char* temp = token;
    int pocet = 0;
    while((temp = strstr(temp, delimiter)) != NULL) {
        pocet++;
        temp++;
    }
    return pocet;
}

char** rozdelitNaStringy(char* retazec, const char* delimiter, int* pocetRetazcov){
    char* kopiaRetazca = (char*)calloc(strlen(retazec)+1, sizeof(char));
    char* token = NULL, **pole = NULL;

    strcpy(kopiaRetazca, retazec);
    token = strtok(kopiaRetazca, delimiter);
    
    pole = (char**) malloc(pocetTokenov(token, delimiter)*sizeof(char*));
    for (int i = 0; token; i++){
        pole[i] = (char*) calloc(strlen(token) + 1, sizeof(char));
        strcpy(pole[i], token);
        token = strtok(NULL, delimiter);
        (*pocetRetazcov)++;
    }
    return pole;
}

void n(PODUJATIE** hlavicka, int* dlzkaZoznamu){

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
                aktualny = aktualny->dalsi;
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
            case 3:{
                int pocetPrezentujucich = 0;
                char** mena = rozdelitNaStringy(riadok, "#", &pocetPrezentujucich);
                MENO_AUTORA* hlavicka_mena = NULL, *aktualny_mena = NULL;

                for(int k = 0; k < pocetPrezentujucich; k++){
                    int dlzkaMena = 0;
                    char** rozdeleneMeno = rozdelitNaStringy(mena[k], " ", &dlzkaMena);
                    MENO_AUTORA* temp = aktualny_mena; // Ulozim si aktualny
                    
                    if(aktualny_mena){ // Pokial existuje aktualny tak sa posuniem o jeden uzol dopredu
                        aktualny_mena = aktualny_mena->dalsi;
                    }

                    aktualny_mena = (MENO_AUTORA*) malloc(sizeof(MENO_AUTORA)); // Alokujem novy uzol
                    aktualny_mena->predchadzajuci = temp; // Nastavim predchadzajuci na moj stary aktualny uzol
                    
                    if(!temp){ // Pokial neexistuje stary predchadzajuci uzol tak som na zaciatku...
                        hlavicka_mena = aktualny_mena; // ...tym padom nastavim hlavicku na aktualny uzol
                    }
                    else{
                        temp->dalsi = aktualny_mena;  // Inak na starom uzly nastavim moj novy uzol ako dalsi v poradi
                    }
                    
                    for (int j = 0; j < dlzkaMena; j++){
                        if(j == 0){ // Pokial som na prvej iteracii tak ulozim prvu cast retazca ako meno
                            aktualny_mena->meno = (char*) calloc(strlen(rozdeleneMeno[j])+1, sizeof(char));
                            strcpy(aktualny_mena->meno, rozdeleneMeno[j]);
                        }
                        else{ // Inak cast retazca ulozim ako priezvisko
                            if(j == 1){ // Pokial som na druhej iteracii tak si alokujem miesto pre priezvisko
                                aktualny_mena->priezvisko = (char*) calloc(strlen(rozdeleneMeno[j])+1, sizeof(char));
                                strcpy(aktualny_mena->priezvisko, rozdeleneMeno[j]);
                            }
                            else{ // Inak realokujem miesto pre priezvisko
                                aktualny_mena->priezvisko = (char*) realloc(aktualny_mena->priezvisko, strlen(aktualny_mena->priezvisko) + strlen(rozdeleneMeno[j])+2*sizeof(char));
                                strcat(aktualny_mena->priezvisko, " ");
                                strcat(aktualny_mena->priezvisko, rozdeleneMeno[j]);
                            }
                        }
                    }
                    aktualny_mena->dalsi = NULL;
                }
                aktualny->menaAutorov = hlavicka_mena; // Hlavicku linked listu mien nastavim ako mena autorov // TODO vylepsi tento koment :)
                break;
            }
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
                printf("DEBUG\n");
                i = -1; // O jeden menej lebo for loop tuto premennu inkrementuje na 0
                break;
            default:
                printf("Error");
        }
    }
    
    
    *dlzkaZoznamu = pocetZaznamov;
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

    if(!hlavicka){
        printf("Prázdny zoznam záznamov.\n");
        return;
    }

    PODUJATIE* aktualny = hlavicka;

    for(int i = 1; aktualny; i++){
        printf("%d\n", i);
        printf("ID cislo : %d\n", aktualny->ID);
        printf("Nazov prispevku: %s", aktualny->nazovPrispevku);
        
        MENO_AUTORA* aktualny_mena = aktualny->menaAutorov;
        printf("Mena autorov:\n");
        for (int j = 1; aktualny_mena; j++) {
            printf("%d: %s %s", j, aktualny_mena->meno, aktualny_mena->priezvisko);
            if(aktualny_mena->dalsi){
                printf("\n");
            }
            aktualny_mena = aktualny_mena->dalsi;
        }

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
        printf("Meno Autora: ");
            
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
        printf("Meno Autora: ");
        printf("Typ prezentovania: %s", aktualny->typPrezentovania);
        printf("Cas prezentovania: %d\n", aktualny->casPrezentovania);
        printf("Datum: %d\n", aktualny->datum);
        if(aktualny->predchadzajuci){
            aktualny = aktualny->predchadzajuci;
        }
        else{ break; }
    }
}