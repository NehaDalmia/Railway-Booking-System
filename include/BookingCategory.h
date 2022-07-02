#ifndef BOOKING_CATEGORY_H
#define BOOKING_CATEGORY_H


#include <iostream>
#include <sstream>
#include <string>
#include "Booking.h"
#include "Exceptions.h"

class Booking;
class Passenger;

using namespace std;

template<typename T>
class BookingCategoryTypes;

// defining publically so that these can be used by class Booking as well

struct GeneralType{};
struct LadiesType{};
struct SeniorCitizenType{};
struct DivyaangType{};
struct TatkalType{};
struct PremiumTatkalType{};

class BookingCategory {
private:
    BookingCategory(const BookingCategory& C);
protected:
    BookingCategory();
    ~BookingCategory();
public:
    static void UnitTest();
    virtual string GetName() const = 0;
    virtual void Eligibility(const Passenger &passenger, const Date& dateOfReservation, const Date& dateOfBooking) const = 0;
    virtual Booking *ReserveInCategory(const Station &fromStation, const Station &toStation, const Date &dateOfBooking, const Date &dateOfReservation, const BookingClasses &bookingClass, const Passenger &passenger) const = 0;
    friend ostream &operator<<(ostream &out, const BookingCategory &bcat);
    typedef BookingCategoryTypes<GeneralType> General;
    typedef BookingCategoryTypes<LadiesType> Ladies;
    typedef BookingCategoryTypes<SeniorCitizenType> SeniorCitizen;
    typedef BookingCategoryTypes<DivyaangType> DivyaangCat;
    typedef BookingCategoryTypes<TatkalType> Tatkal;
    typedef BookingCategoryTypes<PremiumTatkalType> PremiumTatkal;

};

template<typename T>
class BookingCategoryTypes : public BookingCategory{
private:
    BookingCategoryTypes(const BookingCategoryTypes& C);
    static const string sName;

    BookingCategoryTypes() 
    {
        #ifdef _DEBUG
        cout << *this << " --CONSTRUCTED" << endl;
        #endif
    };
    ~BookingCategoryTypes() 
    {
        #ifdef _DEBUG
        cout << *this << "  --DESTRUCTED" << endl;
        #endif
    };

public:
    static const BookingCategoryTypes<T>& Type(){
        static const BookingCategoryTypes<T> obj;
        return obj;
    }
    friend ostream &operator<<(ostream &out, const BookingCategoryTypes<T> &bcat) {
        out << "Booking Category = " << bcat.GetName();
        return out;
    }
    string GetName() const {
        return BookingCategoryTypes<T>::sName;
    }
    void Eligibility(const Passenger &passenger, const Date& dateOfReservation, const Date& dateOfBooking) const;
    Booking *ReserveInCategory(const Station &fromStation, const Station &toStation, const Date &dateOfBooking, const Date &dateOfReservation, const BookingClasses &bookingClass, const Passenger &passenger) const
    {
        bool result = false;
        try {
            result = BookingTypes<T>::CheckEligibility(passenger, BookingCategoryTypes<T>::Type(),dateOfReservation, dateOfBooking);
        }
        catch (Bad_Booking &bk) {
            throw;
        }
        return new BookingTypes<T>(fromStation, toStation, dateOfBooking, dateOfReservation, bookingClass, BookingCategoryTypes<T>::Type(), passenger);
    }
};

#endif //BOOKING_CATEGORY_H