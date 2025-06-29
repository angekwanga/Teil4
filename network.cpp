#include "network.h"
#include "csv.h"
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace bht {

Network::Network(std::string directory) {
  // Fetch data
  readAgencies(directory + "/agency.txt");
  readCalendarDates(directory + "/calendar_dates.txt");
  readCalendars(directory + "/calendar.txt");
  readLevels(directory + "/levels.txt");
  readPathways(directory + "/pathways.txt");
  readRoutes(directory + "/routes.txt");
  readShapes(directory + "/shapes.txt");
  readStops(directory + "/stops.txt");
  readStopTimes(directory + "/stop_times.txt");
  readTransfers(directory + "/transfers.txt");
  readTrips(directory + "/trips.txt");
}

std::vector<Stop> Network::search(std::string needle) const {
  std::vector<Stop> result;

  for (const std::pair<const std::string, Stop>& pair : stops) {
      if (pair.second.name.find(needle) != std::string::npos) {
          result.push_back(pair.second);
      }
  }

  return result;
}

std::vector<Route> Network::getRoutes() const {
    std::vector<Route> result;

    for (auto &route : routes) {
        result.push_back(route.second);
    }

    std::sort(result.begin(), result.end(), [] (const Route& lhs, const Route& rhs) {
        return lhs.shortName < rhs.shortName;
    });

    return result;
}

std::string Network::getRouteDisplayName(Route route) const {
    std::string displayName = route.shortName;
    if (!route.longName.empty()) {
        displayName = displayName + " - " + route.longName;
    }
    return displayName;
}

std::vector<Trip> Network::getTripsForRoute(std::string routeId) const {
    std::vector<Trip> result;
    for (auto &trip : trips) {
        if (trip.routeId == routeId) {
            result.push_back(trip);
        }
    }
    return result;
}

std::string Network::getTripDisplayName(Trip trip) const {
    return trip.shortName + " - " + trip.headsign;
}

std::vector<StopTime> Network::getStopTimesForTrip(std::string tripId) const {
    return searchStopTimesForTrip("", tripId);
}

Stop Network::getStopById(std::string stopId) const {
    return stops.at(stopId);
}

std::vector<StopTime> Network::searchStopTimesForTrip(std::string needle, std::string tripId) const {
    std::vector<StopTime> result;
    
    auto range = tripStopTimes.equal_range(tripId);
    for (auto it = range.first; it != range.second; ++it) {
        const StopTime& stopTime = it->second;
        if (needle.empty() || stops.at(stopTime.stopId).name.find(needle) != std::string::npos) {
            result.push_back(stopTime);
        }
    }

    std::sort(result.begin(), result.end(), [](const StopTime& lhs, const StopTime& rhs) {
        return lhs.stopSequence < rhs.stopSequence;
    });

    return result;
}

// New methods for Aufgabe 4

std::vector<Stop> Network::getStopsForTransfer(const std::string& stopId) const {
    std::vector<Stop> result;
    
    // Add the stop itself
    if (stops.find(stopId) != stops.end()) {
        result.push_back(stops.at(stopId));
    }
    
    const Stop& stop = stops.at(stopId);
    
    if (stop.locationType == LocationType_Station) {
        // If it's a station, find all platforms/tracks
        auto range = stopsForTransfer.equal_range(stopId);
        for (auto it = range.first; it != range.second; ++it) {
            if (stops.find(it->second) != stops.end()) {
                const Stop& childStop = stops.at(it->second);
                if (childStop.id != stopId) {
                    result.push_back(childStop);
                }
            }
        }
    } else {
        // If it's a platform/track, find the parent station and all sibling platforms
        if (!stop.parentStation.empty()) {
            // Add parent station
            if (stops.find(stop.parentStation) != stops.end()) {
                const Stop& parentStop = stops.at(stop.parentStation);
                bool alreadyAdded = false;
                for (const auto& existingStop : result) {
                    if (existingStop.id == parentStop.id) {
                        alreadyAdded = true;
                        break;
                    }
                }
                if (!alreadyAdded) {
                    result.push_back(parentStop);
                }
            }
            
            // Add all sibling platforms
            auto range = stopsForTransfer.equal_range(stop.parentStation);
            for (auto it = range.first; it != range.second; ++it) {
                if (stops.find(it->second) != stops.end()) {
                    const Stop& siblingStop = stops.at(it->second);
                    if (siblingStop.id != stopId) {
                        bool alreadyAdded = false;
                        for (const auto& existingStop : result) {
                            if (existingStop.id == siblingStop.id) {
                                alreadyAdded = true;
                                break;
                            }
                        }
                        if (!alreadyAdded) {
                            result.push_back(siblingStop);
                        }
                    }
                }
            }
        }
    }
    
    return result;
}

std::unordered_set<std::string> Network::getNeighbors(const std::string& stopId) const {
    std::unordered_set<std::string> neighbors;
    
    // Get all trips that stop at this station
    auto tripRange = stopTrips.equal_range(stopId);
    for (auto tripIt = tripRange.first; tripIt != tripRange.second; ++tripIt) {
        const std::string& tripId = tripIt->second;
        
        // Get all stops for this trip in order
        std::vector<StopTime> tripStops;
        auto stopRange = tripStopTimes.equal_range(tripId);
        for (auto stopIt = stopRange.first; stopIt != stopRange.second; ++stopIt) {
            tripStops.push_back(stopIt->second);
        }
        
        // Sort by stop sequence
        std::sort(tripStops.begin(), tripStops.end(), 
                  [](const StopTime& a, const StopTime& b) {
                      return a.stopSequence < b.stopSequence;
                  });
        
        // Find current stop and add next/previous stops
        for (size_t i = 0; i < tripStops.size(); ++i) {
            if (tripStops[i].stopId == stopId) {
                // Add next stop
                if (i + 1 < tripStops.size()) {
                    neighbors.insert(tripStops[i + 1].stopId);
                }
                // Add previous stop
                if (i > 0) {
                    neighbors.insert(tripStops[i - 1].stopId);
                }
                break;
            }
        }
    }
    
    // Add transfer possibilities (same station)
    std::vector<Stop> transferStops = getStopsForTransfer(stopId);
    for (const auto& transferStop : transferStops) {
        if (transferStop.id != stopId) {
            neighbors.insert(transferStop.id);
        }
    }
    
    return neighbors;
}

std::vector<Stop> Network::getTravelPath(const std::string& fromStopId, const std::string& toStopId) const {
    if (fromStopId == toStopId) {
        return {stops.at(fromStopId)};
    }
    
    // BFS for shortest path
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
            // Reconstruct path
            std::vector<Stop> path;
            std::string node = toStopId;
            while (!node.empty()) {
                if (stops.find(node) != stops.end()) {
                    path.push_back(stops.at(node));
                }
                node = parent[node];
            }
            std::reverse(path.begin(), path.end());
            return path;
        }
        
        // Get neighbors
        std::unordered_set<std::string> neighbors = getNeighbors(current);
        for (const std::string& neighbor : neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                parent[neighbor] = current;
                queue.push(neighbor);
            }
        }
    }
    
    // No path found
    return {};
}

NetworkScheduledTrip Network::getScheduledTrip(const std::string& tripId) const {
    std::vector<StopTime> tripStopTimes;
    
    auto range = this->tripStopTimes.equal_range(tripId);
    for (auto it = range.first; it != range.second; ++it) {
        tripStopTimes.push_back(it->second);
    }
    
    std::sort(tripStopTimes.begin(), tripStopTimes.end(), 
              [](const StopTime& a, const StopTime& b) {
                  return a.stopSequence < b.stopSequence;
              });
    
    return NetworkScheduledTrip(tripId, tripStopTimes);
}

void Network::readAgencies(std::string source) {
  bht::CSVReader reader{source};
  do {
    std::string id = reader.getField("agency_id");
    if (id.empty() == false) {
      Agency item = {
        id,
        reader.getField("agency_name"),
        reader.getField("agency_url"),
        reader.getField("agency_timezone"),
        reader.getField("agency_lang"),
        reader.getField("agency_phone")
      };
      agencies[id] = item;
    }
  } while (reader.next());
}

void Network::readCalendarDates(std::string source) {
  bht::CSVReader reader(source);
  do {
    std::string id = reader.getField("service_id");
    if (id.empty() == false) {
      CalendarDate item = {
        id,
        parseDate(reader.getField("date")),
        (ECalendarDateException)std::stoi(reader.getField("exception_type"))
      };
      calendarDates.push_back(item);
    }
  } while (reader.next());
}

void Network::readCalendars(std::string source) {
  bht::CSVReader reader(source);
  do {
    std::string id = reader.getField("service_id");
    if (id.empty() == false) {
      Calendar item = {
        id,
        (ECalendarAvailability)std::stoi(reader.getField("monday")),
        (ECalendarAvailability)std::stoi(reader.getField("tuesday")),
        (ECalendarAvailability)std::stoi(reader.getField("wednesday")),
        (ECalendarAvailability)std::stoi(reader.getField("thursday")),
        (ECalendarAvailability)std::stoi(reader.getField("friday")),
        (ECalendarAvailability)std::stoi(reader.getField("saturday")),
        (ECalendarAvailability)std::stoi(reader.getField("sunday")),
        parseDate(reader.getField("start_date")),
        parseDate(reader.getField("end_date"))
      };
      calendars[id] = item;
    }
  } while (reader.next());
}

void Network::readLevels(std::string source) {
  bht::CSVReader reader(source);
  do {
    std::string id = reader.getField("level_id");
    if (id.empty() == false) {
      Level item = {
        id,
        (unsigned int)std::stoi(reader.getField("level_index")),
        reader.getField("level_name")
      };
      levels[id] = item;
    }
  } while (reader.next());
}

void Network::readPathways(std::string source) {
  bht::CSVReader reader(source);
  do {
    std::string id = reader.getField("pathway_id");
    if (id.empty() == false) {
      Pathway item = {
        id,
        reader.getField("from_stop_id"),
        reader.getField("to_stop_id"),
        (EPathwayMode)std::stoi(reader.getField("pathway_mode", "1")),
        reader.getField("is_bidirectional") == "1",
        std::stof(reader.getField("length", "0.0")),
        (unsigned int)std::stoi(reader.getField("traversal_time", "0")),
        (unsigned int)std::stoi(reader.getField("stair_count", "0")),
        std::stof(reader.getField("max_slope", "0.0")),
        std::stof(reader.getField("min_width", "0.0")),
        reader.getField("signposted_as")
      };
      pathways[id] = item;
    }
  } while (reader.next());
}

void Network::readRoutes(std::string source) {
  bht::CSVReader reader(source);
  do {
    std::string id = reader.getField("route_id");
    if (id.empty() == false) {
      Route item = {
        id,
        reader.getField("agency_id"),
        reader.getField("route_short_name"),
        reader.getField("route_long_name"),
        reader.getField("route_desc"),
        (RouteType)std::stoi(reader.getField("route_type", "0")),
        reader.getField("route_color"),
        reader.getField("route_text_color")
      };
      routes[id] = item;
    }
  } while (reader.next());
}

void Network::readShapes(std::string source) {
  bht::CSVReader reader(source);
  do {
    std::string id = reader.getField("shape_id");
    if (id.empty() == false) {
      Shape item = {
        id,
        std::stod(reader.getField("shape_pt_lat")),
        std::stod(reader.getField("shape_pt_lon")),
        (unsigned int)std::stoi(reader.getField("shape_pt_sequence"))
      };
      shapes.push_back(item);
    }
  } while (reader.next());
}

void Network::readStopTimes(std::string source) {
  bht::CSVReader reader(source);
  do {
    std::string id = reader.getField("trip_id");
    if (id.empty() == false) {
      StopTime item = {
        id,
        parseTime(reader.getField("arrival_time")),
        parseTime(reader.getField("departure_time")),
        reader.getField("stop_id"),
        (unsigned int)std::stoi(reader.getField("stop_sequence")),
        (EPickupType)std::stoi(reader.getField("pickup_type")),
        (EDropOffType)std::stoi(reader.getField("drop_off_type")),
        reader.getField("stop_headsign") 
      };
      stopTimes.push_back(item);
      
      // Build optimized data structures
      stopTrips.insert({item.stopId, item.tripId});
      tripStops.insert({item.tripId, item.stopId});
      tripStopTimes.insert({item.tripId, item});
    }
  } while (reader.next());
}

void Network::readStops(std::string source) {
  bht::CSVReader reader(source);
  do {
    std::string id = reader.getField("stop_id");
    if (id.empty() == false) {
      Stop item = {
        id,
        reader.getField("stop_code"),
        reader.getField("stop_name"),
        reader.getField("stop_desc"),
        std::stod(reader.getField("stop_lat")),
        std::stod(reader.getField("stop_lon")),
        (LocationType)std::stoi(reader.getField("location_type")),
        reader.getField("parent_station"),
        (WheelchairAccessibility)std::stoi(reader.getField("wheelchair_boarding")),
        reader.getField("platform_code"),
        reader.getField("level_id"),
        reader.getField("zone_id")
      };
      stops[id] = item;
      
      // Build transfer data structures
      if (item.locationType == LocationType_Station) {
        stopsForTransfer.insert({id, id});
      } else if (!item.parentStation.empty()) {
        stopsForTransfer.insert({item.parentStation, id});
      }
    }
  } while (reader.next());
}

void Network::readTransfers(std::string source) {
  bht::CSVReader reader(source);
  do {
    std::string id = reader.getField("from_stop_id");
    if (id.empty() == false) {
      Transfer item = {
        id,
        reader.getField("to_stop_id"),
        reader.getField("from_route_id"),
        reader.getField("to_route_id"),
        reader.getField("from_trip_id"),
        reader.getField("to_trip_id"),
        (TransferType)std::stoi(reader.getField("transfer_type")),
        (unsigned int)std::stoi(reader.getField("min_transfer_time", "0"))
      };
      transfers.push_back(item);
    }
  } while (reader.next());
}

void Network::readTrips(std::string source) {
  bht::CSVReader reader(source);
  do {
    std::string id = reader.getField("trip_id");
    if (id.empty() == false) {
      Trip item = {
        id,
        reader.getField("route_id"),
        reader.getField("service_id"),
        reader.getField("trip_headsign"),
        reader.getField("trip_short_name"),
        (TripDirection)std::stoi(reader.getField("direction_id")),
        reader.getField("block_id"),
        reader.getField("shape_id"),
        (WheelchairAccessibility)std::stoi(reader.getField("wheelchair_accessible")),
        reader.getField("bikes_allowed") == "1",
      };
      trips.push_back(item);
    }
  } while (reader.next());
}

GTFSDate Network::parseDate(std::string input) {
  GTFSDate result = { 
    .day = (unsigned char)std::stoi(input.substr(6, 2)),
    .month = (unsigned char)std::stoi(input.substr(4, 2)),
    .year = (unsigned short)std::stoi(input.substr(0, 4))
  };

  return result;
}

GTFSTime Network::parseTime(std::string input) {
  size_t first = input.find(":");
  size_t next = input.find(":", first + 1);
  GTFSTime result = { 
    .hour = (unsigned char)std::stoi(input.substr(0, first)),
    .minute = (unsigned char)std::stoi(input.substr(first + 1, next - first)),
    .second = (unsigned char)std::stoi(input.substr(next + 1))
  };

  return result;
}

}