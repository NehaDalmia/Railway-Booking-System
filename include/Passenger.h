
// #define _DEBUG
#ifndef PASSENGER_H
#define PASSENGER_H

#include "Name.h"
#include "Date.h"
#include "Divyaang.h"
#include "Gender.h"

class Divyaang;
class DivyaangConcession;
class BookingCategory;
template<typename T> class BookingCategoryTypes;
template<typename T> class BookingTypes;
struct GeneralType;
struct LadiesType;
struct SeniorCitizenType;
struct DivyaangType;
struct TatkalType;
struct PremiumTatkalType;

class Passenger
{
private:
    const Name name_;
    const Date dateOfBirth_;
    const Gender &gender_;
    const string aadharNumber_;
    const string mobileNumber_;
    const Divyaang *disabilityType_;
    const string disabilityID_;
    unsigned int age_;
    Passenger(const Name &name, const Date &dateOfBirth, const Gender &gender, const string &aadhar, const string &mobileNo, const Divyaang *disability = NULL, const string &disabilityID = "");    
public:
    static void UnitTest();
    Passenger(const Passenger &copyPassenger);
    bool operator==(const Passenger &p) const;
    static Passenger GetPassenger(const Name &name, const Date &dateOfBirth, const Gender &gender, const string &aadhar, const string &mobileNo, const Divyaang *disability = NULL, const string &disabilityID = "");
    static void IsValid(const Name &name, const Date &dateOfBirth, const Gender &gender, const string &aadhar, const string &mobileNo, const Divyaang *disability , const string &disabilityID );
    friend ostream &operator<<(ostream &out, const Passenger &p);
    friend DivyaangConcession;
    friend BookingCategoryTypes<GeneralType>;
    friend BookingCategoryTypes<LadiesType>;
    friend BookingCategoryTypes<SeniorCitizenType>;
    friend BookingCategoryTypes<DivyaangType>;
    friend BookingCategoryTypes<TatkalType>;
    friend BookingCategoryTypes<PremiumTatkalType>;
    friend BookingTypes<SeniorCitizenType>;
    friend BookingTypes<LadiesType>;
    ~Passenger();
};

#endif //PASSENGER_H