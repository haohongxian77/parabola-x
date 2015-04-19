//
//  GameOverLayer.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 4/12/15.
//
//

#include "GameOverLayer.h"
bool GameOverLayer::init(){
    if (Layer::init()) {
        return true;
    }
    return false;
}
void GameOverLayer::initBg(){
    Sprite* spBg = Sprite::create("gameover_mainbg.png");
   // spBg->setPosition(ccp)
}
void GameOverLayer::initScore(){
}