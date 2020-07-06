#ifndef PHONELIGHTINGMODELCALCULATION_H
#define PHONELIGHTINGMODELCALCULATION_H

#include "color.h"
#include "phonglightingmodel.h"

template <typename T>
class PhoneLightingModelCalculation
{
public:
    static T Calculate(const PhongLightingParameters<T>& param)
    {
        Vector h = (param.LUnit().dot(param.VUnit())) / (param.LUnit() + param.VUnit()).squaredLength();
        h.normalise();
        T compE = param.Ie();

        T compA = param.Ia() * param.Pa();

        double tempDOT = param.LUnit().dot(param.NUnit());
        T compD = param.Id() * param.Pd() * fmax(0, tempDOT);

        tempDOT =  param. VUnit().dot(param.LUnit());
//        tempDOT =  param. VUnit().dot(param.RUnit());

        T compS = param.Is() * param.Ps() * pow(fmax(0, tempDOT), param.F());
        tempDOT = param.VUnit().dot(param.NUnit());
        if (tempDOT < 0)
        {
            compS = 0;
        }

        T I = compE+ compA + compD + compS;
        return I;
    }
};

#endif // PHONELIGHTINGMODELCALCULATION_H
