#include "Date.h"
#include "Exceptions.h"
#include <vector>
#include <ctime>

const char Date::sMonthNames[][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                     "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

Date::Date(UINT d, UINT m, UINT y) : date_(d), month_(static_cast<Month>(m)), year_(y)
{
    #ifdef _DEBUG
    cout << "Date = " << *this << "  --CONSTRUCTED" << endl;
    #endif
}
void Date::IsValid(UINT date, UINT month, UINT year) {
    //Out of range
    if(year<1900 || year>2099) {
        throw Invalid_Year("Date Error: Year is invalid");
    }
    // Out of range
    if(month>12 || month <1) {
        throw Invalid_Month("Date Error: Month is invalid");
    }
    // Out of range
    if(date < 1) {
        throw Invalid_Day("Date Error: Date is invalid");
    }
    //Various conditions of a leap year
    bool isLeap = false;
    if (year % 400 == 0)
        isLeap = true;
    else if (year % 100 == 0)
        isLeap = false;
    else if (year % 4 == 0)
        isLeap = true;
    //Month constraints in a leap year
    if(isLeap) {
        if(month == 2) {
            if(date > 29) {
                throw Invalid_Day("Date Error: Date is invalid");
            }
        }
        else if(month == 4 || month == 6 || month == 9 || month == 11) {
            if(date > 30) {
                throw Invalid_Day("Date Error: Date is invalid");
            }
        }
        else {
            if(date > 31) {
                throw Invalid_Day("Date Error: Date is invalid");
            }
        }
    }  //Month constraints in a non leap year
    else {
        if(month == 2) {
            if(date > 28) {
                throw Invalid_Day("Date Error: Date is invalid");
            }
        }
        else if(month == 4 || month == 6 || month == 9 || month == 11) {
            if(date > 30) {
                throw Invalid_Day("Date Error: Date is invalid");
            }
        }
        else {
            if(date > 31) {
                throw Invalid_Day("Date Error: Date is invalid");
            }
        }
    }
}
void Date::IsValid(const string &d) {
    // Check if format is DD/MM/YYYY
    try{
        stoi(d.substr(0,2));    //checks if DD is numeric
        stoi(d.substr(3,2));    //checks if MM is numeric
        stoi(d.substr(6,4));    //checks if YYYY is numeric
    }
    catch(...) {
        throw Invalid_Format("Date Error: Date format should be DD/MM/YYYY, where DD,MM,YYYY are numeric");
    }
    //Wrong format
    if(d.length()!=10 || d[2]!='/' || d[5]!='/'){
        throw Invalid_Format("Date Error: Date format should be DD/MM/YYYY, where DD,MM,YYYY are numeric");
    }
    UINT date = stoi(d.substr(0,2));
    UINT month = stoi(d.substr(3,2));
    UINT year = stoi(d.substr(6,4));
    //Out of range
    if(year<1900 || year>2099) {
        throw Invalid_Year("Date Error: Year is invalid");
    }
    //Out of range
    if(month>12 || month <1) {
        throw Invalid_Month("Date Error: Month is invalid");
    }
    //Out of range
    if(date < 1) {
        throw Invalid_Day("Date Error: Date is invalid");
    }
    //various conditions of leap year
    bool isLeap = false;
    if (year % 400 == 0)
        isLeap = true;
    else if (year % 100 == 0)
        isLeap = false;
    else if (year % 4 == 0)
        isLeap = true;
    if(isLeap) {
        if(month == 2) {
            if(date > 29) {
                throw Invalid_Day("Date Error: Date is invalid");
            }
        }
        else if(month == 4 || month == 6 || month == 9 || month == 11) {
            if(date > 30) {
                throw Invalid_Day("Date Error: Date is invalid");
            }
        }
        else {
            if(date > 31) {
                throw Invalid_Day("Date Error: Date is invalid");
            }
        }
    }
    else {
        if(month == 2) {
            if(date > 28) {
                throw Invalid_Day("Date Error: Date is invalid");
            }
        }
        else if(month == 4 || month == 6 || month == 9 || month == 11) {
            if(date > 30) {
                throw Invalid_Day("Date Error: Date is invalid");
            }
        }
        else {
            if(date > 31) {
                throw Invalid_Day("Date Error: Date is invalid");
            }
        }
    }
}
//returns toda's date
Date Date::Today() 
{ 
    time_t now = time(0);
    tm * ti = localtime(&now);
    return Date(ti->tm_mday, 1 + ti->tm_mon, 1900 + ti->tm_year);
}
//returns date object
Date Date::GetDate(const string &d) {
    // try{
        Date::IsValid(d);
    // }
    // catch(Bad_Date &bd) {
    //     throw bd;
    // }
    UINT date = stoi(d.substr(0,2));
    UINT month = stoi(d.substr(3,2));
    UINT year = stoi(d.substr(6,4));
    return Date(date, month, year);
}
//returns date object
Date Date::GetDate(UINT date, UINT month, UINT year) 
{
    // try{
        Date::IsValid(date, month, year);
    // }
    // catch(Bad_Date &bd) {
    //     throw bd;
    // }
    return Date(date, month, year);
}
//Calculates age based on today's date
Date::UINT Date::CalculateAge() const
{
    UINT monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    // if birth date is greater then current month then do not count this month and add 30
    // to the date so as to subtract the date and get the remaining days
    UINT currentDate = Date::Today().date_;
    UINT currentMonth = Date::Today().month_;
    UINT currentYear = Date::Today().year_;
    if (date_ > Date::Today().date_) {
        currentDate = currentDate + monthDays[month_ - 1];
        currentMonth = currentMonth - 1;
    }
 
    // if birth month exceeds current month, then do not count this year and add 12 to the month so
    // that we can subtract and find out the difference
    if (month_ > currentMonth) {
        currentYear = currentYear - 1;
        currentMonth = currentMonth + 12;
    }
 
    // calculate age
    UINT age = currentYear - year_;

    // print the present age
    return age;
}
bool Date::IsLeapYear() const   
{
// If a year is multiple of 400,
    // then it is a leap year
    if (year_ % 400 == 0)
        return true;
 
    // Else If a year is multiple of 100,
    // then it is not a leap year
    if (year_ % 100 == 0)
        return false;
 
    // Else If a year is multiple of 4,
    // then it is a leap year
    if (year_ % 4 == 0)
        return true;
    return false;
}

int Date::CalculateSpan(const Date &d) const 
{
    const UINT monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int years = year_;
    // Check if the current year needs to be considered for the count of leap years or not
    if (month_ <= 2)
        years--;
    // An year is a leap year if it is a multiple of 4 OR multiple of 400 and not a multiple of 100.
    UINT noOfLeapsBeforeD1 = years / 4 - years / 100 + years / 400;
    
    years = d.year_;
    // Check if the current year needs to be considered for the count of leap years or not
    if (d.month_ <= 2)
        years--;
    // An year is a leap year if it is a multiple of 4 OR multiple of 400 and not a multiple of 100.
    UINT noOfLeapsBeforeD2 = years / 4 - years / 100 + years / 400;
    
    UINT n1 = year_ * 365 + date_;
    // Add days for months in given date
    for (int i = 0; i < month_ - 1; i++)
        n1 += monthDays[i];
    // Since every leap year is of 366 days, add a day for every leap year
    n1 += noOfLeapsBeforeD1;
 
    // SIMILARLY, COUNT TOTAL NUMBER OF DAYS BEFORE 'd'
 
    long int n2 = d.year_ * 365 + d.date_;
    for (int i = 0; i < d.month_ - 1; i++)
        n2 += monthDays[i];
    n2 += noOfLeapsBeforeD2;
 
    // return difference between two counts
   return n2 - n1;
}
//operator== check
bool Date::operator==(const Date &d) const {
    return date_==d.date_&&month_==d.month_&&year_==d.year_;
}

Date::Date(const Date &copy) : date_(copy.date_), month_(copy.month_), year_(copy.year_)
{

}
/*
Date& Date::operator=(const Date& d)
{
    date_ = d.date_; month_ = d.month_; year_ = d.year_;
    return *this;
}
*/

ostream &operator<<(ostream &out, const Date &obj)
{
    out << obj.date_ << "/" << Date::sMonthNames[obj.month_ - 1] << "/" << obj.year_;
    return out;
}
void Date::UnitTest()
{
    int testCount=20;
    bool f = true;
    
    cout << "\n\nCLASS DATE\n\n";
    //cout<<"Failed Tests:\n";
    
    //Checking the friend output streaming operator
    cout<<"TESTCASE 1: Checking the friend output streaming operator : ";
    string outputGolden="25/Jul/2021";
    stringstream ss;
    Date dTest(25,7,2021);
    ss<<dTest;
    if(ss.str()!=outputGolden)
    {
        f=false;
        cout<<"FAIL on calling ostream operator<< for Date\n";
    }
    else 
    {
        cout<<"PASS\n";
    }

    //Check 'Date' construction
    cout<<"TESTCASE 2: CCheck 'Date' construction : ";
    Date dateObj(1, 1, 2001);
    if (dateObj.date_ != 1 || dateObj.month_ != static_cast<Month>(1) || dateObj.year_ != 2001){ //Check if Date matches
        cout << "FAIL Date Construction Error on Date(1,1,2001)\n";
        f=false;
        
    }
    else 
    {
        cout<<"PASS\n";
    }

    //Check 'Date' copy construction
    cout<<"TESTCASE 3: CCheck 'Date' construction : ";
    Date dateObj2(dateObj);
    if(dateObj2.date_ != dateObj.date_ || dateObj2.month_ != dateObj.month_ || dateObj2.year_ != dateObj.year_){ //Check if dateObj, dateObj2 matches
        cout<<"FAIL : Date Copy Construction Error on Date(1,1,2001)\n";
        f=false;
        
    }
    else 
    {
        cout<<"PASS\n";
    }
    //Checking GetDay()
    cout<<"TESTCASE 4: Checking GetDay() : ";
    if(dateObj.GetDay()!=1)
    {
        cout<<"FAIL : GetDay() not working for 1-1-2001\n";
        f=false;
        
    }
    else 
    {
        cout<<"PASS\n";
    }
    //Checking GetMonth()
    cout<<"TESTCASE 5: Checking  GetMonth() : ";
    if(dateObj.GetMonth()!=1)
    {
        cout<<"FAIL : GetMonth() not working for 1-1-2001\n";
        f=false;
        
    }
    else 
    {
        cout<<"PASS\n";
    }
    //Checking GetYear()
    cout<<"TESTCASE 6: Checking GetYear() : ";
    if(dateObj.GetYear()!=2001)
    {
        cout<<"FAIL : GetYear() not working for 1-1-2001\n";
        f=false;
        
    }
    else 
    {
        cout<<"PASS\n";
    }
    //Checking IsLeapYear() - Non Leap Year
    cout<<"TESTCASE 7: Checking IsLeapYear() - Non Leap Year : ";
    if(dateObj.IsLeapYear())
    {
        cout<<"FAIL : IsLeapYear() Not Working for 2001\n";
        f=false;
        
    }
    else 
    {
        cout<<"PASS\n";
    }
    // Check for leap year - Non leap year
    cout<<"TESTCASE 8: Check for leap year - Non leap year : ";
    Date dateObjy2 = Date(1,1,1900);
    if(dateObjy2.IsLeapYear())
    {
        cout<<"FAIL : IsLeapYear() Not Working for 1900\n";
        
    }
    else 
    {
        cout<<"PASS\n";
    }
    // Check for leap year - leap year
    cout<<"TESTCASE 9: Check for leap year - leap year : ";
    Date dateObjy = Date(1,1,2000);
    if(!dateObjy.IsLeapYear())
    {
        cout<<"FAIL : IsLeapYear() Not Working for 2000\n";
        f=false;
        
    }
    else 
    {
        cout<<"PASS\n";
    }
    cout<<"TESTCASE 10: Check for leap year - leap year : ";
    // Check for leap year - leap year
    Date dateObj3 = Date(1,1,2004);
    if(!dateObj3.IsLeapYear())
    {
        cout<<"FAIL IsLeapYear() Not Working for 2004\n";
        f=false;  
    }
    else 
    {
        cout<<"PASS\n";
    }
    //Calculate Age Check
    cout<<"TESTCASE 11: Calculate Age Check : ";
    if(dateObjy2.CalculateAge()!=121)
    {
        cout<<"FAIL : Calculate Age not Working for 1-1-1900\n";
        f=false;
    }
    else 
    {
        cout<<"PASS\n";
    }
    //Calculate Span Check (includes leap years also)
    cout<<"TESTCASE 12: Calculate Span Check (includes leap years also) : ";
    if(dateObjy2.CalculateSpan(dateObj)!=36890)
    {
        cout<<dateObjy2.CalculateSpan(dateObj);
        cout<<"FAIL : Calculate Span not Working \n";
        f=false;
    }
    else 
    {
        cout<<"PASS\n";
    }
    //Calcualate Span without leap years
    cout<<"TESTCASE 13: Calcualate Span without leap years : ";
    if(Date::Today().CalculateSpan(Date::Today())!=0)
    {
        cout<<"FAIL : Calculate Span not Working \n";
        f=false;
    }
    else 
    {
        cout<<"PASS\n";
    }

    //Date Today cannot be verified here, will throw errors on checking
    cout<<"TESTCASE 14: Copy Assignment Operator : ";
    //== operator
    if(!(Date::Today()==Date::Today()))
    {
        cout<<"FAIL\n";
        f=false;
    }
    else 
    {
        cout<<"PASS\n";
    }

    cout<<"TESTCASE 15: Copy Assignment Operator - Not Equal : ";
    if(Date::Today()==dateObjy)
    {
        cout<<"== not working\n";
        f=false;
    }
    else 
    {
        cout<<"PASS\n";
    }

    //IsValid() with integer inputs
    cout<<"TESTCASE 16: IsValid() with integer inputs - Invalid Year : ";
    //Invalid Year
    try
    {
        IsValid(1,1,1000);
    }
    catch(Invalid_Year iv)
    {
        cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<iv.what()<<"\n";
        testCount--;
    }
    catch(...)
    {
        cout<<"FAIL Invalid Year 1000 throws errors\n";
    }
    //Invalid Month - +ve
    cout<<"TESTCASE 17: IsValid() with integer inputs - Invalid Month +ve : ";
    try
    {
        IsValid(1,13,2000);
    }
    catch(Invalid_Month iv)
    {
        cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<iv.what()<<"\n";
        testCount--;
    }
    catch(...)
    {
        cout<<"FAIL : Invalid Month 13 throws errors\n";
    }
    cout<<"TESTCASE 18: IsValid() with integer inputs - Invalid Month  -ve: ";
    //Invalid Month - -ve
    try
    {
        IsValid(1,-1,2000);
    }
    catch(Invalid_Month iv)
    {
        cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<iv.what()<<"\n";
        testCount--;
    }
    catch(...)
    {
        cout<<"FAIL Invalid Month -1 throws errors\n";
    }
    //Invalid Date
    cout<<"TESTCASE 19: IsValid() with integer inputs - Invalid Date : ";
    try
    {
        IsValid(0,1,2000);
    }
    catch(Invalid_Day iv)
    {
        cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<iv.what()<<"\n";
        testCount--;
    }
    catch(...)
    {
        cout<<"FAIL Invalid Date 0 throws errors\n";
    }
    //Invalid Date - 29 days in February without leap year
    cout<<"TESTCASE 20: IsValid() with integer inputs - Invalid Date - 29 days in February without leap year : ";
    try
    {
        IsValid(29,2,2001);
    }
    catch(Invalid_Day iv)
    {
        cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<iv.what()<<"\n";
        testCount--;

    }
    catch(...)
    {
        cout<<"FAIL Invalid Date 29-2-2001 throws errors\n";
    }
    cout<<"TESTCASE 21: IsValid() with integer inputs - Invalid Date - 31 days in April : ";
    //Invalid Date - 31 days in April
    try
    {
        IsValid(31,4,2001);
    }
    catch(Invalid_Day iv)
    {
        cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<iv.what()<<"\n";
        testCount--;

    }
    catch(...)
    {
        cout<<"FAIL Invalid Date 31-4-2001 throws errors\n";
    }
      //Invalid Date - 32 days in January
    cout<<"TESTCASE 22: IsValid() with integer inputs - Invalid Date - 32 days in January : ";
    try
    {
        IsValid(32,1,2001);
    }
    catch(Invalid_Day iv)
    {
        cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<iv.what()<<"\n";
        testCount--;

    }
    catch(...)
    {
        cout<<"FAIL Invalid Date 32-1-2001 throws errors\n";
    }
      //valid Date - 29 days in February in leap year
      bool test_pass = true;
    cout<<"TESTCASE 23: IsValid() with integer inputs - valid Date - 29 days in February in leap year : ";
    try
    {
        IsValid(29,2,2004);
    }
    catch(...)
    {
        f=false;
        test_pass = false;
        cout<<"FAIL : Valid date 29-2-2004 shows as Invalid\n";
    }
    if(test_pass)
    {
        cout<<"PASS\n";
    }
    test_pass = true;

     //IsValid() with string inputs
    //Invalid Year
    cout<<"TESTCASE 24: IsValid() with string inputs - Invalid Year : ";
    try
    {
        IsValid("01/01/1000");
    }
    catch(Invalid_Year iv)
    {
        cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<iv.what()<<"\n";
        testCount--;

    }
    catch(...)
    {
        cout<<"FAIL : Invalid Year 1000 throws errors\n";
    }
    //Invalid Month - +ve
    cout<<"TESTCASE 25: IsValid() with string inputs - Invalid Month - +ve: ";
    try
    {
        IsValid("01/13/2000");
    }
    catch(Invalid_Month iv)
    {
        cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<iv.what()<<"\n";
        testCount--;

    }
    catch(...)
    {
        cout<<"FAIL : Invalid Month 13 throws errors\n";
    }
    cout<<"TESTCASE 25: IsValid() with string inputs -Invalid Month -ve : ";
    //Invalid Month - -ve
    try
    {
        IsValid("01/-1/2000");
    }
    catch(Invalid_Month iv)
    {

        testCount--;
        cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<iv.what()<<"\n";

    }
    catch(...)
    {
        cout<<"FAIL : Invalid Month -1 throws errors\n";
    }
    cout<<"TESTCASE 26: IsValid() with string inputs -Invalid Date : ";
    //Invalid Date
    try
    {
        IsValid("00/01/2000");
        
    }
    catch(Invalid_Day iv)
    {

        testCount--;
        cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<iv.what()<<"\n";

    }
    catch(...)
    {
        cout<<"FAIL : Invalid Date 0 throws errors\n";
    }
    cout<<"TESTCASE 27: IsValid() with string inputs -Invalid Date - 29 days without leap year : ";
    //Invalid Date - 29 days without leap year
    try
    {
        IsValid("29/02/2001");
    }
    catch(Invalid_Day iv)
    {
        cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<iv.what()<<"\n";
        testCount--;

    }
    catch(...)
    {  
        cout<<"FAIL Invalid Date 29-2-2001 throws errors\n";
    }
    //Invalid Date - 31 days in April
    cout<<"TESTCASE 28: IsValid() with string inputs -Invalid Date - 31 days in April : ";
    try
    {
        IsValid("31/04/2001");
    }
    catch(Invalid_Day iv)
    {
         cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<iv.what()<<"\n";
        testCount--;

    }
    catch(...)
    {
        cout<<"FAIL Invalid Date 31-4-2001 throws errors\n";
    }
    cout<<"TESTCASE 29: IsValid() with string inputs -Invalid Date - 32 days in January: ";
      //Invalid Date - 32 days in January
    try
    {
        IsValid("32/01/2001");
    }
    catch(Invalid_Day iv)
    {
        cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<iv.what()<<"\n";
        testCount--;

    }
    catch(...)
    {
        cout<<"FAIL Invalid Date 32-1-2001 throws errors\n";
    }
      //valid Date - 29 days in February in leap year
      cout<<"TESTCASE 30: IsValid() with string inputs -valid Date - 29 days in February in leap year : ";
    try
    {
        IsValid("29/02/2004");
    }
    catch(...)
    {
        f=false;
        test_pass= false;
        cout<<"FALSE Valid date 29-2-2004 shows as Invalid\n";
    }
    if(test_pass)
    {
        cout<<"PASS\n";
    }
    test_pass = true;
    cout<<"TESTCASE 31: IsValid() with string inputs -invalid format - 1 : ";
    //invalid format - 1
    try
    {
        IsValid("323/01/2001");
    }
    catch(Invalid_Format iv)
    {
        test_pass= false;
        cout<<"FALSE Valid date 29-2-2004 shows as Invalid\n";
        testCount--;

    }
    catch(...)
    {
        cout<<"FAIL : Invalid Date 323-1-2001 throws errors\n";
    }
    cout<<"TESTCASE 32: IsValid() with string inputs -invalid format - 2 :";
    //invalid format - 2
    try
    {
        IsValid("31@1/2001");
    }
    catch(Invalid_Format iv)
    {
        cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<iv.what()<<"\n";
        testCount--;

    }
    catch(...)
    {
        cout<<"FAIL : Invalid Date 32-@-2001 throws errors\n";
    }
    //invalid format - 3
    cout<<"TESTCASE 33: IsValid() with string inputs -invalid format - 3 :";
    try
    {
        IsValid("a3/1/2001");
    }
    catch(Invalid_Format iv)
    {
        cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<iv.what()<<"\n";
        testCount--;

    }
    catch(...)
    {
        cout<<"FAIL : Invalid Date a3-1-2001 throws errors\n";
    }
    cout<<"TESTCASE 34: IsValid() with string inputs - invalid format - 4:";
    //invalid format - 4
    try
    {
        IsValid("1/1/2001");
    }
    catch(Invalid_Format iv)
    {
        cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<iv.what()<<"\n";
        testCount--;

    }
    catch(...)
    {
        cout<<"FAIL : Invalid Date 1-1-2001 throws errors\n";
    }

    //Get Date with invalid string
    cout<<"TESTCASE 35: IsValid() with string inputs - Get Date with invalid string :";
    try
    {
        GetDate("1/1/200");
    }
    catch(Bad_Date ex)
    {
        testCount--;
        cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<ex.what()<<"\n";
    }
    //Get date with valid string
    cout<<"TESTCASE 36: IsValid() with string inputs - Get date with valid string:";
    try
    {
        GetDate("01/01/2001");
    }
    catch(Exceptions ex)
    {
        f=false;
        test_pass = false;
        cout<<"FAIL : GetDate with date 01/01/2001 return invalid\n";
    }
    if(test_pass)
    {
        cout<<"PASS\n";
    }
    cout<<"TESTCASE 37: IsValid() with string inputs - Get Date with invalid string :";
    //Get Date with invalid input
    try
    {
        GetDate(50,1,1000);
    }
    catch(Exceptions ex)
    {

        testCount--;
        cout<<"PASS\n";
        cout<<"Expected Exception thrown "<<ex.what()<<"\n";

    }
    catch(...)
    {
        cout<<"FAIL\n";
    }
    //Get date with valid input
    test_pass = true;
    cout<<"TESTCASE 38: Get date with valid input :";
    try
    {
        GetDate(1,1,2001);
    }
    catch(Exceptions ex)
    {
        f=false;
        test_pass = false;
        cout<<"FAIL : GetDate with date 01/01/2001 return invalid\n";
    }
    if(test_pass)
    {
        cout<<"PASS\n";
    }

    cout<<"\n----- VERDICT : ";
    if(testCount!=0 || f==false)
    {
        cout<<"FAIL -----\n";
    }
    else 
    cout<<"38/38 Test cases Passed -----\n";
  
}
Date::~Date()
{
    #ifdef _DEBUG
    cout << "Date = " << *this << "  --DESTRUCTED" << endl;
    #endif
}