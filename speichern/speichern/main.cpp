#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <Windows.h>
#include "funktionen.h"
#include "konstante.h"
#include "suchen.h"

void main()
{
	mitarbeiter ma[MAX_MA];
	ABTEILUNG ab[MAX_AB];
	int counter_ma = 0;
	int counter_ab = 0;
	char eingabe;
	int error;

	error = load_all(ma, ab, &counter_ma, &counter_ab); //Alle Daten aus Dateien holen
	do
	{
		if (error) //Wenn Dateien gefunden wurden
		{
			system("cls");
			menu(counter_ma, counter_ab); //Ausgabe Menü
			eingabe = getche(); //Abfrage, was gemacht werden soll
			eingabe = toupper(eingabe);

			switch (eingabe)
			{
			case '1' /*Neuer Mitarbeiter*/:
				system("cls");
				new_ma(ma, &counter_ma, ab, counter_ab);
				break;
			case '2' /*Neue Abteilung*/:
				system("cls");
				new_ab(ab, ma, &counter_ab, counter_ma);
				break;
			case '3': /* Zeigen alle Mitarbeiter */
				system("cls");
				show_all_ma(ma, &counter_ma, ab, counter_ab);
				break;
			case '4': /* Zeige alle Abteilungen */
				system("cls");
				show_all_ab(ab, ma, &counter_ab, counter_ma);
				break;
			case '5': /* Suchen */
				system("cls");
				switch (menu_suchen()) //Menü suchen ausgeben
				{
				case 1:/* Mitarbeiter-Id */
					system("cls");
					search_ma_id(ma, counter_ma, ab, counter_ab);
					break;
				case 2:/* Vorname */
					search_ma_vname(ma, counter_ma, ab, counter_ab);
					break;
				case 3:/* Nachname */
					search_ma_name(ma, counter_ma, ab, counter_ab);
					break;
				case 4:/* Abteilungsname */
					search_ab_name(ma, ab, counter_ma, counter_ab);
					break;
				default:
					break;
				}
				break;
			case '6': /* Speichern */
				system("cls");
				save_all(ma, ab, counter_ma, counter_ab); //Alle Daten speichern
				break;
			default:
				if (eingabe != 'X') //Wenn nicht "X" gedrückt wurde
					printf("ERROR");
				break;
			}
		}
		else //Dateien erstellen???
		{
			printf("Eine der Dateien konnte nicht gefunden werden.\n Soll die fehlende Datei erstellt werden? [J/n]");
			eingabe = toupper(getche());
			printf("%c", eingabe);
			if (eingabe == 'N')
			{
				printf("\nDas Programm wird geschlossen");
				eingabe = 'X';
			}
			else
			{
				printf("\nDie Dateien werden angelegt");
				create_files();
				error = 1;
			}
			getchar();
			system("cls");
		}
	} while (eingabe != 'X'); //Solange das Program laufen lassen, bis "X" gedrückt wurde
}