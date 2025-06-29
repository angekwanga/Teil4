#include "scheduled_trip.h"
#include <stdexcept>

namespace bht {

// Constructeur de NetworkScheduledTrip
NetworkScheduledTrip::NetworkScheduledTrip(const std::string& tripId, const std::vector<StopTime>& stopTimes)
    : stopTimes(stopTimes), tripId(tripId) {
}

// Constructeurs de l'iterator
NetworkScheduledTrip::iterator::iterator() 
    : stopTimes(nullptr), currentIndex(0), tripId("") {
}

NetworkScheduledTrip::iterator::iterator(const std::vector<StopTime>* stopTimes, size_t index, const std::string& tripId)
    : stopTimes(stopTimes), currentIndex(index), tripId(tripId) {
}

// Opérateurs d'incrémentation
NetworkScheduledTrip::iterator& NetworkScheduledTrip::iterator::operator++() {
    if (stopTimes && currentIndex < stopTimes->size()) {
        ++currentIndex;
    }
    return *this;
}

NetworkScheduledTrip::iterator NetworkScheduledTrip::iterator::operator++(int) {
    iterator temp = *this;
    ++(*this);
    return temp;
}

// Opérateurs de décrémentation
NetworkScheduledTrip::iterator& NetworkScheduledTrip::iterator::operator--() {
    if (currentIndex > 0) {
        --currentIndex;
    }
    return *this;
}

NetworkScheduledTrip::iterator NetworkScheduledTrip::iterator::operator--(int) {
    iterator temp = *this;
    --(*this);
    return temp;
}

// Opérateur de déréférencement
const StopTime& NetworkScheduledTrip::iterator::operator*() const {
    if (!stopTimes || currentIndex >= stopTimes->size()) {
        throw std::out_of_range("Iterator out of range");
    }
    return (*stopTimes)[currentIndex];
}

// Opérateur de pointeur
const StopTime* NetworkScheduledTrip::iterator::operator->() {
    if (!stopTimes || currentIndex >= stopTimes->size()) {
        throw std::out_of_range("Iterator out of range");
    }
    return &((*stopTimes)[currentIndex]);
}

// Getter pour trip ID
const std::string& NetworkScheduledTrip::iterator::getTripId() const {
    return tripId;
}

// Getter pour stop sequence
unsigned int NetworkScheduledTrip::iterator::getStopSequence() const {
    if (!stopTimes || currentIndex >= stopTimes->size()) {
        // Retourner une valeur invalide pour indiquer la fin
        return UINT_MAX;
    }
    return (*stopTimes)[currentIndex].stopSequence;
}

// Méthodes begin et end de NetworkScheduledTrip
NetworkScheduledTrip::iterator NetworkScheduledTrip::begin() const {
    return iterator(&stopTimes, 0, tripId);
}

NetworkScheduledTrip::iterator NetworkScheduledTrip::end() const {
    return iterator(&stopTimes, stopTimes.size(), tripId);
}

// Opérateurs de comparaison globaux
bool operator==(const NetworkScheduledTrip::iterator& a, const NetworkScheduledTrip::iterator& b) {
    return a.getTripId() == b.getTripId() && a.getStopSequence() == b.getStopSequence();
}

bool operator!=(const NetworkScheduledTrip::iterator& a, const NetworkScheduledTrip::iterator& b) {
    return !(a == b);
}

}