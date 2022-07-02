#include "Passenger.h"
#include "Exceptions.h"

Passenger::Passenger(const Name &name, const Date &dateOfBirth, const Gender &gender, const string &aadhar, const string &mobileNo, const Divyaang *disability, const string &disabilityID): name_(name),dateOfBirth_(dateOfBirth),gender_(gender),aadharNumber_(aadhar),mobileNumber_(mobileNo),disabilityType_(disability),disabilityID_(disabilityID)
{
    //calculate age based on today's date
    age_  = dateOfBirth.CalculateAge();
    #ifdef _DEBUG
    cout << "Passenger = \n" <<(*this)<<"\n  --CONSTRUCTED"<<endl;
    #endif
}
Passenger::Passenger(const Passenger &copyPassenger):name_(copyPassenger.name_),dateOfBirth_(copyPassenger.dateOfBirth_),gender_(copyPassenger.gender_),aadharNumber_(copyPassenger.aadharNumber_),mobileNumber_(copyPassenger.mobileNumber_),disabilityType_(copyPassenger.disabilityType_),disabilityID_(copyPassenger.disabilityID_)
{
     //calculate age based on today's date
    age_ = copyPassenger.age_;
    #ifdef _DEBUG
    cout << "Copy Ctor Passenger = \n" <<(*this)<<"\n  --CONSTRUCTED"<<endl;
    #endif
}
bool Passenger::operator==(const Passenger &p) const {
    return name_.firstName_==p.name_.firstName_ && name_.middleName_==p.name_.middleName_ && name_.lastName_==p.name_.lastName_ && dateOfBirth_==p.dateOfBirth_ && gender_.GetName()==p.gender_.GetName() && aadharNumber_==p.aadharNumber_ && mobileNumber_==p.mobileNumber_ && disabilityType_ == p.disabilityType_ && disabilityID_ == p.disabilityID_;
}
void Passenger::IsValid(const Name &name, const Date &dateOfBirth, const Gender &gender, const string &aadhar, const string &mobileNo, const Divyaang *disability , const string &disabilityID)
{
    //BadName
    if(name.firstName_=="" && name.lastName_=="")
        throw Bad_Name("Passenger Error: Passenger must have at least one of First Name and Last Name");
    //BadAadhar
    if(aadhar.length()!=12)
        throw Bad_Aadhar_Number("Passenger Error: Passenger must have a 12 Digit Aadhaar Number");
    for(auto it: aadhar)
    if(it<'0'||it>'9')
        throw Bad_Aadhar_Number("Passenger Error: Passenger Aadhaar Number cannot contain characters");
    //Bad mobile no
    if(mobileNo!="" && mobileNo.length()!=10)
        throw Bad_Mobile_Number("Passenger Error: Passenger must have a 10 Digit Mobile Number");
    for(auto it: mobileNo)
    if(it<'0'||it>'9')
        throw Bad_Mobile_Number("Passenger Error: Passenger Mobile Number cannot contain characters");
    //Bad Age
    if(dateOfBirth.CalculateSpan(Date::Today())<0)
        throw Bad_Age("Passenger Error: Passenger has not been born yet");
}
Passenger Passenger::GetPassenger(const Name &name, const Date &dateOfBirth, const Gender &gender, const string &aadhar, const string &mobileNo, const Divyaang *disability, const string &disabilityID)
{
    IsValid(name,dateOfBirth,gender,aadhar,mobileNo,disability,disabilityID);
    return Passenger(name,dateOfBirth,gender,aadhar,mobileNo,disability,disabilityID);
}
ostream &operator<<(ostream &out, const Passenger &p) {
    out<<"-- Passenger Details --\n";
    out<<"Name = "<<p.name_<<"\n";
    out<<"Age = "<<p.age_<<"\n";
    out<<"Gender = "<<p.gender_<<"\n";
    out<<"Aadhar Number = "<<p.aadharNumber_;
    if(p.mobileNumber_!="") {
        out<<"\nMobile Number = "<<p.mobileNumber_;
    }
    if(p.disabilityType_!=NULL) {
        out<<"\nDisability Type = "<<*(p.disabilityType_)<<"\n";
        out<<"DisabilityID = "<<p.disabilityID_;
    }
    return out;
}
void Passenger::UnitTest()
{
    cout<<"\n\nCLASS PASSENGER\n\n";
    int totalCount= 9;
    bool f=true;
    
    cout<<"TESTCASE 1: Testing IsValid()-   Both first and last names missing : ";
    //Testing IsValid()
    //BadName - Both first and last names missing
    try
    {
        IsValid(Name("","","Y"), Date::Today(),Gender::Male::Type(),"123456789999","1234567890",NULL,"");
    }
    catch(Bad_Name bn)
    {
        cout<<"PASS\n";
        cout<<"Expected Exception thrown: "<<bn.what()<<"\n";
        totalCount-- ;
    }
    catch(...)
    {
        cout<<"FAIL\n";
    }
    //Valid Naming + aadhar + birthday + mobile no - Middle Name missing
    cout<<"TESTCASE 2: Testing IsValid()-   Valid Naming + aadhar + birthday + mobile no - Middle Name missing : ";
    try
    {
       IsValid(Name("X","Y",""), Date::Today(),Gender::Male::Type(),"123456789999","1234567890",NULL,"");
    }
    catch(...)
    {
        f=false;
        cout<<"FAIL\n";
    }
    if(f)
    {
        cout<<"PASS\n";
    }
    cout<<"TESTCASE 3: Testing IsValid()-   Valid Naming + aadhar + birthday + mobile no - No Name missing: ";

    //Valid Naming + aadhar + birthday + mobile no - No Name missing
    try
    {
        IsValid(Name("X","Y","Z"), Date::Today(),Gender::Male::Type(),"123456789999","1234567890",NULL,"");
    }
    catch(...)
    {
        f=false;
        cout<<"FAIL\n";
    }
    if(f)
    {
        cout<<"PASS\n";
    }
    //BadAadhaar - Not 12 digits
    cout<<"TESTCASE 4: Testing IsValid()-   /BadAadhaar - Not 12 digits: ";
    try
    {
        IsValid(Name("X","Y",""), Date::Today(),Gender::Male::Type(),"1234567899999","1234567890",NULL,"");
    }
    catch(Bad_Aadhar_Number bn)
    {
        totalCount-- ;
        cout<<"PASS\n";
        cout<<"Expected Exception thrown: "<<bn.what()<<"\n";
    }
    catch(...)
    {
        cout<<"FAIL\n";
    }
    //BadAadhar - Non numeric
    cout<<"TESTCASE 5: Testing IsValid()-  BadAadhar - Non numeric: ";
    try
    {
        IsValid(Name("X","Y",""), Date::Today(),Gender::Male::Type(),"123456789a99","1234567890",NULL,"");
    }
    catch(Bad_Aadhar_Number bn)
    {
        totalCount-- ;
        cout<<"PASS\n";
        cout<<"Expected Exception thrown: "<<bn.what()<<"\n";
    }
    catch(...)
    {
        cout<<"FAIL\n";
    }
    cout<<"TESTCASE 6: Testing IsValid()-  Bad Mobile no - non empty with length not 10: ";
    //Bad Mobile no - non empty with length not 10
    try
    {
        IsValid(Name("X","Y",""), Date::Today(),Gender::Male::Type(),"123456789999","12314567890",NULL,"");
    }
    catch(Bad_Mobile_Number bn)
    {
        totalCount-- ;
        cout<<"PASS\n";
        cout<<"Expected Exception thrown: "<<bn.what()<<"\n";
    }
    catch(...)
    {
        cout<<"FAIL\n";
    }
    cout<<"TESTCASE 7: Testing IsValid()-  Bad Mobile no - non empty with non numeric: ";
    //Bad Mobile no - non empty with non numeric
    try
    {
        IsValid(Name("X","Y",""), Date::Today(),Gender::Male::Type(),"123456789999","12314a7890",NULL,"");
    }
    catch(Bad_Mobile_Number bn)
    {
        totalCount-- ;
         cout<<"PASS\n";
        cout<<"Expected Exception thrown: "<<bn.what()<<"\n";
    }
    catch(...)
    {
        cout<<"FAIL\n";
    }
    cout<<"TESTCASE 8: Testing IsValid()- Mobile Number is valid: ";
    //Mobile Number is valid
    try
    {
        IsValid(Name("X","Y",""), Date::Today(),Gender::Male::Type(),"123456789999","",NULL,"");
    }
    catch(...)
    {
        f=false;
        cout<<"FAIL\n";
    }
    if(f)
    {
        cout<<"PASS\n";
    }
    cout<<"TESTCASE 9: Testing IsValid()- Bad Age - Not born yet: ";
    //Bad Age - Not born yet
    try
    {
       IsValid(Name("X","Y",""), Date::GetDate(1,1,2050),Gender::Male::Type(),"123456789999","1235476890",NULL,"");
    }
    catch(Bad_Age bn)
    {
        totalCount-- ;
        cout<<"PASS\n";
        cout<<"Expected Exception thrown: "<<bn.what()<<"\n";
    }
    catch(...)
    {
        cout<<"FAIL\n";
    }
    cout<<"TESTCASE 10: Testing the overloaded == operator - valid Case ";
    //testing the overloaded == operator
    Passenger p1 = Passenger(Name("X","Y","Z"), Date::Today(),Gender::Male::Type(),"123456789999","1234567890");
    Passenger p2 = Passenger(Name("X","Y","Z"), Date::Today(),Gender::Male::Type(),"123456789999","1234567890");
    if((p1==p2))
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else
    {
        cout<<"FAIL\n";
    }
    cout<<"TESTCASE 11: Testing the overloaded == operator - valid Case ";
    //Testing GetPasseneger - Valid Case
    try
    {
        Passenger p3 = GetPassenger(Name("X","Y",""), Date::Today(),Gender::Male::Type(),"123456789999","1231478190");
    }
    catch(...)
    {
        f=false;
        cout<<"FAIL\n";
    }
    if(f)
    {
        cout<<"PASS\n";
    }
    //Testing GetPasseneger - InValid Case
    bool t_c = false;
    cout<<"TESTCASE 12: Testing GetPasseneger - InValid Case :  ";
    try
    {
        Passenger p3 = GetPassenger(Name("","Y",""), Date::Today(),Gender::Male::Type(),"123456789999","123147890");
    }
    catch(Bad_Passenger bp)
    {
        totalCount--;
        t_c = true;
        cout<<"PASS\n";
        cout<<"Expection error : "<<bp.what()<<"\n";
        
    }
    if(!t_c)
    {
        cout<<"FAIL\n";
    }
    cout<<"TESTCASE 12: Test Output streaming operator for Passenger :  ";
    // Test Output streaming operator for Passenger
    Passenger p5 = Passenger::GetPassenger(Name("Priyanka","Chopra"),Date::GetDate(12,12,1988),Gender::Female::Type(),"123456789123","0123456789",&Divyaang::Blind::Type(),"e");
    string outputGolden = "-- Passenger Details --\nName = Priyanka Chopra\nAge = 32\nGender = Female\nAadhar Number = 123456789123\nMobile Number = 0123456789\nDisability Type = Blind\nDisabilityID = e";
    stringstream ss;
    ss<<p5;
    if(ss.str()==outputGolden)
    {   
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout<<"FAIL\n";
    }
    cout<<"\n----- VERDICT : ";
    if(totalCount==0 && f==true)
    {
        cout<<"12/12 test cases passed -----\n";
    }
    else 
    {
        cout<<"FAIL -----\n";
    }
    
}
Passenger::~Passenger()
{
    #ifdef _DEBUG
    cout << "Passenger = " <<(*this)<<"\n  --DESTRUCTED"<<endl;
    #endif
}