#include "header.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int novi_artikl() {
	FILE* fp = NULL;
	ARTIKL* novi_artikl = NULL;
	novi_artikl = (ARTIKL*)malloc(sizeof(ARTIKL));
	int broj_artikala;
	int odabir_kategorije;

	if (novi_artikl == NULL) {
		return 1;
	}
	else {
		printf("Unesite naslov artikla: ");
		scanf(" %99[^\n]", novi_artikl->naslov_artikla);

		printf("Odaberite kategoriju artikla:");
		printf("\n\t1. Automobili\n");
		printf("\t2. Nekretnine\n");
		printf("\t3. Racunala i oprema\n");
		printf("\t4. Uredaji\n");
		odabir_kategorije = getch();
		switch (odabir_kategorije) {
		case '1':
			strcpy(novi_artikl->kategorija, "Automobili");
			break;
		case '2':
			strcpy(novi_artikl->kategorija, "Nekretnine");
			break;
		case '3':
			strcpy(novi_artikl->kategorija, "Racunala i oprema");
			break;
		case '4':
			strcpy(novi_artikl->kategorija, "Uredaji");
			break;
		default:
			printf("\nKrivi unos!\n");
			break;
		}

		printf("Unesite lokaciju artikla: ");
		scanf(" %49[^\n]", novi_artikl->lokacija);

		printf("Unesite cijenu artikla: ");
		scanf("%f", &novi_artikl->cijena);

		printf("Unesite kratak opis artikla: ");
		scanf(" %299[^\n]", novi_artikl->opis);

		fp = fopen("artikli.bin", "rb");
		if (fp == NULL) {
			fp = fopen("artikli.bin", "wb");
			broj_artikala = 1;
			fwrite(&broj_artikala, sizeof(int), 1, fp);
			fwrite(novi_artikl, sizeof(ARTIKL), 1, fp);
			fclose(fp);
		}
		else {
			fclose(fp);
			fp = fopen("artikli.bin", "rb+");
			if (fp == NULL) {
				return 1;
			}
			else {
				fseek(fp, 0, SEEK_SET);
				fread(&broj_artikala, sizeof(int), 1, fp);
				broj_artikala++;
				fseek(fp, 0, SEEK_SET);
				fwrite(&broj_artikala, sizeof(int), 1, fp);
				fseek(fp, 0, SEEK_END);
				fwrite(novi_artikl, sizeof(ARTIKL), 1, fp);
				fclose(fp);
			}
		}
	}
	free(novi_artikl);
	return 0;
}

void izbornik_pretrzaivanje() {
	system("cls");
	printf("\n\n1. Pretrazivanje po imenu\n");
	printf("2. Pretrazivanje po kategoriji\n");
	printf("3. Pretrazivanje po lokaciji\n");
	printf("4. Pretrazivanje po cijeni\n");
	char odabir = getch();
	switch (odabir) {
	case '1':
		pretrazivanje('i');
		break;
	case '2':
		pretrazivanje('k');
		break;
	case '3':
		pretrazivanje('l');
		break;
	case '4':
		pretrazivanje('c');
		break;
	default:
		printf("\nKrivi unos.");
	}
}

void pretrazivanje(char kriterij) {
	ARTIKL* artikli = NULL;
	FILE* fp = NULL;
	char trazeno_ime[100];
	char trazena_kategorija[18];
	int odabir_kategorije;
	char trazena_lokacija[50];
	float min_cijena;
	float max_cijena;
	int broj_artikala;
	int f = 0;

	fp = fopen("artikli.bin", "rb");
	if (fp == NULL) {
		printf("\nGreska.\n");
	}
	else {
		fread(&broj_artikala, sizeof(int), 1, fp);
		artikli = (ARTIKL*)malloc(sizeof(ARTIKL));
		if (artikli == NULL) {
			printf("Greska.\n");
		}
		else {
			switch (kriterij) {
			case 'i':
				printf("\nUnesite ime trazenog artikla: ");
				scanf(" %99[^\n]", trazeno_ime);
				for (int i = 0; i < broj_artikala; i++) {
					fread(artikli, sizeof(ARTIKL), 1, fp);
					if (strcmp(artikli->naslov_artikla, trazeno_ime) == 0) {
						ispisArtikla(artikli);
						f = 1;
						break;
					}
				}
				break;
			case 'k':
				printf("\nOdaberite kategoriju: ");
				printf("\n\t1. Automobili\n");
				printf("\t2. Nekretnine\n");
				printf("\t3. Racunala i oprema\n");
				printf("\t4. Uredaji\n");
				odabir_kategorije = getch();
				switch (odabir_kategorije) {
				case '1':
					strcpy(trazena_kategorija, "Automobili");
					break;
				case '2':
					strcpy(trazena_kategorija, "Nekretnine");
					break;
				case '3':
					strcpy(trazena_kategorija, "Racunala i oprema");
					break;
				case '4':
					strcpy(trazena_kategorija, "Uredaji");
					break;
				default:
					printf("\nKrivi unos!\n");
					break;
				}
				for (int i = 0; i < broj_artikala; i++) {
					fread(artikli, sizeof(ARTIKL), 1, fp);
					if (strcmp(artikli->kategorija, trazena_kategorija) == 0) {
						ispisArtikla(artikli);
						f = 1;
					}
				}
				break;
			case 'l':
				printf("\nUnesite lokaciju trazenog artikla: ");
				scanf(" %99[^\n]", trazena_lokacija);
				for (int i = 0; i < broj_artikala; i++) {
					fread(artikli, sizeof(ARTIKL), 1, fp);
					if (strcmp(artikli->lokacija, trazena_lokacija) == 0) {
						ispisArtikla(artikli);
						f = 1;
						break;
					}
				}
				break;
			case 'c':
				printf("Unesite minimalnu cijenu: ");
				scanf(" %f", &min_cijena);
				printf("Unesite maksimalnu cijenu: ");
				scanf(" %f", &max_cijena);
				for (int i = 0; i < broj_artikala; i++) {
					fread(artikli, sizeof(ARTIKL), 1, fp);
					if (artikli->cijena >= min_cijena && artikli->cijena <= max_cijena) {
						ispisArtikla(artikli);
						f = 1;
					}
				}
				break;
			}
			if (f == 0) {
				printf("\nNije moguce pronaci artikl.");
			}
			fclose(fp);
		}
	}
}

void ispisArtikla(ARTIKL* artikli) {
	printf("\n\nNaslov: %s", artikli->naslov_artikla);
	printf("\nCijena: %.2fkn", artikli->cijena);
	printf("\nKategorija: %s", artikli->kategorija);
	printf("\nLokacija: %s", artikli->lokacija);
	printf("\n-%s", artikli->opis);

	return;
}

int ispis_Artikala() {
	int broj;
	ARTIKL* artikli = NULL;
	FILE* fp = NULL;
	fp = fopen("artikli.bin", "rb");
	if (fp == NULL) {
		return 1;
	}
	else {
		fread(&broj, sizeof(int), 1, fp);
		artikli = (ARTIKL*)malloc(sizeof(ARTIKL));
		if (artikli == NULL) {
			return 1;
		}
		else {
			printf("Na oglasniku je objavljen %d  oglas.", broj);
			for (int i = 0; i < broj; i++) {
				fread(artikli, sizeof(ARTIKL), 1, fp);
				ispisArtikla(artikli);
			}
			free(artikli);
			fclose(fp);
			return broj;
		}
	}
}

void uredivanje_Artikla() {
	FILE* fp = NULL;
	ARTIKL* oglas = NULL;
	int broj_artikala;
	fp = fopen("artikli.bin", "rb+");
	if (fp == NULL) {
		printf("\nGreska!");
	}
	else {
		fread(&broj_artikala, sizeof(int), 1, fp);
		oglas = (ARTIKL*)malloc(sizeof(ARTIKL));
		if (oglas == NULL) {
			printf("\nGreska!");
		}
		else {
			char trazeni_naslov[100];
			int f = 0;
			system("cls");
			printf("Unesite naslov artikla kojeg zelite izmjeniti:");
			scanf(" %99[^\n]", trazeni_naslov);
			for (int i = 0; i < broj_artikala; i++) {
				fread(oglas, sizeof(ARTIKL), 1, fp);
				if (strcmp(oglas->naslov_artikla, trazeni_naslov) == 0) {
					f = 1;
					ispisArtikla(oglas);
					printf("\n\nOdaberite opciju:");
					printf("\n1.Promjena naslova");
					printf("\n2.Promjena kategorije");
					printf("\n3.Promjena cijene");
					printf("\n4.Promjena lokacije");
					printf("\n5.Promjena opisa");
					printf("\n6.Povratak u izbornik\n");

					char odabir = getch();
					switch (odabir) {
					case '1'://Promjena naslova
						printf("\nUnesite novi naslov:");
						char novi_naslov[100];
						scanf(" %99[^\n]", novi_naslov);
						strcpy((oglas)->naslov_artikla, novi_naslov);
						fseek(fp, -(int)sizeof(ARTIKL), SEEK_CUR);
						fwrite(oglas, sizeof(ARTIKL), 1, fp);
						printf("\nNaslov uspjesno promjenjen");
						break;

					case '2'://Promjena kategorije
						printf("\nOdaberite novu kategoriju:");
						printf("\n\t1. Automobili\n");
						printf("\t2. Nekretnine\n");
						printf("\t3. Racunala i oprema\n");
						printf("\t4. Uredaji\n");
						int nova_kategorija = getch();
						switch (nova_kategorija) {
						case '1':
							strcpy((oglas)->kategorija, "Automobili");
							break;
						case '2':
							strcpy((oglas)->kategorija, "Nekretnine");
							break;
						case '3':
							strcpy((oglas)->kategorija, "Racunala i oprema");
							break;
						case '4':
							strcpy((oglas)->kategorija, "Uredaji");
							break;
						default:
							printf("\nKrivi unos!\n");
							break;
						}
						fseek(fp, -(int)sizeof(ARTIKL), SEEK_CUR);
						fwrite(oglas, sizeof(ARTIKL), 1, fp);
						printf("Kategorija uspjesno promjenjena");
						break;

					case '3'://Promjena cijene
						printf("\nUnesite novu cijenu: ");
						float nova_cijena;
						scanf("%f", &nova_cijena);
						oglas->cijena = nova_cijena;
						fseek(fp, -(int)sizeof(ARTIKL), SEEK_CUR);
						fwrite(oglas, sizeof(ARTIKL), 1, fp);
						printf("\nCijena uspjesno promjenjena.\n");
						break;

					case '4'://Promjena lokacije
						printf("\nUnesite novu lokaciju:");
						char nova_lokacija[50];
						scanf(" %49[^\n]", nova_lokacija);
						strcpy((oglas)->lokacija, nova_lokacija);
						fseek(fp, -(int)sizeof(ARTIKL), SEEK_CUR);
						fwrite(oglas, sizeof(ARTIKL), 1, fp);
						printf("\nLokacija uspjesno promjenjena");
						break;

					case '5'://Promjena opisa
						printf("\nUnesite novi opis: ");
						char novi_opis[300];
						scanf(" %299[^\n]", novi_opis);
						strcpy((oglas)->opis, novi_opis);
						fseek(fp, -(int)sizeof(ARTIKL), SEEK_CUR);
						fwrite(oglas, sizeof(ARTIKL), 1, fp);
						printf("\nOpis uspjesno promjenjen");
						break;

					case'6'://povratak
						return;
						break;

					default:
						printf("Krivi unos.");
					}
					break;
				}
			}
			if (f == 0) {
					printf("Artikl nije pronaden");
			}

		}
		fclose(fp);
	}
	free(oglas);
}

void sortiranje_izbornik() {
	ARTIKL* artikli = NULL;
	FILE* fp = NULL;

	char odabir1;
	int broj_artikala;
	system("cls");

	fp = fopen("artikli.bin", "rb");
	if (fp == NULL) {
		printf("\nGreska.\n");
	}
	else {
		fread(&broj_artikala, sizeof(int), 1, fp); //citanje broja artikala
		artikli = (ARTIKL*)malloc(broj_artikala * sizeof(ARTIKL));
		if (artikli == NULL) {
			printf("\nGreska!");
		}

		else {
			fread(artikli, sizeof(ARTIKL), broj_artikala, fp);
			system("cls");
			printf("Odaberite nacin sortiranja cijene:\n");
			printf("\n1. Od manje prema vecoj");
			printf("\n2. Od vece prema manjoj\n");
			odabir1 = getch();

			switch (odabir1) {
			case '1'://Manja prema vecoj
				sortiranjeCijene_manja_prema_vecoj(artikli, broj_artikala);
				break;

			case '2'://Veca prema manjoj
				sortiranjeCijene_veca_prema_manjoj(artikli, broj_artikala);
				break;

			default:
				printf("\nKrivi unos.");
				break;
			}


			fclose(fp);
			fp = fopen("artikli.bin", "wb");
			if (fp == NULL) {
				printf("\nGreska!");
			}
			else {
				//azuriranje datoteke
				fwrite(&broj_artikala, sizeof(int), 1, fp);
				fwrite(artikli, sizeof(ARTIKL), broj_artikala, fp);
				fclose(fp);
			}
			free(artikli);
			artikli = NULL;
		}
	}


	printf("\n\nSortiranje uspjesno obavljeno.");
	printf("\nPritisnite bilo koju tipku za povratak...\n");
	getch();
}

void sortiranjeCijene_manja_prema_vecoj(ARTIKL* artikli, int broj_artikala) {
	ARTIKL temp;
	float cijena1, cijena2;
	int min;

	for (int i = 0; i < broj_artikala - 1; i++) {
		min = i;
		cijena1 = (artikli + i)->cijena;
		for (int j = i + 1; j < broj_artikala; j++) {
			cijena2 = (artikli + j)->cijena;
			if (cijena1 > cijena2) {
				min = j;
				cijena1 = (artikli + j)->cijena;
			}
		}
		//zamjena naslova oglasa
		strcpy(temp.naslov_artikla, (artikli + i)->naslov_artikla);
		strcpy((artikli + i)->naslov_artikla, (artikli + min)->naslov_artikla);
		strcpy((artikli + min)->naslov_artikla, temp.naslov_artikla);
		//zamjena kategorije artikla
		strcpy(temp.kategorija, (artikli + i)->kategorija);
		strcpy((artikli + i)->kategorija, (artikli + min)->kategorija);
		strcpy((artikli + min)->kategorija, temp.kategorija);
		//zamjena lokacije artikla
		strcpy(temp.lokacija, (artikli + i)->lokacija);
		strcpy((artikli + i)->lokacija, (artikli + min)->lokacija);
		strcpy((artikli + min)->lokacija, temp.lokacija);
		//zamjena opisa artikla
		strcpy(temp.opis, (artikli + i)->opis);
		strcpy((artikli + i)->opis, (artikli + min)->opis);
		strcpy((artikli + min)->opis, temp.opis);
		//zamjena cijene
		temp.cijena = (artikli + i)->cijena;
		(artikli + i)->cijena = (artikli + min)->cijena;
		(artikli + min)->cijena = temp.cijena;
	}

	return;
}

void sortiranjeCijene_veca_prema_manjoj(ARTIKL* artikli, int broj_artikala) {
	ARTIKL temp;
	float cijena1, cijena2;
	int max;

	for (int i = 0; i < broj_artikala - 1; i++) {
		max = i;
		cijena1 = (artikli + i)->cijena;
		for (int j = i + 1; j < broj_artikala; j++) {
			cijena2 = (artikli + j)->cijena;
			if (cijena1 < cijena2) {
				max = j;
				cijena1 = (artikli + j)->cijena;
			}
		}
		//zamjena naslova oglasa
		strcpy(temp.naslov_artikla, (artikli + i)->naslov_artikla);
		strcpy((artikli + i)->naslov_artikla, (artikli + max)->naslov_artikla);
		strcpy((artikli + max)->naslov_artikla, temp.naslov_artikla);
		//zamjena kategorije artikla
		strcpy(temp.kategorija, (artikli + i)->kategorija);
		strcpy((artikli + i)->kategorija, (artikli + max)->kategorija);
		strcpy((artikli + max)->kategorija, temp.kategorija);
		//zamjena lokacije artikla
		strcpy(temp.lokacija, (artikli + i)->lokacija);
		strcpy((artikli + i)->lokacija, (artikli + max)->lokacija);
		strcpy((artikli + max)->lokacija, temp.lokacija);
		//zamjena opisa artikla
		strcpy(temp.opis, (artikli + i)->opis);
		strcpy((artikli + i)->opis, (artikli + max)->opis);
		strcpy((artikli + max)->opis, temp.opis);
		//zamjena cijene
		temp.cijena = (artikli + i)->cijena;
		(artikli + i)->cijena = (artikli + max)->cijena;
		(artikli + max)->cijena = temp.cijena;
	}

	return;
}

void brisanje() {
	FILE* fp = NULL;
	ARTIKL* oglas = NULL;
	int broj_artikala;
	int index_brisanja;

	fp = fopen("artikli.bin", "rb");
	if (fp == NULL) {
		printf("\nGreska! ");
	}
	
	else {
		fread(&broj_artikala, sizeof(int), 1, fp);
		oglas = (ARTIKL*)malloc(broj_artikala * sizeof(ARTIKL));
		if (oglas == NULL) {
			printf("\nGreska.");
		}
		else {
			fread(oglas, sizeof(ARTIKL), broj_artikala, fp);
			fclose(fp);
			//trazenje
			char trazeni_naslov[100];
			int f = 0;
			system("cls");
			printf("Unesite naslov artikla kojeg zelite obrisati: ");
			scanf(" %99[^\n]", trazeni_naslov);
			for (int i = 0; i < broj_artikala; i++) {
				if (strcmp((oglas + i)->naslov_artikla, trazeni_naslov) == 0) {
					ispisArtikla(oglas + i);
					index_brisanja = i;
					f = 1;
					break;
				}
			}
			if (f == 0) {
				printf("\nArtikl nije pronaden.");
			}
			else {
				fclose(fp);
				fp = fopen("artikli.bin", "wb");
				if (fp == NULL) {
					printf("\nGreska.");
				}
				else {
					broj_artikala--;
					fwrite(&broj_artikala, sizeof(int), 1, fp);
					for (int i = 0; i < broj_artikala + 1; i++) {
						if (i == index_brisanja) {
							continue;
						}
						else {
							fwrite((oglas + i), sizeof(ARTIKL), 1, fp);
						}
					}
					printf("\n\nArtikl je uspjesno obrisan!");
					fclose(fp);
				}
			}
		}
	}
}

void izlazak() {
	int odabir;

	printf("Zelite li izaci iz programa?");
	printf("\n1. DA.");
	printf("\n2. NE.\n");

	do {
		scanf("%d", &odabir);
		if (odabir < 1 || odabir > 2) {
			printf("\nKrivi unos.\nPokusajte ponovo: ");
		}
	} while (odabir < 1 || odabir > 2);

	if (odabir == 1) {
		printf("\n\nPritisnite bilo koju tipku da zatvorite program...");
		exit(EXIT_SUCCESS);
	}
	else {
		return;
	}
}
