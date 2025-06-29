BEWERTUNG: 0

# Auswertung der Abgabe

- Status: Abgabe wurde bewertet
- Punkte: **0** von **100**

## Test 1

- Test: *Erforderliche Dateien sind vorhanden*
- Beschreibung: Das erforderliche Makefile muss vorhanden sein.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000023
##### Testschritte
- Makefile soll vorhanden sein: OK

## Test 2

- Test: *Makefile-Target autotest existiert*
- Beschreibung: Das Makefile besitzt ein Target zum kompilieren der Tests.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000166
##### Testschritte
- Inhalt von Makefile prüfen: OK

## Test 3

- Test: *tester.cpp-Datei ist unverändert*
- Beschreibung: Die Datei tester.cpp wurde nicht verändert und ist genau so wie im Original-Repository.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000102
##### Testschritte
- Hash-Test von tester.cpp auf ['bb698344ebab4b0dc10373ba34d09ded7fbdf01f']: OK

## Test 4

- Test: *Kompilieren der Tests*
- Beschreibung: Mit dem Befehl `make autotest` können die Tests kompiliert werden.
- Status: ausgeführt
- Erfolgreich: **Nein**
- Laufzeit: 0:00:01.061634
- Punkte: **0**
- Return-Code / Fehlercode: `2`
- Kommandozeile: `make autotest`
##### Testschritte
- Rückgabe-Code ist `0`: fehlgeschlagen

##### Ausgabe

```g++ -I. -I/usr/local/include -std=c++17 -Wall -Wextra -c network.cpp -o network.o
```

##### Fehlerausgabe

```network.cpp: In member function 'void bht::Network::readAgencies(std::string)':
network.cpp:277:8: error: 'CSVReader' is not a member of 'bht'; did you mean 'CSVReader'?
  277 |   bht::CSVReader reader{source};
      |        ^~~~~~~~~
In file included from network.cpp:2:
csv.h:9:7: note: 'CSVReader' declared here
    9 | class CSVReader {
      |       ^~~~~~~~~
network.cpp:279:22: error: 'reader' was not declared in this scope
  279 |     std::string id = reader.getField("agency_id");
      |                      ^~~~~~
network.cpp:291:12: error: 'reader' was not declared in this scope
  291 |   } while (reader.next());
      |            ^~~~~~
network.cpp:276:40: warning: unused parameter 'source' [-Wunused-parameter]
  276 | void Network::readAgencies(std::string source) {
      |                            ~~~~~~~~~~~~^~~~~~
network.cpp: In member function 'void bht::Network::readCalendarDates(std::string)':
network.cpp:295:8: error: 'CSVReader' is not a member of 'bht'; did you mean 'CSVReader'?
  295 |   bht::CSVReader reader(source);
      |        ^~~~~~~~~
csv.h:9:7: note: 'CSVReader' declared here
    9 | class CSVReader {
      |       ^~~~~~~~~
network.cpp:297:22: error: 'reader' was not declared in this scope
  297 |     std::string id = reader.getField("service_id");
      |                      ^~~~~~
network.cpp:306:12: error: 'reader' was not declared in this scope
  306 |   } while (reader.next());
      |            ^~~~~~
network.cpp:294:45: warning: unused parameter 'source' [-Wunused-parameter]
  294 | void Network::readCalendarDates(std::string source) {
      |                                 ~~~~~~~~~~~~^~~~~~
network.cpp: In member function 'void bht::Network::readCalendars(std::string)':
network.cpp:310:8: error: 'CSVReader' is not a member of 'bht'; did you mean 'CSVReader'?
  310 |   bht::CSVReader reader(source);
      |        ^~~~~~~~~
csv.h:9:7: note: 'CSVReader' declared here
    9 | class CSVReader {
      |       ^~~~~~~~~
network.cpp:312:22: error: 'reader' was not declared in this scope
  312 |     std::string id = reader.getField("service_id");
      |                      ^~~~~~
network.cpp:328:12: error: 'reader' was not declared in this scope
  328 |   } while (reader.next());
      |            ^~~~~~
network.cpp:309:41: warning: unused parameter 'source' [-Wunused-parameter]
  309 | void Network::readCalendars(std::string source) {
      |                             ~~~~~~~~~~~~^~~~~~
network.cpp: In member function 'void bht::Network::readLevels(std::string)':
network.cpp:332:8: error: 'CSVReader' is not a member of 'bht'; did you mean 'CSVReader'?
  332 |   bht::CSVReader reader(source);
      |        ^~~~~~~~~
csv.h:9:7: note: 'CSVReader' declared here
    9 | class CSVReader {
      |       ^~~~~~~~~
network.cpp:334:22: error: 'reader' was not declared in this scope
  334 |     std::string id = reader.getField("level_id");
      |                      ^~~~~~
network.cpp:343:12: error: 'reader' was not declared in this scope
  343 |   } while (reader.next());
      |            ^~~~~~
network.cpp:331:38: warning: unused parameter 'source' [-Wunused-parameter]
  331 | void Network::readLevels(std::string source) {
      |                          ~~~~~~~~~~~~^~~~~~
network.cpp: In member function 'void bht::Network::readPathways(std::string)':
network.cpp:347:8: error: 'CSVReader' is not a member of 'bht'; did you mean 'CSVReader'?
  347 |   bht::CSVReader reader(source);
      |        ^~~~~~~~~
csv.h:9:7: note: 'CSVReader' declared here
    9 | class CSVReader {
      |       ^~~~~~~~~
network.cpp:349:22: error: 'reader' was not declared in this scope
  349 |     std::string id = reader.getField("pathway_id");
      |                      ^~~~~~
network.cpp:366:12: error: 'reader' was not declared in this scope
  366 |   } while (reader.next());
      |            ^~~~~~
network.cpp:346:40: warning: unused parameter 'source' [-Wunused-parameter]
  346 | void Network::readPathways(std::string source) {
      |                            ~~~~~~~~~~~~^~~~~~
network.cpp: In member function 'void bht::Network::readRoutes(std::string)':
network.cpp:370:8: error: 'CSVReader' is not a member of 'bht'; did you mean 'CSVReader'?
  370 |   bht::CSVReader reader(source);
      |        ^~~~~~~~~
csv.h:9:7: note: 'CSVReader' declared here
    9 | class CSVReader {
      |       ^~~~~~~~~
network.cpp:372:22: error: 'reader' was not declared in this scope
  372 |     std::string id = reader.getField("route_id");
      |                      ^~~~~~
network.cpp:386:12: error: 'reader' was not declared in this scope
  386 |   } while (reader.next());
      |            ^~~~~~
network.cpp:369:38: warning: unused parameter 'source' [-Wunused-parameter]
  369 | void Network::readRoutes(std::string source) {
      |                          ~~~~~~~~~~~~^~~~~~
network.cpp: In member function 'void bht::Network::readShapes(std::string)':
network.cpp:390:8: error: 'CSVReader' is not a member of 'bht'; did you mean 'CSVReader'?
  390 |   bht::CSVReader reader(source);
      |        ^~~~~~~~~
csv.h:9:7: note: 'CSVReader' declared here
    9 | class CSVReader {
      |       ^~~~~~~~~
network.cpp:392:22: error: 'reader' was not declared in this scope
  392 |     std::string id = reader.getField("shape_id");
      |                      ^~~~~~
network.cpp:402:12: error: 'reader' was not declared in this scope
  402 |   } while (reader.next());
      |            ^~~~~~
network.cpp:389:38: warning: unused parameter 'source' [-Wunused-parameter]
  389 | void Network::readShapes(std::string source) {
      |                          ~~~~~~~~~~~~^~~~~~
network.cpp: In member function 'void bht::Network::readStopTimes(std::string)':
network.cpp:406:8: error: 'CSVReader' is not a member of 'bht'; did you mean 'CSVReader'?
  406 |   bht::CSVReader reader(source);
      |        ^~~~~~~~~
csv.h:9:7: note: 'CSVReader' declared here
    9 | class CSVReader {
      |       ^~~~~~~~~
network.cpp:408:22: error: 'reader' was not declared in this scope
  408 |     std::string id = reader.getField("trip_id");
      |                      ^~~~~~
network.cpp:427:12: error: 'reader' was not declared in this scope
  427 |   } while (reader.next());
      |            ^~~~~~
network.cpp:405:41: warning: unused parameter 'source' [-Wunused-parameter]
  405 | void Network::readStopTimes(std::string source) {
      |                             ~~~~~~~~~~~~^~~~~~
network.cpp: In member function 'void bht::Network::readStops(std::string)':
network.cpp:431:8: error: 'CSVReader' is not a member of 'bht'; did you mean 'CSVReader'?
  431 |   bht::CSVReader reader(source);
      |        ^~~~~~~~~
csv.h:9:7: note: 'CSVReader' declared here
    9 | class CSVReader {
      |       ^~~~~~~~~
network.cpp:433:22: error: 'reader' was not declared in this scope
  433 |     std::string id = reader.getField("stop_id");
      |                      ^~~~~~
network.cpp:458:12: error: 'reader' was not declared in this scope
  458 |   } while (reader.next());
      |            ^~~~~~
network.cpp:430:37: warning: unused parameter 'source' [-Wunused-parameter]
  430 | void Network::readStops(std::string source) {
      |                         ~~~~~~~~~~~~^~~~~~
network.cpp: In member function 'void bht::Network::readTransfers(std::string)':
network.cpp:462:8: error: 'CSVReader' is not a member of 'bht'; did you mean 'CSVReader'?
  462 |   bht::CSVReader reader(source);
      |        ^~~~~~~~~
csv.h:9:7: note: 'CSVReader' declared here
    9 | class CSVReader {
      |       ^~~~~~~~~
network.cpp:464:22: error: 'reader' was not declared in this scope
  464 |     std::string id = reader.getField("from_stop_id");
      |                      ^~~~~~
network.cpp:478:12: error: 'reader' was not declared in this scope
  478 |   } while (reader.next());
      |            ^~~~~~
network.cpp:461:41: warning: unused parameter 'source' [-Wunused-parameter]
  461 | void Network::readTransfers(std::string source) {
      |                             ~~~~~~~~~~~~^~~~~~
network.cpp: In member function 'void bht::Network::readTrips(std::string)':
network.cpp:482:8: error: 'CSVReader' is not a member of 'bht'; did you mean 'CSVReader'?
  482 |   bht::CSVReader reader(source);
      |        ^~~~~~~~~
csv.h:9:7: note: 'CSVReader' declared here
    9 | class CSVReader {
      |       ^~~~~~~~~
network.cpp:484:22: error: 'reader' was not declared in this scope
  484 |     std::string id = reader.getField("trip_id");
      |                      ^~~~~~
network.cpp:500:12: error: 'reader' was not declared in this scope
  500 |   } while (reader.next());
      |            ^~~~~~
network.cpp:481:37: warning: unused parameter 'source' [-Wunused-parameter]
  481 | void Network::readTrips(std::string source) {
      |                         ~~~~~~~~~~~~^~~~~~
make: *** [Makefile:19: network.o] Error 1
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

