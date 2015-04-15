//
//  MainLayer.h
//  GWPJUMP
//
//  Created by 易水流年 on 4/4/15.
//
//

#ifndef __GWPJUMP__MainLayer__
#define __GWPJUMP__MainLayer__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class MainLayer :public Layer{
    MainLayer();
    ~MainLayer();
public:
    CREATE_FUNC(MainLayer);
    bool init();
private:
    void initBg();
    void initLogo();
    void initMenu();
    void initHero();
    
    
//    void acLogo();
//    void acHero();
//    void acMenu();
public:
    void menuSet(Ref* sender);
    void menuRank(Ref* sender);
    void menuShare(Ref* sender);
    void menuStart(Ref* sender);
private:
    Sprite* m_logo = NULL;
    Sprite* m_hero = NULL;
    Node* m_menu = NULL;
    Node* m_shareNode = NULL;
};

#endif /* defined(__GWPJUMP__MainLayer__) */
