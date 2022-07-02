#ifndef BOOKING_CLASSES_H
#define BOOKING_CLASSES_H

#include <iostream>
#include <sstream>

//#include "Divyaang.h"

using namespace std;

template<typename T>
class BookingClassTypes;
class Divyaang;

//EXTENSIBLE, ABSTRACT
class BookingClasses
{
private:
    struct AC2TierType{};
    struct AC3TierType{};
    struct ACChairCarType{};
    struct ACFirstClassType{};
    struct ExecutiveChairCarType{};
    struct FirstClassType{};
    struct SecondSittingType{};
    struct SleeperType{};
    BookingClasses(const BookingClasses& book);
protected:
    // Constructor for the class BookingClasses
    BookingClasses();
    // Virtual Destructor for the class BookingClasses, supports polymorphic hierarchy
    virtual ~BookingClasses();
public:
    //STATIC METHODS
    static void UnitTestBookingClasses();   //For Unit Testing
    //--------------

    //PURE VIRTUALS (Get Overriden In Specialized Classes)
    virtual double GetLoadFactor() const = 0;
    virtual string GetName() const = 0;
    virtual int GetNumberOfTiers() const = 0;
    virtual double GetReservationCharge() const = 0;
    virtual bool IsAC() const = 0;
    virtual bool IsLuxury() const = 0;
    virtual bool IsSitting() const = 0;

    virtual double GetTatkalLoadFactor() const = 0;
    virtual double GetMinTatkalCharge() const = 0;
    virtual double GetMaxTatkalCharge() const = 0;
    virtual double GetMinTatkalDistance() const = 0;

    virtual double GetConcessionForDivyaang(const Divyaang *dis) const = 0;
    //-------------

    friend ostream &operator<<(ostream &out, const BookingClasses &bc);
    static void UnitTest();
    typedef BookingClassTypes<AC2TierType> AC2Tier;
    typedef BookingClassTypes<AC3TierType> AC3Tier;
    typedef BookingClassTypes<ACChairCarType> ACChairCar;
    typedef BookingClassTypes<ACFirstClassType> ACFirstClass;
    typedef BookingClassTypes<ExecutiveChairCarType> ExecutiveChairCar;
    typedef BookingClassTypes<FirstClassType> FirstClass;
    typedef BookingClassTypes<SecondSittingType> SecondSitting;
    typedef BookingClassTypes<SleeperType> Sleeper;
};

template<typename T>
class BookingClassTypes : public BookingClasses {
private:
    static const double sLoadFactor;
    static const string sName;
    static const int sNumberOfTiers;
    static const double sReservationCharge;
    static const bool sAC;
    static const bool sLuxury;
    static const bool sSitting;
    
    static const double sTatkalLoadFactor;
    static const double sMinTatkalCharge;
    static const double sMaxTatkalCharge;
    static const double sMinTatkalDistance;
    BookingClassTypes(const BookingClassTypes& book);
    BookingClassTypes();
    ~BookingClassTypes();

public:
    static const BookingClassTypes<T> &Type();
    //utility function to get divyaang concession using Divyaang *, not included in class diagram/design.txt
    double GetConcessionForDivyaang(const Divyaang *dis) const;
    double GetLoadFactor() const;
    string GetName() const;
    int GetNumberOfTiers() const;
    double GetReservationCharge() const;
    bool IsAC() const;
    bool IsLuxury() const;
    bool IsSitting() const;
    double GetTatkalLoadFactor() const;
    double GetMinTatkalCharge() const;
    double GetMaxTatkalCharge() const;
    double GetMinTatkalDistance() const;
    friend ostream &operator<<(ostream &out, const BookingClassTypes<T> &bclass)
    {
        out << "Called From: "<<bclass.GetName()<<"\n";
        out << "Travel Class = " << bclass.GetName() << "\n";
        if (bclass.IsSitting() == false)
            out << " : "
                << "Mode: "
                << "Sleeping"
                << "\n";
        else
            out << " : "
                << "Mode: "
                << "Sitting"
                << "\n";
        if (bclass.IsAC() == false)
            out << " : "
                << "Comfort: "
                << "Non-AC"
                << "\n";
        else
            out << " : "
                << "Comfort: "
                << "AC"
                << "\n";
        out << " : "
            << "Bunks: " << bclass.GetNumberOfTiers() << "\n";
        if (bclass.IsLuxury() == false)
            out << " : "
                << "Luxury: "
                << "No"
                << "\n";
        else
            out << " : "
                << "Luxury: "
                << "Yes"
                << "\n";
        return out;
    }
//Overrides virtual double BookingClasses::GetLoadFactor() = 0, Returns sLoadFactor
//Overrides virtual string BookingClasses::GetName() = 0, Returns the name of booking class in-situ
//Overrides virtual bool BookingClasses::IsAC() = 0, Returns whether AC/Non-AC in-situ
//Overrides virtual bool BookingClasses::IsLuxury() = 0, Returns sLuxury
};

#endif //BOOKING_CLASSES_H