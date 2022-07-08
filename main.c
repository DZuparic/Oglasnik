#include "header.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int odabir_opcije;
	while (1) {
		system("cls");
		printf("******************OGLASNIK******************\n");
		printf("____________________________________________\n");
		printf("---------1. Dodavanje novog artikla---------\n");
		printf("____________________________________________\n");
		printf("----------2. Pretrazivanje artikla----------\n");
		printf("____________________________________________\n");
		printf("--------------3. Ispis artikala-------------\n");
		printf("____________________________________________\n");
		printf("------------4. Uredivanje artikla-----------\n");
		printf("____________________________________________\n");
		printf("-----------5. Sortiranje artikala-----------\n");
		printf("____________________________________________\n");
		printf("-------------6. Brisanje artikla------------\n");
		printf("____________________________________________\n");
		printf("-----------7. Izlazak iz izbornika----------\n");
		printf("____________________________________________\n");

		printf("Odaberite opciju: ");

		odabir_opcije = getch();//Korisnik unosi jednu od ponudenih opcija
		switch (odabir_opcije) {
		case '1': //dodavanje novog artikla pomocu funkcije novi_artikl
			system("cls");
			if (novi_artikl() == 1) {
				printf("\nGreska. \n");
			}
			printf("\n\nPritisnite bilo koju tipku za povrtak....\n\n");
			getch();
			break;

		case '2': //otvara se novi izbornik koji nudi cetiri tipa pretrazivanja
			izbornik_pretrzaivanje();
			printf("\n\nPritisnite bilo koju tipku za povratak...\n\n");
			getch();
			break;

		case '3': //ispis svih unesenih oglasa
			system("cls");
			if (ispis_Artikala() == -1) {
				printf("\nGreska.\n");
			}
			printf("\n\nPritisnite bilo koju tipku za povratak....\n\n");
			getch();
			break;

		case '4'://Uredivanje artikla - izmjena naziva, kategorije, cijene, lokacije, opisa
			uredivanje_Artikla();
			printf("\n\nPritisnite bilo koju tipku za povratak....\n\n");
			getch();
			break;

		case '5'://Sortiranje po cijeni - od vece prema manjoj, i obrnuto
			system("cls");
			sortiranje_izbornik();//Izbornik koji nam nudi dvije opcije sortiranja
			break;

		case '6'://Brisanje artikla iz oglasnika
			brisanje();
			printf("\n\nPritisnite bilo koju tipku za povratak....\n\n");
			getch();
			break;

		case '7'://Izlazak iz programa
			system("cls");
			izlazak();
			break;
		
		default:
			printf("\nPritisnite bilo koju tipku za povrtaka....\n");
			getch();
		}

	}
}