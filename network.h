#pragma once
#include "types.h"
#include <vector>
#include <unordered_map>

namespace bht {

class Network {
  private:
    void readAgencies(std::string source);
    void readCalendarDates(std::string source);
    void readCalendars(std::string source);
    void readLevels(std::string source);
    void readPathways(std::string source);
    void readRoutes(std::string source);
    void readShapes(std::string source);
    void readStopTimes(std::string source);
    void readStops(std::string source);
    void readTransfers(std::string source);
    void readTrips(std::string source);

    /**
     * Parse a date string to a date component struct
     */
    GTFSDate parseDate(std::string input);

    /**
     * Parse a time string to a time component struct
     */
    GTFSTime parseTime(std::string input);

  public:
    /// @brief Properties fetched from GTFS files
    std::unordered_map<std::string, Agency> agencies;
    std::vector<CalendarDate> calendarDates;
    std::unordered_map<std::string, Calendar> calendars;
    std::unordered_map<std::string, Level> levels;
    std::unordered_map<std::string, Pathway> pathways;
    std::unordered_map<std::string, Route> routes;
    std::vector<Shape> shapes;
    std::vector<StopTime> stopTimes;
    std::unordered_map<std::string, Stop> stops;
    std::vector<Transfer> transfers;
    std::vector<Trip> trips;

    /**
     * Create a new network and read all data from files
     * located in the given directory
     */
    Network(std::string directory);

    /**
     * @brief search Search for stops matching the given search string
     * @param needle Search string to use to find stops
     * @return Result vector with matching stops
     */
    std::vector<Stop> search(std::string needle) const;

    /**
     * @brief Return a vector of all routes in the network
     * @return Ordered result vector of routes
     */
    std::vector<Route> getRoutes() const;

    /**
     * @brief Return the display name of a route to show to the user
     * @param route Route object to return the display name for
     * @return String to display for the route
     */
    std::string getRouteDisplayName(Route route) const;

    /**
     * Return a vector of all trips associated with the given route
     * @param routeId ID of the route to get trips for
     * @return Ordered result vector of trips
     */
    std::vector<Trip> getTripsForRoute(std::string routeId) const;

    /**
     * @brief Return the display name of a trip to show to the user
     * @param trip Trip object to return the display name for
     * @return String to display for the trip
     */
    std::string getTripDisplayName(Trip trip) const;

    /**
     * @brief Return a vector of all stops and their times associated with the given trip
     * @param tripId ID of the trip to get stop times for
     * @return Ordered result vector of stop times
     */
    std::vector<StopTime> getStopTimesForTrip(std::string tripId) const;

    /**
     * @brief Return the stop object for the object identified by the given id
     * @param stopId ID of the stop to get the datastructure for
     * @return Stop data structure
     */
    Stop getStopById(std::string stopId) const;

    /**
     * @brief Return a vector of all stops and their times associated with the given trip
     * filtered by the given search word
     * @param needle Search string to use to find stops
     * @param tripId ID of the trip to get stop times for
     * @return Ordered result vector of stop times matching the given search query
     */
    std::vector<StopTime> searchStopTimesForTrip(std::string needle, std::string tripId) const;
};

}
