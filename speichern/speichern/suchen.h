/*
# search_ma_id: Suchen nach Mitarbeiter-ID
#
# IN:	int counter_ma: Anzahl Mitarbeiter
#		int counter_ab: Anzahl Abteilungen
#
# IN/OUT: mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilungsarray
*/
extern void search_ma_id(mitarbeiter *ma, int counter_ma, ABTEILUNG *ab, int counter_ab);

/*
# search_ma_vname: Suchen nach Mitarbeiter-Vorname
#
# IN:	int counter_ma: Anzahl Mitarbeiter
#		int counter_ab: Anzahl Abteilungen
#
# IN/OUT: mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilungsarray
*/
extern void search_ma_vname(mitarbeiter *ma, int counter_ma, ABTEILUNG *ab, int counter_ab);

/*
# search_ma_name: Suchen nach Mitarbeiter-Nachname
#
# IN:	int counter_ma: Anzahl Mitarbeiter
#		int counter_ab: Anzahl Abteilungen
#
# IN/OUT: mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilungsarray
*/
extern void search_ma_name(mitarbeiter *ma, int counter_ma, ABTEILUNG *ab, int counter_ab);

/*
# search_ab_name: Suchen nach Abteilungs-Name
#
# IN:	int counter_ma: Anzahl Mitarbeiter
#		int counter_ab: Anzahl Abteilungen
#
# IN/OUT: mitarbeiter *ma: Zeiger auf Mitarbeiter-Array
#			ABTEILUNG *ab: Zeiger auf Abteilungsarray
*/
extern void search_ab_name(mitarbeiter *ma, ABTEILUNG *ab, int counter_ma, int counter_ab);