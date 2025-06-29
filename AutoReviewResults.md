BEWERTUNG: 0

# Auswertung der Abgabe

- Status: Abgabe wurde bewertet
- Punkte: **0** von **100**

## Test 1

- Test: *Erforderliche Dateien sind vorhanden*
- Beschreibung: Das erforderliche Makefile muss vorhanden sein.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000041
##### Testschritte
- Makefile soll vorhanden sein: OK

## Test 2

- Test: *Makefile-Target autotest existiert*
- Beschreibung: Das Makefile besitzt ein Target zum kompilieren der Tests.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000272
##### Testschritte
- Inhalt von Makefile prüfen: OK

## Test 3

- Test: *tester.cpp-Datei ist unverändert*
- Beschreibung: Die Datei tester.cpp wurde nicht verändert und ist genau so wie im Original-Repository.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000156
##### Testschritte
- Hash-Test von tester.cpp auf ['bb698344ebab4b0dc10373ba34d09ded7fbdf01f']: OK

## Test 4

- Test: *Kompilieren der Tests*
- Beschreibung: Mit dem Befehl `make autotest` können die Tests kompiliert werden.
- Status: ausgeführt
- Erfolgreich: **Nein**
- Laufzeit: 0:00:02.806775
- Punkte: **0**
- Return-Code / Fehlercode: `2`
- Kommandozeile: `make autotest`
##### Testschritte
- Rückgabe-Code ist `0`: fehlgeschlagen

##### Ausgabe

```g++ -I. -I/usr/local/include -std=c++17 -Wall -Wextra -c network.cpp -o network.o
g++ -I. -I/usr/local/include -std=c++17 -Wall -Wextra -c csv.cpp -o csv.o
g++ -I. -I/usr/local/include -std=c++17 -Wall -Wextra -c scheduled_trip.cpp -o scheduled_trip.o
```

##### Fehlerausgabe

```scheduled_trip.cpp:49:17: error: no declaration matches 'const bht::StopTime* bht::NetworkScheduledTrip::iterator::operator->() const'
   49 | const StopTime* NetworkScheduledTrip::iterator::operator->() const {
      |                 ^~~~~~~~~~~~~~~~~~~~
In file included from scheduled_trip.cpp:1:
scheduled_trip.h:74:25: note: candidate is: 'const bht::StopTime* bht::NetworkScheduledTrip::iterator::operator->()'
   74 |         const StopTime* operator->();
      |                         ^~~~~~~~
scheduled_trip.h:35:11: note: 'class bht::NetworkScheduledTrip::iterator' defined here
   35 |     class iterator {
      |           ^~~~~~~~
make: *** [Makefile:19: scheduled_trip.o] Error 1
```

## Test 5

- Test: *Ausführbare Anwendung der Unit-Tests wurde erstellt*
- Beschreibung: Die Anwendung wird mit Unit-Tests kompiliert und erzeugt die geforderte Datei `/repo/test_runner`.
- Status: nicht ausgeführt
- Erfolgreich: **Nein**
##### Hinweise zur Behebung des Fehlers

Der Test wurde nicht ausgeführt, da vorherige Tests fehlgeschlagen sind. Beheben Sie die vorherigen Probleme und versuchen Sie es dann erneut.

## Test 6

- Test: *Ausführbare Anwendung der Unit-Tests enthält die Testfälle*
- Beschreibung: Die geforderte Datei `/repo/test_runner` enthält die `tester.cpp`-Datei.
- Status: nicht ausgeführt
- Erfolgreich: **Nein**
##### Hinweise zur Behebung des Fehlers

Der Test wurde nicht ausgeführt, da vorherige Tests fehlgeschlagen sind. Beheben Sie die vorherigen Probleme und versuchen Sie es dann erneut.

## Test 7

- Test: *Testfälle werden korrekt ausgeführt*
- Beschreibung: Die Unit-Tests der Anwendung werden korrekt ausgeführt (max. Laufzeit 60 Sekunden).
- Status: nicht ausgeführt
- Erfolgreich: **Nein**
- Punkte: **0**
##### Hinweise zur Behebung des Fehlers

Der Test wurde nicht ausgeführt, da vorherige Tests fehlgeschlagen sind. Beheben Sie die vorherigen Probleme und versuchen Sie es dann erneut.

