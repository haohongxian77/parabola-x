//
//  GameBgBeforeLayer.cpp
//  GwsJump
//
//  Created by 易水流年 on 4/26/15.
//
//

#include "GameBgBeforeLayer.h"
#include "helper/GameMainHelper.h"
GameBgBeforeLayer::GameBgBeforeLayer(){
}
GameBgBeforeLayer::~GameBgBeforeLayer(){
}
bool GameBgBeforeLayer::init(){
    if (Layer::init()) {
        initBg();
        return true;
    }
    return false;
}
void GameBgBeforeLayer::initBg(){
    Size size = Director::getInstance()->getWinSize();
    m_bg1 = Sprite::create("game_bgBefore_0.png");
    m_bg1->setAnchorPoint(Vec2(0, 0));
    m_bg1->setPosition(0, 0);
    addChild(m_bg1);
    int m_bgH = m_bg1->getContentSize().height;
    GameMainHelper::getInstance()->setEarthH(m_bgH);
    m_bg2 = Sprite::create("game_bgBefore_0.png");
    m_bg2->setAnchorPoint(Vec2(0, 0));
    m_bg2->setPosition(m_bg1->getContentSize().width, 0);
    addChild(m_bg2);
  
}


void GameBgBeforeLayer::update(float dt,float bgMoveSpeed){
    
    updateBg(bgMoveSpeed);
    
    
    
}
void GameBgBeforeLayer::updateBg(float dX){
    this->setPositionX(this->getPositionX()+dX);
    if(m_bg1->getPositionX()+m_bg1->getContentSize().width+this->getPositionX()<0){
        m_bg1->setPositionX(m_bg2->getPositionX()+m_bg2->getContentSize().width);
    }
    if(m_bg2->getPositionX()+m_bg2->getContentSize().width+this->getPositionX()<0){
        m_bg2->setPositionX(m_bg1->getPositionX()+m_bg1->getContentSize().width);
    }
}