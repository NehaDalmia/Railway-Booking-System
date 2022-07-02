#include "Concessions.h"

#ifndef LADIES_CONCESSIONS_H
#define LADIES_CONCESSIONS_H

class LadiesConcession : public Concessions {
private:
    // Stores the concession factor
    static const double sConcessionFactor;
    // Constructor for the class LadiesConcession
    LadiesConcession();
    LadiesConcession(LadiesConcession& lc);
    // Destructor for the class LadiesConcession
    ~LadiesConcession();
protected:

public:
    // Returns static const singleton object of type LadiesConcession
    static const LadiesConcession& Type();
    // Returns the concession factor for this category
    double GetConcessionFactor(const Passenger &passenger) const;
};

#endif //LADIES_CONCESSIONS_H