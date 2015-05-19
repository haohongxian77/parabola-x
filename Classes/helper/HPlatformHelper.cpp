//
//  HPlatformHelper.cpp
//  GwsJump
//
//  Created by 易水流年 on 4/18/15.
//
//

#include "HPlatformHelper.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/HHPlatform.h"
#endif
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
void HPlatformHelper::share(int shareType,std::string fullPath){


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	HHPlatform::GetInstance()->share(shareType,fullPath);
#endif
}
void HPlatformHelper::showRank(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    HHPlatform::GetInstance()->showRank();
#endif
}
