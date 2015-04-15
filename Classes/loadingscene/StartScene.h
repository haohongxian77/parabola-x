//
//  StartScene.h
//  GWPJUMP
//
//  Created by 易水流年 on 4/4/15.
//
//

#ifndef __GWPJUMP__StartScene__
#define __GWPJUMP__StartScene__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class StartScene : public cocos2d::Scene
{
public:
    bool init();
    void initLayer();
    
    // a selector callback
    CREATE_FUNC(StartScene);
};

#endif /* defined(__GWPJUMP__StartScene__) */
