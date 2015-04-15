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
    
    bool init();
    void initBg();
    void initMenu();
    void acNode();
public:
    void menuSound(Ref* obj);
    void menuMusic(Ref* obj);
    
};

#endif /* defined(__GWPJUMP__SettingLayer__) */
