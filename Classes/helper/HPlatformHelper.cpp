//
//  HPlatformHelper.cpp
//  GwsJump
//
//  Created by 易水流年 on 4/18/15.
//
//

#include "HPlatformHelper.h"
HPlatformHelper* HPlatformHelper::platfromHelper = NULL;
HPlatformHelper* HPlatformHelper::getInstance(){
    if (platfromHelper == NULL) {
        platfromHelper = new HPlatformHelper();
    }
    return platfromHelper;
}
HPlatformHelper::HPlatformHelper(){
}
HPlatformHelper::~HPlatformHelper(){
}
void HPlatformHelper::share(std::string fullPath){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
#endif
}