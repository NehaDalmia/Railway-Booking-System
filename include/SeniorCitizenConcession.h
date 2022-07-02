// #define _DEBUG
#include "Concessions.h"

#ifndef SENIORCITIZEN_CONCESSIONS_H
#define SENIORCITIZEN_CONCESSIONS_H

class SeniorCitizenConcession : public Concessions {
private:
    // Stores the concession factor for males
    static const double sMaleConcessionFactor;
    // Stores the concession factor for females
    static const double sFemaleConcessionFactor;
    // Constructor for the class SeniorCitizenConcession
    SeniorCitizenConcession();
    SeniorCitizenConcession(SeniorCitizenConcession& scc);
    // Destructor for the class SeniorCitizenConcession
    ~SeniorCitizenConcession();
protected:

public:
    // Returns static const singleton object of type SeniorCitizenConcession
    static const SeniorCitizenConcession& Type();
    // Returns the concession factor for males belonging to this category
    double GetConcessionFactor(const Passenger &passenger, const Gender::Male &gender) const;
    // Returns the concession factor for females belonging to this category
    double GetConcessionFactor(const Passenger &passenger, const Gender::Female &gender) const;
};

#endif //SENIORCITIZEN_CONCESSIONS_H