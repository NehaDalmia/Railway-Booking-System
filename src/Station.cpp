#include "Station.h"
#include "Railways.h"
#include "Exceptions.h"
Station::Station(const char *name) : name_(name)
{
    #ifdef _DEBUG
    cout << "Station = " <<(*this)<<" --CONSTRUCTED"<<endl;
    #endif
}
Station::Station(const string &sName) : name_(sName)
{
    #ifdef _DEBUG
    cout << "Station = " <<(*this)<<" --CONSTRUCTED"<<endl;
    #endif
}
Station::Station(const Station &copy) : name_(copy.name_)
{
    #ifdef _DEBUG
    cout << "Copy Ctor Station = " <<(*this)<<" --CONSTRUCTED"<<endl;
    #endif
}
Station::~Station()
{
    #ifdef _DEBUG
    cout << "Station = " <<(*this)<<" --DESTRUCTED"<<endl;
    #endif
}
double Station::GetDistance(const Station &stationTwo) const
{
    try
    {
        const Railways &IndianRailways = Railways::Type();
        return IndianRailways.GetDistance(*this, stationTwo);
    }
    catch(Bad_Railways &br)
    {
        throw;
    }
}
string Station::GetName() const
{
    return name_;
}

Station Station::GetStation(const string &name)
{
    IsValid(name);
    return Station(name);
}
Station Station::GetStation(const char * name)
{
    IsValid(name);
    return Station(name);
}

//Throws Bad_Station exception if Station construction invalid
void Station::IsValid(const string &name)
{
    if(name=="")
        throw Bad_Station_Name("Station Error: Station cannot have empty name");
    if(name!="Kolkata" && name!= "Delhi" && name!="Chennai" && name!="Mumbai" && name!="Bangalore")
        throw Bad_Station_Name("Station Error: Station not in Database");
}

//Throws Bad_Station exception if Station construction invalid
void Station::IsValid(const char * name)
{
    if(name==NULL)
        throw Bad_Station_Name("Station Error: Station cannot have empty name");
    if(name[0]=='\0')
        throw Bad_Station_Name("Station Error: Station cannot have empty name");
    string nameTemp = name;
    if(nameTemp=="")
    throw Bad_Station_Name("Station Error: Station cannot have empty name");
    if(nameTemp!="Kolkata" && nameTemp!= "Delhi" && nameTemp!="Chennai" && nameTemp!="Mumbai" && nameTemp!="Bangalore")
        throw Bad_Station_Name("Station Error: Station not in Database");
}


ostream &operator<<(ostream &out, const Station &st)
{
    out << st.name_;
    return out;
}

void Station::UnitTest()
{
    int totalCount = 42;
    
    cout << "\n\nCLASS STATION\n\n";
    
    //Test Output streaming operator for Station
    cout << "TESTCASE 1: Output streaming operator for Station: ";
    string outputGolden="Delhi";
    stringstream ss;
    Station stationTest("Delhi");
    ss<<stationTest;
    if(ss.str()==outputGolden)
    {
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout<<"FAIL\n";
    }

    //Checking Station construction

    Station st1("Mumbai");     //Station constructed with const char * as parameter
    if (st1.name_ == "Mumbai"){ //Check if name matches
        totalCount--;
    }
    else{
        cout << "Station Construction Error on Station st1(\"Mumbai\")\n";
    }

    Station st2 = "Kolkata";    //Station constructed by assginment of const char *
    if (st2.name_ == "Kolkata"){ //Check if name matches
        totalCount--;
    }
    else{
        cout << "Station Construction Error on Station st2 = \"Kolkata\" \n";
    }

    string str = "Delhi";
    Station st3(str);     //Station constructed with string object as parameter
    if (st3.name_ == str){ //Check if name matches
        totalCount--;
    }
    else{
        cout << "Station Construction Error on Station st3(" << str << ")\n";
    }

    str = "Chennai";
    Station st4 = str;    //Station constructed by assginment of std::string
    if (st4.name_ == str){ //Check if name matches
        totalCount--;
    }
    else{
        cout << "Station Construction Error on Station st1(" << str << ")\n";
    }

    //Golden Outputs
    vector<string> stationNames = {"Bangalore", "Chennai", "Delhi", "Kolkata", "Mumbai"};
    //Golden Outputs
    map<pair<string, string>, double> mapDist =
        {
            {{"Mumbai", "Kolkata"}, 2014},
            {{"Mumbai", "Chennai"}, 1338},
            {{"Mumbai", "Bangalore"}, 981},
            {{"Mumbai", "Delhi"}, 1447},

            {{"Delhi", "Kolkata"}, 1472},
            {{"Delhi", "Chennai"}, 2180},
            {{"Delhi", "Bangalore"}, 2150},
            {{"Delhi", "Mumbai"}, 1447},

            {{"Kolkata", "Delhi"}, 1472},
            {{"Kolkata", "Chennai"}, 1659},
            {{"Kolkata", "Bangalore"}, 1871},
            {{"Kolkata", "Mumbai"}, 2014},

            {{"Bangalore", "Delhi"}, 2150},
            {{"Bangalore", "Chennai"}, 350},
            {{"Bangalore", "Kolkata"}, 1871},
            {{"Bangalore", "Mumbai"}, 981},

            {{"Chennai", "Delhi"}, 2180},
            {{"Chennai", "Bangalore"}, 350},
            {{"Chennai", "Kolkata"}, 1659},
            {{"Chennai", "Mumbai"}, 1338}};

    //Checking if 'GetDistance(Station)' returns correct distance
    int k=2;
    for (auto it = stationNames.begin(); it != stationNames.end(); ++it)
    {
        for (auto jt = stationNames.begin(); jt != stationNames.end(); ++jt)
        {
            if (it == jt)
            {
                continue;
            }
            double d = Station(*it).GetDistance(*jt);
            //Check distance between *it and *jt
            cout<<"TESTCASE "<<k++<<": Station::GetDistance() returns correct distance between "<< *it << " and " << *jt<<": ";
            if (d == mapDist[{*it, *jt}])
            {
                totalCount--;
                cout<<"PASS\n";
            }
            else{
                cout<<"FAIL\n";
            }
        }
    }
    //Checking if s1.GetDistance(s2) returns the same value as s2.GetDistance(s1)
    for (auto it = stationNames.begin(); it != stationNames.end(); ++it)
    {
        for (auto jt = it + 1; jt != stationNames.end(); ++jt)
        {
            double d1 = Station(*it).GetDistance(*jt);
            double d2 = Station(*jt).GetDistance(*it);
            //Check distance between *it and *jt
            cout << "TESTCASE "<<k++<<": Station::GetDistance() returns correct distance between "<< *it << "-" << *jt<<" and "<< *jt << "-" << *it<<": ";
            if (d1 == d2)
            {
                totalCount--;
                cout<<"PASS\n";
            }
            else{
                cout<<"FAIL\n";
            }
        }
    }

    str = "Kolkata";
    //Checking if 'GetName()' returns 'name_' correctly
    cout << "TESTCASE "<<k++<<" Station::GetName() returns the correct name: ";
    Station st5(str);
    if (st5.GetName() == "Kolkata"){
        totalCount--;
        cout<<"PASS\n";
    }
    else{
        cout << "FAIL\n";
    }
    
    //Checking 'Station' copy construction
    Station st6(st1);
    if(st6.name_==st1.name_){
        totalCount--;
    }
    else{
        cout<<"Station Copy Construction Error on Station("<<st1.name_<<")\n";
    }

    //Testing IsValid()
    //Station name empty
    cout<<"TESTCASE "<<k++<<" (E): Station::IsValid() throws expected exception: ";
    try
    {
        string s = "";
        IsValid(s);
        cout<<"FAIL\n";
    }
    catch(Bad_Station_Name &bs)
    {
        totalCount--;
        cout<<"PASS\n";
        cout<<"    Exception message - "<<bs.what()<<"\n";
    }
    catch(...)
    {
        cout<<"FAIL\n";
        cout<<"    Exception message - Unexpected Error with Empty Name\n";
    }

    //Station not in Database
    cout<<"TESTCASE "<<k++<<" (E): Station::IsValid() throws expected exception: ";
    try
    {
        IsValid("Jammu");
        cout<<"FAIL\n";
    }
    catch(Bad_Station_Name &bs)
    {
        totalCount--;
        cout<<"PASS\n";
        cout<<"    Exception message - "<<bs.what()<<"\n";
    }
    catch(...)
    {
        cout<<"FAIL\n";
        cout<<"    Error message - Unexpected Error with Out of Database Name\n";
    }
    //Distance between same stations
    cout<<"TESTCASE "<<k++<<" (E): Station::GetDistance() throws expected exception: ";
    try
    {
        Station::GetStation("Kolkata").GetDistance(Station::GetStation("Kolkata"));
        cout<<"FAIL\n";
    }
    catch( Distance_Not_Defined bs)
    {
        totalCount--;
        cout<<"PASS\n";
        cout<<"    Exception message - "<<bs.what()<<"\n";
    }
    catch(...)
    {
        cout<<"FAIL\n";
        cout<<"Error message - Unexpected Error with Same Name in GetDistance\n";
    }
    //GetStation check - valid data
    cout<<"TESTCASE "<<k++<<": Station::GetStation() returns correctly constructed Station: ";
    try
    {
        Station::GetStation("Kolkata");
        totalCount--;
        cout<<"PASS\n";
    }
    catch(...)
    {
        cout<<"FAIL\n";
        cout<<"Error message - Unexpected Error thrown for valid data\n";
    }

    //GetStation check - invalid data
    cout<<"TESTCASE "<<k++<<" (E): Station::GetStation() throws expected exception: ";
    try
    {
        Station::GetStation("");
        cout<<"FAIL\n";
    }
    catch(Bad_Station_Name &bs)
    {
        totalCount--;
        cout<<"PASS\n";
        cout<<"    Exception message - "<<bs.what()<<"\n";
    }
    cout<<"\n----- VERDICT : ";
    if(totalCount==0)
    {
        cout<<"PASS -----\n";
    }
    else 
        cout<<totalCount<<"/42 Tests FAILED -----\n";
}