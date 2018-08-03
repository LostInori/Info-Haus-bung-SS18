#include <conio.h>
#include <stdio.h>
#include <Windows.h>
#include "konstante.h"
#include "funktionen.h"


/*
# search_ma_id: Suchen nach Mitarbeiter-ID
#
# IN:	int counter_ma: Anzahl Mitarbeiter
#		int counter_ab: Anzahl Abteilungen
#
# IN/OUT: mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilungsarray
*/
void search_ma_id(mitarbeiter *ma, int counter_ma, ABTEILUNG *ab, int counter_ab)
{
	int eingabe, i = 0, zaehler = 0, erfolg = 0;

	printf("Bitte geben Sie eine ID ein: ");
	scanf("%i", &eingabe);
	getchar();

	do //Bis alle durchsucht oder gefunden wurde
	{
		if (ma[i].id == eingabe) //Wenn Mitarbeiter mit eingegebener ID gefunden wurde
			erfolg = 1;
		else //Sonst nächsten Datensatz vergleichen
			i++;
	} while (zaehler < counter_ma && erfolg == 0);

	if (erfolg) //Wenn erfolgreich
	{
		//Datensatz ausgeben
		show_ma(ma, i, ab, counter_ab);
	}
	else
		printf("Es wurde kein Datensatz gefunden!");
	getchar();
}//*/

 /*
 # search_ma_vname: Suchen nach Mitarbeiter-Vorname
 #
 # IN:	int counter_ma: Anzahl Mitarbeiter
 #		int counter_ab: Anzahl Abteilungen
 #
 # IN/OUT: mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
 #			ABTEILUNG *ab: Zeiger auf Abteilungsarray
 */
void search_ma_vname(mitarbeiter *ma, int counter_ma, ABTEILUNG *ab, int counter_ab)
{
	char eingabe[20], kontrolle[20];
	int i, z, len, menge = 0;

	printf("Bitte geben Sie den gesuchten Vornamen ein: ");
	fgets(eingabe, 22, stdin); //Eingabe Vorname
	eingabe[strlen(eingabe) - 1] = '\0';

	len = strlen(eingabe); //Länge de Eingabe ermitteln
	
	for (z = 0; z < len; z++) //Jedes Zeichen der Eingabe von Kleinbuchstabe nach Großbuchstabe
		if (eingabe[z] >= 'a' && eingabe[z] <= 'z')
			eingabe[z] = toupper(eingabe[z]);

	for (i = 0; i < counter_ma; i++) //Jeden Mitarbeitervorname vergleichen
	{
		strcpy(kontrolle, ma[i].vname);
		len = strlen(kontrolle);
		for (z = 0; z < len; z++)//Jedes Zeichen des Arrays von Kleinbuchstabe nach Großbuchstabe
			if (kontrolle[z] >= 'a' && kontrolle[z] <= 'z')
				kontrolle[z] = toupper(kontrolle[z]);

		if (strstr(kontrolle, eingabe) != NULL) //Wenn Erfolgreich Beide Strings verglichen
		{
			//Ausgabe vollständigen Datensatz
			menge++;
			show_ma(ma, i, ab, counter_ab); //Ausgabe
			printf("\n");
		}
	}
	if (menge == 0) //Wenn kein Datensatz passte
	{
		printf("Es wurde kein Datensatz gefunden.");
	}
	getchar();
}//*/

 /*
 # search_ma_vname: Suchen nach Mitarbeiter-Nachname
 #
 # IN:	int counter_ma: Anzahl Mitarbeiter
 #		int counter_ab: Anzahl Abteilungen
 #
 # IN/OUT: mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
 #			ABTEILUNG *ab: Zeiger auf Abteilungsarray
 */
void search_ma_name(mitarbeiter *ma, int counter_ma, ABTEILUNG *ab, int counter_ab)
{
	char eingabe[30], kontrolle[30];
	int i, z, len, menge = 0;

	getchar();
	printf("Bitte geben Sie den gesuchten Namen ein: ");
	fgets(eingabe, 22, stdin); //Eingabe Nachname
	eingabe[strlen(eingabe) - 1] = '\0';

	len = strlen(eingabe); //Länge de Eingabe ermitteln
	for (z = 0; z < len; z++) //Jedes Zeichen der Eingabe von Kleinbuchstabe nach Großbuchstabe
		if (eingabe[z] >= 'a' && eingabe[z] <= 'z')
			eingabe[z] = toupper(eingabe[z]);

	for (i = 0; i < counter_ma; i++) //Jeden Mitarbeitervorname vergleichen
	{
		strcpy(kontrolle, ma[i].name);
		len = strlen(kontrolle);
		for (z = 0; z < len; z++) //Jedes Zeichen des Arrays von Kleinbuchstabe nach Großbuchstabe
			if (kontrolle[z] >= 'a' && kontrolle[z] <= 'z')
				kontrolle[z] = toupper(kontrolle[z]);

		if (strstr(kontrolle, eingabe)) //Wenn Erfolgreich Beide Strings verglichen
		{
			//Ausgabe vollständigen Datensatz
			menge++;
			show_ma(ma, i, ab, counter_ab); //Ausgabe
			printf("\n");
		}
	}
	if (menge == 0)
	{
		printf("Es wurde kein Datensatz gefunden."); //Wenn kein Datensatz passte
	}
	getchar();
}

/*
# search_ab_ma: Suchen nach Abteilungs-Name
#
# IN:	int counter_ma: Anzahl Mitarbeiter
#		int counter_ab: Anzahl Abteilungen
#		int ab_id: Abteilungs-ID
#
# IN/OUT:	mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilungsarray
*/
void search_ab_ma(mitarbeiter *ma, ABTEILUNG *ab, int counter_ma, int counter_ab, int ab_id)
{
	int i;

	for (i = 0; i < counter_ma; i++) //Alle Mitarbeiter durchgehen
		if (ma[i].abteilung == ab_id) //Wenn Mitarbeiter in der Abteilung ist
			show_ma(ma, i, ab, counter_ab);
}

/*
# search_ab_name: Suchen nach Abteilungs-Name
#
# IN:	int counter_ma: Anzahl Mitarbeiter
#		int counter_ab: Anzahl Abteilungen
#
# IN/OUT: mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilungsarray
*/
void search_ab_name(mitarbeiter *ma, ABTEILUNG *ab,int counter_ma, int counter_ab)
{
	
	char eingabe[30], kontrolle[30];
	int i, z, len, id, menge = 0;

	printf("Bitte geben Sie den gesuchten Abteilungsnamen ein: ");
	fgets(eingabe, 22, stdin); //Eingabe Abteilungsname
	eingabe[strlen(eingabe) - 1] = '\0';

	len = strlen(eingabe); //Länge der Eingabe ermitteln
	for (z = 0; z < len; z++) //Alle Buchstaben zu Großbuchstaben umwandeln
		if (eingabe[z] >= 'a' && eingabe[z] <= 'z')
			eingabe[z] = toupper(eingabe[z]);
	getchar();
	for (i = 0; i < counter_ab; i++) //Alle Abteilungen durchgehen
	{
		strcpy(kontrolle, ab[i].name);
		len = strlen(kontrolle);
		for (z = 0; z < len; z++) //Alle Namen der Abteilung in Großbuchstaben umwandeln
			if (kontrolle[z] >= 'a' && kontrolle[z] <= 'z')
				kontrolle[z] = toupper(kontrolle[z]);

		if (strstr(kontrolle, eingabe)) //Wenn Eingabe mit Abteilungsname übereinstimmt
		{
			//Ausgabe vollständigen Datensatz
			menge++;
			printf("%s\n", kontrolle);
			id = ab[i].id;
			search_ab_ma(ma, ab, counter_ma, counter_ab, ab[i].id);
		}
	}
	if (menge == 0) //Wenn kein Datensatz gefunden wurde
	{
		printf("Es wurde kein Datensatz gefunden.");
	}
	getchar();
}