#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

using namespace std;

class Exceptions : public exception {
protected:
    string exception_name;
public:
    Exceptions(string exName) : exception_name(exName) {}
    ~Exceptions() {}
    string what() {
        return exception_name;
    }
};

//top-level exception class for bad date construction

class Bad_Date : public Exceptions {
public:
    Bad_Date(string exName) : Exceptions(exName) {}
    ~Bad_Date() {}
};

//invalid format

class Invalid_Format : public Bad_Date {
public:
    Invalid_Format(string exName) : Bad_Date(exName) {}
    ~Invalid_Format() {}
};

//year to be between 1900 and 2099

class Invalid_Year : public Bad_Date {
public:
    Invalid_Year(string exName) : Bad_Date(exName) {}
    ~Invalid_Year() {}
};

//invalid month (not between 1 - 12)

class Invalid_Month : public Bad_Date {
public:
    Invalid_Month(string exName) : Bad_Date(exName) {}
    ~Invalid_Month() {}
};

//invalid date (for the corresponding month and year)

class Invalid_Day : public Bad_Date {
public:
    Invalid_Day(string exName) : Bad_Date(exName) {}
    ~Invalid_Day() {}
};

//top-level exception class for bad station construction

class Bad_Station : public Exceptions
{
public:
    Bad_Station(string exName) : Exceptions(exName) {}
    ~Bad_Station() {}
};

//Station name cannot be empty

class Bad_Station_Name : public Bad_Station
{
public:
    Bad_Station_Name(string exName) : Bad_Station(exName) {}
    ~Bad_Station_Name() {}
};

//top-level exception class for bad railways construction
class Bad_Railways : public Exceptions {
public:
    Bad_Railways(string exName) : Exceptions(exName) {}
    ~Bad_Railways() {}
};

//duplicate Stations not allowed
class Duplicate_Station : public Bad_Railways {
public:
    Duplicate_Station(string exName) : Bad_Railways(exName) {}
    ~Duplicate_Station() {}
};

//distance not defined between all pairs of Stations
class Incomplete_Distance_Information : public Bad_Railways {
public:
    Incomplete_Distance_Information(string exName) : Bad_Railways(exName) {}
    ~Incomplete_Distance_Information() {}
};

//distance between two same Stations is not defined
class Distance_Not_Defined : public Bad_Railways {
public:
    Distance_Not_Defined(string exName) : Bad_Railways(exName) {}
    ~Distance_Not_Defined() {}
};

//top level exception class for bad passenger construction
class Bad_Passenger : public Exceptions {
public:
    Bad_Passenger(string exName) : Exceptions(exName) {}
    ~Bad_Passenger() {}
};

//name not entered according to rules
class Bad_Name : public Bad_Passenger {
public:
    Bad_Name(string exName) : Bad_Passenger(exName) {}
    ~Bad_Name() {}
};

//age must be >0, i.e., dob must be before the date today
class Bad_Age : public Bad_Passenger {
public:
    Bad_Age(string exName) : Bad_Passenger(exName) {}
    ~Bad_Age() {}
};

//should be validated for absence of non-digit and length
class Bad_Aadhar_Number : public Bad_Passenger {
public:
    Bad_Aadhar_Number(string exName) : Bad_Passenger(exName) {}
    ~Bad_Aadhar_Number() {}
};

//should be validated, if provided, for absence of non-digit and length
class Bad_Mobile_Number : public Bad_Passenger {
public:
    Bad_Mobile_Number(string exName) : Bad_Passenger(exName) {}
    ~Bad_Mobile_Number() {}
};

//top level exception class for booking construction
class Bad_Booking : public Exceptions {
public:
    Bad_Booking(string exName) : Exceptions(exName) {}
    ~Bad_Booking() {}
};

//station entered is non existent in the master data
class Invalid_Station : public Bad_Booking {
public:
    Invalid_Station(string exName) : Bad_Booking(exName) {}
    ~Invalid_Station() {}
};

//dob < Date::Today() [date of reservation] < date of booking (not more than 1 year after date of reservation) 

class Bad_Chronology : public Bad_Booking {
public:
    Bad_Chronology(string exName) : Bad_Booking(exName) {}
    ~Bad_Chronology() {}
};

//passenger ineligible to book in entered category

class Ineligible_Passenger : public Bad_Booking {
public:
    Ineligible_Passenger(string exName) : Bad_Booking(exName) {}
    ~Ineligible_Passenger() {}
};

//ineligible for ladies category

class Ineligible_Ladies_Category : public Ineligible_Passenger {
public:
    Ineligible_Ladies_Category(string exName) : Ineligible_Passenger(exName) {}
    ~Ineligible_Ladies_Category() {}
};

//ineligible for senior citizen category

class Ineligible_SeniorCitizen_Category : public Ineligible_Passenger {
public:
    Ineligible_SeniorCitizen_Category(string exName) : Ineligible_Passenger(exName) {}
    ~Ineligible_SeniorCitizen_Category() {}
};

//ineligible for divyaang category

class Ineligible_Divyaang_Category : public Ineligible_Passenger {
public:
    Ineligible_Divyaang_Category(string exName) : Ineligible_Passenger(exName) {}
    ~Ineligible_Divyaang_Category() {}
};

//ineligible for tatkal category

class Ineligible_Tatkal_Category : public Ineligible_Passenger {
public:
    Ineligible_Tatkal_Category(string exName) : Ineligible_Passenger(exName) {}
    ~Ineligible_Tatkal_Category() {}
};

//ineligible for premium tatkal category

class Ineligible_PremiumTatkal_Category : public Ineligible_Passenger {
public:
    Ineligible_PremiumTatkal_Category(string exName) : Ineligible_Passenger(exName) {}
    ~Ineligible_PremiumTatkal_Category() {}
};

#endif //EXCEPTIONS_H