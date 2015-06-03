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
    FrogNone = -1,
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
    FrogStatus m_heroStatus;
    FrogStatus getHeroStatus();
    void setHeroStatus(FrogStatus heroStatus);
    void setHeroMoveParam(Point downPoint,float downAniSpeed, FrogStatus status);
    void setCurPosition(Point pos);
    void setHeroMoveOver();
    bool setHeroFall();
    FrogStatus getPathOverStatus();
public:
    CREATE_FUNC(HeroFrog);
    Rect getFootRect(Point curPoint);
    Rect getBodyRect(Point curPoint);
    void setIsLongJump(bool longJump_);
    void updateMusic(float dt);
private:
    bool init();
    void initData();
    void initAnimation();
    void runStaticAnimation();

    void setHeroStatic();
    void stopAnimation();
    
    
private:
    float downSpeed = 0;
    DrawNode* drawNode;
    //最高点动作转换的动画
    Point downPoint;
    float downAnimSpeed;
    FrogStatus pathoverStatus;
    bool m_isLongJump;
    float m_dStaticMusicTime;
    
    
    
    
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
    
};

#endif /* defined(__GWPJUMP__HeroFrog__) */
