#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <Windows.h>
#include "funktionen.h"
#include "konstante.h"

void menu(int counter_ma, int counter_ab)
{
	printf("1) Neuer Mitarbeiter\n");
	printf("2) Neue Abteilung\n");
	printf("3) Zeige alle Mitarbeiter\n");
	printf("4) Zeige alle Abteilungen\n");
	printf("5) Suchen\n");
	printf("6) Speichern\n");
	printf("X) Schliessen\n");
}

int menu_suchen()
{
	int zeichen;

	printf("MITARBEITER\n");
	printf("1) -ID\n");
	printf("2) Vorname\n");
	printf("3) Nachname\n");
	printf("ABTEILUNG\n");
	printf("4) Name\n");
	printf("5) Abteilungsleiter\n");
	//zeichen = getche();
	scanf("%i", &zeichen);
	getchar();
	return zeichen;
}

void save_all(mitarbeiter *ma, ABTEILUNG *ab, int counter_ma, int counter_ab)
{
	FILE *f_ma, *f_ab;
	f_ma = fopen(FILE_MA, "wb");
	
	if (counter_ma > 0)
	{
		f_ma = fopen(FILE_MA, "wb");
		fwrite(ma, sizeof(mitarbeiter), counter_ma, f_ma);
		fclose(f_ma);
	}
	if (counter_ab > 0)
	{
		f_ab = fopen(FILE_AB, "wb");
		fwrite(ab, sizeof(mitarbeiter), counter_ab, f_ab);
		fclose(f_ab);
	}
	printf("Alles gespeichert\n");
	getchar();
}

int exist_ma_id(int id, mitarbeiter *ma, int counter_ma) //Rückabewerte: 0 = existiert nicht; 1 = existiert
{
	int i = 0, kontrolle = 0;
	do
	{
		if (id == ma[i].id)
			kontrolle = 1;
		i++;
	} while (i<counter_ma && kontrolle == 1);
	if (kontrolle == 1)
		return 1;
	else
		return 0;
}

int set_ma_id(mitarbeiter *ma, int pos, int counter_ma) //Rückgabewert: 0 = Fehler, 1 = erfolgreich
{
	int kontrolle;

	if (!scanf("%i", &kontrolle))
	{
		printf("Zahl eingeben\n");
		return 1;
	}
	else
		if (!exist_ma_id(kontrolle, ma, counter_ma))
		{
			ma[pos].id = kontrolle;
			return 0;
		}
		else
			printf("Die ID existiert bereits!\n");
}

int set_ma_eintrittsmonat(mitarbeiter *ma, int pos)
{
	int kontrolle;
	if (scanf("%i", &kontrolle))
	{
		if ((kontrolle < 1) || (kontrolle > 12))
		{
			printf("Bitte geben Sie eine Zahl zwischen 1 und 12 ein.\n");
			return 1;
		}
		else
		{
			ma[pos].eintritt.monat = kontrolle;
			return 0;
		}
	}
	else
	{
		printf("Bitte geben Sie eine Zahl ein!\n");
		return 1;
	}
	getchar();
}


void new_ma(mitarbeiter *ma, int *pos)
{
	int i, vorhanden = 0, z;
	int kontrolle;
	char test[5], test2[20];

	if (*pos < MAX_MA)
	{
		do
		{
			printf("ID: ");
		} while (set_ma_id(ma, *pos, *pos));
		getchar();
		//ma[*pos].id = kontrolle;

		printf("Vorname: ");
		scanf("%[a-z,A-Z, ]s", &ma[*pos].vname);
		getchar();
		printf("Name: ");
		scanf("%[a-z,A-Z, ]s", &ma[*pos].name);
		
		//######## BEGINN Eintrittsmonat ##############
		/*do
		{
			printf("Eintrittsmonat (1-12): ");
			if (i = scanf("%i", &kontrolle))
			{
				if ((kontrolle < 1) || (kontrolle > 12))
				{
					printf("Bitte geben Sie eine Zahl zwischen 1 und 12 ein.\n");
					i = 0;
				}
			}
			else
			{
				printf("Bitte geben Sie eine Zahl ein!\n");
			}
			getchar();
		} while (!i);
		ma[*pos].eintritt.monat = kontrolle;//*/

		//######## BEGINN Eintrittsmonat ##############
		do
		{
			printf("Eintrittsmonat (1-12): ");
		} while (set_ma_eintrittsmonat(ma, *pos));
		//######## ENDE Eintrittsmonat ##############


		//######## ENDE Eintrittsmonat ##############

		//######## BEGINN Eintrittsjahr ##############
		do
		{
			printf("Eintrittsjahr (XXXX): ");
			if (i = scanf("%i", &kontrolle))
			{
				if ((kontrolle < 1000) || (kontrolle > 9999))
				{
					printf("Bitte geben Sie eine 4-stellige Zahl ein.\n");
					i = 0;
				}
			}
			else
			{
				printf("Bitte geben Sie eine Zahl ein!\n");
			}
			getchar();
		} while (!i);
		ma[*pos].eintritt.jahr = kontrolle;
		//######## ENDE Eintrittsjahr ##############
		//######## BEGINN ADRESSE ##################
		printf("\nAdresse\n");
		printf("Strasse: ");
		scanf("%[a-z,A-Z, ]s", &ma[*pos].kontakt.adresse.strasse); //Strasse
		getchar();
		do //Hausnummer
		{
			printf("Hausnummer: ");
			i = scanf("%i", &kontrolle);
			if (!i)
				printf("Zahl eingeben\n");
			getchar();
		} while (!i);
		ma[*pos].kontakt.adresse.hausnr = kontrolle;//*/
		printf("PLZ: ");
		scanf("%s", &ma[*pos].kontakt.adresse.plz); //PLZ
		//scanf("%s", &test); //PLZ
		getchar();
		getchar(),
		printf("Ort: ");
		scanf("%[a-z,A-Z, ]s", &ma[*pos].kontakt.adresse.ort); //Ort
		//scanf("%[a-z,A-Z, ]s", &test2); //Ort
		//######## ENDE ADRESSE ##################
		//strcpy(ma[*pos].kontakt.adresse.ort, test2);
		//trcpy(ma[*pos].kontakt.adresse.plz, test);
		printf("\n\nPLZ: %s\n\nOrt: %s\n\n", ma[*pos].kontakt.adresse.plz, ma[*pos].kontakt.adresse.ort);
		
		//printf("\n\n%s\n\n", test);
		/*######## ANFANG KONTAKT ##################*/
		printf("\nKONTAKT\n");
		printf("Festnetz: ");
		scanf("%s", ma[*pos].kontakt.telefon.festnetz);
		printf("Mobil: ");
		scanf("%s", ma[*pos].kontakt.telefon.mobil);
		/*######## ENDE KONTAKT ##################*/

		printf("Abteilung: ");
		scanf("%i", &ma[*pos].abteilung); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Auswahl noch verbessern
		*pos = *pos + 1;
		getchar();

	}
	else
		printf("Die maximale Anzahl an Mitarbeitern ist erreicht!\n");
}

int load_all(mitarbeiter *ma, ABTEILUNG *ab, int *counter_ma, int * counter_ab)
{
	FILE *f_ma, *f_ab;
	f_ma = fopen(FILE_MA, "rb");
	f_ab = fopen(FILE_AB, "rb");
	if ((f_ma != NULL) && (f_ab != NULL))
	{
		*counter_ma = fread(ma, sizeof(mitarbeiter), MAX_MA, f_ma);
		*counter_ab = fread(ab, sizeof(ABTEILUNG), MAX_AB, f_ab);
		*counter_ab = *counter_ab - 1;
		fclose(f_ma);
		fclose(f_ab);
		return 1;
	}
	else
		return 0;
}

void show_ma(mitarbeiter *ma, int pos)
{
	printf("ID: %i\n", ma[pos].id);
	printf("%s %s\n", ma[pos].vname, ma[pos].name);
	printf("%s %i\n", ma[pos].kontakt.adresse.strasse, ma[pos].kontakt.adresse.hausnr);
	printf("%s %s\n", ma[pos].kontakt.adresse.plz, ma[pos].kontakt.adresse.ort);
	printf("%s\n", ma[pos].kontakt.adresse.plz);
	printf("Telefon: %s\n", ma[pos].kontakt.telefon.festnetz);
	printf("Mobil: %s\n", ma[pos].kontakt.telefon.mobil);
	printf("Mail: %s.%s@daddeldu.com\n", ma[pos].vname, ma[pos].name);
	printf("Eintritt: %i.%i\n", ma[pos].eintritt.monat, ma[pos].eintritt.jahr);
	printf("Abteilung: %i\n\n", ma[pos].abteilung);
}



void show_ab(ABTEILUNG *ab, mitarbeiter *ma, int pos, int counter_ma)
{
	int i = 0;
	int erfolg = 0;
	printf("Name, %s %s\n", ab[pos].name);
	printf("Standort %s\n", ab[pos].standort);
	//printf("Adresse: %s %i\n\t%s %s\n", ab[pos].adresse.strasse, ab[pos].adresse.hausnr, ab[pos].adresse.plz, ab[pos].adresse.ort);
	//printf("Abteilungsleiter: %i", ab[pos].abteilungsleiter);
	do
	{
		if (ab[pos].abteilungsleiter == ma[i].id)
		{
			printf("Abteilungsleiter: %s %s", ma[i].vname, ma[i].name);
			erfolg = 1;
		}
		i++;
	} while (erfolg != 1 || i < counter_ma);
	if (!erfolg)
	{
		printf("Konnte den ABteilungsleiter nicht finden.");
	}

	getchar();
}

void show_all_ab(ABTEILUNG *ab, mitarbeiter *ma, int counter_ab, int counter_ma)
{
	int i;
	printf("Counter: %i\n\n", counter_ab);
	for (i = 0; i < counter_ab; i++)
	{
		show_ab(ab, ma, i, counter_ma);
		printf("\n");
	}
}

void new_ab(ABTEILUNG *ab, mitarbeiter *ma, int *pos, int counter_ma)
{
	int i, counter = 0, leiter;
	int abteilung_a[MAX_MA];
	//ID
	if (*pos < MAX_AB)
	{
		printf("Abteilungsname: ");
		scanf("%s", &ab[*pos].name);
		printf("Standort: ");
		scanf("%s", &ab[*pos].standort);
		printf("Bitte wählen Sie einen Abteilungsleiter aus:\n");
		for (i = 0; i < counter_ma; i++)
		{
			if (ma[i].abteilung == -2)
			{
				printf("%i) ", counter + 1);
				show_ma(ma, i);
				abteilung_a[counter] = ma[i].id;
				counter++;
			}
		}
		printf("\n");
		do
		{
			scanf("%i", &leiter);
		} while (leiter > counter);
		ab[*pos].abteilungsleiter = abteilung_a[leiter - 1];
		//In array die verbindung  MA-ID zu wähltaste

		*pos = *pos + 1;
		//getchar();
		//getchar();
	}
	else
		printf("Die maximale Anzahl an Abteilungen ist erreicht!");
}

void create_files()
{
	FILE *f_ab, *f_ma;
	f_ab = fopen(FILE_AB, "wb");
	f_ma = fopen(FILE_MA, "wb");
	fcloseall();
}

void drop_ma(mitarbeiter *ma, int pos, int *counter_ma)
{
	//show_ma(ma, pos);
	//Wenn nur ein MA
	//Wenn am Ende
	if (pos == *counter_ma)
	{
		printf("letzter Datensatz");
		//counter_ma--;
	}
}

int show_ab_name(ABTEILUNG *ab, int counter_ab, int id) //RETURN POSITION ABTEILUNG IN ARRAY
{
	int i = 0, kontrolle = 0;
	do
	{
		if (id == ab[i].id)
			kontrolle = 1;
		i++;
	} while (i < counter_ab && kontrolle == 1);
	if (kontrolle == 1)
		return i--;
	else
		return -1;
}


void edit_ma(mitarbeiter *ma, int pos, int counter_ma)
{
	int nr, kontrolle;
	printf("(1) ID: %i\n", ma[pos].id);
	printf("(2)Vorname: %s\n(3)Nachname: %s\n", ma[pos].vname, ma[pos].name);
	printf("(4)Strasse: %s\n(5)Hausnr.: %i\n", ma[pos].kontakt.adresse.strasse, ma[pos].kontakt.adresse.hausnr);
	printf("(6)PLZ: %s\n(7)Ort: %s\n", ma[pos].kontakt.adresse.plz, ma[pos].kontakt.adresse.ort);
	//printf("(8)%s\n", ma[pos].kontakt.adresse.plz);
	printf("(8)Telefon: %s\n", ma[pos].kontakt.telefon.festnetz);
	printf("(9)Mobil: %s\n", ma[pos].kontakt.telefon.mobil);
	//printf("Mail: %s.%s@daddeldu.com\n", ma[pos].vname, ma[pos].name);
	printf("(10)Eintrittmonat: %i\n(11) Eintrittsjahr: %i\n", ma[pos].eintritt.monat, ma[pos].eintritt.jahr);
	printf("(12)Abteilung: %i\n\n", ma[pos].abteilung);
	printf("Welche Information wollen Sie aendern?");
	scanf("%i", &nr);
	switch (nr)
	{
	case 1:
		printf("ID: (%i): ", ma[pos].id);
		scanf("%i", &kontrolle);
		printf("Exisitert: %i\n", exist_ma_id(kontrolle, ma, counter_ma));
		if (!exist_ma_id(kontrolle, ma, counter_ma))
			ma[pos].id = kontrolle;
		getchar();
		break;
	case 2:
		printf("Vorname (%s): ", ma[pos].vname);
		break;
	case 3:
		printf("Nachname (%s): ", ma[pos].name);
		break;
	case 4:
		printf("Strasse (%s): ", ma[pos].kontakt.adresse.strasse);
		break;
	case 5:
		printf("Hausnr. (%i): ", ma[pos].kontakt.adresse.hausnr);
		break;
	case 6:
		printf("PLZ (%s): ", ma[pos].kontakt.adresse.plz);
		break;
	case 7:
		printf("Ort(%s):", ma[pos].kontakt.adresse.ort);
		break;
	case 8:
		printf("Telefon (%s): ", ma[pos].kontakt.telefon.festnetz);
		break;
	case 9:
		printf("Mobil (%s): ", ma[pos].kontakt.telefon.mobil);
		break;
	case 10:
		printf("Eintrittmonat (%i): ", ma[pos].eintritt.monat);
		break;
	case 11:
		printf("Eintrittsjahr (%i): ", ma[pos].eintritt.jahr);
		break;
	case 12:
		printf("Abteilung (%i): ", ma[pos].abteilung);
		break;
	default:
		break;
	}
	getchar();
}

void show_all_ma(mitarbeiter *ma, int counter_ma)
{
	int i, kontrolle = 0;
	char zeichen;
	int zeichen_int;
	for (i = 0; i < counter_ma; i++)
	{
		printf("(%i)\n", i + 1);
		show_ma(ma, i);
		printf("\n");
	}
	printf("Was wollen Sie tun?\n(B)earbeiten\n(L)oeschen\n(Z)urueck\nBitte waehlen Sie: ");
	scanf("%c", &zeichen);
	zeichen = toupper(zeichen);
	printf("Mitarbeiter-ID: ");
	scanf("%i", &zeichen_int);
	system("cls");
	i = 0;
	do // POs von Ma ermitteln
	{
		if (ma[i].id == zeichen_int)
			kontrolle = 1;
		i++;
	} while ((i < counter_ma) && (kontrolle == 1));
	i--;
	getchar();
	if (kontrolle == 1)
	{
		switch (zeichen)
		{
		case 'B':
			edit_ma(ma, i, counter_ma);

			break;
		case 'L':
			//drop_ma(ma, )
			break;
		default:
			break;
		}
	}
	else
		printf("Ein Datensatz mit dieser ID: %i existiert nicht", zeichen_int);
	getchar();

}