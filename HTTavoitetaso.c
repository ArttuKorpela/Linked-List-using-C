/*************************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Tekijä: Arttu Korpela
 * Opiskelijanumero: ######
 * Päivämäärä: 07.03.2023
 * Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat
 * lähteet ja henkilöt, ja se näkyy tehtävässä seuraavalla tavalla:
 * Ei muita lähteitä.
 * Mahdollisen vilppiselvityksen varalta vakuutan, että olen tehnyt itse
 * tämän tehtävän ja vain yllä mainitut henkilöt sekä lähteet ovat
 * vaikuttaneet siihen yllä mainituilla tavoilla.
 */
/*************************************************************************/
/* Tehtävä harjoitustyö, tiedoston nimi HTTavoitetaso.c */
#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "HTPerusKirjasto.h"

int main(void) {
    int valinta = 0, *pVknPvLista = NULL, *pMatriisi = NULL;
    char lueTiedNimi[PITUUS], *pLueTiedNimi = NULL, KirTiedNimi[PITUUS], *pKirTiedNimi = NULL;
    TIEDOT *pAlku = NULL;
    TILASTO *pTilasto = NULL;
    SANALUOKKA *lista = NULL;
    
 

    pLueTiedNimi = lueTiedNimi;
    pKirTiedNimi = KirTiedNimi;
    

    do {
        valinta = valikko();

        if (valinta == 1) {
            pLueTiedNimi = nimi(pLueTiedNimi);
            pAlku = lueTiedosto(pAlku,pLueTiedNimi);
        }

        else if (valinta == 2) {
            if (pAlku == NULL) {
                printf("Ei analysoitavaa, lue tiedosto ennen analyysiä.\n");
            }else {
                pTilasto = tilastoAnalyysi(pAlku, pTilasto);
                lista = listaAnalyysi(lista,pAlku);
            }
        }

        else if (valinta == 3) {
            if (pTilasto == NULL) {
                printf("Ei kirjoitettavia tietoja, analysoi tiedot ennen tallennusta.\n");
            }else {
                pKirTiedNimi = nimi(pKirTiedNimi);
                kirjoitus(lista,pTilasto,pKirTiedNimi);
            }
        }

        else if (valinta == 4) {
            if (pAlku == NULL) {
                printf( "Ei analysoitavaa, lue tiedosto ennen analyysiä.\n");
            }else {
                pVknPvLista = vp_Analyysi(pVknPvLista,pAlku);
            }
        }

        else if (valinta == 5) {
            if (pAlku == NULL) {
                printf( "Ei analysoitavaa, lue tiedosto ennen analyysiä.\n");
            }else {
                pMatriisi = kielitasoAnalyysi(pAlku, pMatriisi);
            }
        }

        else if (valinta == 0) {
            printf("Lopetetaan.\n");
        }

        else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }    

        printf("\n");
        
    }while (valinta != 0);
    
    free(lista);
    lista = NULL;
    pAlku = muistinvapautus(pAlku);
    pAlku = NULL;
    free(pTilasto);
    pTilasto = NULL;
    free(pVknPvLista);
    pVknPvLista = NULL;
    free(pMatriisi);
    pMatriisi = NULL;
    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
}
/* eof */
