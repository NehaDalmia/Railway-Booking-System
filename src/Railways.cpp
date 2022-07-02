#include "Station.h"
#include "Railways.h"
#include <bits/stdc++.h>
#include "Exceptions.h"
using namespace std;
const map<pair<string, string>, double> Railways::sDistStations =
    {{{"Mumbai", "Kolkata"}, 2014},
     {{"Mumbai", "Chennai"}, 1338},
     {{"Mumbai", "Bangalore"}, 981},
     {{"Mumbai", "Delhi"}, 1447},

     {{"Delhi", "Kolkata"}, 1472},
     {{"Delhi", "Chennai"}, 2180},
     {{"Delhi", "Bangalore"}, 2150},

     {{"Kolkata", "Chennai"}, 1659},
     {{"Kolkata", "Bangalore"}, 1871},

     {{"Bangalore", "Chennai"}, 350}};

const vector<string> Railways::sStations = {"Mumbai", "Bangalore", "Delhi", "Chennai", "Kolkata"};

Railways::Railways()
{
    #ifdef _DEBUG
    cout << "Railways = " <<(*this)<<" --CONSTRUCTED"<<endl;
    #endif
}

double Railways::GetDistance(const Station &startSt, const Station &endSt) const
{
    if(startSt.GetName()==endSt.GetName())
        throw Distance_Not_Defined("Railways Error: Finding distance between two same Stations is not allowed");
    if(Railways::sDistStations.find(make_pair(startSt.GetName(), endSt.GetName()))==Railways::sDistStations.end() && Railways::sDistStations.find(make_pair(endSt.GetName(),startSt.GetName()))==Railways::sDistStations.end()  )
        throw Distance_Not_Defined("Given pair of Railways Does not Exist in the DataBase\n");
    if(Railways::sDistStations.find(make_pair(startSt.GetName(), endSt.GetName()))!=Railways::sDistStations.end())
        return (*(Railways::sDistStations.find(make_pair(startSt.GetName(), endSt.GetName())))).second;
    else
        return (*(Railways::sDistStations.find(make_pair(endSt.GetName(),startSt.GetName())))).second;
}

const Railways &Railways::Type()
{
    static const Railways IndianRailways;
    return IndianRailways;
}

ostream &operator<<(ostream &out, const Railways &obj)
{
    out << "Stations: \n";
    for (auto it = Railways::sStations.begin(); it != Railways::sStations.end(); ++it)
    {
        out << it - Railways::sStations.begin() + 1 << ". " << *it << "\n";
    }
    out << "\nDistances between Stations:\n";
    for (auto it : Railways::sDistStations)
    {
        cout << it.first.first << " - TO - " << it.first.second << " - " << it.second << " KM\n";
    }
    return out;
}
void Railways::IsValid()
{
    const Railways& testobj = Railways::Type();
    //Duplicate Stations Check
    if(std::count(testobj.sStations.begin(),testobj.sStations.end(),"Kolkata")!=1)
        throw Duplicate_Station("Railways Error: Duplicate Station found - Kolkata");
    if(std::count(testobj.sStations.begin(),testobj.sStations.end(),"Delhi")!=1)
        throw Duplicate_Station("Railways Error: Duplicate Station found - Delhi");
    if(std::count(testobj.sStations.begin(),testobj.sStations.end(),"Bangalore")!=1)
        throw Duplicate_Station("Railways Error: Duplicate Station found - Bangalore");
    if(std::count(testobj.sStations.begin(),testobj.sStations.end(),"Chennai")!=1)
        throw Duplicate_Station("Railways Error: Duplicate Station found - Chennai");
    if(std::count(testobj.sStations.begin(),testobj.sStations.end(),"Mumbai")!=1)
        throw Duplicate_Station("Railways Error: Duplicate Station found - Mumbai");
    
    //Both directions stored
    if(testobj.sDistStations.find({"Mumbai", "Kolkata"})!=testobj.sDistStations.end() && testobj.sDistStations.find({"Kolkata", "Mumbai"})!=testobj.sDistStations.end())
        throw Bad_Railways("Railways Error: Distance between both pairs found");
    if(testobj.sDistStations.find({"Mumbai", "Bangalore"})!=testobj.sDistStations.end() && testobj.sDistStations.find({"Bangalore", "Mumbai"})!=testobj.sDistStations.end())
        throw Bad_Railways("Railways Error: Distance between both pairs found");
    if(testobj.sDistStations.find({"Mumbai", "Chennai"})!=testobj.sDistStations.end() && testobj.sDistStations.find({"Chennai", "Mumbai"})!=testobj.sDistStations.end())
        throw Bad_Railways("Railways Error: Distance between both pairs found");
    if(testobj.sDistStations.find({"Mumbai", "Delhi"})!=testobj.sDistStations.end() && testobj.sDistStations.find({"Delhi", "Mumbai"})!=testobj.sDistStations.end())
        throw Bad_Railways("Railways Error: Distance between both pairs found");
    if(testobj.sDistStations.find({"Delhi", "Kolkata"})!=testobj.sDistStations.end() && testobj.sDistStations.find({"Kolkata", "Delhi"})!=testobj.sDistStations.end())
        throw Bad_Railways("Railways Error: Distance between both pairs found");
    if(testobj.sDistStations.find({"Delhi", "Chennai"})!=testobj.sDistStations.end() && testobj.sDistStations.find({"Chennai", "Delhi"})!=testobj.sDistStations.end())
        throw Bad_Railways("Railways Error: Distance between both pairs found");
    if(testobj.sDistStations.find({"Delhi", "Bangalore"})!=testobj.sDistStations.end() && testobj.sDistStations.find({"Bangalore", "Delhi"})!=testobj.sDistStations.end())
        throw Bad_Railways("Railways Error: Distance between both pairs found");
    if(testobj.sDistStations.find({"Kolkata", "Bangalore"})!=testobj.sDistStations.end() && testobj.sDistStations.find({"Bangalore", "Kolkata"})!=testobj.sDistStations.end())
        throw Bad_Railways("Railways Error: Distance between both pairs found");
    if(testobj.sDistStations.find({"Kolkata", "Chennai"})!=testobj.sDistStations.end() && testobj.sDistStations.find({"Chennai", "Kolkata"})!=testobj.sDistStations.end())
        throw Bad_Railways("Railways Error: Distance between both pairs found");
    if(testobj.sDistStations.find({"Chennai", "Bangalore"})!=testobj.sDistStations.end() && testobj.sDistStations.find({"Bangalore", "Chennai"})!=testobj.sDistStations.end())
        throw Bad_Railways("Railways Error: Distance between both pairs found");
    
    //Checking distance between every pair is there
    if(testobj.sDistStations.count({"Mumbai","Kolkata"})!=1)
        throw Incomplete_Distance_Information("Railways Error: Distance not found between Mumbai and Kolkata");
    if(testobj.sDistStations.count({"Mumbai","Delhi"})!=1)
        throw Incomplete_Distance_Information("Railways Error: Distance not found between Mumbai and Delhi");
    if(testobj.sDistStations.count({"Mumbai","Chennai"})!=1)
        throw Incomplete_Distance_Information("Railways Error: Distance not found between Mumbai and Chennai");
    if(testobj.sDistStations.count({"Mumbai","Bangalore"})!=1)
        throw Incomplete_Distance_Information("Railways Error: Distance not found between Mumbai and Bangalore");
    if(testobj.sDistStations.count({"Delhi","Kolkata"})!=1)
        throw Incomplete_Distance_Information("Railways Error: Distance not found between Delhi and Kolkata");
    if(testobj.sDistStations.count({"Delhi","Bangalore"})!=1)
        throw Incomplete_Distance_Information("Railways Error: Distance not found between Delhi and Bangalore");
    if(testobj.sDistStations.count({"Delhi","Chennai"})!=1)
        throw Incomplete_Distance_Information("Railways Error: Distance not found between Delhi and Chennai");
    if(testobj.sDistStations.count({"Kolkata","Bangalore"})!=1)
        throw Incomplete_Distance_Information("Railways Error: Distance not found between Kolkata and Bangalore");
    if(testobj.sDistStations.count({"Kolkata","Chennai"})!=1)
        throw Incomplete_Distance_Information("Railways Error: Distance not found between Kolkata and Chennai");
    if(testobj.sDistStations.count({"Bangalore","Chennai"})!=1)
        throw Incomplete_Distance_Information("Railways Error: Distance not found between Bangalore and Chennai");
    
    //Pair has both elements same
    if(testobj.sDistStations.count({"Bangalore","Bangalore"}))
        throw Bad_Railways("Railways Error: Distance between same stations");
    if(testobj.sDistStations.count({"Chennai","Chennai"}))
        throw Bad_Railways("Railways Error: Distance between same stations ");
    if(testobj.sDistStations.count({"Kolkata","Kolkata"}))
        throw Bad_Railways("Railways Error: Distance between same stations");
    if(testobj.sDistStations.count({"Delhi","Delhi"}))
        throw Bad_Railways("Railways Error: Distance between same stations");
    if(testobj.sDistStations.count({"Mumbai","Mumbai"}))
        throw Bad_Railways("Railways Error: Distance between same stations ");
}
void Railways::UnitTest()
{
    int counter = 5 + 20 + 10 + 3;

    cout << "\n\nCLASS RAILWAYS\n\n";
    const Railways &testObj = Railways::Type();

    // //Check if class 'Railways' is indeed a Singleton
    // const Railways &testObj2 = Railways::Type();
    // if (&testObj2 != &testObj) //Check the addresses of the two objects
    // {
    //     cout << "class \'Railways\' is not a Singleton";
    //     counter--;
    // }

    //Check if sStations stores all the required stations
    int k=1;
    vector<string> stationNames = {"Bangalore", "Chennai", "Delhi", "Kolkata", "Mumbai"}; //Golden Outputs
    for (auto it = stationNames.begin(); it != stationNames.end(); it++)
    {
        bool match = false;
        cout<<"TESTCASE "<<k++<<": Checking if "<<*it<<" is present in the static data: ";
        for (auto jt = stationNames.begin(); jt != stationNames.end(); jt++)
        {
            if (*it == *jt)
            {
                match = true;
                cout<<"PASS\n";
                counter--;
                break;
            }
        }
        if (!match)
        {
            cout<<"FAIL\n";
        }
    }

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

    //Check if sDistStations stores correct distance between stations (matching with Golden Output)

    for (auto it = stationNames.begin(); it != stationNames.end(); it++)
    {
        for (auto jt = it+1; jt != stationNames.end(); jt++)
        {
            double dist;
            if(sDistStations.count({*jt, *it})){
                dist = sDistStations.at({*jt, *it});
            }
            else {
                dist = sDistStations.at({*it, *jt});
            }
            //Check distance between *it and *jt
            cout<<"TESTCASE "<<k++<<": Railways::sDistStations stores the correct distances between "<<*it<<" and "<<*jt<<": ";
            if (dist == mapDist[{*it, *jt}])
            {
                cout<<"PASS\n";
                counter--;
            }
            else
            {
                cout << "FAIL\n";
            }
        }
    }

    //Check if testObj.GetDistance() returns correct distance between stations (matching with sDistStations)

    for (auto it = stationNames.begin(); it != stationNames.end(); it++)
    {
        for (auto jt = stationNames.begin(); jt != stationNames.end(); jt++)
        {
            if (*it == *jt)
            {
                continue;
            }
            double dist = testObj.GetDistance(Station::GetStation(*it), Station::GetStation(*jt));
            //Check distance between *it and *jt
            cout<<"TESTCASE "<<k++<<": Railways::GetDistance() returns the correct distances between "<<*it<<" and "<<*jt<<": ";
            if (dist == mapDist[{*it, *jt}])
            {
                cout<<"PASS\n";
                counter--;
            }
            else
            {
                cout << "FAIL\n";
            }
        }
    }
    //Checking all the exceptional Cases
    bool f = true;
    //1. Check whether IsValid returns true
    cout<<"TESTCASE "<<k++<<" : Check if all the data is valid using Railways:: IsValid(): ";
    try
    {
        Railways::IsValid();
        cout<<"PASS\n";
        counter--;
    }
    catch(Duplicate_Station &ds)
    {
        cout<<"FAIL\n";
        cout<<"Unexpected Error: ";
        cout<<ds.what()<<"\n";
    }
    catch(Bad_Railways &br)
    {
        cout<<"FAIL\n";
        cout<<"Unexpected Error: ";
        cout<<br.what()<<"\n";
    }
    catch(...)
    {
        cout<<"FAIL\n";
        cout<<"Unknown error thrown\n";
    }

    cout<<"TESTCASE "<<k++<<": Railways::GetDistance() Error Between Equal Stations : ";
    //GetDistance() between Equal Stations
    try
    {
        Railways::Type().GetDistance(Station::GetStation("Kolkata"),Station::GetStation("Kolkata"));
    }
    catch(Distance_Not_Defined ds)
    {
        counter--;
        cout<<"PASS\n";
        cout<<"    Expected Exception: "<<ds.what()<<"\n";
    }
    catch(...)
    {
        cout<<"FAIL\n";
        cout<<"Unknown error thrown";
    }

    cout<<"TESTCASE "<<k++<<": Railways::GetDistance() Error Between Non existent Distance : ";
    //Get Distance betwwen Non existent stations
    try
    {
        Railways::Type().GetDistance(Station::GetStation("Kolkata"),Station::GetStation("Jammu"));
    }
    catch(Bad_Station_Name bs)
    {
        counter--;
        cout<<"PASS\n";
        cout<<"    Expected Exception: "<<bs.what()<<"\n";
    }
    catch(...)
    {
        cout<<"FAIL\n";
        cout<<"Unknown error thrown\n";
    }
    cout<<"\n----- VERDICT : ";
    if(counter==0)
    {
        cout<<"PASS -----\n";
    }
    else 
    {
        cout<<counter<<" Test Cases FAILED -----\n";
    }
}
Railways::~Railways()
{
    #ifdef _DEBUG
    cout << "Railways = " <<(*this)<<" --DESTRUCTED"<<endl;
    #endif
}