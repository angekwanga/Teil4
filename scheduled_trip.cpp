#include "scheduled_trip.h"

namespace bht {

bool operator==(const NetworkScheduledTrip::iterator& a, const NetworkScheduledTrip::iterator& b) { 
  return a.getTripId() == b.getTripId() && a.getStopSequence() == b.getStopSequence();
}

bool operator!=(const NetworkScheduledTrip::iterator& a, const NetworkScheduledTrip::iterator& b) { 
  return !(a == b); 
}

}