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
    
    Sprite* m_Cloud1 = NULL;
    Sprite* m_Cloud2 = NULL;
    Sprite* m_Cloud3 = NULL;
    
    bool init();
    void initBg();
    void initClound();
public:
    CREATE_FUNC(GameBgLayer);
    void update(float dx);
    void initClound1Pos();
    void initClound2Pos();
    void initClound3Pos();
public:
    void clound1AC();
    void clound2AC();
    void clound3AC();
};
#endif /* defined(__GwsJump__GameBgLayer__) */
