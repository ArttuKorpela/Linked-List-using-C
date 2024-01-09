/*************************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Tekijä: Arttu Korpela
 * Opiskelijanumero: #######
 * Päivämäärä: 07.03.2023
 * Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat
 * lähteet ja henkilöt, ja se näkyy tehtävässä seuraavalla tavalla:
 * Ei muita lähteitä.
 * Mahdollisen vilppiselvityksen varalta vakuutan, että olen tehnyt itse
 * tämän tehtävän ja vain yllä mainitut henkilöt sekä lähteet ovat
 * vaikuttaneet siihen yllä mainituilla tavoilla.
 */
/*************************************************************************/
/* Tehtävä harjoitustyö, tiedoston nimi HTPeruskirjasto.h */
#ifndef HTPERUSKIRJASTO_H
#define HTPERUSKIRJASTO_H
#define _XOPEN_SOURCE 
#define PITUUS 255
#define LISTA_PITUUS 10
#define KIELITASO_MAARA 5
#define VIIKONPAIVAT 7
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



typedef struct tiedot
{
    char sana[PITUUS];
    int luokka;
    int taso;
    struct tm aikaleima;
    struct tiedot *pSeuraana;    
    
} TIEDOT;

typedef struct tilasto
{   
    int maara;
    int yht;
    char pisin[PITUUS];
    char lyhyin[PITUUS];
    char ensnimmainen[PITUUS];
    char viimeinen[PITUUS];

} TILASTO;

typedef struct sanaluokka 
{
    int nLuokka;
    int maara;
} SANALUOKKA;


int valikko();
char* nimi(char* pNImi);
TIEDOT* mv_tiedot( TIEDOT *pointer );
TIEDOT* lisaaListaan(TIEDOT* pAlku, char *sana, int luokka, int taso, struct tm tm);
TIEDOT* lueTiedosto(TIEDOT *pAlku, char *pNimi);
TILASTO* tilastoAnalyysi(TIEDOT* pAlku, TILASTO* pTilastot);
TILASTO* mv_tilasto(TILASTO* pointer);
TIEDOT* muistinvapautus(TIEDOT* pointer);
SANALUOKKA* muistinvarausSanaluokka(SANALUOKKA *lista);
SANALUOKKA* listaAnalyysi(SANALUOKKA *luokkaLista, TIEDOT *pAlku);
void tulostus(FILE *tietovirta, SANALUOKKA *lista, TILASTO *pTilasto);
void kirjoitus(SANALUOKKA *lista, TILASTO *pTilasto, char *nimi);
int* mv_Viikkopaiva(int* pLista);
int* vp_Analyysi(int* pLista, TIEDOT* pAlku);
int* kielitasoAnalyysi(TIEDOT *pAlku, int *pArray);
int* mv_Matriisi(int *pArray,int rivit);
void vp_kirjoitus(char* nimi, int* lista);
void matriisi_Kirjoitus(char* nimi, int* lista, int koko);
#endif
/* eof */
