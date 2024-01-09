/*************************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Tekijä: Arttu Korpela
 * Opiskelijanumero: 001155912
 * Päivämäärä: 07.03.2023
 * Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat
 * lähteet ja henkilöt, ja se näkyy tehtävässä seuraavalla tavalla:
 * Ei muita lähteitä.
 * Mahdollisen vilppiselvityksen varalta vakuutan, että olen tehnyt itse
 * tämän tehtävän ja vain yllä mainitut henkilöt sekä lähteet ovat
 * vaikuttaneet siihen yllä mainituilla tavoilla.
 */
/*************************************************************************/
/* Tehtävä harjoitustyö, tiedoston nimi HTTavoiteKirjasto.c */
#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "HTPerusKirjasto.h"


int* mv_Viikkopaiva(int* pLista) {
    if ((pLista = (int*)malloc(sizeof(int)*VIIKONPAIVAT)) == NULL) {
        perror("Muistinvaraus epäonnistui");
        exit(0);
    }
    return(pLista);
}

int* vp_Analyysi(int* pLista, TIEDOT* pAlku) {
    char tNimi[PITUUS], *pNimi;
    pNimi = tNimi;

    if (pLista != NULL) {
        free(pLista);
        pLista = NULL;
    }

    pLista = mv_Viikkopaiva(pLista);
    for (int i = 0; i < VIIKONPAIVAT; i++) {
        pLista[i] = 0;
    }
    TIEDOT* ptr = pAlku;
    while (ptr != NULL)
    {
        pLista[(ptr->aikaleima).tm_wday] += 1;
        ptr = ptr->pSeuraana; 
    }
    pNimi = nimi(pNimi);
    vp_kirjoitus(pNimi,pLista);
    return(pLista);
}


int* kielitasoAnalyysi(TIEDOT *pAlku, int *pArray) {
    int rivit = 0, *pUusi = NULL; 
    TIEDOT *ptr = NULL;
    char tNimi[PITUUS], *pNimi = NULL;
    ptr = pAlku;
    pNimi = tNimi;

    pNimi = nimi(pNimi);
    
    if (pArray != NULL) { //Jos analyysi tehdään uudestaan
        free(pArray);
        pArray = NULL;
    }

    while (ptr != NULL)
    {
        if (ptr->luokka > rivit) {
            if (rivit == 0) { //Ensimmäisen kerran matriisin alustus
                pArray = mv_Matriisi(pArray,ptr->luokka);
                for (int i = 0; i < ((ptr->luokka*KIELITASO_MAARA)); i++){
                    pArray[i] = 0;
                }
                rivit = ptr->luokka;

            } else {
                pUusi = mv_Matriisi(pUusi,rivit); //Alustetaan matriisi, johon kopioidaan vanhat luvut
            
                for (int i = 0; i < ((rivit*KIELITASO_MAARA)); i++){
                    pUusi[i] = 0;
                    pUusi[i] = pArray[i];
                }
                pArray = mv_Matriisi(pArray, ptr->luokka); //Muistinvaraus rivien mukaan
                for (int i = 0; i < ((ptr->luokka*KIELITASO_MAARA)); i++){
                    if (i < rivit*5) {
                        pArray[i] = 0;
                        pArray[i] = pUusi[i];
                    } else {
                        pArray[i] = 0;
                    }
                }
                
                rivit = ptr->luokka;
            }
        }    
        pArray[(((ptr->luokka-1)*KIELITASO_MAARA)+(ptr->taso)-1)] += 1; // Mennään ensin aikaisempien rivien verran eteenpäin, jonka jälkeen lisätään tason-1, 
        ptr = ptr->pSeuraana;
    }
    matriisi_Kirjoitus(pNimi, pArray, rivit*5);

    free(pUusi);
    pUusi = NULL; //Vapautetaan väliaikaismatriisin muisti
    
    return(pArray);
}

int* mv_Matriisi(int *pArray,int rivit) {
    if ((pArray = realloc(pArray,(rivit*KIELITASO_MAARA)*sizeof(int))) == NULL) {
        perror("Muistinvarauksessa virhe");
        exit(0);
    }
    return(pArray);
}

void vp_kirjoitus(char* nimi, int* lista) {
    FILE* tiedosto;
    

    if ((tiedosto = fopen(nimi,"w"))== NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    fprintf(tiedosto,"Viikonpäivä;Ma;Ti;Ke;To;Pe;La;Su\n");
    fprintf(tiedosto,"Lukumäärä;%d;%d;%d;%d;%d;%d;%d", lista[1], lista[2], lista[3], lista[4], lista[5], lista[6], lista[0]);
    
    printf("Tiedosto '%s' kirjoitettu.\n", nimi);
    fclose(tiedosto);
    return;
}

void matriisi_Kirjoitus(char* nimi, int* lista, int koko) {
    FILE* tiedosto;
    int rivi = 1;
    

    if ((tiedosto = fopen(nimi,"w"))== NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    fprintf(tiedosto,"Sanaluokka;A1;A2;B1;B2;C1");
    for (int i = 0; i < (koko); i++) {
        if ((i)%5 == 0){fprintf(tiedosto,"\nLuokka %d",rivi++);}
        fprintf(tiedosto,";%d",lista[i]);
    }
    printf("Tiedosto '%s' kirjoitettu.\n",nimi);
    fclose(tiedosto);
    return;
}
/* eof */