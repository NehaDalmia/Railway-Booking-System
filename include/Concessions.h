#include "Passenger.h"

#ifndef CONCESSIONS_H
#define CONCESSIONS_H

class Concessions 
{
private:
    // Copy Constructor for the class Concessions
    Concessions(const Concessions &c);  // blocked
protected:
    // Constructor for the class Concessions
    Concessions();
public:
    // Destructor for the class Concessions
    ~Concessions();
    // Returns static const singleton object of type Concessions
    static const Concessions& Type();
    // Gets concession factor for class Concessions
    double GetConcessionFactor() const;
    // Unit Testing method
    static void UnitTest();
};

#endif //CONCESSIONS_H