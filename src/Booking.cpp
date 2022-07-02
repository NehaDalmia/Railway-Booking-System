
#include "Booking.h"
#include "Station.h"
#include "Railways.h"
#include "BookingCategory.h"
#include "Exceptions.h"
#include "Passenger.h"
#include "LadiesConcession.h"
#include "SeniorCitizenConcession.h"
#include "DivyaangConcession.h"
#include "GeneralConcession.h"
#include <bits/stdc++.h>

unsigned int Booking::sBookingPNRSerial = 1;
vector<Booking *> Booking::sBookings = {};

Booking *Booking::Reserve(const Station &fromStation, const Station &toStation, const Date &dateOfBooking, const Date &dateOfReservation, const BookingClasses &bookingClass, const BookingCategory &bookingCategory, const Passenger &passenger)
{
    try{
        if(fromStation.GetName()==toStation.GetName()) 
        {
            throw Bad_Booking("Booking Error: From Station and To Station cannot be the same");
        }
    }
    catch (Bad_Booking &bk) {
        throw;
    }

    Booking *booking = NULL;
    try {
        booking = bookingCategory.ReserveInCategory(fromStation, toStation, dateOfBooking, dateOfReservation, bookingClass, passenger);
    }
    catch (Bad_Booking &bk) {
        throw;
    }
    return booking;
}

Booking::Booking(const Station &fromStation, const Station &toStation, const Date &dateOfBooking, const Date &dateOfReservation, const BookingClasses &bookingClass, const BookingCategory &bookingCategory,const Passenger &passenger) : 
fromStation_(fromStation), toStation_(toStation), dateOfBooking_(dateOfBooking), dateOfReservation_(dateOfReservation), bookingClass_(bookingClass), bookingCategory_(bookingCategory), passenger_(passenger), PNR_(sBookingPNRSerial)
{
    bookingStatus_=true;
    bookingMessage_="BOOKING SUCCESSFUL";
    #ifdef _DEBUG
    cout << "Abstract Parent Class Booking"<< "  --CONSTRUCTED" << endl;
    #endif
}

Booking::~Booking()
{
    #ifdef _DEBUG
    cout << "Abstract Parent Class Booking "<< "  --DESTRUCTED" << endl;
    #endif
}

// Constructor for the parametrized class BookingTypes
template<typename T>
BookingTypes<T>::BookingTypes(const Station &fromStation, const Station &toStation, const Date &dateOfBooking, const Date &dateOfReservation, const BookingClasses &bookingClass, const BookingCategory &bookingCategory, const Passenger &passenger):
Booking(fromStation, toStation, dateOfBooking, dateOfReservation, bookingClass, bookingCategory, passenger)
{
    Booking::sBookingPNRSerial += 1;
    bookingStatus_ = true;
    ComputeFare();
    bookingMessage_ = string("BOOKING SUCCEEDED");
    Booking::sBookings.push_back(this);
    
    #ifdef _DEBUG
    cout << "Booking = \n" << *this << " --CONSTRUCTED" << endl;
    #endif
}

// Destructor for the parametrized class BookingTypes
template<typename T>
BookingTypes<T>::~BookingTypes() 
{
    #ifdef _DEBUG
    cout <<*this << " DESTRUCTED" << endl;
    #endif
}

//Returns false if it catches a Bad_Booking else returns true
template<typename T> 
bool BookingTypes<T>::CheckEligibility(const Passenger &passenger, const BookingCategory &bookingCategory, const Date &dateOfReservation, const Date &dateOfBooking) {
    try
    {
        bookingCategory.Eligibility(passenger, dateOfReservation, dateOfBooking);
    }
    catch(Bad_Booking &bk)
    {
        throw;
    }
    return true;
}

template<>
void Booking::GeneralBooking::ComputeFare() 
{
    //General Class has no concession or extra fare
    double baseFareRate = sBaseFarePerKM;
    double baseFare = baseFareRate*(Railways::Type().GetDistance(fromStation_, toStation_));
    double loadedFare = baseFare*bookingClass_.GetLoadFactor();
    double concessionFare = loadedFare*(1 - GeneralConcession::Type().GetConcessionFactor());
    double finalFare = concessionFare + bookingClass_.GetReservationCharge();
    fare_ = static_cast<unsigned int>(round(finalFare));
}
template<>
void Booking::LadiesBooking::ComputeFare() 
{
    //Ladies can have concession
    double baseFareRate = sBaseFarePerKM;
    double baseFare = baseFareRate*(Railways::Type().GetDistance(fromStation_, toStation_));
    double loadedFare = baseFare*bookingClass_.GetLoadFactor();
    double concessionFare = loadedFare*(1 - LadiesConcession::Type().GetConcessionFactor(passenger_));
    double finalFare = concessionFare + bookingClass_.GetReservationCharge();
    fare_ = static_cast<unsigned int>(round(finalFare));
}
template<>
void Booking::SeniorCitizenBooking::ComputeFare() 
{
    //Senior Citizen has concession based on the gender
    double baseFareRate = sBaseFarePerKM;
    double baseFare = baseFareRate*(Railways::Type().GetDistance(fromStation_, toStation_));
    double loadedFare = baseFare*bookingClass_.GetLoadFactor();
    double concessionFare = 0.0;
    if(passenger_.gender_.GetName()=="Male")
    concessionFare = loadedFare*(1 - SeniorCitizenConcession::Type().GetConcessionFactor(passenger_, Gender::Male::Type() ));
    else
    if(passenger_.gender_.GetName()=="Female")
    concessionFare = loadedFare*(1 - SeniorCitizenConcession::Type().GetConcessionFactor(passenger_, Gender::Female::Type() ));
    double finalFare = concessionFare + bookingClass_.GetReservationCharge();
    fare_ = static_cast<unsigned int>(round(finalFare));
}
template<>
void Booking::TatkalBooking::ComputeFare() 
{
    //Tatkal Booking has extra cost
    double baseFareRate = sBaseFarePerKM;
    double baseFare = baseFareRate*(Railways::Type().GetDistance(fromStation_, toStation_));
    double loadedFare = baseFare*bookingClass_.GetLoadFactor();
    double premiumFare = bookingClass_.GetMinTatkalCharge();
    if(Railways::Type().GetDistance(fromStation_, toStation_)>=bookingClass_.GetMinTatkalDistance())
    {
        premiumFare = min(bookingClass_.GetMaxTatkalCharge(),loadedFare*bookingClass_.GetTatkalLoadFactor());
    }
    if(Railways::Type().GetDistance(fromStation_, toStation_)<bookingClass_.GetMinTatkalDistance())
    premiumFare = 0.0;
    double finalFare = loadedFare + premiumFare + bookingClass_.GetReservationCharge();
    fare_ = static_cast<unsigned int>(round(finalFare));
}
template<>
void Booking::PremiumTatkalBooking::ComputeFare() 
{
    //Premium tatkal has extra cost
    double baseFareRate = sBaseFarePerKM;
    double baseFare = baseFareRate*(Railways::Type().GetDistance(fromStation_, toStation_));
    double loadedFare = baseFare*bookingClass_.GetLoadFactor();
    double premiumFare = bookingClass_.GetMinTatkalCharge();
    if(Railways::Type().GetDistance(fromStation_, toStation_)>=bookingClass_.GetMinTatkalDistance())
    {
        premiumFare = min(bookingClass_.GetMaxTatkalCharge(),loadedFare*bookingClass_.GetTatkalLoadFactor());
    }
    if(Railways::Type().GetDistance(fromStation_, toStation_)<bookingClass_.GetMinTatkalDistance())
    premiumFare = 0.0;
    //Twice the premiumFare of Tatkal
    double finalFare = loadedFare + 2.0*premiumFare + bookingClass_.GetReservationCharge();
    fare_ = static_cast<unsigned int>(round(finalFare));
}

template<>
void Booking::DivyaangBooking::ComputeFare() 
{
    //Divyaang has different kinds of concessions
    double baseFareRate = sBaseFarePerKM;
    double baseFare = baseFareRate*(Railways::Type().GetDistance(fromStation_, toStation_));
    double loadedFare = baseFare*bookingClass_.GetLoadFactor();
    double concessionFare = 0.0;
    concessionFare = loadedFare*(1 - DivyaangConcession::Type().GetConcessionFactor(passenger_, bookingClass_));
    double finalFare = concessionFare + bookingClass_.GetReservationCharge();
    fare_ = static_cast<unsigned int>(round(finalFare));
}

ostream &operator<<(ostream& out, const Booking &bk) {
    out << bk.bookingMessage_;
    if (true == bk.bookingStatus_)
    {
        out << ":\n";
        out << bk.passenger_ << "\n";
        out << "-- Booking Details -- \n";
        out << "PNR Number = " << bk.PNR_ << "\n";
        out << "From Station = " << bk.fromStation_ << "\n";
        out << "To Station = " << bk.toStation_ << "\n";
        out << "Travel Date = " << bk.dateOfBooking_ << "\n";
        out << "Reservation Date = " << bk.dateOfReservation_ << "\n";
        out << bk.bookingCategory_ << "\n";
        out << bk.bookingClass_;
        out << "Fare = " << bk.fare_ << "\n";
        out << "\n";
        return out;
    }
    out << "\n";
    return out;
}
//The UnitTest() method of this class
void Booking::UnitTest() 
{
    cout<<"\n\nCLASS BOOKING\n\n";
    int testCount=27;
    Passenger p1 = Passenger::GetPassenger(Name("Priyanka","Chopra"),Date::GetDate(12,12,1988),Gender::Female::Type(),"123456789123","0123456789",&Divyaang::Blind::Type(),"e");
    Passenger p2 = Passenger::GetPassenger(Name("Nick","Jonas"),Date::GetDate(5,1,1996),Gender::Male::Type(),"123456789123","0123456789");
    // Test Booking::Reserve
    Booking *b1=NULL;
    try {
        b1 = Booking::Reserve(Station::GetStation("Mumbai"), Station::GetStation("Delhi"), Date::GetDate("02/05/2021"), Date::Today(), BookingClasses::AC2Tier::Type(), BookingCategory::Ladies::Type(),p1);
    }
    catch (Bad_Booking &bk) {
        cout<<bk.what();
    }
    bool check = true;
    if(NULL==b1) {
        check = false;
    }
    else if(b1->fromStation_.GetName()!="Mumbai") {
        check = false;
    }
    else if(b1->toStation_.GetName()!="Delhi") {
        check = false;
    }
    else if(!(b1->dateOfBooking_==Date::GetDate("02/05/2021"))) {
        check = false;
    }
    else if(!(b1->dateOfReservation_==Date::Today())) {
        check = false;
    }
    else if(b1->bookingClass_.GetName()!="AC 2 Tier") {
        check = false;
    }
    else if(b1->bookingCategory_.GetName()!="Ladies") {
        check = false;
    }
    else if(!(b1->passenger_==Passenger::GetPassenger(Name("Priyanka","Chopra"),Date::GetDate(12,12,1988),Gender::Female::Type(),"123456789123","0123456789",&Divyaang::Blind::Type(),"e"))) {
        check = false;
    }
    cout<<"TESTCASE 1: Booking::Reserve() executes reservation correctly: ";
    if(check == false) {
        cout<<"FAIL\n";
    }
    else {
        testCount--;
        cout<<"PASS\n";
    }

    check = true;
    Booking *b2=NULL;
    try
    {    
       b2 = Booking::Reserve(Station::GetStation("Bangalore"), Station::GetStation("Chennai"), Date::Today(), Date::Today(), BookingClasses::ExecutiveChairCar::Type(), BookingCategory::Tatkal::Type(),p2);
    }
    catch (Bad_Booking &bk) {
        cout<<bk.what();
    }
    if(NULL==b2) {
        check = false;
    }
    else if(b2->fromStation_.GetName()!="Bangalore") {
        check = false;
    }
    else if(b2->toStation_.GetName()!="Chennai") {
        check = false;
    }
    else if(!(b2->dateOfBooking_==Date::Today())) {
        check = false;
    }
    else if(!(b2->dateOfReservation_==Date::Today())) {
        check = false;
    }
    else if(b2->bookingClass_.GetName()!="Executive Chair Car") {
        check = false;
    }
    else if(b2->bookingCategory_.GetName()!="Tatkal") {
        check = false;
    }
    else if(!(b2->passenger_==Passenger::GetPassenger(Name("Nick","Jonas"),Date::GetDate(5,1,1996),Gender::Male::Type(),"123456789123","0123456789"))) {
        check = false;
    }
    cout<<"TESTCASE 2: Booking::Reserve() executes reservation correctly: ";
    if(check == false) {
        cout<<"FAIL\n";
    }
    else {
        testCount--;
        cout<<"PASS\n";
    }
    // Invalid case: FromStation is same as ToStation
    cout<<"TESTCASE 3 (E): Booking::Reserve() throws expected exception: ";
    Booking *b3=NULL;
    try {
        b3 = Booking::Reserve(Station::GetStation("Delhi"), Station::GetStation("Delhi"), Date::GetDate("02/05/2021"), Date::Today(), BookingClasses::AC2Tier::Type(), BookingCategory::Ladies::Type(),p1);
    }
    catch (Bad_Booking &bk){
        cout<<"PASS\n";
        cout<<"    Exception message - "<<bk.what()<<"\n";
    }
    if(NULL==b3) {
        testCount--;
    }
    else {
        cout<<"FAIL\n";
    }
    // Test Booking::ComputeFare
    Passenger p11 = Passenger::GetPassenger(Name("Oswald","Magic","Octopus"),Date::GetDate(5,1,1900),Gender::Female::Type(),"123456789123","0123456789",&Divyaang::Blind::Type(),"e");
    Passenger p21 = Passenger::GetPassenger(Name("Oswald","Magic","Octopus"),Date::GetDate(5,1,1900),Gender::Male::Type(),"123456789123","0123456789",&Divyaang::CancerPatient::Type(),"f");
    Date reser = Date::Today();
    Date book = Date::Today();
    Booking* b4=NULL;
    try {
        b4 = Booking::Reserve(Station::GetStation("Kolkata"),Station::GetStation("Delhi"),book,reser, BookingClasses::AC2Tier::Type(), BookingCategory::Ladies::Type(),p11); //Ladies Booking
    }
    catch (Bad_Booking &bk) {
        cout<<bk.what();
    }
    b4->ComputeFare();
    cout<<"TESTCASE 4: Booking::Ladies::ComputeFare() calculates fare correctly: ";
    if(b4->fare_==2994) {
        cout<<"PASS\n";
        testCount--;
    }
    else {
        cout<<"FAIL\n";
    }
    
    Booking* b5=NULL;
    try
    {
    b5 = Booking::Reserve(Station::GetStation("Mumbai"),Station::GetStation("Delhi"),book,reser, BookingClasses::AC3Tier::Type(), BookingCategory::General::Type(),p11);  //General Booking
    }
    catch (Bad_Booking &bk) {
        cout<<bk.what();
    }
    b5->ComputeFare();
    cout<<"TESTCASE 5: Booking::General::ComputeFare() calculates fare correctly: ";
    if(b5->fare_==1849) {
        cout<<"PASS\n";
        testCount--;
    }
    else {
        cout<<"FAIL\n";
    }
    
    Booking *b6=NULL;
    try{
        b6 = Booking::Reserve(Station::GetStation("Mumbai"),Station::GetStation("Delhi"),book,reser, BookingClasses::ACFirstClass::Type(), BookingCategory::General::Type(),p11); //General Booking
    }
    catch (Bad_Booking &bk) {
        cout<<bk.what();
    }
    b6->ComputeFare();
    cout<<"TESTCASE 6: Booking::General::ComputeFare() calculates fare correctly: ";
    if(b6->fare_==4763) {
        cout<<"PASS\n";
        testCount--;
    }
    else {
        cout<<"FAIL\n";
    }
    
    Booking* b7=NULL;
    try
    {
        b7 = Booking::Reserve(Station::GetStation("Mumbai"),Station::GetStation("Delhi"),book,reser, BookingClasses::AC3Tier::Type(), BookingCategory::SeniorCitizen::Type(),p21); //Senior Citizen Booking
        
    }
    catch (Bad_Booking &bk) {
        
        cout<<bk.what();
    }
    b7->ComputeFare();
    cout<<"TESTCASE 7: Booking::SeniorCitizen::ComputeFare() calculates fare correctly: ";
    if(b7->fare_==1125) {
        cout<<"PASS\n";
        testCount--;
    }
    else {
        cout<<"FAIL\n";
    }

    Booking *b8=NULL;
    try {
        b8 = Booking::Reserve(Station::GetStation("Mumbai"),Station::GetStation("Delhi"),book,reser, BookingClasses::ACFirstClass::Type(), BookingCategory::SeniorCitizen::Type(),p11); //Senior Citizen Booking
    }
    catch (Bad_Booking &bk) {
        cout<<bk.what();
    }
    b8->ComputeFare();
    cout<<"TESTCASE 8: Booking::SeniorCitizen::ComputeFare() calculates fare correctly: ";
    if(b8->fare_==2411) {
        cout<<"PASS\n";
        testCount--;
    }
    else {
        cout<<"FAIL\n";
    }

    Booking* b9=NULL;
    try
    {
        b9 = Booking::Reserve(Station::GetStation("Mumbai"),Station::GetStation("Delhi"),book,reser, BookingClasses::AC3Tier::Type(), BookingCategory::DivyaangCat::Type(),p11); //Divyaang Booking
    }
    catch (Bad_Booking &bk) {
        cout<<bk.what();
    }
    b9->ComputeFare();
    cout<<"TESTCASE 9: Booking::DivyaangCat::ComputeFare() calculates fare correctly: ";
    if(b9->fare_==492) {
        cout<<"PASS\n";
        testCount--;
    }
    else {
        cout<<"FAIL\n";
    }

    Booking* b10=NULL;
    try
    {
        b10 = Booking::Reserve(Station::GetStation("Mumbai"),Station::GetStation("Delhi"),book,reser, BookingClasses::ACFirstClass::Type(), BookingCategory::DivyaangCat::Type(),p21); //Divyaang Booking
    }
    catch (Bad_Booking &bk) {
        cout<<bk.what();
    }
    b10->ComputeFare();
    cout<<"TESTCASE 10: Booking::DivyaangCat::ComputeFare() calculates fare correctly: ";
    if(b10->fare_==2411) {
        cout<<"PASS\n";
        testCount--;
    }
    else {
        cout<<"FAIL\n";
    }

    Booking* b11=NULL;
    try
    {
       b11 = Booking::Reserve(Station::GetStation("Delhi"),Station::GetStation("Mumbai"),book,reser, BookingClasses::AC3Tier::Type(), BookingCategory::Tatkal::Type(),p11); //Tatkal Booking
    }
    catch (Bad_Booking &bk) {
        cout<<bk.what();
    }
    b11->ComputeFare();
    cout<<"TESTCASE 11: Booking::Tatkal::ComputeFare() calculates fare correctly: ";
    if(b11->fare_==2249) {
        cout<<"PASS\n";
        testCount--;
    }
    else {
        cout<<"FAIL\n";
    }

    Booking* b12=NULL;
    try
    {
        b12 = Booking::Reserve(Station::GetStation("Chennai"),Station::GetStation("Bangalore"),book,reser, BookingClasses::ACFirstClass::Type(), BookingCategory::Tatkal::Type(),p11); //Tatkal Booking
    }
    catch (Bad_Booking &bk) {
        cout<<bk.what();
    }
    b12->ComputeFare();
    cout<<"TESTCASE 12: Booking::Tatkal::ComputeFare() calculates fare correctly: ";
    if(b12->fare_==1198) {
        cout<<"PASS\n";
        testCount--;
    }
    else {
        cout<<"FAIL\n";
    }

    Booking *b13=NULL;
    try{
        b13 = Booking::Reserve(Station::GetStation("Chennai"),Station::GetStation("Bangalore"),book,reser, BookingClasses::ACFirstClass::Type(), BookingCategory::PremiumTatkal::Type(),p11); //Premium Tatkal Booking
    }
    catch (Bad_Booking &bk) {
        cout<<bk.what();
    }
    b13->ComputeFare();
    cout<<"TESTCASE 13: Booking::PremiumTatkal::ComputeFare() calculates fare correctly: ";
    if(b13->fare_==1198) {
        cout<<"PASS\n";
        testCount--;
    }
    else {
        cout<<"FAIL\n";
    }

    Booking *b14=NULL;
    try 
    {
        b14 = Booking::Reserve(Station::GetStation("Delhi"),Station::GetStation("Mumbai"),book,reser, BookingClasses::AC3Tier::Type(), BookingCategory::PremiumTatkal::Type(),p11);//Premium Tatkal Booking
    }
    catch (Bad_Booking &bk) {
        cout<<bk.what();
    }
    b14->ComputeFare();
    cout<<"TESTCASE 14: Booking::PremiumTatkal::ComputeFare() calculates fare correctly: ";
    if(b14->fare_==2649) {
        cout<<"PASS\n";
        testCount--;
    }
    else {
        cout<<"FAIL\n";
    }

    // Test Booking::GeneralBooking::CheckEligibility
    // Valid case
    cout<<"TESTCASE 15: Booking::GeneralBooking::CheckEligibility() executes eligibility check correctly: ";
    bool result = false;
    try {
        result = Booking::GeneralBooking::CheckEligibility(p1, BookingCategory::General::Type(), Date::Today(), Date::GetDate(2,5,2021));
    }
    catch (Bad_Booking &bk){
        cout<<"FAIL\n";
    }
    if(result) {
        testCount--;
        cout<<"PASS\n";
    }
    // Invalid case: Date of Booking is before Date of reservation
    cout<<"TESTCASE 16 (E): Booking::GeneralBooking::CheckEligibility() throws expected exception: ";
    result = false;
    try {
        result = Booking::GeneralBooking::CheckEligibility(p1, BookingCategory::General::Type(), Date::Today(), Date::GetDate(3,5,1900));
    }
    catch (Bad_Chronology &bk){
        testCount--;
        cout<<"PASS\n";
        cout<<"    Exception message - "<<bk.what()<<"\n";
    }
    if(result) {
        cout<<"FAIL\n";
    }
    // Test Booking::LadiesBooking::CheckEligibility
    // Valid case
    cout<<"TESTCASE 17: Booking::LadiesBooking::CheckEligibility() executes eligibility check correctly: ";
    result = false;
    try {
        result = Booking::LadiesBooking::CheckEligibility(p1, BookingCategory::Ladies::Type(), Date::Today(), Date::GetDate(2,5,2021));
    }
    catch (Bad_Booking &bk){
        cout<<"FAIL\n";
    }
    if(result) {
        testCount--;
        cout<<"PASS\n";
    }
    // Invalid case: Male of age 12+
    cout<<"TESTCASE 18 (E): Booking::LadiesBooking::CheckEligibility() throws expected exception: ";
    result = false;
    try {
        result = Booking::LadiesBooking::CheckEligibility(p2, BookingCategory::Ladies::Type(), Date::Today(), Date::GetDate(2,5,2021));
    }
    catch (Ineligible_Ladies_Category &bk){
        testCount--;
        cout<<"PASS\n";
        cout<<"    Exception message - "<<bk.what()<<"\n";
    }
    if(result) {
        cout<<"FAIL\n";
    }
    // Test Booking::SeniorCitizenBooking::CheckEligibility
    // Valid case
    cout<<"TESTCASE 19: Booking::SeniorCitizenBooking::CheckEligibility() executes eligibility check correctly: ";
    result = false;
    try {
        result = Booking::SeniorCitizenBooking::CheckEligibility(Passenger::GetPassenger(Name("Jai","Shah"),Date::GetDate(5,1,1950),Gender::Female::Type(),"123456789123","0123456789",&Divyaang::Blind::Type(),"e"), BookingCategory::SeniorCitizen::Type(), Date::Today(), Date::GetDate(2,5,2021));
    }
    catch (Bad_Booking &bk){
        cout<<"FAIL\n";
    }
    if(result) {
        testCount--;
        cout<<"PASS\n";
    }
    // Invalid case: Male of age <60
    cout<<"TESTCASE 20 (E): Booking::SeniorCitizenBooking::CheckEligibility() throws expected exception: ";
    result = false;
    try {
        result = Booking::SeniorCitizenBooking::CheckEligibility(p2, BookingCategory::SeniorCitizen::Type(), Date::Today(), Date::GetDate(2,5,2021));
    }
    catch (Ineligible_SeniorCitizen_Category &bk){
        testCount--;
        cout<<"PASS\n";
        cout<<"    Exception message - "<<bk.what()<<"\n";
    }
    if(result) {
        cout<<"FAIL\n";
    }
    // Test Booking::DivyaangBooking::CheckEligibility
    // Valid case
    cout<<"TESTCASE 21: Booking::DivyaangBooking::CheckEligibility() executes eligibility check correctly: ";
    result = false;
    try {
        result = Booking::DivyaangBooking::CheckEligibility(p1, BookingCategory::DivyaangCat::Type(), Date::Today(), Date::GetDate(2,5,2021));
    }
    catch (Bad_Booking &bk){
        cout<<"FAIL\n";
    }
    if(result) {
        testCount--;
        cout<<"PASS\n";
    }
    // Invalid case: No Disability in Passenger
    cout<<"TESTCASE 22 (E): Booking::DivyaangBooking::CheckEligibility() throws expected exception: ";
    result = false;
    try {
        result = Booking::DivyaangBooking::CheckEligibility(p2, BookingCategory::DivyaangCat::Type(), Date::Today(), Date::GetDate(2,5,2021));
    }
    catch (Ineligible_Divyaang_Category &bk){
        testCount--;
        cout<<"PASS\n";
        cout<<"    Exception message - "<<bk.what()<<"\n";
    }
    if(result) {
        cout<<"FAIL\n";
    }
    // Test Booking::TatkalBooking::CheckEligibility
    // Valid case
    cout<<"TESTCASE 23: Booking::TatkalBooking::CheckEligibility() executes eligibility check correctly: ";
    result = false;
    try {
        result = Booking::TatkalBooking::CheckEligibility(p1, BookingCategory::Tatkal::Type(), Date::Today(), Date::Today());
    }
    catch (Bad_Booking &bk){
        cout<<"FAIL\n";
    }
    if(result) {
        testCount--;
        cout<<"PASS\n";
    }
    // Invalid case: Date of Booking is not within 1 day of Date of Reservation
    cout<<"TESTCASE 24 (E): Booking::TatkalBooking::CheckEligibility() throws expected exception: ";
    result = false;
    try {
        result = Booking::TatkalBooking::CheckEligibility(p1, BookingCategory::Tatkal::Type(), Date::Today(), Date::GetDate(2,7,2021));
    }
    catch (Ineligible_Tatkal_Category &bk){
        testCount--;
        cout<<"PASS\n";
        cout<<"    Exception message - "<<bk.what()<<"\n";
    }
    if(result) {
        cout<<"FAIL\n";
    }
    // Test Booking::PremiumTatkalBooking::CheckEligibility
    // Valid case
    cout<<"TESTCASE 25: Booking::PremiumTatkalBooking::CheckEligibility() executes eligibility check correctly: ";
    result = false;
    try {
        result = Booking::PremiumTatkalBooking::CheckEligibility(p1, BookingCategory::Tatkal::Type(), Date::Today(), Date::Today());
    }
    catch (Bad_Booking &bk){
        cout<<"FAIL\n";
    }
    if(result) {
        testCount--;
        cout<<"PASS\n";
    }
    // Invalid case: Date of Booking is not within 1 day of Date of Reservation
    cout<<"TESTCASE 26 (E): Booking::PremiumTatkalBooking::CheckEligibility() throws expected exception: ";
    result = false;
    try {
        result = Booking::PremiumTatkalBooking::CheckEligibility(p1, BookingCategory::PremiumTatkal::Type(), Date::Today(), Date::GetDate(2,7,2021));
    }
    catch (Ineligible_PremiumTatkal_Category &bk){
        testCount--;
        cout<<"PASS\n";
        cout<<"    Exception message - "<<bk.what()<<"\n";
    }
    if(result) {
        cout<<"FAIL\n";
    }
    // Test on Booking
    // Test Output streaming operator
    cout<<"TESTCASE 27: Output streaming operator for Booking: ";
    string outputGolden="BOOKING SUCCEEDED:\n-- Passenger Details --\nName = Bob Dylan Magic\nAge = 121\nGender = Female\nAadhar Number = 123456789123\nMobile Number = 0123456789\nDisability Type = Blind\nDisabilityID = e\n-- Booking Details -- \nPNR Number = 15\nFrom Station = Mumbai\nTo Station = Delhi\nTravel Date = 2/Apr/2021\nReservation Date = 2/Apr/2021\nBooking Category = General\nTravel Class = AC 3 Tier\n : Mode: Sleeping\n : Comfort: AC\n : Bunks: 3\n : Luxury: No\nFare = 1849\n\n";
    const Passenger &p10 = Passenger::GetPassenger(Name("Bob","Magic","Dylan"),Date::GetDate(5,1,1900),Gender::Female::Type(),"123456789123","0123456789",&Divyaang::Blind::Type(),"e");
    const Booking* bTest = Booking::Reserve(Station::GetStation("Mumbai"),Station::GetStation("Delhi"),Date::GetDate(2,4,2021),Date::GetDate(2,4,2021), BookingClasses::AC3Tier::Type(), BookingCategory::General::Type(),p10);
    stringstream ss1;
    ss1<<*bTest;
    if(ss1.str()==outputGolden)
    {   
        testCount--;
        cout<<"PASS\n";
    }
    else{
        cout<<"FAIL\n";
    }
    cout<<"\n----- VERDICT : ";
    if(testCount==0)
    {
        cout<<"27/27 test cases passed -----\n";
    }
    else 
    {
        cout<<testCount<<"/27 Tests FAILED -----\n";
    }

}

// int main()
// {
//     cout<<"it runs! yay";
//     Station st1 = Station::GetStation("Kolkata");
//     //Station st2 = Station::GetStation("");
//     //Station st3 = Station::GetStation(NULL);
//     string test = "Kolkata";
//     Station st4 = Station::GetStation(test);
//     test = "";
//     try
//     {
//         Station st5 = Station::GetStation(test);
//     }
//     catch(Bad_Station_Name ex)
//     {
//         cout<<ex.what()<<"\n";
//     }
//     // Railways::IsValid();
//     // cout<<Railways::Type().GetDistance(Station::GetStation("Kolkata"),Station::GetStation("Mumbai"));
//     // Railways::Type().GetDistance(Station::GetStation("Kolkata"),Station::GetStation("Kolkata"));
//     // Booking *b1 = Booking::Reserve(Station::GetStation("Kolkata"), Station::GetStation("Delhi"), Date::GetDate(25, 7, 2021), Date::GetDate(24, 7, 2021), BookingClasses::ACFirstClass::Type(), BookingCategory::DivyaangCat::Type(), Passenger::GetPassenger(Name("Oxford", "Oswald", ""), Date::GetDate(3,6,2001), Gender::Male::Type(), "1000000000", "7980791905", &Divyaang::OrthopaedicallyHandicapped::Type(), "12"));
//     // Passenger p2 = Passenger::GetPassenger(Name("","Magic",""),Date(5,5,2021),Gender::Female::Type(),"123456789123","0123456789");
//     // Passenger p3 = Passenger::GetPassenger(Name("Oswald","Magic","Octopus"),Date(5,5,2021),Gender::Female::Type(),"12345689123","0123456789");
//     // Passenger p4 = Passenger::GetPassenger(Name("Oswald","Magic","Octopus"),Date(5,5,2021),Gender::Female::Type(),"12345a789123","0123456789");
//     // Passenger p5 = Passenger::GetPassenger(Name("Oswald","Magic","Octopus"),Date(5,5,2021),Gender::Female::Type(),"123456789123","013456789");
//     // Passenger p6 = Passenger::GetPassenger(Name("Oswald","Magic","Octopus"),Date(5,5,2021),Gender::Female::Type(),"123456789123","012345a789");
//     // cout<<DivyaangConcession::Type().GetConcessionFactor(p1, BookingClasses::AC2Tier::Type());
//     // cout<<Date::Today().CalculateSpan(Date::GetDate("30/06/2021"));
//     cout<<Gender::Male::Type();
//     Passenger p1 = Passenger::GetPassenger(Name("Oswald","Magic","Octopus"),Date::GetDate(5,1,1900),Gender::Female::Type(),"123456789123","0123456789",&Divyaang::Blind::Type(),"e");
//     Passenger p2 = Passenger::GetPassenger(Name("Oswald","Magic","Octopus"),Date::GetDate(5,1,1900),Gender::Male::Type(),"123456789123","0123456789",&Divyaang::CancerPatient::Type(),"f");
//     Date reser = Date::Today();
//     Date book = Date::Today();
//     Station to = Station::GetStation("Kolkata");
//     Station from = Station::GetStation("Delhi");
//     const Booking* b1 = Booking::Reserve(to,from,book,reser, BookingClasses::AC2Tier::Type(), BookingCategory::Ladies::Type(),p1);
//     cout<<(*b1);
//     const Booking* b2 = Booking::Reserve(Station::GetStation("Mumbai"),Station::GetStation("Delhi"),book,reser, BookingClasses::AC3Tier::Type(), BookingCategory::General::Type(),p1);
//     cout<<(*b2)<<"\n";
//     const Booking* b3 = Booking::Reserve(Station::GetStation("Mumbai"),Station::GetStation("Delhi"),book,reser, BookingClasses::ACFirstClass::Type(), BookingCategory::General::Type(),p1);
//     cout<<(*b3)<<"\n";
//     const Booking* b4 = Booking::Reserve(Station::GetStation("Mumbai"),Station::GetStation("Delhi"),book,reser, BookingClasses::AC3Tier::Type(), BookingCategory::SeniorCitizen::Type(),p2);
//     cout<<(*b4)<<"\n";
//     const Booking* b5 = Booking::Reserve(Station::GetStation("Mumbai"),Station::GetStation("Delhi"),book,reser, BookingClasses::ACFirstClass::Type(), BookingCategory::SeniorCitizen::Type(),p1);
//     cout<<(*b5)<<"\n";
//     const Booking* b6 = Booking::Reserve(Station::GetStation("Mumbai"),Station::GetStation("Delhi"),book,reser, BookingClasses::AC3Tier::Type(), BookingCategory::DivyaangCat::Type(),p1);
//     cout<<(*b6)<<"\n";
//     const Booking* b7 = Booking::Reserve(Station::GetStation("Mumbai"),Station::GetStation("Delhi"),book,reser, BookingClasses::ACFirstClass::Type(), BookingCategory::DivyaangCat::Type(),p2);
//     cout<<(*b7)<<"\n";
//     const Booking* b8 = Booking::Reserve(Station::GetStation("Delhi"),Station::GetStation("Mumbai"),book,reser, BookingClasses::AC3Tier::Type(), BookingCategory::Tatkal::Type(),p1);
//     cout<<(*b8)<<"\n";
//     const Booking* b9 = Booking::Reserve(Station::GetStation("Chennai"),Station::GetStation("Bangalore"),book,reser, BookingClasses::ACFirstClass::Type(), BookingCategory::PremiumTatkal::Type(),p1);
//     cout<<(*b9)<<"\n";
//     cout<<Date::GetDate(3,6,2001).CalculateAge();
//     BookingCategory::UnitTest();
//     Concessions::UnitTest();
//     Date::UnitTest();
//     Divyaang::UnitTest();
//     Gender::UnitTest();
//     Booking::UnitTest();
//     Passenger::UnitTest();
//     BookingClasses::UnitTest();
//     return 0;
// }