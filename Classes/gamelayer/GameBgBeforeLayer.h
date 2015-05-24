//
//  GameBgBeforeLayer.h
//  GwsJump
//
//  Created by 易水流年 on 4/26/15.
//
//

#ifndef __GwsJump__GameBgBeforeLayer__
#define __GwsJump__GameBgBeforeLayer__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class GameBgBeforeLayer :public Layer{
    GameBgBeforeLayer();
    ~GameBgBeforeLayer();
private:
    Sprite* m_bg1 = NULL;
    Sprite* m_bg2 = NULL;
    
    
    bool init();
    void initBg();
public:
    CREATE_FUNC(GameBgBeforeLayer);
    void update(float dt,float bgMoveSpeed);
    void changeSprite();
private:
    void updateBg(float dX);
};

#endif /* defined(__GwsJump__GameBgBeforeLayer__) */
