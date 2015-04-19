//
//  GameBgLayer.cpp
//  GwsJump
//
//  Created by 易水流年 on 4/18/15.
//
//

#include "GameBgLayer.h"

GameBgLayer::GameBgLayer(){
}
GameBgLayer::~GameBgLayer(){
}
bool GameBgLayer::init(){
    if (Layer::init()) {
        initBg();
        initClound();
        return true;
    }
    return false;
}
void GameBgLayer::initBg(){
    Size size = Director::getInstance()->getWinSize();
    m_bg1 = Sprite::create("main_bg.jpg");
    m_bg1->setAnchorPoint(Vec2(0, 0));
    m_bg1->setPosition(0, 0);
    addChild(m_bg1);
    m_bg2 = Sprite::create("main_bg.jpg");
    m_bg2->setAnchorPoint(Vec2(0, 0));
    m_bg2->setPosition(0, 0);
    addChild(m_bg2);
}
void GameBgLayer::initClound(){
    Size size = Director::getInstance()->getWinSize();
    m_Cloud1 = Sprite::create("game_cloud1.png");
    m_Cloud1->setAnchorPoint(Vec2(0, 0));
    m_Cloud1->setPosition(size.width, size.height/2);
    addChild(m_Cloud1);
    clound1AC();
    
    m_Cloud2 = Sprite::create("game_cloud2.png");
    m_Cloud2->setAnchorPoint(Vec2(0, 0));
    m_Cloud2->setPosition(size.width, size.height*3/4);
    addChild(m_Cloud2);
    clound2AC();
    
    m_Cloud3 = Sprite::create("game_cloud3.png");
    m_Cloud3->setAnchorPoint(Vec2(0,0));
    m_Cloud3->setPosition(size.width, size.height*5/8);
    addChild(m_Cloud3);
    clound3AC();
}
void GameBgLayer::clound1AC(){
    Size size = Director::getInstance()->getWinSize();
    MoveTo* moveClound11 = MoveTo::create(10, Point(size.width/4,size.height*5/8));
    MoveTo* moveClound12 = MoveTo::create(3.3f, Point(-m_Cloud1->getContentSize().width,size.height/2));
    Sequence* seq = Sequence::create(moveClound11,moveClound12,CallFunc::create(CC_CALLBACK_0(GameBgLayer::initClound1Pos, this)), NULL);
    m_Cloud1->runAction(RepeatForever::create(seq));
}
void GameBgLayer::clound2AC(){
    Size size = Director::getInstance()->getWinSize();
    MoveTo* moveClound11 = MoveTo::create(10, Point(size.width/2,size.height*7/8));
    MoveTo* moveClound12 = MoveTo::create(10, Point(-m_Cloud1->getContentSize().width,size.height*3/4));
    Sequence* seq = Sequence::create(DelayTime::create(3), moveClound11,moveClound12,CallFunc::create(CC_CALLBACK_0(GameBgLayer::initClound1Pos, this)), NULL);
    m_Cloud1->runAction(RepeatForever::create(seq));
}
void GameBgLayer::clound3AC(){
    Size size = Director::getInstance()->getWinSize();
    MoveTo* moveClound11 = MoveTo::create(5, Point(size.width*3/4,size.height*3/4));
    MoveTo* moveClound12 = MoveTo::create(12, Point(-m_Cloud1->getContentSize().width,size.height*3/4));
    Sequence* seq = Sequence::create(DelayTime::create(7),moveClound11,moveClound12,CallFunc::create(CC_CALLBACK_0(GameBgLayer::initClound1Pos, this)), NULL);
    m_Cloud1->runAction(RepeatForever::create(seq));
}
void GameBgLayer::initClound1Pos(){
    Size size = Director::getInstance()->getWinSize();
    m_Cloud1->setPosition(size.width, size.height/2);
}
void GameBgLayer::initClound2Pos(){
    Size size = Director::getInstance()->getWinSize();
    m_Cloud2->setPosition(size.width, size.height*3/4);
}
void GameBgLayer::initClound3Pos(){
    Size size = Director::getInstance()->getWinSize();
    m_Cloud3->setPosition(size.width, size.height*5/8);
}
void GameBgLayer::update(float dx){
}









