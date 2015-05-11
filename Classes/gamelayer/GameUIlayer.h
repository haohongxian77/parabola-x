//
//  GameUIlayer.h
//  GwsJump
//
//  Created by 易水流年 on 5/9/15.
//
//

#ifndef __GwsJump__GameUIlayer__
#define __GwsJump__GameUIlayer__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class GameUIlayer :public Node{
    GameUIlayer();
    ~GameUIlayer();
public:
    CREATE_FUNC(GameUIlayer);
    void changeScore(int curScore);
private:
    bool init();
    Sprite* m_scoreBg ;
    LabelAtlas* m_scoreLabel ;
    
};

#endif /* defined(__GwsJump__GameUIlayer__) */
