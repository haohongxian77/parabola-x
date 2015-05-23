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
    
    m_bg2 = Sprite::create("main_bg.jpg");
    m_bg2->setAnchorPoint(Vec2(0, 0));
    m_bg2->setPosition(m_bg1->getContentSize().width, 0);
    addChild(m_bg2);
    initClound();
    //m_bg2->setVisible(false);
}
void GameBgLayer::initClound(){
    Size size = Director::getInstance()->getWinSize();
    Sprite* m_Cloud1 = Sprite::createWithSpriteFrameName("game_cloud1.png");
    m_Cloud1->setAnchorPoint(Vec2(0, 0));
    m_Cloud1->setTag(101);
    m_Cloud1->setPosition(size.width, size.height/2);
    addChild(m_Cloud1);
    MoveTo* mvTo1 = MoveTo::create(48, Point(-m_Cloud1->getContentSize().width,m_Cloud1->getPositionY()));
    Sequence* seq1 = Sequence::create(mvTo1,CCCallFunc::create( CC_CALLBACK_0(GameBgLayer::initClound11Position, this)),NULL);
    m_Cloud1->runAction(RepeatForever::create(seq1));
    
    Sprite* m_Cloud2 = Sprite::createWithSpriteFrameName("game_cloud2.png");
    m_Cloud2->setAnchorPoint(Vec2(0, 0));
    m_Cloud2->setTag(102);
    m_Cloud2->setPosition(size.width+size.width/4, size.height*3/4);
    addChild(m_Cloud2);
    MoveTo* mvTo2 = MoveTo::create(60, Point(-m_Cloud2->getContentSize().width,m_Cloud2->getPositionY()));
    Sequence* seq2 = Sequence::create(mvTo2,CCCallFunc::create( CC_CALLBACK_0(GameBgLayer::initClound12Position, this)),NULL);

    m_Cloud2->runAction(RepeatForever::create(seq2));

    
    Sprite* m_Cloud3 = Sprite::createWithSpriteFrameName("game_cloud3.png");
    m_Cloud3->setAnchorPoint(Vec2(0,0));
    m_Cloud3->setTag(103);
    m_Cloud3->setPosition(size.width+size.width/2, size.height*5/8);
    addChild(m_Cloud3);
    MoveTo* mvTo3 = MoveTo::create(72, Point(-m_Cloud3->getContentSize().width,m_Cloud3->getPositionY()));
    Sequence* seq3 = Sequence::create(mvTo3,CCCallFunc::create( CC_CALLBACK_0(GameBgLayer::initClound13Position, this)),NULL);
   
    m_Cloud3->runAction(RepeatForever::create(seq3));

}
void GameBgLayer::initClound11Position(){
    Size size = Director::getInstance()->getWinSize();
    Node* sp = this->getChildByTag(101);
    sp->setPosition(size.width-this->getPositionX(), size.height/2);
}
void GameBgLayer::initClound12Position(){
    Size size = Director::getInstance()->getWinSize();
    Node* sp = this->getChildByTag(102);
    sp->setPosition(size.width+size.width/4-this->getPositionX(), size.height/2);
}
void GameBgLayer::initClound13Position(){
    Size size = Director::getInstance()->getWinSize();
    Node* sp = this->getChildByTag(103);
    sp->setPosition(size.width+size.width/2-this->getPositionX(), size.height/2);
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









