typedef struct
{
	int monat;
	int jahr;
} EINTRITT;

typedef struct
{
	char plz_test[6];
	char strasse[20];
	int hausnr;
	char ort[30];
} ADRESSE;

typedef struct
{
	char mobil[20];
	char festnetz[20];
} TELEFON;

typedef struct
{
	ADRESSE adresse;
	TELEFON telefon;
	//char mail[54]; //14+vname, name
} KONTAKT;

typedef struct
{
	char eingabe[30];
} EINGABE;

typedef struct
{
	int id;
	char vname[20];
	char name[20];
	EINTRITT eintritt;
	KONTAKT kontakt;
	int abteilung; //-1: Keine Abteilung zugewiesen; -2: Kann Abteilungsleiter sein
}mitarbeiter;

typedef struct
{
	int id;
	char name[20];
	ADRESSE adresse;
	char standort[10];
	int abteilungsleiter;
} ABTEILUNG;

/*
# menu: Ausgabe des Hauptmenüs
#
# IN:	int counter_ma: Anzahl Mitarbeiter
#		int counter_ab: Anzahl Abteilungen
*/
extern void menu(int counter_ma, int counter_ab);

/*
# save_all: Speichern aller Datensätze in die Dateien, die in der Datei konstante.h unter FILE_MA und FILE_AB hinterlegt sind
#
# IN:	int counter_ma: Anzahl Mitarbeiter
#		int counter_ab: Anzahl Abteilungen
#
# IN/OUT mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#		 ABTEILUNG *ab: Zeiger auf Abteilung-Array
*/
extern void save_all(mitarbeiter *ma, ABTEILUNG *ab, int counter_ma, int counter_ab);

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
extern void new_ma(mitarbeiter *ma, int *pos, ABTEILUNG *ab, int counter_ab);

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
extern int load_all(mitarbeiter *ma, ABTEILUNG *ab, int *counter_ma, int *counter_ab);

/*
# show_ma: Anzeigen eines Mitarbeiter
#
# IN:		int pos: Position im Mitarbeiter Array
#			int_counter_ab: Anzahl von Abteilungsdatensätzen
#
# IN/OUT	mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilung-Array
*/
extern void show_ma(mitarbeiter *ma, int pos, ABTEILUNG *ab, int counter_ab);

/*
# show_all_ma: Zeigt alle Mitarbeiter an
#
# IN:		int_counter_ab: Anzahl von Abteilungsdatensätzen
#
# IN/OUT	mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilung-Array
#			int *counter_ma: Zeiger auf Anzahl Mitarbeiter
*/
extern void show_all_ma(mitarbeiter *ma, int *counter_ma, ABTEILUNG *ab, int counter_ab);

/*
# show_ab: Zeigt eine Abteilung an
#
# IN:		int_counter_ma: Anzahl von Mitarbeiterdatensätzen
#			int pos: Position im Abteilungsdatensatz
#
# IN/OUT	mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilung-Array
*/
extern void show_ab(ABTEILUNG *ab, mitarbeiter *ma, int pos, int counter_ma);

/*
# show_all_ab: Zeigt alle Abteilungen an
#
# IN:		int_counter_ma: Anzahl von Mitarbeiterdatensätzen
#
# IN/OUT	mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilung-Array
#			int *counter_ab: Zeiger auf Anzahl Abteilungen
*/
extern void show_all_ab(ABTEILUNG *ab, mitarbeiter *ma, int *counter_ab, int counter_ma);

/*
# new_ab: Erzeugt einen neuen Abteilungdatensatz
#
# IN:		int_counter_ma: Anzahl von Mitarbeiterdatensätzen
#
# IN/OUT	mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilung-Array
#			int *pos: Zeiger auf Position im Abteilungs-Array; wird nach erfolgreichem anlegen um 1 erhöht
*/
extern void new_ab(ABTEILUNG *ab, mitarbeiter *ma, int *pos, int counter_ma);

/*
# create_files: Erzeugt die Dateien für Mitarbeiter- und Abteilungsdatensätze. 
*/
extern void create_files();

/*
# menu_suchen: Zeigt das Suchenmenü an
#
# RETURN: Gibt zurück, wonach gesucht werden soll
*/
extern int menu_suchen();

/*
# drop_ma: Löscht einen Mitarbeiteratensatz
#
# IN:		int pos: Positon im Mitarbeiter-Array
#
# IN/OUT	mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			int *counter_ab: Zeiger auf Anzahl Mitarbeiter; wird bei erfolgreichem Löschen um 1 reduziert
*/
extern void drop_ma(mitarbeiter *ma, int pos, int *counter_ma);