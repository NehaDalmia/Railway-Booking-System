#include "Booking.h"
#include "BookingCategory.h"
#include "Exceptions.h"
#include "Divyaang.h"

template<> const string BookingCategory::General::sName = "General";
template<> const string BookingCategory::Ladies::sName = "Ladies";
template<> const string BookingCategory::SeniorCitizen::sName = "Senior Citizen";
template<> const string BookingCategory::DivyaangCat::sName = "Divyaang";
template<> const string BookingCategory::Tatkal::sName = "Tatkal";
template<> const string BookingCategory::PremiumTatkal::sName = "Premium Tatkal";

// template<typename T>
// Booking *BookingCategoryTypes<T>::ReserveInCategory(const Station &fromStation, const Station &toStation, const Date &dateOfBooking, const Date &dateOfReservation, const BookingClasses &bookingClass, const Passenger &passenger) const {
//     if(BookingTypes<T>::CheckEligibility(passenger, BookingCategoryTypes<T>::Type(),dateOfReservation, dateOfBooking))
//         return new BookingTypes<T>(fromStation, toStation, dateOfBooking, dateOfReservation, bookingClass, BookingCategoryTypes<T>::Type(), passenger);
//     return NULL;
// }

BookingCategory::BookingCategory() 
{
    #ifdef _DEBUG
    cout << "Abstract Base Class Booking Category"<< "  --CONSTRUCTED" << endl;
    #endif
}

BookingCategory::~BookingCategory() 
{
    #ifdef _DEBUG
    cout << "Abstract Base Class Booking Category"<< "  --DESTRUCTED" << endl;
    #endif
}

ostream &operator<<(ostream &out, const BookingCategory &bcat)
{
    out << "Booking Category = " << bcat.GetName();
    return out;
}
//General Category Eligibility
template<>
void BookingCategory::General::Eligibility(const Passenger &passenger, const Date& dateOfReservation, const Date& dateOfBooking) const
{
    //Various Conditions as described in UnitTest
    if(passenger.dateOfBirth_.CalculateSpan(dateOfReservation)<0)
        throw Bad_Chronology("Please enter a passenger who has been born");
    if(dateOfReservation.CalculateSpan(dateOfBooking)<0)
        throw Bad_Chronology("Date of Reservation must be either same as or before date of Booking");
    Date d = Date::GetDate(dateOfReservation.GetDay(),dateOfReservation.GetMonth(), dateOfReservation.GetYear()+1);
    if(d.CalculateSpan(dateOfBooking)>0)
        throw Bad_Chronology("Date of Reservation and Booking must be within 1 year");
}
//Specialised BookingCategory Ladies
template<>
void BookingCategory::Ladies::Eligibility(const Passenger &passenger, const Date& dateOfReservation, const Date& dateOfBooking) const
{
     //Various Conditions as described in UnitTest
    if(passenger.dateOfBirth_.CalculateSpan(dateOfReservation)<0)
        throw Bad_Chronology("Please enter a passenger who has been born");
    if(dateOfReservation.CalculateSpan(dateOfBooking)<0)
        throw Bad_Chronology("Date of Reservation must be either same as or before date of Booking");
    Date d = Date::GetDate(dateOfReservation.GetDay(),dateOfReservation.GetMonth(), dateOfReservation.GetYear()+1);
    if(d.CalculateSpan(dateOfBooking)>0)
        throw Bad_Chronology("Date of Reservation and Booking must be within 1 year");

    if(passenger.gender_.GetName()=="Male")
    {
        if(passenger.dateOfBirth_.CalculateAge()>12)
            throw Ineligible_Ladies_Category("Booking Error: Male of Age greater than 12");
    }
}
//SeniorCitizen Category Eligibility

template<>
void BookingCategory::SeniorCitizen::Eligibility(const Passenger &passenger, const Date& dateOfReservation, const Date& dateOfBooking) const
{
     //Various Conditions as described in UnitTest
    if(passenger.dateOfBirth_.CalculateSpan(dateOfReservation)<0)
        throw Bad_Chronology("Please enter a passenger who has been born");
    if(dateOfReservation.CalculateSpan(dateOfBooking)<0)
        throw Bad_Chronology("Date of Reservation must be either same as or before date of Booking");
    Date d = Date::GetDate(dateOfReservation.GetDay(),dateOfReservation.GetMonth(), dateOfReservation.GetYear()+1);
    if(d.CalculateSpan(dateOfBooking)>0)
        throw Bad_Chronology("Date of Reservation and Booking must be within 1 year");
    if(passenger.gender_.GetName()=="Male")
    {
        if(passenger.dateOfBirth_.CalculateAge()<60)
        throw Ineligible_SeniorCitizen_Category("Booking Error: Male of Age less than 60 years");
    }
    else 
    if(passenger.gender_.GetName()=="Female")
    {
        if(passenger.dateOfBirth_.CalculateAge()<58)
            throw Ineligible_SeniorCitizen_Category("Booking Error: Female of Age less than 58 years");
    }
}
//Divyaang eligibility
template<>
void BookingCategory::DivyaangCat::Eligibility(const Passenger &passenger, const Date& dateOfReservation, const Date& dateOfBooking) const
{
     //Various Conditions as described in UnitTest
    if(passenger.dateOfBirth_.CalculateSpan(dateOfReservation)<0)
    throw Bad_Chronology("Please enter a passenger who has been born");
    if(dateOfReservation.CalculateSpan(dateOfBooking)<0)
    throw Bad_Chronology("Date of Reservation must be either same as or before date of Booking");
    Date d = Date::GetDate(dateOfReservation.GetDay(),dateOfReservation.GetMonth(), dateOfReservation.GetYear()+1);
    if(d.CalculateSpan(dateOfBooking)>0)
    throw Bad_Chronology("Date of Reservation and Booking must be within 1 year");
    if(passenger.disabilityType_ == NULL || passenger.disabilityID_=="")
    throw Ineligible_Divyaang_Category("Passenger does not have a valid Disability Type and/or DivyaangID");
}
//Tatkal Eligibility
template<>
void BookingCategory::Tatkal::Eligibility(const Passenger &passenger, const Date& dateOfReservation, const Date& dateOfBooking) const
{
     //Various Conditions as described in UnitTest
    if(passenger.dateOfBirth_.CalculateSpan(dateOfReservation)<0)
    throw Bad_Chronology("Please enter a passenger who has been born");
    if(dateOfReservation.CalculateSpan(dateOfBooking)<0)
    throw Bad_Chronology("Date of Reservation must be either same as or before date of Booking");
    Date d = Date::GetDate(dateOfReservation.GetDay(),dateOfReservation.GetMonth(), dateOfReservation.GetYear()+1);
    if(d.CalculateSpan(dateOfBooking)>0)
    throw Bad_Chronology("Date of Reservation and Booking must be within 1 year");
    if(dateOfReservation.CalculateSpan(dateOfBooking)>1)
    throw Ineligible_Tatkal_Category("Tatkal Booking attempted with a gap greater than 1 Day");
}
//Premium Tatkal Eligibility
template<>
void BookingCategory::PremiumTatkal::Eligibility(const Passenger &passenger, const Date& dateOfReservation, const Date& dateOfBooking) const
{
     //Various Conditions as described in UnitTest
    if(passenger.dateOfBirth_.CalculateSpan(dateOfReservation)<0)
    throw Bad_Chronology("Please enter a passenger who has been born");
    if(dateOfReservation.CalculateSpan(dateOfBooking)<0)
    throw Bad_Chronology("Date of Reservation must be either same as or before date of Booking");
    Date d = Date::GetDate(dateOfReservation.GetDay(),dateOfReservation.GetMonth(), dateOfReservation.GetYear()+1);
    if(d.CalculateSpan(dateOfBooking)>0)
    throw Bad_Chronology("Date of Reservation and Booking must be within 1 year");
    if(dateOfReservation.CalculateSpan(dateOfBooking)>1)
    throw Ineligible_PremiumTatkal_Category("Tatkal Booking attempted with a gap greater than 1 Day");
}
//Unit Tests
void BookingCategory::UnitTest()
{
    cout<<"\n\nCLASS BOOKING CATEGORY\n\n";
    //Constructor Destructorare checked in Application Test
    int totalCount = 22;
    bool f = true;
    Passenger p1 = Passenger::GetPassenger(Name("Bob","Dylan"),Date::GetDate(5,1,1999),Gender::Male::Type(),"123456789123","0123456789",&Divyaang::Blind::Type(),"e");
    Passenger p2 = Passenger::GetPassenger(Name("Priyanka","Chopra"),Date::GetDate(5,1,1950),Gender::Female::Type(),"123456789123","0123456789",&Divyaang::Blind::Type(),"e");
    //Checking Eligibilty
    //1. BookingCategory::General::Eligibility
    //Date of Reservation after Date of Booking
    cout<<"TESTCASE 1:  BookingCategory::General::Eligibility throws correct error : ";
    try
    {
        BookingCategory::General::Type().Eligibility(p2, Date::Today(), Date::GetDate(3,5,1900));
    }
    catch(Bad_Chronology bc)
    {
        totalCount--;
        cout<<"PASS\n Exception thrown: "<<bc.what()<<"\n";
    }
    catch(Exceptions ex)
    {
        cout<<"FAIL\n Incorrect Exception thrown: "<<ex.what()<<"\n";
    }
    
    //Date of Reservation more than an year before Booking
    cout<<"TESTCASE 2:  BookingCategory::General::Eligibility throws correct error : ";
    try
    {
        BookingCategory::General::Type().Eligibility(p2, Date::Today(), Date::GetDate(3,5,2025));
    }
    catch(Bad_Chronology bc)
    {
        totalCount--;
        cout<<"PASS\n Exception thrown: "<<bc.what()<<"\n";
    }
     catch(Exceptions ex)
    {
        cout<<"FAIL\n Incorrect Exception thrown: "<<ex.what()<<"\n";
    }
    //No Error
    bool flag_check = true;
    cout<<"TESTCASE 3:  BookingCategory::General::Eligibility allows eligible passenger : ";
    try
    {
        BookingCategory::General::Type().Eligibility(p2, Date::Today(), Date::GetDate(3,6,2021));
    }
    catch(Exceptions bb)
    {
        f=false;
        flag_check = false;
        cout<<"FAIL\n Incorrect Exception thrown: "<<bb.what()<<"\n";
    }
    if(flag_check)
    {
        cout<<"PASS\n";
        totalCount++;
    }
    
    //2. BookingCategory::Ladies::Eligibility
    //Date of Reservation after Date of Booking
    cout<<"TESTCASE 4:  BookingCategory::Ladies::Eligibility Correct error thrown : ";
    try
    {
        BookingCategory::Ladies::Type().Eligibility(p2, Date::Today(), Date::GetDate(3,5,1900));
    }
    catch(Bad_Chronology bc)
    {
        totalCount--;
        cout<<"PASS\n Exception thrown: "<<bc.what()<<"\n";
    }
     catch(Exceptions ex)
    {
        cout<<"FAIL\n Incorrect Exception thrown: "<<ex.what()<<"\n";
    }
    //Date of Reservation more than an year before Booking
    cout<<"TESTCASE 5:  BookingCategory::Ladies::Eligibility Correct error thrown : ";
    try
    {
        BookingCategory::Ladies::Type().Eligibility(p2, Date::Today(), Date::GetDate(3,5,2025));
    }
    catch(Bad_Chronology bc)
    {
        totalCount--;
        cout<<"PASS\n Exception thrown: "<<bc.what()<<"\n";
    }
    catch(Exceptions ex)
    {
        cout<<"FAIL\n Incorrect Exception thrown: "<<ex.what()<<"\n";
    }
    //Male more than 12 years of age
    cout<<"TESTCASE 6:  BookingCategory::Ladies::Eligibility Correct error thrown : ";
    try
    {
        BookingCategory::Ladies::Type().Eligibility(p1, Date::Today(), Date::GetDate(3,6,2021));
    }
    catch(Ineligible_Ladies_Category bc)
    {
        totalCount--;
        cout<<"PASS\n Exception thrown: "<<bc.what()<<"\n";
    }
    catch(Exceptions ex)
    {
        cout<<"FAIL\n Incorrect Exception thrown: "<<ex.what()<<"\n";
    }
    //No Error
    cout<<"TESTCASE 7:  BookingCategory::Ladies::Eligibility allows eligible passenger : ";
    try
    {
        BookingCategory::Ladies::Type().Eligibility(p2, Date::Today(), Date::GetDate(3,6,2021));
    }
    catch(Exceptions bb)
    {
        f=false;
        flag_check = false;
        cout<<"FAIL\n Incorrect Exception thrown: "<<bb.what()<<"\n";
    }
    if(flag_check)
    {
        cout<<"PASS\n";
        totalCount++;
    }
    //3. BookingCategory::SeniorCitizen::Eligibility
    cout<<"TESTCASE 8:  BookingCategory::SeniorCitizen::Eligibility Correct error thrown : ";
    //Date of Reservation after Date of Booking
    try
    {
        BookingCategory::SeniorCitizen::Type().Eligibility(p2, Date::Today(), Date::GetDate(3,5,1900));
    }
    catch(Bad_Chronology bc)
    {
        totalCount--;
        cout<<"PASS\n Exception thrown: "<<bc.what()<<"\n";
    }
    catch(Exceptions ex)
    {
    cout<<"FAIL\n Incorrect Exception thrown: "<<ex.what()<<"\n";
    }
    cout<<"TESTCASE 9:  BookingCategory::SeniorCitizen::Eligibility Correct error thrown : ";
    //Date of Reservation more than an year before Booking
    try
    {
        BookingCategory::SeniorCitizen::Type().Eligibility(p2, Date::Today(), Date::GetDate(3,5,2025));
    }
    catch(Bad_Chronology bc)
    {
        totalCount--;
        cout<<"PASS\n Exception thrown: "<<bc.what()<<"\n";
    }
     catch(Exceptions ex)
    {
        cout<<"FAIL\n Incorrect Exception thrown: "<<ex.what()<<"\n";
    }
    cout<<"TESTCASE 10:  BookingCategory::SeniorCitizen::Eligibility Correct error thrown : ";
    //Male less than 60 years of age
    try
    {
        BookingCategory::SeniorCitizen::Type().Eligibility(Passenger::GetPassenger(Name("Bob","Dylan"),Date::GetDate(5,1,2020),Gender::Male::Type(),"123456789123","0123456789",&Divyaang::Blind::Type(),"e"), Date::Today(), Date::GetDate(3,6,2021));
    }
    catch(Ineligible_SeniorCitizen_Category bc)
    {
        totalCount--;
        cout<<"PASS\n Exception thrown: "<<bc.what()<<"\n";
    }
     catch(Exceptions ex)
    {
       cout<<"FAIL\n Incorrect Exception thrown: "<<ex.what()<<"\n";
    }
    cout<<"TESTCASE 11:  BookingCategory::SeniorCitizen::Eligibility Correct error thrown : ";
    //Female less than 58 years of age
    try
    {
        BookingCategory::SeniorCitizen::Type().Eligibility(Passenger::GetPassenger(Name("Priyanka","Chopra"),Date::GetDate(5,1,2020),Gender::Female::Type(),"123456789123","0123456789",&Divyaang::Blind::Type(),"e"), Date::Today(), Date::GetDate(3,6,2021));
    }
    catch(Ineligible_SeniorCitizen_Category bc)
    {
        totalCount--;
        cout<<"PASS\n Exception thrown: "<<bc.what()<<"\n";
    }
    catch(Exceptions ex)
    {
        cout<<"FAIL\n Incorrect Exception thrown: "<<ex.what()<<"\n";
    }
    
    //No Error
    cout<<"TESTCASE 12:  BookingCategory::SeniorCitizen::Eligibility allows eligible passenger : ";
    try
    {
        BookingCategory::SeniorCitizen::Type().Eligibility(p2, Date::Today(), Date::GetDate(3,6,2021));
    }
    catch(Exceptions bc)
    {
        f=false;
        flag_check  = false;
        cout<<"FAIL\n Incorrect Exception thrown: "<<bc.what()<<"\n";
    }
    if(flag_check)
    {
        cout<<"PASS\n";
    }
    flag_check = true;
    //4. BookingCategory::Divyaang::Eligibility
    //Date of Reservation after Date of Booking
    cout<<"TESTCASE 13:  BookingCategory::DivyaangCat::Eligibility Correct error thrown : ";
    try
    {
        BookingCategory::DivyaangCat::Type().Eligibility(p2, Date::Today(), Date::GetDate(3,5,1900));
    }
    catch(Bad_Chronology bc)
    {
        cout<<"PASS\n Exception thrown: "<<bc.what()<<"\n";
        totalCount--;
    }
     catch(Exceptions ex)
    {
       cout<<"FAIL\n Incorrect Exception thrown: "<<ex.what()<<"\n";
    }
    //Date of Reservation more than an year before Booking
    cout<<"TESTCASE 14:  BookingCategory::DivyaangCat::Eligibility Correct error thrown : ";
    try
    {
        BookingCategory::DivyaangCat::Type().Eligibility(p2, Date::Today(), Date::GetDate(3,5,2025));
    }
    catch(Bad_Chronology bc)
    {
        cout<<"PASS\n Exception thrown: "<<bc.what()<<"\n";
        totalCount--;
    }
     catch(Exceptions ex)
    {
        cout<<"FAIL\n Incorrect Exception thrown: "<<ex.what()<<"\n";
    }
    cout<<"TESTCASE 15:  BookingCategory::DivyaangCat::Eligibility Correct error thrown : ";
    //Invalid Divyaang Type
    try
    {
        BookingCategory::DivyaangCat::Type().Eligibility(Passenger::GetPassenger(Name("Priyanka","Chopra"),Date::GetDate(5,1,2020),Gender::Female::Type(),"123456789123","0123456789"), Date::Today(), Date::GetDate(3,6,2021));

    }
    catch(Ineligible_Divyaang_Category id )
    {
        cout<<"PASS\n Exception thrown: "<<id.what()<<"\n";
        totalCount--;
    }
     catch(Exceptions ex)
    {
        cout<<"FAIL\n Incorrect Exception thrown: "<<ex.what()<<"\n";
    }
   
    //No Error
    cout<<"TESTCASE 16:  BookingCategory::DivyaangCat::Eligibility allows eligible passenger : ";
    try
    {
        BookingCategory::DivyaangCat::Type().Eligibility(p2, Date::Today(), Date::GetDate(3,6,2021));
    }
    catch(Exceptions bb)
    {
        f=false;
        cout<<"FAIL\n Incorrect Exception thrown: "<<bb.what()<<"\n";
    }
    if(flag_check)
    {
        cout<<"PASS\n";
    }
    flag_check = true;
    
    //5. BookingCategory::Tatkal::Eligibility
    cout<<"TESTCASE 17:  BookingCategory::Tatkal::Eligibility Correct error thrown : ";
    //Date of Reservation after Date of Booking
    try
    {
        BookingCategory::Tatkal::Type().Eligibility(p2, Date::Today(), Date::GetDate(3,5,1900));
    }
    catch(Bad_Chronology bc)
    {
        totalCount--;
        cout<<"PASS\n Exception thrown: "<<bc.what()<<"\n";
    }
    catch(Exceptions ex)
    {
        cout<<"FAIL\n Incorrect Exception thrown: "<<ex.what()<<"\n";
    }
    //Date of Reservation more than an year before Booking
    cout<<"TESTCASE 18:  BookingCategory::Tatkal::Eligibility Correct error thrown : ";
    try
    {
        BookingCategory::Tatkal::Type().Eligibility(p2, Date::Today(), Date::GetDate(3,5,2025));
    }
    catch(Bad_Chronology bc)
    {
        totalCount--;
        cout<<"PASS\n Exception thrown: "<<bc.what()<<"\n";
    }
     catch(Exceptions ex)
    {
        cout<<"FAIL\n Incorrect Exception thrown: "<<ex.what()<<"\n";
    }
    //Booking timing invalid
    cout<<"TESTCASE 19:  BookingCategory::Tatkal::Eligibility Correct error thrown : ";
    try
    {
        BookingCategory::Tatkal::Type().Eligibility(Passenger::GetPassenger(Name("Priyanka","Chopra"),Date::GetDate(5,1,2020),Gender::Male::Type(),"123456789123","0123456789",&Divyaang::Blind::Type(),"e"), Date::Today(), Date::GetDate(2,4,2022));
    }
    catch(Ineligible_Tatkal_Category bc)
    {
        totalCount--;
        cout<<"PASS\n Exception thrown: "<<bc.what()<<"\n";
    }
    catch(Exceptions ex)
    {
        cout<<"FAIL\n Incorrect Exception thrown: "<<ex.what()<<"\n";
    }
   // No Error
    cout<<"TESTCASE 20:  BookingCategory::Tatkal::Eligibility allows eligible passenger : ";
    try
    {
        BookingCategory::Tatkal::Type().Eligibility(p2, Date::Today(), Date::Today());
    }
    catch(Exceptions bc)
    {
        f=false;
        flag_check = false;
        cout<<"FAIL\n Incorrect Exception thrown: "<<bc.what()<<"\n";
    }
    if(flag_check)
    {
        cout<<"PASS\n";
    }
    flag_check = true;
    //6. BookingCategory::PremiumTatkal::Eligibility
    //Date of Reservation after Date of Booking
    cout<<"TESTCASE 21:  BookingCategory::PremiumTatkal::Eligibility Correct error thrown : ";
    try
    {
        BookingCategory::PremiumTatkal::Type().Eligibility(p2, Date::Today(), Date::GetDate(3, 5, 1900));
    }
    catch (Bad_Chronology bc)
    {
        cout<<"PASS\n Exception thrown: "<<bc.what()<<"\n";
        totalCount--;
    }
    catch (Exceptions ex)
    {
        cout<<"FAIL\n Incorrect Exception thrown: "<<ex.what()<<"\n";
    }
    
    //Date of Reservation more than an year before Booking
    cout<<"TESTCASE 22:  BookingCategory::PremiumTatkal::Eligibility Correct error thrown : ";
    try
    {
        BookingCategory::PremiumTatkal::Type().Eligibility(p2, Date::Today(), Date::GetDate(3, 5, 2025));
    }
    catch (Bad_Chronology bc)
    {
        cout<<"PASS\n Exception thrown: "<<bc.what()<<"\n";
        totalCount--;
    }
    catch (Exceptions ex)
    {
        cout<<"FAIL\n Incorrect Exception thrown: "<<ex.what()<<"\n";
    }
    //Booking timing invalid
    cout<<"TESTCASE 23:  BookingCategory::PremiumTatkal::Eligibility Correct error thrown : ";
    try
    {
        BookingCategory::PremiumTatkal::Type().Eligibility(Passenger::GetPassenger(Name("Priyanka", "", "Octopus"), Date::GetDate(5, 1, 2020), Gender::Male::Type(), "123456789123", "0123456789", &Divyaang::Blind::Type(), "e"), Date::Today(), Date::GetDate(3, 6, 2021));
    }
    catch (Ineligible_PremiumTatkal_Category bc)
    {
        cout<<"PASS\n Exception thrown: "<<bc.what()<<"\n";
        totalCount--;
    }
    catch (Exceptions ex)
    {
        cout<<"FAIL\n Incorrect Exception thrown: "<<ex.what()<<"\n";
    }
    //No Error
    cout<<"TESTCASE 24:  BookingCategory::Tatkal::Eligibility allows eligible passenger : ";
    try
    {
        BookingCategory::PremiumTatkal::Type().Eligibility(p2, Date::Today(), Date::Today());
    }
     catch(Exceptions bc)
    {
        f=false;
        flag_check = false;
        cout<<"FAIL\n Incorrect Exception thrown: "<<bc.what()<<"\n";
    }
    if(flag_check)
    {
        cout<<"PASS\n";
    }
    flag_check = true;
    cout<<"TESTCASE 25:  BookingCategory method ReserveInCategory allows eligible passenger : ";
    Booking* b1 = NULL;
    try {
        b1 = BookingCategory::General::Type().ReserveInCategory(Station::GetStation("Mumbai"),Station::GetStation("Delhi"),Date::Today(),Date::Today(), BookingClasses::ACFirstClass::Type(),p2);
    }
    catch (Bad_Booking &bk)
    {
        cout<<"FAIL\n Incorrect Exception thrown : ";
        cout<<bk.what();
    }
    if(b1==NULL)
    {
        cout<<"FAIL";
        f=false;
    }
    if(flag_check)
    {
        cout<<"PASS\n";

    }
    flag_check = true;
    cout<<"TESTCASE 26: BookingCategory method ReserveInCategory throws error for ineligible passenger : ";
    bool fx = false;
    Booking* b2 = NULL;
    try
    {
        b2 = BookingCategory::Ladies::Type().ReserveInCategory(Station::GetStation("Mumbai"),Station::GetStation("Delhi"),Date::Today(),Date::Today(), BookingClasses::ACFirstClass::Type(),p1);
    }
    catch(Bad_Booking& bk)
    {
        totalCount--;
        cout<<"PASS\n";
        fx = true;
    }
    if(fx==false)
    {
        cout<<"FAIL : Reserve in Category Test Failed, Gave  Non - Null when not supposed to\n";
    }
    // Test Output streaming operator for BookingCategoryTypes<T>
    cout<<"TESTCASE 27: Output streaming operator for BookingCategoryTypes<T> : ";
    const BookingCategory::DivyaangCat &dTest = BookingCategory::DivyaangCat::Type();
    string outputGolden = "Booking Category = Divyaang";
    stringstream ss;
    ss<<dTest;
    if(ss.str()==outputGolden)
    {   cout<<"PASS\n";
        totalCount--;
    }
    else{
        cout<<"FAIL : Test failed in calling ostream operator<< for BookingCategory::Divyaang\n";
    }
    // Test working of polymorphic hierarchy by comparing the GetName() function return value
    cout<<"TESTCASE 28: working of polymorphic hierarchy for BookingCategoryTypes<T> : ";
    const BookingCategory &obj = BookingCategory::Ladies::Type();
    if(obj.GetName()=="Ladies") {
        cout<<"PASS\n";
        totalCount--;
    }
    else{
        cout<<"FAIL\n";
    }
    // Test Output streaming operator for BookingCategory
    cout<<"TESTCASE 29: Output streaming operator for BookingCategoryTypes<T> : ";
    const BookingCategory &bTest = BookingCategory::Ladies::Type();
    outputGolden = "Booking Category = Ladies";
    stringstream ss_;
    ss_<<bTest;
    if(ss_.str()==outputGolden)
    {   
        cout<<"PASS\n";
        totalCount--;
    }
    else{
        cout<<"FAIL\n";
    }
    cout<<"\n----- VERDICT"<<" : ";
    if(f==false)
    {
        cout<<"FAIL"<<totalCount/29<<" Tests Failed -----\n";
    }
    else 
        cout<<"29/29 Tests Passed -----\n";
    
}