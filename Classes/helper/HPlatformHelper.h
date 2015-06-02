//
//  HPlatformHelper.h
//  GwsJump
//
//  Created by 易水流年 on 4/18/15.
//
//

#ifndef __GwsJump__HPlatformHelper__
#define __GwsJump__HPlatformHelper__

#include <stdio.h>
#include "cocos2d.h"
class HPlatformHelper {
    HPlatformHelper();
    ~HPlatformHelper();
public:
    static HPlatformHelper* platfromHelper;
    static HPlatformHelper* getInstance();
    void share(int shareType,int shareFrom,std::string path);
    void showRank();
    void commitScore(int score);
    void showFullAd();
    void showToast(std::string content);
};
#endif /* defined(__GwsJump__HPlatformHelper__) */
