# Übung 4 - Objektorientierte Programmierung

## Structure du projet

```
Uebung04/
├── gtfsshort/              # Dossier avec les données GTFS (à ajouter)
│   ├── agency.txt
│   ├── calendar.txt
│   ├── calendar_dates.txt
│   ├── levels.txt
│   ├── pathways.txt
│   ├── routes.txt
│   ├── shapes.txt
│   ├── stop_times.txt
│   ├── stops.txt
│   ├── transfers.txt
│   └── trips.txt
├── config.h               # Configuration (chemin GTFS)
├── csv.h / csv.cpp        # Lecteur CSV
├── types.h                # Définitions des structures GTFS
├── network.h / network.cpp # Classe principale Network
├── scheduled_trip.h / scheduled_trip.cpp # Classe pour les trajets avec itérateurs
├── main.cpp               # Application console pour tester les itérateurs
├── main_qt.cpp            # Point d'entrée Qt (interface graphique)
├── mainwindow.h / mainwindow.cpp # Interface Qt
├── mainwindow.ui          # Interface utilisateur Qt
├── stoptimestablemodel.h / stoptimestablemodel.cpp # Modèle pour la table Qt
├── tester.cpp             # Tests automatiques (ne pas modifier)
├── localtest.cpp          # Tests locaux (ne pas modifier)
├── Makefile               # Build pour les tests
└── Uebung04.pro           # Projet Qt
```

## Compilation et tests

### Tests automatiques
```bash
make autotest
```

### Application console (test des itérateurs)
```bash
make main_app
./main_app ./gtfsshort
```

### Test de l'application console
```bash
make test_main
```

### Application Qt (interface graphique)
```bash
make qt-app
# ou directement:
qmake Uebung04.pro
make
./Uebung04
```

### Nettoyage
```bash
make clean
```

## Applications

### 1. Application console (`main.cpp`)
Cette application teste spécifiquement les itérateurs de `NetworkScheduledTrip` :
```cpp
bht::Network n{argv[1]};
bht::NetworkScheduledTrip trip = n.getScheduledTrip("230419258");
for (bht::NetworkScheduledTrip::iterator iter = trip.begin(); iter != trip.end(); iter++) {
  std::cout << iter->stopSequence << ": " << n.stops[iter->stopId].name << std::endl;
}
```

Sortie attendue :
```
0: S Erkner Bhf
1: S Wilhelmshagen (Berlin)
2: S Rahnsdorf (Berlin)
```

### 2. Application Qt (`main_qt.cpp`)
Interface graphique avec sélection de lignes, trajets et affichage des arrêts.

## Fonctionnalités implémentées

### Aufgabe a) - Bahnhöfe und Umstiege
- `getStopsForTransfer()` : Trouve tous les quais d'une station pour les transferts

### Aufgabe b) - Routen berechnen  
- `getNeighbors()` : Trouve les arrêts voisins connectés
- `getTravelPath()` : Calcule le chemin le plus court entre deux arrêts

### Aufgabe c) - Verwendung von Iteratoren
- `getScheduledTrip()` : Crée un objet NetworkScheduledTrip
- Itérateur bidirectionnel pour parcourir les arrêts d'un trajet

## Optimisations de performance

Le code utilise des structures de données optimisées pour accélérer les recherches :
- `stopTrips` : Mapping arrêt → trajets
- `tripStops` : Mapping trajet → arrêts  
- `tripStopTimes` : Mapping trajet → horaires
- `stopsForTransfer` : Mapping station → arrêts de transfert

## Notes importantes

- Le fichier `config.h` est configuré pour chercher les données GTFS dans `./gtfsshort`
- `main.cpp` : Version console pour tester les itérateurs (requis par l'exercice)
- `main_qt.cpp` : Version Qt pour l'interface graphique
- Assurez-vous d'ajouter le dossier `gtfsshort` avec tous les fichiers GTFS
- Les fichiers `tester.cpp`, `localtest.cpp`, `types.h`, et la structure de `scheduled_trip.h` ne doivent pas être modifiés
- La compilation nécessite C++17 et les bibliothèques Google Test pour les tests