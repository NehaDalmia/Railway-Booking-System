

//BookingClasses.cpp

#include "BookingClasses.h"
#include "Divyaang.h"

// Names defined as static constants
template<> const string BookingClasses::ACFirstClass::sName =              "AC First Class";
template<> const string BookingClasses::ExecutiveChairCar::sName =         "Executive Chair Car";
template<> const string BookingClasses::AC2Tier::sName =                   "AC 2 Tier";
template<> const string BookingClasses::FirstClass::sName =                "First Class";
template<> const string BookingClasses::AC3Tier::sName =                   "AC 3 Tier";
template<> const string BookingClasses::ACChairCar::sName =                "AC Chair Car";
template<> const string BookingClasses::Sleeper::sName =                   "Sleeper";
template<> const string BookingClasses::SecondSitting::sName =             "Second Sitting";
// Number of Tiers defined as static constants
template<> const int BookingClasses::ACFirstClass::sNumberOfTiers =        2;
template<> const int BookingClasses::ExecutiveChairCar::sNumberOfTiers =   0;
template<> const int BookingClasses::AC2Tier::sNumberOfTiers =             2;
template<> const int BookingClasses::FirstClass::sNumberOfTiers =          2;
template<> const int BookingClasses::AC3Tier::sNumberOfTiers =             3;
template<> const int BookingClasses::ACChairCar::sNumberOfTiers =          0;
template<> const int BookingClasses::Sleeper::sNumberOfTiers =             3;
template<> const int BookingClasses::SecondSitting::sNumberOfTiers =       0;
// Sitting/Sleeping status defined as static constants
template<> const bool BookingClasses::ACFirstClass::sSitting =             false;
template<> const bool BookingClasses::ExecutiveChairCar::sSitting =        true;
template<> const bool BookingClasses::AC2Tier::sSitting =                  false;
template<> const bool BookingClasses::FirstClass::sSitting =               false;
template<> const bool BookingClasses::AC3Tier::sSitting =                  false;
template<> const bool BookingClasses::ACChairCar::sSitting =               true;
template<> const bool BookingClasses::Sleeper::sSitting =                  false;
template<> const bool BookingClasses::SecondSitting::sSitting =            true;
// AC/Non-AC status defined as static constants
template<> const bool BookingClasses::ACFirstClass::sAC =                  true;
template<> const bool BookingClasses::ExecutiveChairCar::sAC =             true;
template<> const bool BookingClasses::AC2Tier::sAC =                       true;
template<> const bool BookingClasses::FirstClass::sAC =                    false;
template<> const bool BookingClasses::AC3Tier::sAC =                       true;
template<> const bool BookingClasses::ACChairCar::sAC =                    true;
template<> const bool BookingClasses::Sleeper::sAC =                       false;
template<> const bool BookingClasses::SecondSitting::sAC =                 false;
// Tatkal Load Factor defined as static constants
template<> const double BookingClasses::ACFirstClass::sTatkalLoadFactor =          0.3;
template<> const double BookingClasses::ExecutiveChairCar::sTatkalLoadFactor =     0.3;
template<> const double BookingClasses::AC2Tier::sTatkalLoadFactor =               0.3;
template<> const double BookingClasses::FirstClass::sTatkalLoadFactor =            0.3;
template<> const double BookingClasses::AC3Tier::sTatkalLoadFactor =               0.3;
template<> const double BookingClasses::ACChairCar::sTatkalLoadFactor =            0.3;
template<> const double BookingClasses::Sleeper::sTatkalLoadFactor =               0.3;
template<> const double BookingClasses::SecondSitting::sTatkalLoadFactor =         0.1;
// Minimum Tatkal Charge defined as static constants
template<> const double BookingClasses::ACFirstClass::sMinTatkalCharge =           400.0;
template<> const double BookingClasses::ExecutiveChairCar::sMinTatkalCharge =      400.0;
template<> const double BookingClasses::AC2Tier::sMinTatkalCharge =                400.0;
template<> const double BookingClasses::FirstClass::sMinTatkalCharge =             400.0;
template<> const double BookingClasses::AC3Tier::sMinTatkalCharge =                300.0;
template<> const double BookingClasses::ACChairCar::sMinTatkalCharge =             125.0;
template<> const double BookingClasses::Sleeper::sMinTatkalCharge =                100.0;
template<> const double BookingClasses::SecondSitting::sMinTatkalCharge =          10.0;
// Maximum Tatkal Charge defined as static constants
template<> const double BookingClasses::ACFirstClass::sMaxTatkalCharge =           500.0;
template<> const double BookingClasses::ExecutiveChairCar::sMaxTatkalCharge =      500.0;
template<> const double BookingClasses::AC2Tier::sMaxTatkalCharge =                500.0;
template<> const double BookingClasses::FirstClass::sMaxTatkalCharge =             500.0;
template<> const double BookingClasses::AC3Tier::sMaxTatkalCharge =                400.0;
template<> const double BookingClasses::ACChairCar::sMaxTatkalCharge =             225.0;
template<> const double BookingClasses::Sleeper::sMaxTatkalCharge =                200.0;
template<> const double BookingClasses::SecondSitting::sMaxTatkalCharge =          15.0;
// Minimum Tatkal Distance defined as static constants
template<> const double BookingClasses::ACFirstClass::sMinTatkalDistance =         500.0;
template<> const double BookingClasses::ExecutiveChairCar::sMinTatkalDistance =    250.0;
template<> const double BookingClasses::AC2Tier::sMinTatkalDistance =              500.0;
template<> const double BookingClasses::FirstClass::sMinTatkalDistance =           500.0;
template<> const double BookingClasses::AC3Tier::sMinTatkalDistance =              500.0;
template<> const double BookingClasses::ACChairCar::sMinTatkalDistance =           250.0;
template<> const double BookingClasses::Sleeper::sMinTatkalDistance =              500.0;
template<> const double BookingClasses::SecondSitting::sMinTatkalDistance =        100.0;

BookingClasses::BookingClasses() 
{
    #ifdef _DEBUG
    cout << "Abstract base class Booking Classes"<<" --CONSTRUCTED" << endl;
    #endif
};   //Ctor
BookingClasses::~BookingClasses() 
{
    #ifdef _DEBUG
    cout << "Abstract Base Class Booking Classes"<< "  --DESTRUCTED" << endl;
    #endif
};  //Virtual dtor for polymorphic hierarchy

ostream &operator<<(ostream &out, const BookingClasses &bclass)
{
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

template<typename T>
BookingClassTypes<T>::BookingClassTypes() {
    #ifdef _DEBUG
    cout << "Booking Class = \n" << *this << " --CONSTRUCTED" << endl;
    #endif
};

template<typename T>
BookingClassTypes<T>::~BookingClassTypes() {
    #ifdef _DEBUG
    cout << "Booking Class = \n" << *this << "  --DESTRUCTED" << endl;
    #endif
};

template<typename T>
const BookingClassTypes<T> &BookingClassTypes<T>::Type(){
    static const BookingClassTypes<T> obj;
    return obj;
}

template<typename T>
double BookingClassTypes<T>::GetConcessionForDivyaang(const Divyaang *dis) const {
    return dis->GetDivyaangConcessionFactor(*this);
}
template<typename T>
double BookingClassTypes<T>::GetLoadFactor() const {
    return BookingClassTypes<T>::sLoadFactor;
}
template<typename T>    
string BookingClassTypes<T>::GetName() const {
    return BookingClassTypes<T>::sName;
}
template<typename T>
int BookingClassTypes<T>::GetNumberOfTiers() const {
    return BookingClassTypes<T>::sNumberOfTiers;
}
template<typename T>
double BookingClassTypes<T>::GetReservationCharge() const {
    return BookingClassTypes<T>::sReservationCharge;
}
template<typename T>
bool BookingClassTypes<T>::IsAC() const {
    return BookingClassTypes<T>::sAC;
}
template<typename T>
bool BookingClassTypes<T>::IsLuxury() const {
    return BookingClassTypes<T>::sLuxury;
}
template<typename T>
bool BookingClassTypes<T>::IsSitting() const {
    return BookingClassTypes<T>::sSitting;
}
template<typename T>
double BookingClassTypes<T>::GetTatkalLoadFactor() const {
    return BookingClassTypes<T>::sTatkalLoadFactor;
}
template<typename T>
double BookingClassTypes<T>::GetMinTatkalCharge() const {
    return BookingClassTypes<T>::sMinTatkalCharge;
}
template<typename T>
double BookingClassTypes<T>::GetMaxTatkalCharge() const {
    return BookingClassTypes<T>::sMaxTatkalCharge;
}
template<typename T>
double BookingClassTypes<T>::GetMinTatkalDistance() const {
    return BookingClassTypes<T>::sMinTatkalDistance;
}

void BookingClasses::UnitTest()
{
    int totalCount = 91;
    
    cout << "\n\nCLASS BOOKINGCLASSES\n\n";
    //Test methods of BookingClasses::AC3Tier

    const BookingClasses::AC3Tier &AC3TierObj = BookingClasses::AC3Tier::Type();
    double loadFactorTest = AC3TierObj.GetLoadFactor();
    double rChargeTest = AC3TierObj.GetReservationCharge();
    string nameTest = AC3TierObj.GetName();
    bool ACTest = AC3TierObj.IsAC();
    bool luxuryTest = AC3TierObj.IsLuxury();
    bool sittingTest = AC3TierObj.IsSitting();
    int numTest = AC3TierObj.GetNumberOfTiers();
    double resTest = AC3TierObj.GetReservationCharge();
    double tLoadTest = AC3TierObj.GetTatkalLoadFactor();
    double tMinCharge = AC3TierObj.GetMinTatkalCharge();
    double tMaxCharge = AC3TierObj.GetMaxTatkalCharge();
    unsigned int tMinDist = AC3TierObj.GetMinTatkalDistance();

    cout << "TESTCASE 1: AC3Tier::GetLoadFactor() returns the correct load factor: ";
    if (loadFactorTest == 2.5)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 2: AC3Tier::GetName() returns the correct name: ";
    if (nameTest == "AC 3 Tier")
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 3: AC3Tier::IsAC() returns correct AC status: ";
    if (ACTest == true)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 4: AC3Tier::IsLuxury() returns correct luxury status: ";
    if (luxuryTest == false)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 5: AC3Tier::IsSitting() returns correct sitting status: ";
    if (sittingTest == false)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 6: AC3Tier::GetNumberOfTiers() returns the correct number of tiers: ";
    if (numTest == 3)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 7: AC3Tier::GetReservationCharge() returns the correct reservation charge: ";
    if (resTest == 40)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 8: AC3Tier::GetTatkalLoadFactor() returns the correct tatkal load factor: ";
    if (tLoadTest == 0.3)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 9: AC3Tier::GetMinTatkalCharge() returns the correct minimum tatkal charge: ";
    if (tMinCharge == 300)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 10: AC3Tier::GetMaxTatkalCharge() returns the correct maximum tatkal charge: ";
    if (tMaxCharge == 400)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 11: AC3Tier::GetMinTatkalDist() returns the correct minimum tatkal distance: ";
    if (tMinDist == 500)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    //Test methods of BookingClasses::Sleeper

    const BookingClasses::Sleeper &SleeperObj = BookingClasses::Sleeper::Type();
    loadFactorTest = SleeperObj.GetLoadFactor();
    rChargeTest = SleeperObj.GetReservationCharge();
    nameTest = SleeperObj.GetName();
    ACTest = SleeperObj.IsAC();
    luxuryTest = SleeperObj.IsLuxury();
    sittingTest = SleeperObj.IsSitting();
    numTest = SleeperObj.GetNumberOfTiers();
    resTest = SleeperObj.GetReservationCharge();
    tLoadTest = SleeperObj.GetTatkalLoadFactor();
    tMinCharge = SleeperObj.GetMinTatkalCharge();
    tMaxCharge = SleeperObj.GetMaxTatkalCharge();
    tMinDist = SleeperObj.GetMinTatkalDistance();

    cout << "TESTCASE 12: Sleeper::GetLoadFactor() returns the correct load factor: ";
    if (loadFactorTest == 1)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 13: Sleeper::GetName() returns the correct name: ";
    if (nameTest == "Sleeper")
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 14: Sleeper::IsAC() returns correct AC status: ";
    if (ACTest == false)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 15: Sleeper::IsLuxury() returns correct luxury status: ";
    if (luxuryTest == false)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 16: Sleeper::IsSitting() returns correct sitting status: ";
    if (sittingTest == false)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 17: Sleeper::GetNumberOfTiers() returns the correct number of tiers: ";
    if (numTest == 3)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 18: Sleeper::GetReservationCharge() returns the correct reservation charge: ";
    if (resTest == 20)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 19: Sleeper::GetTatkalLoadFactor() returns the correct tatkal load factor: ";
    if (tLoadTest == 0.3)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 20: Sleeper::GetMinTatkalCharge() returns the correct minimum tatkal charge: ";
    if (tMinCharge == 100)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 21: Sleeper::GetMaxTatkalCharge() returns the correct maximum tatkal charge: ";
    if (tMaxCharge == 200)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 22: Sleeper::GetMinTatkalDist() returns the correct minimum tatkal distance: ";
    if (tMinDist == 500)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    //Test methods of BookingClasses::AC2Tier

    const BookingClasses::AC2Tier &AC2TierObj = BookingClasses::AC2Tier::Type();
    loadFactorTest = AC2TierObj.GetLoadFactor();
    rChargeTest = AC2TierObj.GetReservationCharge();
    nameTest = AC2TierObj.GetName();
    ACTest = AC2TierObj.IsAC();
    luxuryTest = AC2TierObj.IsLuxury();
    sittingTest = AC2TierObj.IsSitting();
    numTest = AC2TierObj.GetNumberOfTiers();
    resTest = AC2TierObj.GetReservationCharge();
    tLoadTest = AC2TierObj.GetTatkalLoadFactor();
    tMinCharge = AC2TierObj.GetMinTatkalCharge();
    tMaxCharge = AC2TierObj.GetMaxTatkalCharge();
    tMinDist = AC2TierObj.GetMinTatkalDistance();

    cout << "TESTCASE 23: AC2Tier::GetLoadFactor() returns the correct load factor: ";
    if (loadFactorTest == 4)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 24: AC2Tier::GetName() returns the correct name: ";
    if (nameTest == "AC 2 Tier")
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 25: AC2Tier::IsAC() returns correct AC status: ";
    if (ACTest == true)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 26: AC2Tier::IsLuxury() returns correct luxury status: ";
    if (luxuryTest == false)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 27: AC2Tier::IsSitting() returns correct sitting status: ";
    if (sittingTest == false)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 28: AC2Tier::GetNumberOfTiers() returns the correct number of tiers: ";
    if (numTest == 2)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 29: AC2Tier::GetReservationCharge() returns the correct reservation charge: ";
    if (resTest == 50)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 30: AC2Tier::GetTatkalLoadFactor() returns the correct tatkal load factor: ";
    if (tLoadTest == 0.3)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 31: AC2Tier::GetMinTatkalCharge() returns the correct minimum tatkal charge: ";
    if (tMinCharge == 400)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 32: AC2Tier::GetMaxTatkalCharge() returns the correct maximum tatkal charge: ";
    if (tMaxCharge == 500)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 33: AC2Tier::GetMinTatkalDist() returns the correct minimum tatkal distance: ";
    if (tMinDist == 500)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    //Test methods of BookingClasses::ACFirstClass
    
    const BookingClasses::ACFirstClass &ACFirstClassObj = BookingClasses::ACFirstClass::Type();
    loadFactorTest = ACFirstClassObj.GetLoadFactor();
    rChargeTest = ACFirstClassObj.GetReservationCharge();
    nameTest = ACFirstClassObj.GetName();
    ACTest = ACFirstClassObj.IsAC();
    luxuryTest = ACFirstClassObj.IsLuxury();
    sittingTest = ACFirstClassObj.IsSitting();
    numTest = ACFirstClassObj.GetNumberOfTiers();
    resTest = ACFirstClassObj.GetReservationCharge();
    tLoadTest = ACFirstClassObj.GetTatkalLoadFactor();
    tMinCharge = ACFirstClassObj.GetMinTatkalCharge();
    tMaxCharge = ACFirstClassObj.GetMaxTatkalCharge();
    tMinDist = ACFirstClassObj.GetMinTatkalDistance();

    cout << "TESTCASE 34: ACFirstClass::GetLoadFactor() returns the correct load factor: ";
    if (loadFactorTest == 6.5)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 35: ACFirstClass::GetName() returns the correct name: ";
    if (nameTest == "AC First Class")
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 36: ACFirstClass::IsAC() returns correct AC status: ";
    if (ACTest == true)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 37: ACFirstClass::IsLuxury() returns correct luxury status: ";
    if (luxuryTest == true)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 38: ACFirstClass::IsSitting() returns correct sitting status: ";
    if (sittingTest == false)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 39: ACFirstClass::GetNumberOfTiers() returns the correct number of tiers: ";
    if (numTest == 2)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 40: ACFirstClass::GetReservationCharge() returns the correct reservation charge: ";
    if (resTest == 60)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 41: ACFirstClass::GetTatkalLoadFactor() returns the correct tatkal load factor: ";
    if (tLoadTest == 0.3)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 42: ACFirstClass::GetMinTatkalCharge() returns the correct minimum tatkal charge: ";
    if (tMinCharge == 400)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 43: ACFirstClass::GetMaxTatkalCharge() returns the correct maximum tatkal charge: ";
    if (tMaxCharge == 500)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 44: ACFirstClass::GetMinTatkalDist() returns the correct minimum tatkal distance: ";
    if (tMinDist == 500)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    //Test methods of BookingClasses::FirstClass
    
    const BookingClasses::FirstClass &FirstClassObj = BookingClasses::FirstClass::Type();
    loadFactorTest = FirstClassObj.GetLoadFactor();
    rChargeTest = FirstClassObj.GetReservationCharge();
    nameTest = FirstClassObj.GetName();
    ACTest = FirstClassObj.IsAC();
    luxuryTest = FirstClassObj.IsLuxury();
    sittingTest = FirstClassObj.IsSitting();
    numTest = FirstClassObj.GetNumberOfTiers();
    resTest = FirstClassObj.GetReservationCharge();
    tLoadTest = FirstClassObj.GetTatkalLoadFactor();
    tMinCharge = FirstClassObj.GetMinTatkalCharge();
    tMaxCharge = FirstClassObj.GetMaxTatkalCharge();
    tMinDist = FirstClassObj.GetMinTatkalDistance();

    cout << "TESTCASE 45: FirstClass::GetLoadFactor() returns the correct load factor: ";
    if (loadFactorTest == 3)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 46: FirstClass::GetName() returns the correct name: ";
    if (nameTest == "First Class")
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 47: FirstClass::IsAC() returns correct AC status: ";
    if (ACTest == false)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 48: FirstClass::IsLuxury() returns correct luxury status: ";
    if (luxuryTest == true)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 49: FirstClass::IsSitting() returns correct sitting status: ";
    if (sittingTest == false)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 50: FirstClass::GetNumberOfTiers() returns the correct number of tiers: ";
    if (numTest == 2)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 51: FirstClass::GetReservationCharge() returns the correct reservation charge: ";
    if (resTest == 50)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 52: FirstClass::GetTatkalLoadFactor() returns the correct tatkal load factor: ";
    if (tLoadTest == 0.3)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 53: FirstClass::GetMinTatkalCharge() returns the correct minimum tatkal charge: ";
    if (tMinCharge == 400)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 54: FirstClass::GetMaxTatkalCharge() returns the correct maximum tatkal charge: ";
    if (tMaxCharge == 500)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 55: FirstClass::GetMinTatkalDist() returns the correct minimum tatkal distance: ";
    if (tMinDist == 500)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    //Test methods of BookingClasses::ACChairCar

    const BookingClasses::ACChairCar &ACChairCarObj = BookingClasses::ACChairCar::Type();
    loadFactorTest = ACChairCarObj.GetLoadFactor();
    rChargeTest = ACChairCarObj.GetReservationCharge();
    nameTest = ACChairCarObj.GetName();
    ACTest = ACChairCarObj.IsAC();
    luxuryTest = ACChairCarObj.IsLuxury();
    sittingTest = ACChairCarObj.IsSitting();
    numTest = ACChairCarObj.GetNumberOfTiers();
    resTest = ACChairCarObj.GetReservationCharge();
    tLoadTest = ACChairCarObj.GetTatkalLoadFactor();
    tMinCharge = ACChairCarObj.GetMinTatkalCharge();
    tMaxCharge = ACChairCarObj.GetMaxTatkalCharge();
    tMinDist = ACChairCarObj.GetMinTatkalDistance();

    cout << "TESTCASE 56: ACChairCar::GetLoadFactor() returns the correct load factor: ";
    if (loadFactorTest == 2)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 57: ACChairCar::GetName() returns the correct name: ";
    if (nameTest == "AC Chair Car")
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 58: ACChairCar::IsAC() returns correct AC status: ";
    if (ACTest == true)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 59: ACChairCar::IsLuxury() returns correct luxury status: ";
    if (luxuryTest == false)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 60: ACChairCar::IsSitting() returns correct sitting status: ";
    if (sittingTest == true)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 61: ACChairCar::GetNumberOfTiers() returns the correct number of tiers: ";
    if (numTest == 0)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 62: ACChairCar::GetReservationCharge() returns the correct reservation charge: ";
    if (resTest == 40)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 63: ACChairCar::GetTatkalLoadFactor() returns the correct tatkal load factor: ";
    if (tLoadTest == 0.3)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 64: ACChairCar::GetMinTatkalCharge() returns the correct minimum tatkal charge: ";
    if (tMinCharge == 125)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 65: ACChairCar::GetMaxTatkalCharge() returns the correct maximum tatkal charge: ";
    if (tMaxCharge == 225)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 66: ACChairCar::GetMinTatkalDist() returns the correct minimum tatkal distance: ";
    if (tMinDist == 250)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    //Test methods of BookingClasses::SecondSitting

    const BookingClasses::SecondSitting &SecondSittingObj = BookingClasses::SecondSitting::Type();
    loadFactorTest = SecondSittingObj.GetLoadFactor();
    rChargeTest = SecondSittingObj.GetReservationCharge();
    nameTest = SecondSittingObj.GetName();
    ACTest = SecondSittingObj.IsAC();
    luxuryTest = SecondSittingObj.IsLuxury();
    sittingTest = SecondSittingObj.IsSitting();
    numTest = SecondSittingObj.GetNumberOfTiers();
    resTest = SecondSittingObj.GetReservationCharge();
    tLoadTest = SecondSittingObj.GetTatkalLoadFactor();
    tMinCharge = SecondSittingObj.GetMinTatkalCharge();
    tMaxCharge = SecondSittingObj.GetMaxTatkalCharge();
    tMinDist = SecondSittingObj.GetMinTatkalDistance();

    cout << "TESTCASE 67: SecondSitting::GetLoadFactor() returns the correct load factor: ";
    if (loadFactorTest == 0.6)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 68: SecondSitting::GetName() returns the correct name: ";
    if (nameTest == "Second Sitting")
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 69: SecondSitting::IsAC() returns correct AC status: ";
    if (ACTest == false)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 70: SecondSitting::IsLuxury() returns correct luxury status: ";
    if (luxuryTest == false)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 71: SecondSitting::IsSitting() returns correct sitting status: ";
    if (sittingTest == true)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 72: SecondSitting::GetNumberOfTiers() returns the correct number of tiers: ";
    if (numTest == 0)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 73: SecondSitting::GetReservationCharge() returns the correct reservation charge: ";
    if (resTest == 15)
    {
        totalCount--;
    }
    else{
        cout << "Test failed when calling SecondSitting::GetReservationCharge() \n";
    }

    cout << "TESTCASE 74: SecondSitting::GetTatkalLoadFactor() returns the correct tatkal load factor: ";
    if (tLoadTest == 0.1)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 75: SecondSitting::GetMinTatkalCharge() returns the correct minimum tatkal charge: ";
    if (tMinCharge == 10)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 76: SecondSitting::GetMaxTatkalCharge() returns the correct maximum tatkal charge: ";
    if (tMaxCharge == 15)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 77: SecondSitting::GetMinTatkalDist() returns the correct minimum tatkal distance: ";
    if (tMinDist == 100)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    //Test methods of BookingClasses::ExecutiveChairCar

    const BookingClasses::ExecutiveChairCar &ExecutiveChairCarObj = BookingClasses::ExecutiveChairCar::Type();
    loadFactorTest = ExecutiveChairCarObj.GetLoadFactor();
    rChargeTest = ExecutiveChairCarObj.GetReservationCharge();
    nameTest = ExecutiveChairCarObj.GetName();
    ACTest = ExecutiveChairCarObj.IsAC();
    luxuryTest = ExecutiveChairCarObj.IsLuxury();
    sittingTest = ExecutiveChairCarObj.IsSitting();
    numTest = ExecutiveChairCarObj.GetNumberOfTiers();
    resTest = ExecutiveChairCarObj.GetReservationCharge();
    tLoadTest = ExecutiveChairCarObj.GetTatkalLoadFactor();
    tMinCharge = ExecutiveChairCarObj.GetMinTatkalCharge();
    tMaxCharge = ExecutiveChairCarObj.GetMaxTatkalCharge();
    tMinDist = ExecutiveChairCarObj.GetMinTatkalDistance();

    cout << "TESTCASE 78: ExecutiveChairCar::GetLoadFactor() returns the correct load factor: ";
    if (loadFactorTest == 5)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 79: ExecutiveChairCar::GetName() returns the correct name: ";
    if (nameTest == "Executive Chair Car")
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 80: ExecutiveChairCar::IsAC() returns correct AC status: ";
    if (ACTest == true)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 81: ExecutiveChairCar::IsLuxury() returns correct luxury status: ";
    if (luxuryTest == true)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 82: ExecutiveChairCar::IsSitting() returns correct sitting status: ";
    if (sittingTest == true)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 83: ExecutiveChairCar::GetNumberOfTiers() returns the correct number of tiers: ";
    if (numTest == 0)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 84: ExecutiveChairCar::GetReservationCharge() returns the correct reservation charge: ";
    if (resTest == 60)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 85: ExecutiveChairCar::GetTatkalLoadFactor() returns the correct tatkal load factor: ";
    if (tLoadTest == 0.3)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    cout << "TESTCASE 86: ExecutiveChairCar::GetMinTatkalCharge() returns the correct minimum tatkal charge: ";
    if (tMinCharge == 400)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 87: ExecutiveChairCar::GetMaxTatkalCharge() returns the correct maximum tatkal charge: ";
    if (tMaxCharge == 500)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout << "TESTCASE 88: ExecutiveChairCar::GetMinTatkalDist() returns the correct minimum tatkal distance: ";
    if (tMinDist == 250)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    //Test Output streaming operator for BookingClassTypes<T>
    
    string outputGolden="Called From: AC 2 Tier\nTravel Class = AC 2 Tier\n : Mode: Sleeping\n : Comfort: AC\n : Bunks: 2\n : Luxury: No\n";
    stringstream ss;
    const BookingClasses::AC2Tier& aTest = AC2Tier::Type(); 
    ss<<aTest;
    cout << "TESTCASE 89: Output streaming operator for BookingClasses<T> (BookingClasses::AC2Tier): ";
    if(ss.str()==outputGolden)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    // Test on BookingClasses
    // Test working of polymorphic hierarchy by comparing the GetName() function return value
    cout << "TESTCASE 90: Testing the correct working of polymorphic heirarchy (using GetName()): ";
    const BookingClasses &obj = BookingClasses::AC3Tier::Type();
    if(obj.GetName()=="AC 3 Tier") {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    //Test Output streaming operator for BookingClasses
    cout << "TESTCASE 91: Output streaming operator for BookingClasses: ";
    outputGolden="Travel Class = AC 2 Tier\n : Mode: Sleeping\n : Comfort: AC\n : Bunks: 2\n : Luxury: No\n";
    const BookingClasses& bTest = AC2Tier::Type(); 
    stringstream ss_;
    ss_<<bTest;
    if(ss_.str()==outputGolden)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }

    cout<<"\n----- VERDICT : ";
    if(totalCount==0)
    {
        cout<<"91/91 test cases passed -----\n";
    }
    else 
    {
        cout<<totalCount<<"/91 Tests FAILED -----\n";
    }
}
