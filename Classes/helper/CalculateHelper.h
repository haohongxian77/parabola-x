//
//  CalculateHelper.h
//  GWPJUMP
//
//  Created by 易水流年 on 3/19/15.
//
//

#ifndef __GWPJUMP__CalculateHelper__
#define __GWPJUMP__CalculateHelper__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class CalculateHelper{

public:
    static std::vector<float> getPathParametersXAHK(Point _curPoint,Point highestPoint);
    static float getPathAHK (float X, std::vector<float> params,bool isPositive = false);
    
    static std::vector<float> getPathParametersXABC(Point _curPoint,Point highestPoint);
    static float getPathABC (float X, std::vector<float> params);
   
    
    
};

#endif /* defined(__GWPJUMP__CalculateHelper__) */
