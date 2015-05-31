//
//  GameGuildLayer.h
//  GwsJump
//
//  Created by 易水流年 on 5/30/15.
//
//

#ifndef __GwsJump__GameGuildLayer__
#define __GwsJump__GameGuildLayer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class GameGuildLayer : public Layer{
    GameGuildLayer();
    ~GameGuildLayer();
public:
    CREATE_FUNC(GameGuildLayer);
private:
    virtual bool init();
    void initBg();
    void initMenu();
    void initArrow();
    void startGame(cocos2d::Ref *sender);
    
};

#endif /* defined(__GwsJump__GameGuildLayer__) */
