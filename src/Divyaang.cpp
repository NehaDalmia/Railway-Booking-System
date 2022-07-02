#include "Divyaang.h"

template<> const string Divyaang::Blind::sName                          = "Blind";
template<> const string Divyaang::OrthopaedicallyHandicapped::sName     = "Orthopaedically Handicapped";
template<> const string Divyaang::CancerPatient::sName                  = "Cancer Patient";
template<> const string Divyaang::TBPatient::sName                      = "TB Patient";

Divyaang::Divyaang() 
{
    #ifdef _DEBUG
    cout << "Abstract Base Class Divyaang --CONSTRUCTED" << endl;
    #endif
}

Divyaang::~Divyaang() 
{
    #ifdef _DEBUG
    cout << "Abstract Base Class Divyaang  --DESTRUCTED" << endl;
    #endif
}

ostream &operator<<(ostream &out, const Divyaang &d) {
    out<<d.GetName();
    return out;
}
//Templatised Disability Types constructor definition
template<typename T>
DisabilityTypes<T>::DisabilityTypes() {
    #ifdef _DEBUG
    cout << "Divyaang = " <<(*this)<<" --CONSTRUCTED"<< endl;
    #endif
}
//Templatised Disability Types destructor definition
template<typename T>
DisabilityTypes<T>::~DisabilityTypes() {
    #ifdef _DEBUG
    cout << "Divyaang = " <<(*this)<<" --DESTRUCTED"<< endl;
    #endif
}
//Templatised Disability Types getname definition

template<typename T>
string DisabilityTypes<T>::GetName() const {
    return DisabilityTypes<T>::sName;
}
//Templatised Disability Types GetDivyaangConcessionFactor definitions for different booking classes

template<typename T>
double DisabilityTypes<T>::GetDivyaangConcessionFactor(const BookingClasses::ACFirstClass&) const {
    return DisabilityTypes<T>::sACFirstClassConcession;
}

template<typename T>
double DisabilityTypes<T>::GetDivyaangConcessionFactor(const BookingClasses::ExecutiveChairCar&) const {
    return DisabilityTypes<T>::sExecutiveChairCarConcession;
}

template<typename T>
double DisabilityTypes<T>::GetDivyaangConcessionFactor(const BookingClasses::AC2Tier&) const {
    return DisabilityTypes<T>::sAC2TierConcession;
}

template<typename T>
double DisabilityTypes<T>::GetDivyaangConcessionFactor(const BookingClasses::FirstClass&) const {
    return DisabilityTypes<T>::sFirstClassConcession;
}

template<typename T>
double DisabilityTypes<T>::GetDivyaangConcessionFactor(const BookingClasses::ACChairCar&) const {
    return DisabilityTypes<T>::sACChairCarConcession;
}

template<typename T>
double DisabilityTypes<T>::GetDivyaangConcessionFactor(const BookingClasses::AC3Tier&) const {
    return DisabilityTypes<T>::sAC3TierConcession;
}

template<typename T>
double DisabilityTypes<T>::GetDivyaangConcessionFactor(const BookingClasses::Sleeper&) const {
    return DisabilityTypes<T>::sSleeperConcession;
}

template<typename T>
double DisabilityTypes<T>::GetDivyaangConcessionFactor(const BookingClasses::SecondSitting&) const {
    return DisabilityTypes<T>::sSecondSittingConcession;
}

template<typename T>
const DisabilityTypes<T> &DisabilityTypes<T>::Type(){
    static const DisabilityTypes<T> obj;
    return obj;
} 

void Divyaang::UnitTest()
{   
cout<<"\n\nCLASS DIVYAANG\n\n";
double goldenConcession;
double concession = 0.0;
int totalCount = 15;
//Test GetDivyaangConcessionFactor() for all sub-types of Divyaang 
//Divyang Concession - ACFirstClass - Blind
goldenConcession = 0.5;
concession = Divyaang::Blind::Type().GetDivyaangConcessionFactor(BookingClasses::ACFirstClass::Type());
 cout<<"TESTCASE 1 : Divyaang:GetDivyaangConcessionFactor - ACFirstClass - Blind : ";
if(concession==goldenConcession)
{
     totalCount--;
    cout<<"PASS\n";
}
else 
{
    cout<<"FAIL\n";
}
//Executive Chair Car - Blind
 cout<<"TESTCASE 2 : Divyaang:GetDivyaangConcessionFactor - Executive Chair Car - Blind : ";

goldenConcession = 0.75;
concession =Divyaang::Blind::Type().GetDivyaangConcessionFactor( BookingClasses::ExecutiveChairCar::Type());
if(concession==goldenConcession)
{
    totalCount--;
    cout<<"PASS\n";
}
else 
{
     cout<<"FAIL\n";
}
//AC 2 Tier - Blind
cout<<"TESTCASE 3 : Divyaang::GetDivyaangConcessionFactor - AC 2 Tier - Blind :  ";
goldenConcession = 0.50;
concession = Divyaang::Blind::Type().GetDivyaangConcessionFactor( BookingClasses::AC2Tier::Type());
if(concession==goldenConcession)
{
    totalCount--;
    cout<<"PASS\n";
}
else 
{
    cout<<"FAIL\n";
}
//First Class - Blind
cout<<"TESTCASE 4 : Divyaang:GetDivyaangConcessionFactor - First Class - Blind :  ";
goldenConcession = 0.75;
concession = Divyaang::Blind::Type().GetDivyaangConcessionFactor( BookingClasses::FirstClass::Type());
if(concession==goldenConcession)
{
    
    totalCount--;
    cout<<"PASS\n";
}
else 
{
    cout<<"FAIL\n";
}
//AC3Tier - Blind
cout<<"TESTCASE 5 : Divyaang:GetDivyaangConcessionFactor - AC3Tier - Blind :  ";
goldenConcession = 0.75;
concession =Divyaang::Blind::Type().GetDivyaangConcessionFactor(BookingClasses::AC3Tier::Type());
if(concession==goldenConcession)
{
    totalCount--;
    cout<<"PASS\n";
}
else 
{
    cout<<"FAIL\n";
}
//AC Chair Car Orthopaedically Handicapped
cout<<"TESTCASE 6 : Divyaang:GetDivyaangConcessionFactor - AC Chair Car Orthopaedically Handicapped :  ";
goldenConcession = 0.75;
concession = Divyaang::OrthopaedicallyHandicapped::Type().GetDivyaangConcessionFactor(BookingClasses::ACChairCar::Type());
if(concession==goldenConcession)
{
    totalCount--;
    cout<<"PASS\n";
}
else 
{
    cout<<"FAIL\n";
}
//Sleeper Cancer Patient
cout<<"TESTCASE 7 : Divyaang:GetDivyaangConcessionFactor - Sleeper Cancer Patient :  ";

goldenConcession = 1.00;
concession = Divyaang::CancerPatient::Type().GetDivyaangConcessionFactor( BookingClasses::Sleeper::Type());
if(concession==goldenConcession)
{
    totalCount--;
    cout<<"PASS\n";
}
else 
{
    cout<<"FAIL\n";
}
//Second Sitting TB Patient
cout<<"TESTCASE 8 : Divyaang:GetDivyaangConcessionFactor - Second Sitting TB Patient :  ";

goldenConcession = 0.75;
concession =Divyaang::TBPatient::Type().GetDivyaangConcessionFactor( BookingClasses::SecondSitting::Type());
if(concession==goldenConcession)
{
    totalCount--;
    cout<<"PASS\n";
}
else 
{
    cout<<"FAIL\n";
}
//Test GetName for all sub-types of Divyaang 
cout<<"TESTCASE 9 : Divyaang:Blind::GetName()   ";

if(Divyaang::Blind::Type().GetName()=="Blind")
{
    totalCount--;
    cout<<"PASS\n";
}
else 
{
    cout<<"FAIL\n";
}
cout<<"TESTCASE 10: Divyaang:OrthopaedicallyHandicapped::GetName()   ";
if(Divyaang::OrthopaedicallyHandicapped::Type().GetName()=="Orthopaedically Handicapped")
{
    totalCount--;
    cout<<"PASS\n";
}
else 
{
    cout<<"FAIL\n";
}
cout<<"TESTCASE 11: Divyaang:CancerPatient::GetName()   ";

if(Divyaang::CancerPatient::Type().GetName()=="Cancer Patient")
{
    totalCount--;
    cout<<"PASS\n";
}
else 
{
     cout<<"FAIL\n";
}
cout<<"TESTCASE 12: Divyaang:CancerPatient::GetName()   ";

if(Divyaang::TBPatient::Type().GetName()=="TB Patient")
{
    totalCount--;
    cout<<"PASS\n";
}
else 
{
    cout<<"FAIL\n";
}

// Test Output streaming operator for DivyaangTypes<T>
cout<<"TESTCASE 13: outputstream  :  ";

const Divyaang::TBPatient &tTest = Divyaang::TBPatient::Type();
string outputGolden = "TB Patient";
stringstream ss;
ss<<tTest;
if(ss.str()==outputGolden)
{   
    totalCount--;
    cout<<"PASS\n";
}
else{
    cout<<"FAIL\n";
}

// Test on Divyaang
// Test working of polymorphic hierarchy by comparing the GetName() function return value
cout<<"TESTCASE 14: Test working of polymorphic hierarchy by comparing the GetName() function return value : ";

const Divyaang &obj = Divyaang::Blind::Type();
if(obj.GetName()=="Blind") {
    totalCount--;
    cout<<"PASS\n";
}
else{
   cout<<"FAIL\n";
}

// Test Output streaming operator for Divyaang
cout<<"TESTCASE 15: Test Output streaming operator for Divyaang : ";

const Divyaang &dTest = Divyaang::Blind::Type();
outputGolden = "Blind";
stringstream ss_;
ss_<<dTest;
if(ss_.str()==outputGolden)
{   
    totalCount--;
    cout<<"PASS\n";
}
else{
    cout<<"FAIL\n";
}

cout<<"\n----- VERDICT : ";
if(totalCount==0)
{
    cout<<"15/15 test cases passed -----\n";
}
else 
{
    cout<<totalCount<<"/15 Tests FAILED -----\n";
}

}  
// int main(){
//     const Divyaang &d = Divyaang::TBPatient::Type();
//     cout<<d.GetDivyaangConcessionFactor(BookingClasses::ACFirstClass::Type());
//     return 0;
// }