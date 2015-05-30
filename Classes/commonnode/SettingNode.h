//
//  SettingLayer.h
//  GWPJUMP
//
//  Created by 易水流年 on 4/5/15.
//
//

#ifndef __GWPJUMP__SettingLayer__
#define __GWPJUMP__SettingLayer__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class SettingNode : public Node{
    SettingNode();
    ~SettingNode();
public:
    CREATE_FUNC(SettingNode);
private:
    Sprite* bg = NULL;
    Sprite* musicVisible;
    Sprite* SoundVisible;
    Sprite* rankVisible;
    
    bool init();
    void initBg();
    void initMenu();
    void acNode();
    void initSprite();
public:
    void menuSound(Ref* obj);
    void menuMusic(Ref* obj);
    void menuRank(Ref* obj);
    void menuHome(Ref* obj);
    
};

#endif /* defined(__GWPJUMP__SettingLayer__) */
