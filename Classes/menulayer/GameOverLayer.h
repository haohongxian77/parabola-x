//
//  GameOverLayer.h
//  GWPJUMP
//
//  Created by 易水流年 on 4/12/15.
//
//

#ifndef __GWPJUMP__GameOverLayer__
#define __GWPJUMP__GameOverLayer__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class GameOverLayer :public Layer{
private:
    bool init();
    void initBg();
    void initScore();
    void initHeroAni();
    bool isNewHight ;
public:
    CREATE_FUNC(GameOverLayer);
};

#endif /* defined(__GWPJUMP__GameOverLayer__) */
