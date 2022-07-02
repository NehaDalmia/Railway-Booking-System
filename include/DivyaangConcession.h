// #define _DEBUG
#include "Concessions.h"

#ifndef DIVYAANG_CONCESSIONS_H
#define DIVYAANG_CONCESSIONS_H

class DivyaangConcession : public Concessions {
private:
    // Constructor for the class DivyaangConcession
    DivyaangConcession();
    // Destructor for the class DivyaangConcession
    ~DivyaangConcession();
protected:

public:
    // Returns static const singleton object of type DivyaangConcession
    static const DivyaangConcession& Type();
    // Returns the concession factor for provided passenger (with disability) and booking class
    double GetConcessionFactor(const Passenger &passenger, const BookingClasses &bookingClass) const;
};

#endif //DIVYAANG_CONCESSIONS_H