#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <Windows.h>
#include "funktionen.h"
#include "konstante.h"

/*
# menu: Ausgabe des Hauptmenüs
#
# IN:	int counter_ma: Anzahl Mitarbeiter
#		int counter_ab: Anzahl Abteilungen
*/
void menu(int counter_ma, int counter_ab)
{
	printf("1) Neuer Mitarbeiter\n");
	printf("2) Neue Abteilung\n");
	if (counter_ma > 0)
		printf("3) Zeige alle Mitarbeiter\n");
	if (counter_ab > 0)
		printf("4) Zeige alle Abteilungen\n");
	if (counter_ma > 0 || counter_ab > 0)
		printf("5) Suchen\n");
	printf("6) Speichern\n");
	printf("X) Schliessen\n");
}

/*
# menu_suchen: Zeigt das Suchenmenü an
#
# RETURN: Gibt zurück, wonach gesucht werden soll
*/
int menu_suchen()
{
	int zeichen;

	printf("MITARBEITER\n");
	printf("1) -ID\n");
	printf("2) Vorname\n");
	printf("3) Nachname\n");
	printf("ABTEILUNG\n");
	printf("4) Name\n");
	scanf("%i", &zeichen);
	getchar();
	return zeichen;
}

/*
# save_all: Speichern aller Datensätze in die Dateien, die in der Datei konstante.h unter FILE_MA und FILE_AB hinterlegt sind
#
# IN:	int counter_ma: Anzahl Mitarbeiter
#		int counter_ab: Anzahl Abteilungen
#
# IN/OUT mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#		 ABTEILUNG *ab: Zeiger auf Abteilung-Array
*/
void save_all(mitarbeiter *ma, ABTEILUNG *ab, int counter_ma, int counter_ab)
{
	FILE *f_ma, *f_ab;
	
	if (counter_ma > 0) //Bei mehr als 0 Mitarbeitern speichern
	{
		f_ma = fopen(FILE_MA, "wb");
		fwrite(ma, sizeof(mitarbeiter), counter_ma, f_ma);
		fclose(f_ma);
	}
	if (counter_ab > 0) //Bei mehr als 0 Abteilungen speichern
	{
		f_ab = fopen(FILE_AB, "wb");
		fwrite(ab, sizeof(ABTEILUNG), counter_ab, f_ab);
		fclose(f_ab);
	}
	printf("Alles gespeichert\n");
	getchar();
}

/*
# exists_ma_id: Ermittelt ob ID schon vorhanden
#
# IN:		int id: Zu suchende ID
#			int counter_ma: Anzahl von Datensätzen im Array
#
# IN/OUT:	 int mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#
# RETURN:	0 = Exisitiert nicht
#			1 = Existiert
*/
int exist_ma_id(int id, mitarbeiter *ma, int counter_ma) //Rückabewerte: 0 = existiert nicht; 1 = existiert
{
	int i = 0, kontrolle = 0;

	do //Solange, bis alle IDs kontrolliert wurden, oder die zu testende ID gefunden wurde
	{
		if (id == ma[i].id)
			kontrolle = 1;
		i++;
	} while (i<counter_ma && kontrolle != 1);
	if (kontrolle == 1)
		return 1;
	else
		return 0;
}

/*
# exists_ab_id: Ermittelt ob ID schon vorhanden
#
# IN:		int id: Zu suchende ID
#			int counter_ab: Anzahl von Datensätzen im Array
#
# IN/OUT:	 int ABTEILUNG *ab: Zeiger auf Abteilungs-Array
#
# RETURN:	0 = Exisitiert nicht
#			1 = Existiert
*/
int exist_ab_id(int id, ABTEILUNG *ab, int counter_ab) //Rückabewerte: 0 = existiert nicht; 1 = existiert
{
	int i = 0, kontrolle = 0;
	do //Solange, bis alle IDs kontrolliert wurden, oder die zu testende ID gefunden wurde
	{
		if (id == ab[i].id)
			kontrolle = 1;
		i++;
	} while (i<counter_ab && kontrolle != 1);
	if (kontrolle == 1)
		return 1;
	else
		return 0;
}

/*
# set_ma_pos: Ermittelt Position vom gesuchten Datensatz im Array
#
# IN:		int id: Zu suchende ID
#			int counter_ma: Anzahl von Datensätzen im Array
#
# IN/OUT:	 int mitarbaiter *ma: Zeiger auf Mitarbeiter-Array
#
# RETURN:	Position im Array
#			Wenn kein Datensatz gefunden wurde: -1
*/
int get_ma_pos(int id, mitarbeiter *ma, int counter_ma)
{
	int i = 0, kontrolle = 0;
	do //Solange, bis alle IDs kontrolliert wurden, oder die zu testende ID gefunden wurde
	{
		if (ma[i].id == id) // Gefunden, dann Kontrolle = 1
			kontrolle = 1;
		i++;
	} while (i < counter_ma && kontrolle != 1);
	if (kontrolle == 1)
	{
		return i-1; //Rückgabe von Position im Array
	}
	else
		return -1;
}

/*
# set_ab_pos: Ermittelt Position vom gesuchten Datensatz im Array
#
# IN:		int id: Zu suchende ID
#			int counter_ab: Anzahl von Datensätzen im Array
#
# IN/OUT:	 int ABTEILUNG *ab: Zeiger auf Abteilungs-Array
#
# RETURN:	Position im Array
#			Wenn kein Datensatz gefunden wurde: -1
*/
int get_ab_pos(int id, ABTEILUNG *ab, int counter_ab) //return: -1: Kein Datensatz gefunden; Position des Datensatzes
{
	int i = 0, kontrolle = 0;

	do //Solange, bis alle IDs kontrolliert wurden, oder die zu testende ID gefunden wurde
	{
		if (ab[i].id == id) // Gefunden, dann Kontrolle = 1
			kontrolle = 1;
		i++;
	} while (i < counter_ab && kontrolle != 1);
	if (kontrolle == 1)
	{
		return i - 1; //Rückgabe von Position im Array
	}
	else
		return -1;
}

/*
# set_ma_id: Erstellen einer Mitarbeiter-ID (incl. Überprüfung, ob schon vorhanden)
#
# IN:		int pos: Zeiger auf Position im Mitarbeiter-Array, an der der neue Datensatz abgelegt werden soll
#			int counter_ma: Anzahl von Datensätzen im Array
#
# IN/OUT:	 int mitarbaiter *ma: Zeiger auf Mitarbeiter-Array
#
# RETURN:	0 = Eingabe ist Okey (Erfolgreich)
#			1 = Fehler
*/
int set_ma_id(mitarbeiter *ma, int pos, int counter_ma) //Rückgabewert: 0 = Erfolgreich, 1 = Fehler
{
	int kontrolle = 0, i = 0, erfolg = 1;
	char kontrolle1[20];

	scanf("%s", &kontrolle1); //Einlesen von String
	do //Jede Stelle von String durchgehen, bis ein Buchstabe gefunden wurde.
	{
		if (isdigit(kontrolle1[i]) == 0) //Ein Buchstabe gefunden
			erfolg = 0;
		i++;
	} while (i < strlen(kontrolle1) && erfolg == 1);

	if (!erfolg) //Wenn eine Buchstabe im String enthalten war
	{
		printf("Zahl eingeben\n");
		getchar();
		return 1;
	}
	else
	{
		kontrolle = atoi(kontrolle1); //Umwandeln in int
		if (!exist_ma_id(kontrolle, ma, counter_ma)) //Kontrolle, ob ID existiert
		{
			ma[pos].id = kontrolle;
			return 0;
		}
		else
		{
			printf("Die ID existiert bereits!\n");
			return 1;
		}
	}
}

/*
# set_ab_id: Erstellen einer Abteilungs-ID (incl. Überprüfung, ob schon vorhanden)
#
# IN:		int pos: Zeiger auf Position im Abteilungs-Array, an der der neue Datensatz abgelegt werden soll
#			int counter_ab: Anzahl von Datensätzen im Array
#
# IN/OUT:	 int ABTEILUNG *ab: Zeiger auf Abteilungs-Array
#
# RETURN:	0 = Eingabe ist Okey (Erfolgreich)
#			1 = Fehler
*/
int set_ab_id(ABTEILUNG *ab, int pos, int counter_ab) //Rückgabewert: 0 = Erfolgreich, 1 = Fehler
{

	int kontrolle, i = 0, erfolg = 1;
	char kontrolle1[20];

	scanf("%s", &kontrolle1); //Einlesen von String
	do //Jede Stelle von String durchgehen, bis ein Buchstabe gefunden wurde.
	{
		if (isdigit(kontrolle1[i]) == 0) //Ein Buchstabe gefunden
			erfolg = 0;
		i++;
	} while (i < strlen(kontrolle1) && erfolg == 1);

	if (!erfolg) //Wenn ein Buchstabe im String enthalten war
	{
		printf("Zahl eingeben\n");
		getchar();
		return 1;
	}
	else
	{
		kontrolle = atoi(kontrolle1); //Umwandeln in int
		if (!exist_ab_id(kontrolle, ab, counter_ab)) //Kontrolle, ob ID existiert
		{
			ab[pos].id = kontrolle;
			return 0;
		}
		else
		{
			printf("Die ID existiert bereits!\n");
			return 1;
		}
	}
}

/*
# set_ma_eintrittsmonat: Einlesen eines Eintrittmonats
#
# IN:	int pos: Zeiger auf Position im Mitarbeiter-Array, an der der neue Datensatz abgelegt werden soll
#
# IN/OUT:	 int mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#
# RETURN:	0 = Eingabe ist Okey (Erfolgreich)
#			1 = Fehler
*/
int set_ma_eintrittsmonat(mitarbeiter *ma, int pos) //Rückgabewert: 0 = Erfolgreich, 1 = Fehler
{
	int kontrolle, i = 0, erfolg = 1;
	char kontrolle1[20];

	scanf("%s", &kontrolle1); //Einlesen eines Strings
	do //Jede Stelle von String durchgehen, bis ein Buchstabe gefunden wurde.
	{
		if (isdigit(kontrolle1[i]) == 0) //Ein Buchstabe gefunden
			erfolg = 0;
		i++;
	} while (i < strlen(kontrolle1) && erfolg == 1);


	if (erfolg) //Wenn kein Buchstabe im String enthalten war
	{
		kontrolle = atoi(kontrolle1);
		if ((kontrolle < 1) || (kontrolle > 12)) //Wenn es keine Zahl zwischen 1 und 12
		{
			printf("Bitte geben Sie eine Zahl zwischen 1 und 12 ein.\n");
			return 1;
		}
		else //Speichern im Array
		{
			ma[pos].eintritt.monat = kontrolle;
			return 0;
		}
	}
	else // Wenn ein Buchstabe im String enthalten ist
	{
		printf("Bitte geben Sie eine Zahl ein!\n");
		getchar();
		return 1;
	}
	getchar();
}

/*
# set_ma_eintrittsjahr: Einlesen eines Eintrittjahres
#
# IN:		int pos: Zeiger auf Position im Mitarbeiter-Array, an der der neue Datensatz abgelegt werden soll
#
# IN/OUT:	 int mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#
# RETURN:	0 = Eingabe ist Okey (Erfolgreich)
#			1 = Fehler
*/
int set_ma_eintrittsjahr(mitarbeiter *ma, int pos) //Rückgabewert: 0 = Erfolgreich, 1 = Fehler
{
	int kontrolle, i = 0, erfolg = 1;
	char kontrolle1[20];

	scanf("%s", &kontrolle1); //Einlesen eines Strings
	do //Jede Stelle von String durchgehen, bis ein Buchstabe gefunden wurde.
	{
		if (isdigit(kontrolle1[i]) == 0) //Ein Buchstabe gefunden
			erfolg = 0;
		i++;
	} while (i < strlen(kontrolle1) && erfolg == 1);

	if (erfolg) //Wenn kein Buchstabe im String enthalten war
	{
		kontrolle = atoi(kontrolle1);
		if ((kontrolle < 1000) || (kontrolle > 9999)) //Wenn es keine Zahl zwischen 1000 und 9999
		{
			printf("Bitte geben Sie eine 4-stellige Zahl ein.\n");
			//getchar();
			return 1;
		}
		else //Speichern im Array
		{
			ma[pos].eintritt.jahr = kontrolle;
			return 0;
		}
	}
	else // Wenn ein Buchstabe im String enthalten ist
	{
		printf("Bitte geben Sie eine Zahl ein!\n");
		getchar();
		return 1;
	}
	getchar();
}

/*
# set_ma_hausnr: Einlesen einer Hausnummer
#
# IN:	int pos: Zeiger auf Position im Mitarbeiter-Array, an der der neue Datensatz abgelegt werden soll
#		
# IN/OUT:	 int mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#
#RETURN:	0 = Eingabe ist Okey (Erfolgreich)
			1 = Fehler
*/
int set_ma_hausnr(mitarbeiter *ma, int pos) //Rückgabewert: 0 = Erfolgreich, 1 = Fehler
{
	int kontrolle, i = 0, erfolg = 1;
	char kontrolle1[20];

	scanf("%s", &kontrolle1); //Einlesen eines Strings
	do //Jede Stelle von String durchgehen, bis ein Buchstabe gefunden wurde.
	{
		if (isdigit(kontrolle1[i]) == 0) //Ein Buchstabe gefunden
			erfolg = 0;
		i++;
	} while (i < strlen(kontrolle1) && erfolg == 1);

	if (!erfolg) //Wenn ein Buchstabe gefunden wurde
	{
		printf("Zahl eingeben\n");
		getchar();
		return 1;
	}
	else //Wen kein Buchstabe gefunden wurde
	{
		kontrolle = atoi(kontrolle1); //Umwandeln in int
		ma[pos].kontakt.adresse.hausnr = kontrolle; //Speichern im Array
		return 0;
	}
}

/*
# set_ab_hausnr: Einlesen einer Hausnummer
#
# IN:		int pos: Zeiger auf Position im Abteilungs-Array, an der der neue Datensatz abgelegt werden soll
#
# IN/OUT:	 int ABTEILUNG *ab: Zeiger auf Abteilung-Array
#
# RETURN:	0 = Eingabe ist Okey (Erfolgreich)
#			1 = Fehler
*/
int set_ab_hausnr(ABTEILUNG *ab, int pos) //Rückgabewert: 0 = Erfolgreich, 1 = Fehler
{
	int kontrolle, i = 0, erfolg = 1;
	char kontrolle1[20];

	scanf("%s", &kontrolle1); //Einlesen eines Strings
	do //Jede Stelle von String durchgehen, bis ein Buchstabe gefunden wurde.
	{
		if (isdigit(kontrolle1[i]) == 0) //Ein Buchstabe gefunden
			erfolg = 0;
		i++;
	} while (i < strlen(kontrolle1) && erfolg == 1);

	if (!erfolg) //Wenn ein Buchstabe gefunden wurde
	{
		printf("Zahl eingeben\n");
		getchar();
		return 1;
	}
	else //Wenn kein Buchstabe gefunden wurde
	{
		kontrolle = atoi(kontrolle1); //Umwandeln in int
		ab[pos].adresse.hausnr = kontrolle; //Speichern in Array
		return 0;
	}
}

/*
# set_string_edit: Gibt einen String zurück
#
# RETURN: String
*/
EINGABE set_string(char name[30])
{
	EINGABE eingabe;
	do //Solange bis mindestens ein Zeichen eingegeben wurde
	{
		printf("%s: ", name); //Ausgabe vin Variable name
		fgets(eingabe.eingabe, 30, stdin); //Einlesen von string
		if (strlen(eingabe.eingabe) <= 1) //Wenn nichts eingegeben wurde
			printf("Bitte geben Sie etwas ein!\n");
	} while (strlen(eingabe.eingabe) <= 1); 
	eingabe.eingabe[strlen(eingabe.eingabe) - 1] = '\0'; //Stringende um ein Zeichen nach vorne (/n wird elemeniert)
	return eingabe; //Return string
}

/*
# set_string_edit: Gibt einen String zurück
#
# RETURN: String
*/
EINGABE set_string_edit()
{
	EINGABE eingabe;
	do //Solange bis mindestens ein Zeichen eingegeben wurde
	{
		fgets(eingabe.eingabe, 30, stdin); //Einlesen von string
		if (strlen(eingabe.eingabe) <= 1)
			printf("Bitte geben Sie etwas ein!\n");
	} while (strlen(eingabe.eingabe) <= 1); //Wenn nichts eingegeben wurde
	eingabe.eingabe[strlen(eingabe.eingabe) - 1] = '\0'; //Stringende um ein Zeichen nach vorne (/n wird elemeniert)
	return eingabe; //Return string
}

/*
# new_ma: Erstellen eines neuen Mitarbeiters
#
# IN:	mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#		int *pos: Zeiger auf Position im Mitarbeiter-Array, an der der neue Datensatz abgelegt werden soll
#		ABTEILUNG *ab: Zeiger auf Abteilung-Array
#		int *counter_ma: Zeiger auf Anzahl Mitarbeiter, wird nach erfolgreichem erstellen um 1 erhöht
#
# IN/OUT int counter_ab: Anzahl Abteilungen
*/
void new_ma(mitarbeiter *ma, int *pos, ABTEILUNG *ab, int counter_ab)
{
	int i;
	int abteilung[MAX_AB+3];
	int abteilung_r;
	int zurueck;
	EINGABE eingabe;
	

	if (*pos < MAX_MA) //Wenn nicht alle Plätze im Array belegt sind, dann neuen Mitarbeiter anlegen
	{

		do //Solange bis eine nicht vergebene ID eingegeben wurde
		{
			printf("ID: ");
		} while (set_ma_id(ma, *pos, *pos));
		getchar();

		//Vorname
		eingabe = set_string("Vorname");
		strcpy(ma[*pos].vname, eingabe.eingabe);

		//Nachname
		eingabe = set_string("Name");
		strcpy(ma[*pos].name, eingabe.eingabe);

		//######## BEGINN Eintrittsmonat ##############
		do
		{
			printf("Eintrittsmonat (1-12): ");
		} while (set_ma_eintrittsmonat(ma, *pos));
		//######## ENDE Eintrittsmonat ##############

		//######## BEGINN Eintrittsjahr ##############
		do
		{
			printf("Eintrittsjahr (XXXX): ");
		} while (set_ma_eintrittsjahr(ma, *pos));
		getchar();
		//######## ENDE Eintrittsjahr ##############
		//######## BEGINN ADRESSE ##################
		printf("\nAdresse\n");

		//Straße
		eingabe = set_string("Strasse");
		strcpy(ma[*pos].kontakt.adresse.strasse, eingabe.eingabe);

		do //Hausnummer
		{
			printf("Hausnummer: ");
		} while (set_ma_hausnr(ma, *pos));
		getchar();

		//PLZ
		eingabe = set_string("PLZ");
		strcpy(ma[*pos].kontakt.adresse.plz_test, eingabe.eingabe);

		//Ort
		eingabe = set_string("Ort");
		strcpy(ma[*pos].kontakt.adresse.ort, eingabe.eingabe);

		//######## ENDE ADRESSE ##################

		//######## ANFANG KONTAKT ##################
		printf("\nKONTAKT\n");

		//Festnetz
		eingabe = set_string("Festnetz");
		strcpy(ma[*pos].kontakt.telefon.festnetz, eingabe.eingabe);

		//Mobil
		eingabe = set_string("Mobil");
		strcpy(ma[*pos].kontakt.telefon.mobil, eingabe.eingabe);
//*/
		//######## ENDE KONTAKT ##################*/
		i = 0;
		printf("\nAbteilung\n");
		if (counter_ab > 0) //Mehr als 0 Abteilungen
		{
			for (i = 1; i <= counter_ab; i++) //Alle Abteilungen auslesen
			{
				printf("\n(%i)\t %s", i, ab[i-1].name); //Abteilungsname ausgeben
				abteilung[i] = ab[i-1].id; //Abteilung-ID in Array schreiben
			}
		}
		printf("\n(%i)\tWird Abteilungsleiter\n", i + 1); //Ausgabe Wird Abteilungsleiter ausgeben
		abteilung[i + 1] = -2;
		printf("(%i)\tKeine Abteilung zuweisen\n", i + 2); //Ausgabe "Keine Abteilung zuweisen" ausgeben
		abteilung[i + 2] = -1;


		do //Solange bis eine Zahl die kleiner als Anzahl von Abteilungen +2 ist
		{
			printf("Bitte waehlen Sie: ");
			scanf("%i", &abteilung_r);
		} while (abteilung_r > i + 2);
		ma[*pos].abteilung = abteilung[abteilung_r];

		*pos = *pos + 1; //Position im Array um 1 erhöhen
		getchar();
		system("cls"); //Bildschirm leeren
		printf("\n\nMitarbeiter erfolgreich angelegt");
		getchar();
	}
	else //Wenn alle Plätze im Array belegt sind Fehler ausgeben
		printf("Die maximale Anzahl an Mitarbeitern ist erreicht!\n");
}

/*
# load_all: Laden der kompletten Datenstruktur aus den Dateien, die unter FILE_MA und FILE_AB in konstante.h abgelegt wurde
#
# IN/OUT:	mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilungs-Array
#			int *counter_ma: Zeiger auf Anzahl Mitarbeiter, gibt Anzahl von erfolgreich geladenen Mitarbeiter-Datensätzen zurück
#			int *counter_ab: Zeiger auf Anzahl Abteilungen, gibt Anzahl von erfolgreich geladenen Abteilung-Datensätzen zurück
#
# RETURN:	1: Erfolgreiches Laden der Daten
#			0: Fehler beim Laden der Daten
*/
int load_all(mitarbeiter *ma, ABTEILUNG *ab, int *counter_ma, int *counter_ab)
{
	FILE *f_ma, *f_ab;
	f_ma = fopen(FILE_MA, "rb"); //Dateien zum schreiben binär öffnen
	f_ab = fopen(FILE_AB, "rb");
	if ((f_ma != NULL) && (f_ab != NULL)) //Wenn Dateien erfolgreich geöffnet
	{
		*counter_ma = fread(ma, sizeof(mitarbeiter), MAX_MA, f_ma); //Laden aller Daten aus der Datei
		*counter_ab = fread(ab, sizeof(ABTEILUNG), MAX_AB, f_ab); //Laden aller Daten aus der Datei
		
		fclose(f_ma); //Schließen der Dateien
		fclose(f_ab);
		return 1;
	}
	else //Wenn die Dateien nicht erfolgreich geöffnet werden konnten
		return 0;
}

/*
# show_ma: Anzeigen eines Mitarbeiter
#
# IN:		int pos: Position im Mitarbeiter Array
#			int_counter_ab: Anzahl von Abteilungsdatensätzen
#
# IN/OUT	mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilung-Array
*/
void show_ma(mitarbeiter *ma, int pos, ABTEILUNG *ab, int counter_ab)
{
	//Ausgabe der Informationen vom Mitarbeiter an der Position pos im Array
	printf("ID: %i\n", ma[pos].id);
	printf("%s %s\n", ma[pos].vname, ma[pos].name);
	printf("%s %i\n", ma[pos].kontakt.adresse.strasse, ma[pos].kontakt.adresse.hausnr);
	printf("%s %s\n", ma[pos].kontakt.adresse.plz_test, ma[pos].kontakt.adresse.ort);
	//printf("%s\n", ma[pos].kontakt.adresse.plz);
	printf("Telefon: %s\n", ma[pos].kontakt.telefon.festnetz);
	printf("Mobil: %s\n", ma[pos].kontakt.telefon.mobil);
	printf("Mail: %s.%s@daddeldu.com\n", ma[pos].vname, ma[pos].name);
	printf("Eintritt: %i.%i\n", ma[pos].eintritt.monat, ma[pos].eintritt.jahr);

	//Ausgabe der Abteilung
	if (ma[pos].abteilung == -1)
		printf("Abteilung: Keine Abteilung zugewiesen\n");
	else if (ma[pos].abteilung == -2)
		printf("Abteilung : Kann Abteilungsleiter sein\n");
	else
		printf("Abteilung: %s\n\n", ab[get_ab_pos(ma[pos].abteilung, ab, counter_ab)].name); //Suchen der Abteilung anhand der Abteilungs-ID und anschließender Ausgabe	
}

/*
# edit_ab: Bearbeiten von Abteilungsdatensatz
#
# IN:		int pos: Position im Abteilungs-Array
#			int counter_ma: Anzahl Mitarbeiter-Datensätze
#			int counter_ab: Anzahl von Abteilungsdatensätzen
#
# IN/OUT	mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilung-Array
*/
void edit_ab(mitarbeiter *ma,ABTEILUNG *ab, int pos, int counter_ma, int counter_ab)
{
	int nr, i, counter = 0, leiter;
	int abteilung_a[MAX_MA];
	EINGABE eingabe;

	//Ausgabe der zu veränderbaren Attribute
	printf("(1)Name: %s\n", ab[pos].name);
	printf("(2)Strasse: %s\n", ab[pos].adresse.strasse);
	printf("(3)Hausnr.: %i\n", ab[pos].adresse.hausnr);
	printf("(4)PLZ: %s\n", ab[pos].adresse.plz_test);
	printf("(5)Ort: %s\n", ab[pos].adresse.ort);
	printf("(6)Standort: %s\n", ab[pos].standort);
	printf("(7)Abteilungsleiter: %i\n", ab[pos].abteilungsleiter);
	printf("Welche Information wollen Sie aendern?");
	scanf("%i", &nr); //Abfrage der zu ändernden Variable
	switch (nr)
	{
	case 1: //Name
		printf("Name (%s): ", ab[pos].name);
		eingabe = set_string_edit();
		strcpy(ab[pos].name, eingabe.eingabe);
		break;
	case 2: //Strasse
		printf("Strasse (%s): ", ab[pos].adresse.strasse);
		eingabe = set_string_edit();
		strcpy(ab[pos].adresse.strasse, eingabe.eingabe);
		break;
	case 3: //Hausnummer
		do 
		{
			printf("Hausnummer: ");
		} while (set_ab_hausnr(ab, pos));
		break;
	case 4: //PLZ
		printf("PLZ (%s): ", ab[pos].adresse.plz_test);
		eingabe = set_string_edit();
		strcpy(ab[pos].adresse.plz_test, eingabe.eingabe);
		break;
	case 5: //Ort
		printf("Ort (%s): ", ab[pos].adresse.ort);
		eingabe = set_string_edit();
		strcpy(ab[pos].adresse.ort, eingabe.eingabe);
		break;
	case 6: //Standort
		printf("Standort (%s): ", ab[pos].standort);
		eingabe = set_string_edit();
		strcpy(ab[pos].standort, eingabe.eingabe);
		break;
	case 7: //Abteilungsleiter
		printf("ABTEILUNGSLEITER waehlen\n");
		for (i = 0; i < counter_ma; i++)
			if (ma[i].abteilung == -2)
			{
				printf("(%i)\n", counter + 1);
				show_ma(ma, i, ab, pos);
				abteilung_a[counter] = ma[i].id;
				counter++;
			}
		abteilung_a[counter + 1] = -1;
		do
		{
			printf("Bitte waehlen Sie: ");
			scanf("%i", &leiter);
		} while (leiter > counter + 1);
		ab[pos].abteilungsleiter = abteilung_a[leiter - 1];
//*/
		break;
	default:
		break;
	}
}

/*
# show_ab: Zeigt eine Abteilung an
#
# IN:		int_counter_ma: Anzahl von Mitarbeiterdatensätzen
#			int pos: Position im Abteilungsdatensatz
#
# IN/OUT	mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilung-Array
*/
void show_ab(ABTEILUNG *ab, mitarbeiter *ma, int pos, int counter_ma)
{
	int i = 0;
	int erfolg = 0;

	//Ausgabe aller Variablen an der Stelle pos im Array
	printf("ID: %i\n", ab[pos].id);
	printf("%s\n", ab[pos].name);
	printf("%s %i\n", ab[pos].adresse.strasse, ab[pos].adresse.hausnr);
	printf("%s %s\n", ab[pos].adresse.plz_test, ab[pos].adresse.ort);
	printf("Standort: %s\n", ab[pos].standort);

	do //Mitarbeiter-Array durchgehen, bis Mitarbeiter gefunden wurde oder das komplette Array durchsucht wurde
	{
		if (ma[i].id == ab[pos].abteilungsleiter) //Abteilungsleiter anhand der ID ermitteln
		{
			
			printf("Abteilungsleiter: %s %s\n", ma[i].vname, ma[i].name);
			printf("Telefon: %s\n", ma[i].kontakt.telefon.festnetz);
			printf("Email: %s.%s@daddeldu.com", ma[i].vname, ma[i].name);
			erfolg = 1;
		}
		i++;
	} while (i < counter_ma && erfolg != 1);
	printf("\n");
}

/*
# show_all_ab: Zeigt alle Abteilungen an
#
# IN:		int_counter_ma: Anzahl von Mitarbeiterdatensätzen
#
# IN/OUT	mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilung-Array
#			int *counter_ab: Zeiger auf Anzahl Abteilungen
*/
void show_all_ab(ABTEILUNG *ab, mitarbeiter *ma, int *counter_ab, int counter_ma)
{
	int i, zeichen_int;
	char zeichen;

	for (i = 0; i < *counter_ab; i++) //Von 0 bis Ende Array alle Abteilungen ausgeben
	{
		show_ab(ab, ma, i, counter_ma);
		printf("\n");
	}
	printf("Was wollen Sie tun?\n(B)earbeiten\n(Z)urueck\nBitte waehlen Sie: "); //Auswahl, was damit passieren soll
	scanf("%c", &zeichen);
	zeichen = toupper(zeichen); //Zeichen in großes Zeichen umwandeln
	getchar();
	if (zeichen == 'B') //Bearbeiten
	{
		printf("Abteilungs-ID: "); //Abfrage der Abteilungs-ID
		scanf("%i", &zeichen_int);
		getchar();
		system("cls");
		i = get_ab_pos(zeichen_int, ab, *counter_ab); //Position der Abteilung ermitteln
		if (i >= 0)
		{
			switch (zeichen)
			{
			case 'B':
				edit_ab(ma, ab, i, counter_ma, *counter_ab); //Bearbeiten
				break;
			default:
				break;
			}
		}
		else //Bei falscher ID eingabe
		{
			printf("Es wurde kein Datensatz mit dieser ID gefunden");
			getchar();
		}

	}
}

/*
# new_ab: Erzeugt einen neuen Abteilungdatensatz
#
# IN:		int_counter_ma: Anzahl von Mitarbeiterdatensätzen
#
# IN/OUT	mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilung-Array
#			int *pos: Zeiger auf Position im Abteilungs-Array; wird nach erfolgreichem anlegen um 1 erhöht
*/
void new_ab(ABTEILUNG *ab, mitarbeiter *ma, int *pos, int counter_ma)
{
	int i, counter = 0, leiter;
	int abteilung_a[MAX_MA];
	EINGABE eingabe;

	//ID
	if (*pos < MAX_AB) //Wenn nicht alle Plätze im Array belegt sind
	{
		do //Solage Eingabe der ID bis eine gültige ID eingegeben wurde
		{
			printf("ID: ");
		} while (set_ab_id(ab, *pos, *pos));
		getchar();

		//Abteilungsname
		eingabe = set_string("Abteilungsname");
		strcpy(ab[*pos].name, eingabe.eingabe);
		
		//##### Adresse ######

		//Strasse
		eingabe = set_string("Strasse");
		strcpy(ab[*pos].adresse.strasse, eingabe.eingabe);
		
		//Hausnummer
		do 
		{
			printf("Hausnummer: ");
		} while (set_ab_hausnr(ab, *pos));
		getchar();

		//PLZ
		eingabe = set_string("PLZ");
		strcpy(ab[*pos].adresse.plz_test, eingabe.eingabe);
		
		//Ort
		eingabe = set_string("Ort");
		strcpy(ab[*pos].adresse.ort, eingabe.eingabe);
		
		//Standort
		eingabe = set_string("Standort");
		strcpy(ab[*pos].standort, eingabe.eingabe);
		
		//Abteilungsleiter
		printf("ABTEILUNGSLEITER waehlen\n");
		for (i = 0; i < counter_ma; i++) //Alle Mitarbeiter ausgeben, die bei Abteilung -2 stehen haben
			if (ma[i].abteilung == -2)
			{
				printf("(%i) ", counter + 1);
				printf("%s %s\n", ma[i].vname, ma[i].name);
				abteilung_a[counter] = ma[i].id; //Speichern der Mitarbeiter-ID im Array
				counter++;
			}
		abteilung_a[counter + 1] = -1;
		do //Abfrage Mitarbeiter, bis eine gültige Nummer ausgewählt wurde
		{
			printf("Bitte waehlen Sie: "); 
			scanf("%i", &leiter);
		} while (leiter > counter + 1);
		ab[*pos].abteilungsleiter = abteilung_a[leiter - 1];
		*pos = *pos + 1;
		getchar();
	}
	else
		printf("Die maximale Anzahl an Abteilungen ist erreicht!");
}

/*
# create_files: Erzeugt die Dateien für Mitarbeiter- und Abteilungsdatensätze.
*/
void create_files()
{
	FILE *f_ab, *f_ma;

	f_ab = fopen(FILE_AB, "wb"); //Dateien zum schreiben binär öffnen
	f_ma = fopen(FILE_MA, "wb");
	fcloseall(); //alle Dateien schließen
}

/*
# drop_ma: Löscht einen Mitarbeiteratensatz
#
# IN:		int pos: Positon im Mitarbeiter-Array
#
# IN/OUT	mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			int *counter_ab: Zeiger auf Anzahl Mitarbeiter; wird bei erfolgreichem Löschen um 1 reduziert
*/
void drop_ma(mitarbeiter *ma, int pos, int *counter_ma)
{
	if (pos != *counter_ma-1) //nicht letzter oder einziger
		ma[pos] = ma[*counter_ma - 1];
	*counter_ma = *counter_ma - 1;
}

/*
# show_ab_name: Ermittelt die Position der Abteilung im Array anhand der ID
#
# IN:		int counter_ab: Anzahl von Abteilungsdatensätzen
#			int id: Abteilungs-ID
#
# IN/OUT	ABTEILUNG *ab: Zeiger auf Abteilung-Array
#
# RETURN	Position im Array
*/
int show_ab_name(ABTEILUNG *ab, int counter_ab, int id) //RETURN POSITION ABTEILUNG IN ARRAY
{
	int i = 0, kontrolle = 0;

	do //Solange bis alle Abteilungen durchsucht wurden oder die Entsprechende Abteilung gefunden wurde
	{
		if (id == ab[i].id)
			kontrolle = 1;
		i++;
	} while (i < counter_ab && kontrolle == 1);
	if (kontrolle == 1)
		return i--; //Rückgabe der Position um Array
	else
		return -1;
}

/*
# edit_ma: Bearbeiten von Mitarbeitern
#
# IN:		int counter_ma: Anzahl von Mitarbeiter-Datensätzen
#			int counter_ab: Anzahl von Mitarbeiter-Datensätzen
#
# IN/OUT	mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilungs-Array
#			int *pos: Zeiger auf die Position des zu verändernden Datensatzes
*/
void edit_ma(mitarbeiter *ma, ABTEILUNG *ab, int pos, int counter_ma, int counter_ab)
{
	int i, nr, kontrolle, test = 0, zahl;
	int abteilung_array[MAX_AB];
	int abteilung_r;
	EINGABE eingabe;

	//Ausgabe aller Informationen des Mitarbeiters an Stelle pos
	printf("(1)ID: %i\n", ma[pos].id);
	printf("(2)Vorname: %s\n(3)Nachname: %s\n", ma[pos].vname, ma[pos].name);
	printf("(4)Strasse: %s\n(5)Hausnr.: %i\n", ma[pos].kontakt.adresse.strasse, ma[pos].kontakt.adresse.hausnr);
	printf("(6)PLZ: %s\n(7)Ort: %s\n", ma[pos].kontakt.adresse.plz_test, ma[pos].kontakt.adresse.ort);
	printf("(8)Telefon: %s\n", ma[pos].kontakt.telefon.festnetz);
	printf("(9)Mobil: %s\n", ma[pos].kontakt.telefon.mobil);
	printf("(10)Eintrittmonat: %i\n(11) Eintrittsjahr: %i\n", ma[pos].eintritt.monat, ma[pos].eintritt.jahr);
	//printf("(12)Abteilung: %i\n\n", ma[pos].abteilung);
	//!!!!!!!!!!!!!!
	printf("(12)Abteilung: ");
	if (ma[pos].abteilung == -1)
		printf("Keine Abteilung zugewiesen\n");
	else if (ma[pos].abteilung == -2)
		printf("Kann Abteilungsleiter sein\n");
	else
		printf("%s\n\n", ab[get_ab_pos(ma[pos].abteilung, ab, counter_ab)].name); //Suchen der Abteilung anhand der Abteilungs-ID und anschließender Ausgabe	
	//printf("\n\n");
	printf("Welche Information wollen Sie aendern?");
	scanf("%i", &nr); //Abfrage, welche Information geändert werden soll
	switch (nr)
	{
	case 1: //ID
		do
		{
			printf("ID: (%i): ", ma[pos].id);
		} while (set_ma_id(ma, pos, counter_ma));
		break;
	case 2: //Vorname
		printf("Vorname (%s): ", ma[pos].vname);
		eingabe = set_string_edit();
		strcpy(ma[pos].vname, eingabe.eingabe);
		break;
	case 3: //Nachname
		printf("Name (%s): ", ma[pos].name);
		eingabe = set_string_edit();
		strcpy(ma[pos].name, eingabe.eingabe);
		break;
	case 4://Strasse
		printf("Strasse (%s): ", ma[pos].kontakt.adresse.strasse);
		eingabe = set_string_edit();
		strcpy(ma[pos].kontakt.adresse.strasse, eingabe.eingabe);
		break;
	case 5: //Hausnummer
		do
		{
			printf("Hausnr. (%i): ", ma[pos].kontakt.adresse.hausnr);
		} while (set_ma_hausnr(ma, pos));
		break;
	case 6: //PLZ
		printf("PLZ (%s): ", ma[pos].kontakt.adresse.plz_test);
		eingabe = set_string_edit();
		strcpy(ma[pos].kontakt.adresse.plz_test, eingabe.eingabe);
		break;
	case 7: //Ort
		printf("Ort (%s): ", ma[pos].kontakt.adresse.ort);
		eingabe = set_string_edit();
		strcpy(ma[pos].kontakt.adresse.ort, eingabe.eingabe);
		break;
	case 8: //Festnetz
		printf("Telefon (%s): ", ma[pos].kontakt.telefon.festnetz);
		eingabe = set_string_edit();
		strcpy(ma[pos].kontakt.telefon.festnetz, eingabe.eingabe);
		break;
	case 9: //Mobil
		printf("Mobil (%s): ", ma[pos].kontakt.telefon.mobil);
		eingabe = set_string_edit();
		strcpy(ma[pos].kontakt.telefon.mobil, eingabe.eingabe);
		break;
	case 10: //Eintrittsmonat
		do
		{
			printf("Eintrittmonat (%i): ", ma[pos].eintritt.monat);
		} while (set_ma_eintrittsmonat(ma, pos));
		break;
	case 11: //Eintrittsjahr
		do
		{
			printf("Eintrittsjahr (%i): ", ma[pos].eintritt.jahr);
		} while (set_ma_eintrittsjahr(ma, pos));
		break;
	case 12:
		printf("Abteilung ", ma[pos].abteilung);

		if (ma[pos].abteilung == -1)
			printf("(Keine Abteilung zugewiesen): ");
		else if (ma[pos].abteilung == -2)
			printf("(Kann Abteilungsleiter sein): ");
		else
			printf("(%s): ", ab[get_ab_pos(ma[pos].abteilung, ab, counter_ab)].name); //Suchen der Abteilung anhand der Abteilungs-ID und anschließender Ausgabe	


		i = 0;
		if (counter_ab > 0) //Mehr als 0 Abteilungen
		{
			for (i = 1; i <= counter_ab; i++) //Alle Abteilungen auslesen
			{
				printf("\n(%i)\t %s", i, ab[i-1].name); //Abteilungsname ausgeben
				abteilung_array[i] = ab[i-1].id; //Abteilung-ID in Array schreiben
			}
		}
		printf("\n(%i)\tWird Abteilungsleiter\n", i + 1); //Ausgabe Wird Abteilungsleiter ausgeben
		abteilung_array[i + 1] = -2;
		printf("(%i)\tKeine Abteilung zuweisen\n", i + 2); //Ausgabe "Keine Abteilung zuweisen" ausgeben
		abteilung_array[i + 2] = -1;


		do //Solange bis eine Zahl die kleiner als Anzahl von Abteilungen +2 ist
		{
			printf("Bitte waehlen Sie: ");
			scanf("%i", &abteilung_r);
		} while (abteilung_r > i + 2);
		ma[pos].abteilung = abteilung_array[abteilung_r];
		
		//getchar();
		break;
	default:
		break;
	}
}

/*
# show_all_ma: Zeigt alle Mitarbeiter an
#
# IN:		int_counter_ab: Anzahl von Abteilungsdatensätzen
#
# IN/OUT	mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilung-Array
#			int *counter_ma: Zeiger auf Anzahl Mitarbeiter
*/
void show_all_ma(mitarbeiter *ma, int *counter_ma, ABTEILUNG *ab, int counter_ab)
{
	char zeichen;
	int zeichen_int, i;

	for (i = 0; i < *counter_ma; i++) //Alle Mitarbeiter Ausgeben
	{
		show_ma(ma, i, ab, counter_ab);
		printf("\n");
	}
	printf("Was wollen Sie tun?\n(B)earbeiten\n(L)oeschen\n(Z)urueck\nBitte waehlen Sie: "); //Auswahl, was soll damit gemacht werden
	scanf("%c", &zeichen);
	zeichen = toupper(zeichen); //Zeichen in Grooßbuchstaben umwandeln
	
	if (zeichen == 'B' || zeichen == 'L') //B = Bearbeiten; L = Löschen
	{
		printf("Mitarbeiter-ID: "); //Abfrage, welcher Datensatz soll bearbeitet werden
		scanf("%i", &zeichen_int);
		getchar();
		system("cls");
		i = get_ma_pos(zeichen_int, ma, *counter_ma); //Position im Array ermitteln
		if (i >= 0)
		{
			switch (zeichen)
			{
			case 'B':
				edit_ma(ma, ab, i, *counter_ma, counter_ab);

				break;
			case 'L':
				drop_ma(ma, i, counter_ma);
				break;
			default:
				break;
			}
		}
		else
			printf("Ein Datensatz mit dieser ID: %i existiert nicht", zeichen_int);
		getchar();
	}

}