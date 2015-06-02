//
//  GameGuildLayer.cpp
//  GwsJump
//
//  Created by 易水流年 on 5/30/15.
//
//

#include "GameGuildLayer.h"
#include "commonnode/HMenu.h"
GameGuildLayer::GameGuildLayer(){
}
GameGuildLayer::~GameGuildLayer(){
}
bool GameGuildLayer::init(){
    if (Layer::init()) {
        initBg();
        initMenu();
        initArrow();
        return true;
    }
    return false;
}
void GameGuildLayer::initBg(){
    Size size = Director::getInstance()->getWinSize();
    Sprite* sp = Sprite::create("game_guild_bg.jpg");
    sp->setAnchorPoint(Vec2(0,0));
    sp->setPosition(Vec2(0,0));
    addChild(sp);
    
}
void GameGuildLayer::initMenu(){
     Size size = Director::getInstance()->getWinSize();
   
    HMenu* item1 = HMenu::create("hop_1.png", "hop_2.png",CC_CALLBACK_1(GameGuildLayer::startGame, this));
    item1->getNormalImage()->setAnchorPoint(Vec2(0.5f, 0.5f));
    item1->setPosition(Vec2(size.width*6/7, size.height*3/4));
    
    Node* m_menu = Menu::create(item1, nullptr);
    addChild(m_menu);
    m_menu->setAnchorPoint(Vec2(0, 0));
    m_menu->setPosition(Vec2(0,0));
    
}
void GameGuildLayer::initArrow(){
    Size size = Director::getInstance()->getWinSize();
    Sprite* arrow = Sprite::createWithSpriteFrameName("guild_arrow.png");
    arrow ->setAnchorPoint(Vec2(1,1));
    arrow->setScale(1);
    arrow->setPosition(size.width*16/20, size.height*3/4);
    addChild(arrow);
    
    ScaleTo* scale1 = ScaleTo::create(0.5, 1.5);
    ScaleTo* scale2 = ScaleTo::create(0.7, 1);
    Sequence* seq = Sequence::create(scale1,scale2, NULL);
    arrow->runAction(RepeatForever::create(seq));
}
void GameGuildLayer::startGame(cocos2d::Ref *sender){
    this->removeFromParentAndCleanup(true);
}
