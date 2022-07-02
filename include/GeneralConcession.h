#include "Concessions.h"

#ifndef GENERAL_CONCESSIONS_H
#define GENERAL_CONCESSIONS_H

class GeneralConcession : public Concessions {
private:
    // Stores the concession factor
    static const double sConcessionFactor;
    // Constructor for the class GeneralConcession
    GeneralConcession();
    GeneralConcession(GeneralConcession& gc);
    // Destructor for the class GeneralConcession
    ~GeneralConcession();
protected:

public:
    // Returns static const singleton object of type GeneralConcession
    static const GeneralConcession& Type();
};

#endif //GENERAL_CONCESSIONS_H