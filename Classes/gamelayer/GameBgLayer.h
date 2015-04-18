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
    Sprite* bg1 = NULL;
    Sprite* bg2 = NULL;
    
    bool init();
    void initBg();
public:
    CREATE_FUNC(GameBgLayer);
};
#endif /* defined(__GwsJump__GameBgLayer__) */
