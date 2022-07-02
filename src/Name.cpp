#include "Name.h"
#include <sstream>

Name::Name(const string &firstName, const string &lastName, const string &middleName) : firstName_(firstName), middleName_(middleName), lastName_(lastName)
{
    #ifdef _DEBUG
    cout << "Name = " <<(*this)<<" --CONSTRUCTED"<<endl;
    #endif
}
Name::~Name() {
    #ifdef _DEBUG
    cout << "Name = " <<(*this)<<" --DESTRUCTED"<<endl;
    #endif
}
void Name::UnitTest()
{
    cout<<"\n\nCLASS NAME\n\n";
    int totalCount = 1;
    // Test Output streaming operator
    cout<<"TESTCASE 1: Test Output streaming operator : ";
    Name n = Name("Bob","Dylan");
    string outputGolden = "Bob Dylan";
    stringstream ss;
    ss<<n;
    if(ss.str()==outputGolden)
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
        cout<<"1/1 test cases passed -----\n";
    }
    else 
    {
        cout<<totalCount<<"/1 Tests FAILED -----\n";
    }
}
ostream &operator<<(ostream &out, const Name &n) {
    out<<n.firstName_;
    if(n.firstName_!="") {
        out<<" ";
    }
    out<<n.middleName_;
    if(n.middleName_!="") {
        out<<" ";
    }
    out<<n.lastName_;
    return out;
}