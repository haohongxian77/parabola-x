//
//  GameBgLayer.h
//  GwsJump
//
//  Created by 易水流年 on 4/18/15.
//
//

#ifndef __GwsJump__GameBgLayer__
#define __GwsJump__GameBgLayer__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class GameBgLayer :public Layer{
    GameBgLayer();
    ~GameBgLayer();
private:
    Sprite* m_bg1 = NULL;
    Sprite* m_bg2 = NULL;
    
    
    bool init();
    void initBg();
    void initClound(Sprite* node);
public:
    CREATE_FUNC(GameBgLayer);
    void update(float dt,float bgMoveSpeed);
private:
    void updateBg(float dX);
};
#endif /* defined(__GwsJump__GameBgLayer__) */
