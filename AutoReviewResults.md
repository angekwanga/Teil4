BEWERTUNG: 0

# Auswertung der Abgabe

- Status: Abgabe wurde bewertet
- Punkte: **0** von **100**

## Test 1

- Test: *Erforderliche Dateien sind vorhanden*
- Beschreibung: Das erforderliche Makefile muss vorhanden sein.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000042
##### Testschritte
- Makefile soll vorhanden sein: OK

## Test 2

- Test: *Makefile-Target autotest existiert*
- Beschreibung: Das Makefile besitzt ein Target zum kompilieren der Tests.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000234
##### Testschritte
- Inhalt von Makefile prüfen: OK

## Test 3

- Test: *tester.cpp-Datei ist unverändert*
- Beschreibung: Die Datei tester.cpp wurde nicht verändert und ist genau so wie im Original-Repository.
- Status: ausgeführt
- Erfolgreich: **Ja**
- Laufzeit: 0:00:00.000172
##### Testschritte
- Hash-Test von tester.cpp auf ['bb698344ebab4b0dc10373ba34d09ded7fbdf01f']: OK

## Test 4

- Test: *Kompilieren der Tests*
- Beschreibung: Mit dem Befehl `make autotest` können die Tests kompiliert werden.
- Status: ausgeführt
- Erfolgreich: **Nein**
- Laufzeit: 0:00:03.240821
- Punkte: **0**
- Return-Code / Fehlercode: `2`
- Kommandozeile: `make autotest`
##### Testschritte
- Rückgabe-Code ist `0`: fehlgeschlagen

##### Ausgabe

```g++ -I. -I/usr/local/include -std=c++17 -o test_runner /usr/local/lib/libgtest_main.a /usr/local/lib/libgtest.a tester.cpp csv.cpp network.cpp scheduled_trip.cpp
```

##### Fehlerausgabe

```In file included from /usr/local/include/gtest/gtest.h:67,
                 from tester.cpp:6:
tester.cpp: In member function 'virtual void {anonymous}::Network_NetworkScheduledTrip_iterator_Test::TestBody()':
tester.cpp:148:26: error: no matching function for call to 'distance(bht::NetworkScheduledTrip::iterator, bht::NetworkScheduledTrip::iterator)'
  148 |   EXPECT_EQ(std::distance(trip.begin(), trip.end()), 3) << "std::distance from begin() to end() should return the number of stops in the trip";
      |             ~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~
tester.cpp:148:26: note: there is 1 candidate
In file included from /usr/local/include/c++/15.1.0/bits/stl_algobase.h:66,
                 from /usr/local/include/c++/15.1.0/vector:64,
                 from tester.cpp:2:
/usr/local/include/c++/15.1.0/bits/stl_iterator_base_funcs.h:150:5: note: candidate 1: 'template<class _InputIterator> constexpr typename std::iterator_traits<_Iterator>::difference_type std::distance(_InputIterator, _InputIterator)'
  150 |     distance(_InputIterator __first, _InputIterator __last)
      |     ^~~~~~~~
/usr/local/include/c++/15.1.0/bits/stl_iterator_base_funcs.h:150:5: note: template argument deduction/substitution failed:
/usr/local/include/c++/15.1.0/bits/stl_iterator_base_funcs.h: In substitution of 'template<class _InputIterator> constexpr typename std::iterator_traits<_Iterator>::difference_type std::distance(_InputIterator, _InputIterator) [with _InputIterator = bht::NetworkScheduledTrip::iterator]':
tester.cpp:148:3:   required from here
  148 |   EXPECT_EQ(std::distance(trip.begin(), trip.end()), 3) << "std::distance from begin() to end() should return the number of stops in the trip";
      |             ~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~
/usr/local/include/c++/15.1.0/bits/stl_iterator_base_funcs.h:150:5: error: no type named 'difference_type' in 'struct std::iterator_traits<bht::NetworkScheduledTrip::iterator>'
  150 |     distance(_InputIterator __first, _InputIterator __last)
      |     ^~~~~~~~
scheduled_trip.cpp: In member function 'unsigned int bht::NetworkScheduledTrip::iterator::getStopSequence() const':
scheduled_trip.cpp:73:16: error: 'UINT_MAX' was not declared in this scope
   73 |         return UINT_MAX;
      |                ^~~~~~~~
scheduled_trip.cpp:2:1: note: 'UINT_MAX' is defined in header '<climits>'; this is probably fixable by adding '#include <climits>'
    1 | #include "scheduled_trip.h"
  +++ |+#include <climits>
    2 | #include <stdexcept>
make: *** [Makefile:2: autotest] Error 1
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

