#include "network.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <unordered_map>

namespace bht {

Network::Network(const std::string& gtfsDirectory) {
    loadData(gtfsDirectory);
    buildStationMappings();
    buildTripStopTimes();
    buildNeighborCache();
}

void Network::loadData(const std::string& gtfsDirectory) {
    loadStops(gtfsDirectory + "/stops.txt");
    loadRoutes(gtfsDirectory + "/routes.txt");
    loadTrips(gtfsDirectory + "/trips.txt");
    loadStopTimes(gtfsDirectory + "/stop_times.txt");
    loadAgencies(gtfsDirectory + "/agency.txt");
}

void Network::loadStops(const std::string& filename) {
    CSVReader reader(filename);
    auto data = reader.getData();
    
    for (size_t i = 1; i < data.size(); ++i) { // Skip header
        if (data[i].size() >= 9) {
            Stop stop;
            stop.id = data[i][0];
            stop.code = data[i][1];
            stop.name = data[i][2];
            stop.description = data[i][3];
            stop.latitide = std::stod(data[i][4]);
            stop.longitude = std::stod(data[i][5]);
            stop.locationType = static_cast<LocationType>(std::stoi(data[i][6]));
            stop.parentStation = data[i][7];
            stop.wheelchairBoarding = static_cast<WheelchairAccessibility>(std::stoi(data[i][8]));
            
            stops[stop.id] = stop;
        }
    }
}

void Network::loadRoutes(const std::string& filename) {
    CSVReader reader(filename);
    auto data = reader.getData();
    
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i].size() >= 6) {
            Route route;
            route.id = data[i][0];
            route.agencyId = data[i][1];
            route.shortName = data[i][2];
            route.longName = data[i][3];
            route.description = data[i][4];
            route.type = static_cast<RouteType>(std::stoi(data[i][5]));
            
            routes[route.id] = route;
        }
    }
}

void Network::loadTrips(const std::string& filename) {
    CSVReader reader(filename);
    auto data = reader.getData();
    
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i].size() >= 6) {
            Trip trip;
            trip.id = data[i][0];
            trip.routeId = data[i][1];
            trip.serviceId = data[i][2];
            trip.headsign = data[i][3];
            trip.shortName = data[i][4];
            trip.direction = static_cast<TripDirection>(std::stoi(data[i][5]));
            
            trips[trip.id] = trip;
        }
    }
}

void Network::loadStopTimes(const std::string& filename) {
    CSVReader reader(filename);
    auto data = reader.getData();
    
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i].size() >= 5) {
            StopTime stopTime;
            stopTime.tripId = data[i][0];
            
            // Parse arrival time
            std::string arrivalStr = data[i][1];
            sscanf(arrivalStr.c_str(), "%hhu:%hhu:%hhu", 
                   &stopTime.arrivalTime.hour, 
                   &stopTime.arrivalTime.minute, 
                   &stopTime.arrivalTime.second);
            
            // Parse departure time
            std::string departureStr = data[i][2];
            sscanf(departureStr.c_str(), "%hhu:%hhu:%hhu", 
                   &stopTime.departureTime.hour, 
                   &stopTime.departureTime.minute, 
                   &stopTime.departureTime.second);
            
            stopTime.stopId = data[i][3];
            stopTime.stopSequence = std::stoi(data[i][4]);
            
            stopTimes.push_back(stopTime);
        }
    }
}

void Network::loadAgencies(const std::string& filename) {
    CSVReader reader(filename);
    auto data = reader.getData();
    
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i].size() >= 4) {
            Agency agency;
            agency.id = data[i][0];
            agency.name = data[i][1];
            agency.url = data[i][2];
            agency.timezone = data[i][3];
            
            agencies[agency.id] = agency;
        }
    }
}

void Network::buildStationMappings() {
    for (const auto& [stopId, stop] : stops) {
        if (stop.locationType == LocationType_Station) {
            // C'est une station
            stationToStops[stopId].push_back(stopId);
            stopToStation[stopId] = stopId;
        } else if (stop.locationType == LocationType_Stop && !stop.parentStation.empty()) {
            // C'est un quai avec une station parente
            stationToStops[stop.parentStation].push_back(stopId);
            stopToStation[stopId] = stop.parentStation;
        } else {
            // Arrêt sans station parente
            stationToStops[stopId].push_back(stopId);
            stopToStation[stopId] = stopId;
        }
    }
}

void Network::buildTripStopTimes() {
    for (const auto& stopTime : stopTimes) {
        tripStopTimes[stopTime.tripId].push_back(stopTime);
    }
    
    // Trier les stop_times par séquence pour chaque voyage
    for (auto& [tripId, times] : tripStopTimes) {
        std::sort(times.begin(), times.end(), 
                  [](const StopTime& a, const StopTime& b) {
                      return a.stopSequence < b.stopSequence;
                  });
    }
}

void Network::buildNeighborCache() {
    // Pour chaque voyage, connecter les arrêts consécutifs
    for (const auto& [tripId, times] : tripStopTimes) {
        for (size_t i = 0; i < times.size() - 1; ++i) {
            stopNeighbors[times[i].stopId].insert(times[i + 1].stopId);
        }
    }
    
    // Ajouter les connexions de transfert (quais de la même station)
    for (const auto& [stationId, stopIds] : stationToStops) {
        for (const std::string& stopId1 : stopIds) {
            for (const std::string& stopId2 : stopIds) {
                if (stopId1 != stopId2) {
                    stopNeighbors[stopId1].insert(stopId2);
                }
            }
        }
    }
}

std::vector<Stop> Network::getStopsForTransfer(const std::string& stopId) {
    std::vector<Stop> result;
    
    // Déterminer la station
    std::string stationId;
    if (stopToStation.find(stopId) != stopToStation.end()) {
        stationId = stopToStation[stopId];
    } else {
        stationId = stopId;
    }
    
    // Récupérer tous les arrêts de cette station
    if (stationToStops.find(stationId) != stationToStops.end()) {
        for (const std::string& id : stationToStops[stationId]) {
            if (stops.find(id) != stops.end()) {
                result.push_back(stops[id]);
            }
        }
    }
    
    return result;
}

std::unordered_set<std::string> Network::getNeighbors(const std::string& stopId) {
    std::unordered_set<std::string> result;
    
    // Ajouter les voisins directs (via les voyages)
    if (stopNeighbors.find(stopId) != stopNeighbors.end()) {
        for (const std::string& neighbor : stopNeighbors[stopId]) {
            result.insert(neighbor);
        }
    }
    
    return result;
}

std::vector<Stop> Network::getTravelPath(const std::string& fromStopId, const std::string& toStopId) {
    // Algorithme de recherche en largeur (BFS)
    std::queue<std::string> queue;
    std::unordered_map<std::string, std::string> parent;
    std::unordered_set<std::string> visited;
    
    queue.push(fromStopId);
    visited.insert(fromStopId);
    parent[fromStopId] = "";
    
    while (!queue.empty()) {
        std::string current = queue.front();
        queue.pop();
        
        if (current == toStopId) {
            // Reconstruire le chemin
            std::vector<std::string> path;
            std::string node = toStopId;
            while (!node.empty()) {
                path.push_back(node);
                node = parent[node];
            }
            std::reverse(path.begin(), path.end());
            
            // Convertir en objets Stop
            std::vector<Stop> result;
            for (const std::string& stopId : path) {
                if (stops.find(stopId) != stops.end()) {
                    result.push_back(stops[stopId]);
                }
            }
            return result;
        }
        
        // Explorer les voisins
        for (const std::string& neighbor : getNeighbors(current)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                parent[neighbor] = current;
                queue.push(neighbor);
            }
        }
    }
    
    // Aucun chemin trouvé
    return std::vector<Stop>();
}

NetworkScheduledTrip Network::getScheduledTrip(const std::string& tripId) const {
    if (tripStopTimes.find(tripId) != tripStopTimes.end()) {
        return NetworkScheduledTrip(tripId, tripStopTimes.at(tripId));
    }
    return NetworkScheduledTrip();
}

const Stop& Network::getStopById(const std::string& stopId) const {
    return stops.at(stopId);
}

}