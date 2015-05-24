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
    Sprite* m_bg = NULL;
    
    Node* nodeBg1 = NULL;
    Sprite* m_bgMid1_1 = NULL;
    Sprite* m_bgMid1_2 = NULL;
    
    Node* nodeBg2 = NULL;
    Sprite* m_bgMid2_1 = NULL;
    Sprite* m_bgMid2_2 = NULL;
    
    Sprite* m_Cloud1 = NULL;
    Sprite* m_Cloud2 = NULL;
    Sprite* m_Cloud3 = NULL;
    
    void initSprite();
    bool init();
    void initBg();
    void initMid1Bg();
    void initMid2Bg();
    void initClound();

public:
    CREATE_FUNC(GameBgLayer);
    void update(float dt,float bgMoveSpeed);
    void changeSprite();
private:
    void updateMid1Bg(float dX);
    void updateMid2Bg(float dX);
    void initClound11Position();
    void initClound12Position();
    void initClound13Position();
};
#endif /* defined(__GwsJump__GameBgLayer__) */
