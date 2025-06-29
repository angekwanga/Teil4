#pragma once

#include "types.h"
#include "csv.h"
#include "scheduled_trip.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

namespace bht {

class Network {
public:
    // Constructors
    Network(const std::string& gtfsDirectory);
    
    // Data containers (public pour les tests)
    std::unordered_map<std::string, Stop> stops;
    std::unordered_map<std::string, Route> routes;
    std::unordered_map<std::string, Trip> trips;
    std::vector<StopTime> stopTimes;
    std::unordered_map<std::string, Agency> agencies;
    
    // Méthodes principales
    
    /**
     * Retourne tous les arrêts pour un transfert (station + tous ses quais)
     * Fonctionne avec l'ID d'une station ou l'ID d'un quai
     */
    std::vector<Stop> getStopsForTransfer(const std::string& stopId);
    
    /**
     * Retourne tous les arrêts voisins accessibles depuis un arrêt donné
     * Inclut les connexions via les voyages et les transferts entre quais
     */
    std::unordered_set<std::string> getNeighbors(const std::string& stopId);
    
    /**
     * Calcule le chemin le plus court entre deux arrêts
     */
    std::vector<Stop> getTravelPath(const std::string& fromStopId, const std::string& toStopId);
    
    /**
     * Crée un objet NetworkScheduledTrip pour un voyage donné
     */
    NetworkScheduledTrip getScheduledTrip(const std::string& tripId) const;
    
    /**
     * Retourne un arrêt par son ID
     */
    const Stop& getStopById(const std::string& stopId) const;

private:
    // Méthodes privées d'aide
    void loadData(const std::string& gtfsDirectory);
    void loadStops(const std::string& filename);
    void loadRoutes(const std::string& filename);
    void loadTrips(const std::string& filename);
    void loadStopTimes(const std::string& filename);
    void loadAgencies(const std::string& filename);
    
    // Structures de données pour optimiser les recherches
    std::unordered_map<std::string, std::vector<std::string>> stationToStops; // station -> liste des quais
    std::unordered_map<std::string, std::string> stopToStation; // quai -> station parente
    std::unordered_map<std::string, std::vector<StopTime>> tripStopTimes; // trip_id -> stop_times triés
    std::unordered_map<std::string, std::unordered_set<std::string>> stopNeighbors; // cache des voisins
    
    void buildStationMappings();
    void buildTripStopTimes();
    void buildNeighborCache();
};

}