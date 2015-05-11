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
   // m_bg1->setVisible(false);
    initClound(m_bg1);
    m_bg2 = Sprite::create("main_bg.jpg");
    m_bg2->setAnchorPoint(Vec2(0, 0));
    m_bg2->setPosition(m_bg1->getContentSize().width, 0);
    addChild(m_bg2);
    initClound(m_bg2);
    //m_bg2->setVisible(false);
}
void GameBgLayer::initClound(Sprite* node){
    Size size = Director::getInstance()->getWinSize();
    Sprite* m_Cloud1 = Sprite::createWithSpriteFrameName("game_cloud1.png");
    m_Cloud1->setAnchorPoint(Vec2(0, 0));
    m_Cloud1->setPosition(0, size.height/2);
    node->addChild(m_Cloud1);
  
    
    Sprite* m_Cloud2 = Sprite::createWithSpriteFrameName("game_cloud2.png");
    m_Cloud2->setAnchorPoint(Vec2(0, 0));
    m_Cloud2->setPosition(-size.width/8, size.height*3/4);
    node->addChild(m_Cloud2);

    
    Sprite* m_Cloud3 = Sprite::createWithSpriteFrameName("game_cloud3.png");
    m_Cloud3->setAnchorPoint(Vec2(0,0));
    m_Cloud3->setPosition(-size.width/10, size.height*5/8);
    node->addChild(m_Cloud3);

}

void GameBgLayer::update(float dt,float bgMoveSpeed){
   
    updateBg(bgMoveSpeed);
    
    
    
}
void GameBgLayer::updateBg(float dX){
    this->setPositionX(this->getPositionX()+dX);
    if(m_bg1->getPositionX()+m_bg1->getContentSize().width+this->getPositionX()<0){
        m_bg1->setPositionX(m_bg2->getPositionX()+m_bg2->getContentSize().width);
    }
    if(m_bg2->getPositionX()+m_bg2->getContentSize().width+this->getPositionX()<0){
        m_bg2->setPositionX(m_bg1->getPositionX()+m_bg1->getContentSize().width);
    }
}









