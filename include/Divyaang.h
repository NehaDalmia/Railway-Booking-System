// #define _DEBUG
#ifndef DIVYAANG_H
#define DIVYAANG_H

#include "BookingClasses.h"
#include <iomanip>

template<typename T>
class DisabilityTypes;

class Divyaang {
private:
    struct BlindType{};
    struct OrthopaedicallyHandicappedType{};
    struct CancerPatientType{};
    struct TBPatientType{};
    Divyaang(const Divyaang& d);
protected:
    Divyaang();           //Ctor
    virtual ~Divyaang();  //Virtual dtor for polymorphic hierarchy

public:
    virtual string GetName() const = 0;
    virtual double GetDivyaangConcessionFactor(const BookingClasses::ACFirstClass&) const = 0;
    virtual double GetDivyaangConcessionFactor(const BookingClasses::ExecutiveChairCar&) const = 0;
    virtual double GetDivyaangConcessionFactor(const BookingClasses::AC2Tier&) const = 0;
    virtual double GetDivyaangConcessionFactor(const BookingClasses::FirstClass&) const = 0;
    virtual double GetDivyaangConcessionFactor(const BookingClasses::ACChairCar&) const = 0;
    virtual double GetDivyaangConcessionFactor(const BookingClasses::AC3Tier&) const = 0;
    virtual double GetDivyaangConcessionFactor(const BookingClasses::Sleeper&) const = 0;
    virtual double GetDivyaangConcessionFactor(const BookingClasses::SecondSitting&) const = 0;
    friend ostream &operator<<(ostream &out, const Divyaang &d);
    static void UnitTest();

    typedef DisabilityTypes<BlindType> Blind;
    typedef DisabilityTypes<OrthopaedicallyHandicappedType> OrthopaedicallyHandicapped;
    typedef DisabilityTypes<CancerPatientType> CancerPatient;
    typedef DisabilityTypes<TBPatientType> TBPatient;
};

template<typename T>
class DisabilityTypes : public Divyaang {
private:
    static const string sName;
    static const double sACFirstClassConcession;
    static const double sExecutiveChairCarConcession;
    static const double sAC2TierConcession;
    static const double sFirstClassConcession;
    static const double sAC3TierConcession;
    static const double sACChairCarConcession;
    static const double sSleeperConcession;
    static const double sSecondSittingConcession;
    DisabilityTypes();
    DisabilityTypes(const DisabilityTypes& d);
public:
    ~DisabilityTypes();
    static const DisabilityTypes<T>& Type();
    string GetName() const;
    double GetDivyaangConcessionFactor(const BookingClasses::ACFirstClass&) const;
    double GetDivyaangConcessionFactor(const BookingClasses::ExecutiveChairCar&) const;
    double GetDivyaangConcessionFactor(const BookingClasses::AC2Tier&) const;
    double GetDivyaangConcessionFactor(const BookingClasses::FirstClass&) const;
    double GetDivyaangConcessionFactor(const BookingClasses::ACChairCar&) const;
    double GetDivyaangConcessionFactor(const BookingClasses::AC3Tier&) const;
    double GetDivyaangConcessionFactor(const BookingClasses::Sleeper&) const;
    double GetDivyaangConcessionFactor(const BookingClasses::SecondSitting&) const;
    friend ostream &operator<<(ostream &out, const DisabilityTypes<T> &d) {
        out<<d.GetName();
        return out;
    }
    
};
#endif  //DIVYAANG_H