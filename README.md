# TimeLog

Ein kleines Windows-Tool für die persönliche Zeiterfassung. In den 
90ern entstanden und mein erstes selbstgeschriebenes C++/MFC-Programm.

## Bauen

Ein aktuelles Visual Studio mit C++/MFC Tooling wird zum Bauen gebraucht.

## Bedienungsanleitung

### Installation

Das Programm ist für mobile Installation ausgelegt. Es gibt keinen 
Installer. TimeLog.exe kann also einfach auf einen USB-Stick oder 
in das eigene Userverzeichnis gespeichert werden. Gespeichert wird 
in die Datei TimeLog.txt im selben verzeichnis. Soll ein anderes 
Verzeichnis benutzt werden als das, in dem sich die Exe befindet, 
kann in der Datei TimeLog.ini mit einem Editor unter der Sektion 
[TimeLog] die Zeile "LogFile=C:\Users\ich\Nextcloud\TimeLog.txt" 
(als Beispiel) eingetragen werden.

### Einleitung

Das Programm Timelog dient einzig und allein dem Zweck, eine möglichst
einfache zeitliche Erfassung von Tätigkeiten zu unterstützen. In erster
Linie ist es für Personen entwickelt, die freiberuflich arbeiten und
ihre Tätigkeiten (z.B. bei der Rechnungserstellung) nachweisen müssen.

### Handhabe

TimeLog.exe läuft stand-alone, benötigt also keine DLLs. Es wird jedoch
im Arbeitsverzeichnis eine Datei TimeLog.txt erstellt, die die Daten
enthält. Das Format wurde bewußt als ASCII gewählt, um den einfachsten
Export (z.B. in Textverarbeitungen oder Fakturierprogramme) zu ermög-
lichen. Es ist sinnvoll, eine Verknüpfung in der Autostart-Gruppe zu
erstellen, damit das Programm gleich beim Start des Systems die 
Anfangszeit registriert.

### Bedienung

TimeLog minimiert sich beim Schließen des Fensters in den Systembereich 
der Task-Leiste rechts unten, damit es schnell durch Doppelklicken erreichbar ist.

Nach jeder abgeschlossenen Tätigkeit gib eine kurze Beschreibung in 
das dafür vorgesehene Feld der Eingabemaske ein und drücke OK. Wenn Du
das Feld Bis-Uhrzeit leer lässt, wird die aktuelle Zeit automatisch 
eingetragen. Außerdem ist es möglich, im Feld 'Kürzel' unterschiedliche
Buchstaben einzutragen, falls für mehr als einen Auftraggeber
abgerechnet werden soll. Nach OK erscheint die eingegebene Tätigkeit 
inkl. Zeitangaben in der Liste. Du kannst in der Liste
Zwischenablage-Funktionen durchführen: Wenn Du einen Teil der Liste
selektierst, erscheint die Gesamtzeit für die selektierten Tätig-
keiten hinter 'Selektiert' am unteren Rand des Dialogfensters. Dort
steht auch hinter 'Gesamt' die gesamte Arbeitszeit der Liste.
Mit der rechten Maustaste in der Liste und 'Kopieren' können jetzt 
Teile der aufbereiteten Liste zeilenweise in eine Textverarbeitung oder 
Faktura kopiert werden.

### Aufteilung Mandanten / Projekte / Kostenstellen

Durch das Feld 'Kürzel' kann eine Kodierung der Zeiteinträge nach Kunden 
bzw. Projekten udgl. erfolgen. Gültig sind alle Großbuchstaben. Durch 
Anklicken der Check-Box (rechts neben dem Kürzel-Eingabefeld) kann ein 
Kürzel-Eingabezwang aktiviert werden, so dass die Eingabe des entspr. 
Kunden-Kürzels nicht vergessen werden kann. Um die erfassten Zeiten pro 
Kürzel innerhalb einer Selektion herauszufiltern, muß einfach das ge-
wünschte Kürzel in das Feld rechts von 'Selektiert' eingegeben werden. 
Sofort erscheint die für dieses Kürzel erfaßte Zeit bei 'Selektiert'. 
Ist kein Kürzel eingetragen, wird bei 'Selektiert' die Gesamtzeit der 
Selektion, also aller Kürzel, angezeigt.

### Statistiken

Unter dem Knopf 'Statistiken...' liegt eine Funktionalität, um die 
erfassten Zeiten nach Wochen und Monaten graphisch darzustellen. Es 
werden jeweils die Gesamtzeit (schwarz) und die Zeiten pro Kürzel 
(farbig) dargestellt.

## Lizenz

GNU GPL v3.0