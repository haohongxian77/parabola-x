//
//  HHPlatformHelper.h
//  GwsJump
//
//  Created by 易水流年 on 4/18/15.
//
//

#ifndef __GwsJump__HHPlatformHelper__
#define __GwsJump__HHPlatformHelper__

#include <stdio.h>
class HHPlatformHelper {
    HHPlatformHelper();
    ~HHPlatformHelper();
public:
    static HHPlatformHelper* platfromHelper;
    static HHPlatformHelper* getInstance();
    void share(std::string fullPath);
};


#endif /* defined(__GwsJump__HHPlatformHelper__) */
