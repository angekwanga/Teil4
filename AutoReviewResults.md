BEWERTUNG: 100

# Auswertung der Abgabe

- Status: Abgabe wurde bewertet
- Punkte: **100** von **100**

## Test 1

- Test: *Erforderliche Dateien sind vorhanden*
- Beschreibung: Das erforderliche Makefile muss vorhanden sein.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000037
##### Testschritte
- Makefile soll vorhanden sein: OK

## Test 2

- Test: *Makefile-Target autotest existiert*
- Beschreibung: Das Makefile besitzt ein Target zum kompilieren der Tests.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000263
##### Testschritte
- Inhalt von Makefile prüfen: OK

## Test 3

- Test: *tester.cpp-Datei ist unverändert*
- Beschreibung: Die Datei tester.cpp wurde nicht verändert und ist genau so wie im Original-Repository.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000190
##### Testschritte
- Hash-Test von tester.cpp auf ['bb698344ebab4b0dc10373ba34d09ded7fbdf01f']: OK

## Test 4

- Test: *Kompilieren der Tests*
- Beschreibung: Mit dem Befehl `make autotest` können die Tests kompiliert werden.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:46.102304
- Punkte: **1**
- Return-Code / Fehlercode: `0`
- Kommandozeile: `make autotest`
##### Testschritte
- Rückgabe-Code ist `0`: OK

##### Ausgabe

```g++ -I. -I/usr/local/include -std=c++17 -Wall -Wextra -c scheduled_trip.cpp -o scheduled_trip.o
g++ -I. -I/usr/local/include -std=c++17 -Wall -Wextra -o test_runner /usr/local/lib/libgtest_main.a /usr/local/lib/libgtest.a tester.cpp network.cpp csv.cpp scheduled_trip.cpp -lpthread
./test_runner
Running main() from /usr/src/googletest/googletest/src/gtest_main.cc
[==========] Running 5 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 5 tests from Network
[ RUN      ] Network.getStopsForTransfer
[       OK ] Network.getStopsForTransfer (7962 ms)
[ RUN      ] Network.getNeighbors
[       OK ] Network.getNeighbors (7986 ms)
[ RUN      ] Network.getTravelPath
[       OK ] Network.getTravelPath (9731 ms)
[ RUN      ] Network.getScheduledTrip
[       OK ] Network.getScheduledTrip (7892 ms)
[ RUN      ] Network.NetworkScheduledTrip_iterator
[       OK ] Network.NetworkScheduledTrip_iterator (7896 ms)
[----------] 5 tests from Network (41469 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (41469 ms total)
[  PASSED  ] 5 tests.
```

## Test 5

- Test: *Ausführbare Anwendung der Unit-Tests wurde erstellt*
- Beschreibung: Die Anwendung wird mit Unit-Tests kompiliert und erzeugt die geforderte Datei `/repo/test_runner`.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000046
##### Testschritte
- test_runner soll vorhanden sein: OK

## Test 6

- Test: *Ausführbare Anwendung der Unit-Tests enthält die Testfälle*
- Beschreibung: Die geforderte Datei `/repo/test_runner` enthält die `tester.cpp`-Datei.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.308397
- Return-Code / Fehlercode: `0`
- Kommandozeile: `readelf -s --wide /repo/test_runner`
##### Testschritte
- Ausgabe ist korrekt: OK
- Rückgabe-Code ist `0`: OK

##### Ausgabe

```<AUSGABE WIRD NICHT ANGEZEIGT>
```

## Test 7

- Test: *Testfälle werden korrekt ausgeführt*
- Beschreibung: Die Unit-Tests der Anwendung werden korrekt ausgeführt (max. Laufzeit 60 Sekunden).
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:41.964946
- Punkte: **99**
- Return-Code / Fehlercode: `0`
- Kommandozeile: `/repo/test_runner`
##### Testschritte
- Rückgabe-Code ist `0`: OK

##### Ausgabe

```Running main() from /usr/src/googletest/googletest/src/gtest_main.cc
[==========] Running 5 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 5 tests from Network
[ RUN      ] Network.getStopsForTransfer
[       OK ] Network.getStopsForTransfer (7967 ms)
[ RUN      ] Network.getNeighbors
[       OK ] Network.getNeighbors (8043 ms)
[ RUN      ] Network.getTravelPath
[       OK ] Network.getTravelPath (9774 ms)
[ RUN      ] Network.getScheduledTrip
[       OK ] Network.getScheduledTrip (7936 ms)
[ RUN      ] Network.NetworkScheduledTrip_iterator
[       OK ] Network.NetworkScheduledTrip_iterator (7939 ms)
[----------] 5 tests from Network (41661 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (41661 ms total)
[  PASSED  ] 5 tests.
```

