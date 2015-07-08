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
void HPlatformHelper::share(int shareType,int shareFrom,std::string path){


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	HHPlatform::GetInstance()->share(shareType,shareFrom,path);
#endif
}
void HPlatformHelper::showRank(int score){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    HHPlatform::GetInstance()->showRank(score);
#endif
}
void HPlatformHelper::commitScore(int score){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    HHPlatform::GetInstance()->commitScore(score);
#endif
}
void HPlatformHelper::showFullAd(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    HHPlatform::GetInstance()->showFullAD();
#endif
}
void HPlatformHelper::showAd(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    HHPlatform::GetInstance()->showAd();
#endif
}
void HPlatformHelper::showToast(std::string m_content){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    HHPlatform::GetInstance()->showToast(m_content);
#endif

}












