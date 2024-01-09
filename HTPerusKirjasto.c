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
/* Tehtävä harjoitustyö, tiedoston nimi HTPeruskirjasto.c */
#define _XOPEN_SOURCE 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "HTPerusKirjasto.h"

int valikko() {
    int valinta;
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Lue tiedosto\n");
    printf("2) Analysoi tiedot\n");
    printf("3) Kirjoita tulokset\n");
    printf("4) Viikonpäiväanalyysi\n");
    printf("5) Kielitasoanalyysi\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
        scanf("%d",&valinta);
        getchar();
    return(valinta);
}

char* nimi(char* pNImi) {
    printf("Anna tiedoston nimi: ");
        scanf("%s",pNImi);
        getchar();
    return(pNImi);
}

TIEDOT* mv_tiedot( TIEDOT *pointer ) {

    if ((pointer = (TIEDOT*)malloc(sizeof(TIEDOT))) == NULL) {
        perror("Muistinvaraus epäonnistui");
        exit(0);
    }
    return(pointer);
}

TIEDOT* lisaaListaan(TIEDOT* pAlku, char *sana, int luokka, int taso, struct tm tm) {
    TIEDOT *pUusi = NULL, *ptr;
    
    pUusi = mv_tiedot(pUusi);

    strcpy((pUusi->sana),sana);
    pUusi->luokka = luokka;
    pUusi->taso = taso;
    pUusi->aikaleima = tm;
    pUusi->pSeuraana = NULL;

    if (pAlku == NULL) {
        pAlku = pUusi;
    }else {
        ptr = pAlku;
        while (ptr->pSeuraana != NULL)
        {
            ptr = ptr->pSeuraana;
        }
        ptr->pSeuraana = pUusi;
    }
    return(pAlku);

}

TIEDOT* lueTiedosto(TIEDOT *pAlku, char *pNimi) {
    FILE *tiedosto;
    char rivi[PITUUS];
    char *pSana, sana[PITUUS];
    char *pSLuokka, sLuokka[PITUUS];
    char *pTaso, sTaso[PITUUS];
    
    
    
        
    pSana = sana;
    pSLuokka = sLuokka;
    pTaso = sTaso;

    if (pAlku != NULL) {
        pAlku = muistinvapautus(pAlku);
    }

    if ((tiedosto = fopen(pNimi,"r")) == NULL) {
            perror("Tiedoston avaaminen epäonnistui, lopetetaan");
            exit(0);
    }
    fgets(rivi,PITUUS,tiedosto);
    while ((fgets(rivi,PITUUS,tiedosto)) != NULL)
    { 
        struct tm tm;
        memset(&tm,0,sizeof(tm));
        strcpy(pSana,(strtok(rivi,";")));
        strcpy(pSLuokka,(strtok(NULL,";")));
        strcpy(pTaso,(strtok(NULL,";")));
        strptime(strtok(NULL,";"),"%d-%m-%Y %H:%M:%S",&tm);
        
        
        pAlku = lisaaListaan(pAlku,sana,atoi(sLuokka),atoi(sTaso),tm);
    }
    printf("Tiedosto '%s' luettu.\n", pNimi);
    fclose(tiedosto);
    return(pAlku);
}

TILASTO* tilastoAnalyysi(TIEDOT* pAlku, TILASTO* tilastot) {
    TIEDOT *ptr;
    ptr = pAlku;

    if (tilastot != NULL) { //Muistin vapautus, jos osoitin käytössä
        free(tilastot);
        tilastot = NULL;
    }

    tilastot = mv_tilasto(tilastot);
    //Alustetaan arvot
    tilastot->yht = 0;
    tilastot->maara = 0;
    strcpy((tilastot->lyhyin),(ptr->sana));
    strcpy((tilastot->pisin),(ptr->sana));
    strcpy((tilastot->ensnimmainen),(ptr->sana));
    strcpy((tilastot->viimeinen),(ptr->sana));

    



    while (ptr != NULL) { //Käydään linkitettylista läpi

        if (strlen(tilastot->lyhyin) > (strlen(ptr->sana))) {
            strcpy((tilastot->lyhyin),(ptr->sana));
        }
        if (strlen(tilastot->pisin) < (strlen(ptr->sana))) {
            strcpy((tilastot->pisin),(ptr->sana));
        }
        if (strcmp(ptr->sana,tilastot->ensnimmainen) < 0) {
            strcpy((tilastot->ensnimmainen),(ptr->sana));
        }
        if (strcmp(ptr->sana,tilastot->viimeinen) > 0) {
            strcpy((tilastot->viimeinen),(ptr->sana));
        }
        tilastot->maara++;
        tilastot->yht += strlen(ptr -> sana);

        ptr = ptr->pSeuraana;
    }
    printf("Analysoitu %d sanaa.\n",tilastot->maara);
    return(tilastot);    
}

TILASTO* mv_tilasto(TILASTO* pointer){
    if ((pointer = (TILASTO*)malloc(sizeof(TILASTO))) == NULL) {
        perror("Muistinvaraus epäonnistui");
        exit(0);
    }
    return(pointer);
}

TIEDOT* muistinvapautus(TIEDOT* pointer) {
    TIEDOT *ptr;

    ptr = pointer;
    while (ptr != NULL) {
        
        pointer = ptr->pSeuraana;
        free(ptr);
        ptr = pointer;
    }

    return(NULL);
}

SANALUOKKA* muistinvarausSanaluokka(SANALUOKKA *lista){
    if ((lista = (SANALUOKKA*)malloc(sizeof(SANALUOKKA)*LISTA_PITUUS)) == NULL) {
        perror("Muistinvaraus epäonnistui");
        exit(0);
    }
    return(lista);
}

SANALUOKKA* listaAnalyysi(SANALUOKKA *luokkaLista, TIEDOT *pAlku) {
    TIEDOT *ptr = NULL;

    if (luokkaLista != NULL) { //Muistin vapautus
        free(luokkaLista);
        luokkaLista = NULL;
    }
    
    luokkaLista = muistinvarausSanaluokka(luokkaLista); 
    for (int i = 0; i < LISTA_PITUUS; i++) {//Alustus
        SANALUOKKA uusi;
        uusi.nLuokka = i+1;
        uusi.maara = 0;
        luokkaLista[i] = uusi;
    }

    ptr = pAlku;
    while (ptr != NULL) //Käydään läpi lista, ja lisätään luokan mukaan uuteen staattiseen listaan
    {
        luokkaLista[(ptr->luokka)-1].maara += 1;
        ptr = ptr->pSeuraana; 
    }
    printf("Sanaluokittaiset lukumäärät analysoitu.\n");
    return(luokkaLista);
}

void tulostus(FILE *tietovirta, SANALUOKKA *lista, TILASTO *pTilasto){
    float keskiarvo = ((float)(pTilasto->yht)/(float)pTilasto->maara);
    fprintf(tietovirta,"Tilastotiedot %d sanasta:\n",pTilasto->maara);
    fprintf(tietovirta,"Keskimääräinen sanan pituus on %.1f merkkiä.\n",keskiarvo);
    fprintf(tietovirta,"Pisin sana '%s' on %ld merkkiä pitkä.\n", (pTilasto->pisin),strlen(pTilasto->pisin));
    fprintf(tietovirta,"Lyhyin sana '%s' on %ld merkkiä pitkä.\n", (pTilasto->lyhyin),strlen(pTilasto->lyhyin));
    fprintf(tietovirta,"Aakkosjärjestyksessä ensimmäinen sana on '%s'.\n",pTilasto->ensnimmainen);
    fprintf(tietovirta,"Aakkosjärjestyksessä viimeinen sana on '%s'.\n\n",pTilasto->viimeinen);

    fprintf(tietovirta,"Sanaluokka;Lkm\n");
    for (int i = 0; i < LISTA_PITUUS; i++) {
        fprintf(tietovirta,"Luokka %d;%d\n",lista[i].nLuokka,lista[i].maara);
    }
    return;
}   


void kirjoitus(SANALUOKKA *lista, TILASTO *pTilasto, char *nimi){
    FILE *tiedosto = NULL;
    tulostus(stdout, lista, pTilasto);
    if ((tiedosto = fopen(nimi,"w"))== NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    tulostus(tiedosto, lista, pTilasto);
    fclose(tiedosto);
    printf("Tiedosto '%s' kirjoitettu.\n",nimi);
    return;
}
/* eof */
