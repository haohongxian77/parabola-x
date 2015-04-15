//
//  HeroFrog.h
//  GWPJUMP
//
//  Created by 易水流年 on 3/21/15.
//
//

#ifndef __GWPJUMP__HeroFrog__
#define __GWPJUMP__HeroFrog__
typedef enum{
    frogStatic=0,      //主角静止
    frogTakeoff,       //主角起跳
    frogJumpUp,        //主角上跳
    frogJumpDown,      //主角下跳
    frogFall,          //主角落地
    frogDead1,         //主角死亡碰桩子死亡
    frogDead2,         //主角掉地上死亡
}FrogStatus;
#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class HeroFrog :public Sprite{
    HeroFrog();
    ~HeroFrog();
public:
    CC_SYNTHESIZE(FrogStatus, m_heroStatus, HeroStatus);
public:
    CREATE_FUNC(HeroFrog);
private:
    bool init();
    void setPos(Point pos);
};

#endif /* defined(__GWPJUMP__HeroFrog__) */
