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
#include "mainlayer/GameMainLogoLayer.h"
#include "mainlayer/GameOverLayer.h"
using namespace cocos2d;
typedef enum{
    Tag_GameStart,
    Tag_GameOver,
    
}gameStatus;
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
    
    GameMainLogoLayer* m_logoLayer;
    GameOverLayer* m_gameOverLayer;
};

#endif /* defined(__GWPJUMP__MainLayer__) */
