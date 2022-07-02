// #define _DEBUG
#ifndef RAILWAYS_H
#define RAILWAYS_H

#include <vector>
#include <map>
#include "Station.h"

using namespace std;

//SINGLETON, NOT EXTENSIBLE, CONCRETE
class Railways
{
private:
    //STATIC MEMBERS 
    static const vector<string> sStations;                          //List of Stations
    static const map<pair<string, string>, double> sDistStations;   //List of pairwise distances between all stations
    //--------------

    Railways();                             //private constructor, as class is Singleton and not extendable
    Railways(const Railways &);             //Blocked copy constructor, as not in usage
    Railways operator=(const Railways &);   //Blocked copy assignment operator, as not in usage
    ~Railways();                            //private destructor, as class is Singleton and not extendable

public:
    //STATIC METHODS
    static const Railways &Type();          //Returns a singleton const static object of the class
    static void UnitTest();         //Unit Testing function
    //--------------
    static void IsValid();
    double GetDistance(const Station &startSt, const Station &endSt) const; //Returns the distance between the start and end stations passed as arguments
    friend ostream &operator<<(ostream &out, const Railways &rlw);  //Output streaming operator for this class
};

#endif