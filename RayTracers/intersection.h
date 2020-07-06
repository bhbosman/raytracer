#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "color.h"
#include "material.h"
#include "SurfaceDimension.h"
#include <boost/shared_ptr.hpp>
#include "colorcalculation.h"
enum InterSectionType
{
    InterSectionType_No = 0,
    InterSectionType_Outside = -10,
    InterSectionType_Inside = 10
};



#endif // INTERSECTION_H
