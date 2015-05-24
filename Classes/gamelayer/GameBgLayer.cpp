//
//  GameBgLayer.cpp
//  GwsJump
//
//  Created by 易水流年 on 4/18/15.
//
//

#include "GameBgLayer.h"
#include "helper/GameMainHelper.h"

GameBgLayer::GameBgLayer(){
}
GameBgLayer::~GameBgLayer(){
}
bool GameBgLayer::init(){
    if (Layer::init()) {
        initSprite();
        return true;
    }
    return false;
}
void GameBgLayer::initSprite(){
     initBg();
    initClound();
    initMid1Bg();
    initMid2Bg();
}
void GameBgLayer::initBg(){
    Size size = Director::getInstance()->getWinSize();
    
    int bgIndex = GameMainHelper::getInstance()->getCurBgIndex();
    
    __String* frameName = __String::createWithFormat("game_bg_%d.png",bgIndex);
    m_bg = Sprite::create(frameName->getCString());
    m_bg->setAnchorPoint(Vec2(0,0));
    addChild(m_bg);
    
}
void GameBgLayer::initMid1Bg(){
    nodeBg1 = Node::create();
    nodeBg1->setAnchorPoint(Vec2(0, 0));
    nodeBg1->setPosition(Vec2(0, 0));
    addChild(nodeBg1,1);
    
    float earthH = GameMainHelper::getInstance()->getEarthH();
    
    Size size = Director::getInstance()->getWinSize();
    
    int bgIndex = GameMainHelper::getInstance()->getCurBgIndex();
    
    __String* frameName = __String::createWithFormat("game_midBg2_%d.png",bgIndex);
    m_bgMid1_1 = Sprite::createWithSpriteFrameName(frameName->getCString());
    m_bgMid1_1->setAnchorPoint(Vec2(0, 0));
    m_bgMid1_1->setPosition(0, earthH*4/5);
    nodeBg1->addChild(m_bgMid1_1);
    
    
    m_bgMid1_2 = Sprite::createWithSpriteFrameName(frameName->getCString());
    m_bgMid1_2->setAnchorPoint(Vec2(0, 0));
    m_bgMid1_2->setPosition(m_bgMid1_1->getContentSize().width-10, earthH*4/5);
    nodeBg1->addChild(m_bgMid1_2);
}
void GameBgLayer::initMid2Bg(){
    nodeBg2 = Node::create();
    nodeBg2->setAnchorPoint(Vec2(0, 0));
    nodeBg2->setPosition(Vec2(0, 0));
    addChild(nodeBg2,2);
    
    Size size = Director::getInstance()->getWinSize();
    
    int bgIndex = GameMainHelper::getInstance()->getCurBgIndex();
    
    __String* frameName = __String::createWithFormat("game_midBg1_%d.png",bgIndex);
    m_bgMid2_1 = Sprite::createWithSpriteFrameName(frameName->getCString());
    m_bgMid2_1->setAnchorPoint(Vec2(0, 0));
    m_bgMid2_1->setPosition(0, m_bgMid1_1->getPositionY()+m_bgMid1_1->getContentSize().height);
    nodeBg2->addChild(m_bgMid2_1);
    
    
    m_bgMid2_2 = Sprite::createWithSpriteFrameName(frameName->getCString());
    m_bgMid2_2->setAnchorPoint(Vec2(0, 0));
    m_bgMid2_2->setPosition(m_bgMid2_1->getContentSize().width,m_bgMid1_2->getPositionY()+m_bgMid1_2->getContentSize().height);
    nodeBg2->addChild(m_bgMid2_2);
}
void GameBgLayer::initClound(){
    Size size = Director::getInstance()->getWinSize();
    int bgIndex = GameMainHelper::getInstance()->getCurBgIndex();
    __String* frameName1 = __String::createWithFormat("game_cloud%d_1.png",bgIndex);

    
    m_Cloud1 = Sprite::createWithSpriteFrameName(frameName1->getCString());
    m_Cloud1->setAnchorPoint(Vec2(0, 0));
    m_Cloud1->setTag(101);
    m_Cloud1->setPosition(size.width, size.height/2);
    addChild(m_Cloud1);
    MoveTo* mvTo1 = MoveTo::create(48, Point(-m_Cloud1->getContentSize().width,m_Cloud1->getPositionY()));
    Sequence* seq1 = Sequence::create(mvTo1,CCCallFunc::create( CC_CALLBACK_0(GameBgLayer::initClound11Position, this)),NULL);
    m_Cloud1->runAction(RepeatForever::create(seq1));
    
    __String* frameName2 = __String::createWithFormat("game_cloud%d_2.png",bgIndex);
    m_Cloud2 = Sprite::createWithSpriteFrameName(frameName2->getCString());
    m_Cloud2->setAnchorPoint(Vec2(0, 0));
    m_Cloud2->setTag(102);
    m_Cloud2->setPosition(size.width+size.width/4, size.height*3/4);
    addChild(m_Cloud2);
    MoveTo* mvTo2 = MoveTo::create(60, Point(-m_Cloud2->getContentSize().width,m_Cloud2->getPositionY()));
    Sequence* seq2 = Sequence::create(mvTo2,CCCallFunc::create( CC_CALLBACK_0(GameBgLayer::initClound12Position, this)),NULL);

    m_Cloud2->runAction(RepeatForever::create(seq2));

    __String* frameName3 = __String::createWithFormat("game_cloud%d_3.png",bgIndex);
    m_Cloud3 = Sprite::createWithSpriteFrameName(frameName3->getCString());
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
   
    updateMid1Bg(bgMoveSpeed);
    updateMid2Bg(bgMoveSpeed);
    
    
    
}
void GameBgLayer::updateMid1Bg(float dX){
    nodeBg1->setPositionX(nodeBg1->getPositionX()+dX);
    if(m_bgMid1_1->getPositionX()+m_bgMid1_1->getContentSize().width+nodeBg1->getPositionX()<0){
        m_bgMid1_1->setPositionX(m_bgMid1_2->getPositionX()+m_bgMid1_2->getContentSize().width-10);
    }
    if(m_bgMid1_2->getPositionX()+m_bgMid1_2->getContentSize().width+nodeBg1->getPositionX()<0){
        m_bgMid1_2->setPositionX(m_bgMid1_1->getPositionX()+m_bgMid1_1->getContentSize().width-10);
    }
}
void GameBgLayer::updateMid2Bg(float dX){
    nodeBg2->setPositionX(nodeBg2->getPositionX()+dX*2/3);
    if(m_bgMid2_1->getPositionX()+m_bgMid2_1->getContentSize().width+nodeBg2->getPositionX()<0){
        m_bgMid2_1->setPositionX(m_bgMid2_2->getPositionX()+m_bgMid2_2->getContentSize().width);
    }
    if(m_bgMid2_2->getPositionX()+m_bgMid2_2->getContentSize().width+nodeBg2->getPositionX()<0){
        m_bgMid2_2->setPositionX(m_bgMid2_1->getPositionX()+m_bgMid2_1->getContentSize().width);
    }
}
void GameBgLayer::changeSprite(){
     int bgIndex = GameMainHelper::getInstance()->getCurBgIndex();
    //背景
     __String* bgName = __String::createWithFormat("game_bg_%d.png",bgIndex);

   
    m_bg->setTexture(Director::getInstance()->getTextureCache()->addImage(bgName->_string));
    __String* bgMid1Name = __String::createWithFormat("game_midBg2_%d.png",bgIndex);
    m_bgMid1_1->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(bgMid1Name->getCString()));
    m_bgMid1_2->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(bgMid1Name->getCString()));
    __String* bgMid2Name = __String::createWithFormat("game_midBg1_%d.png",bgIndex);
    m_bgMid2_1->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(bgMid2Name->getCString()));
    m_bgMid2_1->setPositionY(m_bgMid1_1->getPositionY()+m_bgMid1_1->getContentSize().height);
    m_bgMid2_2->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(bgMid2Name->getCString()));
    m_bgMid2_2->setPositionY(m_bgMid1_2->getPositionY()+m_bgMid1_2->getContentSize().height);
    
    __String* cloundName1 = __String::createWithFormat("game_cloud%d_1.png",bgIndex);
    m_Cloud1->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(cloundName1->getCString()));
    __String* cloundName2 = __String::createWithFormat("game_cloud%d_2.png",bgIndex);
    m_Cloud2->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(cloundName2->getCString()));
    
    __String* cloundName3 = __String::createWithFormat("game_cloud%d_3.png",bgIndex);
    m_Cloud3->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(cloundName3->getCString()));

}









