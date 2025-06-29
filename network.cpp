#include "network.h"
#include "csv.h"

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
  readStopTimes(directory + "/stop_times.txt");
  readStops(directory + "/stops.txt");
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
    for (const auto &stopTime : stopTimes) {
        // Check if stop belongs to trip and matches filter if given
        if (stopTime.tripId == tripId && (needle.empty() || stops.at(stopTime.stopId).name.find(needle) != std::string::npos)) {
            result.push_back(stopTime);
        }
    }

    /*std::sort(result.begin(), result.end(), [] (const StopTime& lhs, const StopTime& rhs) {
        return rhs.stopSequence - lhs.stopSequence;
    });*/

    return result;
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
