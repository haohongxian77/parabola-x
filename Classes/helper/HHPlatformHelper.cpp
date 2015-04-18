//
//  HHPlatformHelper.cpp
//  GwsJump
//
//  Created by 易水流年 on 4/18/15.
//
//

#include "HHPlatformHelper.h"
HHPlatformHelper* HHPlatformHelper::platfromHelper = NULL;
HHPlatformHelper* HHPlatformHelper::getInstance(){
    if (platfromHelper == NULL) {
        platfromHelper = new HHPlatformHelper();
    }
    return platfromHelper;
}
HHPlatformHelper::HHPlatformHelper(){
}
HHPlatformHelper::~HHPlatformHelper(){
}
void HHPlatformHelper::share(std::string fullPath){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
#endif
}