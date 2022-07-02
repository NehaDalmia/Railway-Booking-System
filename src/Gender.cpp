// Gender.cpp

#include "Gender.h"
#include <sstream>

// Names defined as static constants

template<> const string Gender::Male::sName = "Male";
template<> const string Gender::Female::sName = "Female";

// Salutations defined as static constants

template<> const string Gender::Male::sSalutation = "Mr.";
template<> const string Gender::Female::sSalutation = "Ms.";

//output streaming operator

ostream &operator<<(ostream &out, const Gender &g) {
    out<<g.GetName();
    return out;
}

void Gender::UnitTest()
{
    cout<<"\n\nCLASS GENDER\n\n";
    int totalCount = 7;
    //Checking GetName for male
    cout<<"TESTCASE 1: Checking GetName for male:  ";
    if(Gender::Male::Type().GetName()=="Male")
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else 
    {
        cout<<"FAIL\n";
    }
    //Checking GetName for female
    cout<<"TESTCASE 2: Checking GetName for female:  ";
    if(Gender::Female::Type().GetName()=="Female")
    {
        totalCount--;
     cout<<"PASS\n";
    }
    else 
    {
        cout<<"FAIL\n";
    }
    //Checking GetTitle for male
    cout<<"TESTCASE 3: Checking GetTitle for male:  ";
    if(Gender::Male::Type().GetTitle()=="Mr.")
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else 
    {
        cout<<"FAIL\n";
    }
    //Checking GetTitle for female
    cout<<"TESTCASE 4: Checking GetTitle for female:  ";
    if(Gender::Female::Type().GetTitle()=="Ms.")
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else 
    {
        cout<<"FAIL\n";
    }
    cout<<"TESTCASE 5: Test Output streaming operator for Gender::Male :  ";
    // Test Output streaming operator for Gender::Male
    const Gender::Female &fTest = Gender::Female::Type();
    string outputGolden = "Female";
    stringstream ss;
    ss<<fTest;
    if(ss.str()==outputGolden)
    {   
        cout<<"PASS\n";
        totalCount--;
    }
    else{
       cout<<"FAIL\n";
    }

    // Tests on Gender
    cout<<"TESTCASE 6:  Test working of polymorphic hierarchy by comparing the GetName() function return value:  ";
    // Test working of polymorphic hierarchy by comparing the GetName() function return value
    const Gender &obj = Gender::Male::Type();
    if(obj.GetName()=="Male") {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
         cout<<"FAIL\n";
    }
    // Test Output streaming operator for Gender
    cout<<"TESTCASE 7:  Test Output streaming operator for Gender:  ";
    const Gender &gTest = Gender::Male::Type();
    outputGolden = "Male";
    stringstream ss_;
    ss_<<gTest;
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
        cout<<"7/7 test cases passed -----\n";
    }
    else 
    {
        cout<<totalCount<<"/7 Tests FAILED -----\n";
    }
}