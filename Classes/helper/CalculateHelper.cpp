//
//  CalculateHelper.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 3/19/15.
//
//

#include "CalculateHelper.h"

std::vector<float> CalculateHelper::getPathParametersXAHK(Point _curPoint, Point highestPoint){
    std::vector<float> param_ ;
    //y = a(x - h)^2 +k;
    float k= highestPoint.y;
    float h= highestPoint.x;
    float dY = _curPoint.y- k;
    float  dx = _curPoint.x -h;
    float a = dY/dx/dx;
    param_.push_back(a);
    param_.push_back(h);
    param_.push_back(k);
    return param_;
    
//    float a = i;
//    float b = -1*2*i*highestPoint.x;
//    float c = i*highestPoint.x*highestPoint.x+highestPoint.y;
    
}
float CalculateHelper::getPathAHK(float X, std::vector<float> params,bool isPositive /*= false*/){
    if (params.size()<3) {
        return -1;
    }
    return params[0]*(X-params[1])*(X-params[1])+params[2];
    //return pos*sqrt(abs((y-params[2])/params[0]))+params[1];
}
std::vector<float> CalculateHelper::getPathParametersXABC(Point _curPoint, Point highestPoint){
    std::vector<float> param_ ;
    /*
     y = a(x - h)^2 +k;
     y = ax^2 +b*x +c ;
     */
    float k= highestPoint.y;
    float h= highestPoint.x;
    float dY = _curPoint.y- k;
    float  dx = _curPoint.x -h;
    float a = dY/dx/dx;
    float b = -1*2*a*highestPoint.x;
    float c = a*highestPoint.x*highestPoint.x+highestPoint.y;
    
    param_.push_back(a);
    param_.push_back(b);
    param_.push_back(c);
    return param_;
    
}
float CalculateHelper::getPathABC(float x, std::vector<float> params){
    if (params.size()<3) {
        return -1;
    }
    return params[0]*x*x+params[1]*x+params[2];
}















