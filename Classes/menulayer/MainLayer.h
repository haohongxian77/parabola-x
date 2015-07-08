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
#include "menulayer/GameMainLogoLayer.h"
#include "menulayer/GameOverLayer.h"
#include "helper/CommomData.h"
using namespace cocos2d;
class MainLayer :public Layer{
    MainLayer();
    ~MainLayer();
public:
    static MainLayer* create(gameStatus status);
    //CREATE_FUNC(MainLayer);
    bool init();
private:
    void initOtherMenu(gameStatus status);
    void initBg();
    void initMenu();
    void initAC();
    void onEnter();
    void onExit();
    
    
//    void acLogo();
//    void acHero();
//    void acMenu();
public:
    void menuSet(Ref* sender);
    void menuRank(Ref* sender);
    void menuShare(Ref* sender);
    void menuStart(Ref* sender);
    void showRank();
    void callback();
    void removeThisCallBack();
    
     bool onTouchBegan(Touch* touch, Event  *event);
private:
    Sprite* m_logo = NULL;
    Sprite* m_hero = NULL;
    Node* m_menu = NULL;
    Node* m_shareNode = NULL;
    bool isClickStart = false;
    
    GameMainLogoLayer* m_logoLayer;
    GameOverLayer* m_gameOverLayer;
    void update(float dt);
};

#endif /* defined(__GWPJUMP__MainLayer__) */
