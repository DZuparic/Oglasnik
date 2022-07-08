#ifndef HEADER_H
#define HEADER_H

typedef struct artikl {
	char naslov_artikla[100];
	float cijena;
	char kategorija[18];
	char lokacija[50];
	char opis[300];
}ARTIKL;

int novi_artikl();

void izbornik_pretrzaivanje();

void pretrazivanje(char);

void ispisArtikla(ARTIKL*);

int ispis_Artikala();

void uredivanje_Artikla();

void sortiranje_izbornik();

void sortiranjeCijene_veca_prema_manjoj(ARTIKL*, int);

void sortiranjeCijene_manja_prema_vecoj(ARTIKL*, int);

void brisanje();

void izlazak();

#endif // !HEADER_H