#pragma once

#include <vector>
#include <string>

/**
 * Simple CSV reader class for GTFS data
 */
class CSVReader {
private:
    std::vector<std::vector<std::string>> data;
    
public:
    /**
     * Constructor that reads the CSV file
     */
    CSVReader(const std::string& filename);
    
    /**
     * Get the parsed CSV data
     */
    const std::vector<std::vector<std::string>>& getData() const;
    
private:
    /**
     * Parse a CSV line, handling quoted fields
     */
    std::vector<std::string> parseLine(const std::string& line);
};