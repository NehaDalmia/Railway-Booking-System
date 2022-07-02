// #define _DEBUG
#ifndef __DATE_H
#define __DATE_H

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//Needs work, see if construction is to be done using a string

class Date
{
private:
    static const char sMonthNames[][4];                 //Month names
    enum Month { Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec };
    typedef unsigned int UINT;
    const UINT date_; const Month month_; const UINT year_;               //date, month and year respectively
    Date(UINT, UINT, UINT); //Ctor
    //Date& operator=(const Date&);                       //Blocked copy assignment operator
    
public:
    Date(const Date&);      //Copy ctor
    friend ostream& operator<<(ostream&, const Date&);  //Output streaming operator for this class
    // Getter for date_
    UINT GetDay() const {
        return date_;
    }
    //Getter for month_
    Month GetMonth() const {
        return month_;
    }
    //Getter for year_
    UINT GetYear() const {
        return year_;
    }
    bool IsLeapYear() const;
    UINT CalculateAge() const;
    int CalculateSpan(const Date &d) const;
    bool operator==(const Date&) const;
    static Date Today();
    static void IsValid(const string &dateString);
    static void IsValid(const UINT, const UINT, const UINT);
    static Date GetDate(const string &dateString);
    static Date GetDate(const UINT, const UINT, const UINT);
    static void UnitTest(); //For Unit Testing
    ~Date();                //Dtor
};

#endif