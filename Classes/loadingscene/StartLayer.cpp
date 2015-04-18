//
//  StartLayer.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 4/4/15.
//
//

#include "StartLayer.h"
#include "gamelayer/GameMainLayer.h"
#include "gamescene/GameMainScene.h"
#define speed 0.05f
#define wordDelayTime 0.1
#define kScaleNum 2

StartLayer::StartLayer(){
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("loadinglayer.plist", "loadinglayer.png");
     
}
StartLayer::~StartLayer(){
    
}
bool StartLayer::init(){
    if (Layer::init()) {
        initBg();
        initGWSsmall();
        initGWSBig();
        initHero();
        return true;
    }
    return false;
}
void StartLayer::onEnter(){
    Layer::onEnter();
    Sequence* seq = Sequence::create(DelayTime::create(2),CallFunc::create(CC_CALLBACK_0(StartLayer::changeScene, this)), NULL);
    this->runAction(seq);
    
}
void StartLayer::initBg(){
    Size size = Director::getInstance()->getWinSize();
    Sprite* bg = Sprite::create("loading_bg.jpg");
    bg->setAnchorPoint(Vec2(0.5f,0.5f));
    bg->setPosition(Vec2(size.width/2, size.height/2));
    addChild(bg);
}
void StartLayer::initGWSsmall(){
    Size winSize = Director::getInstance()->getWinSize();
//    m_spGWSNode = Sprite::createWithSpriteFrameName("loading_gwsk.png");
//    m_spGWSNode->setAnchorPoint(Vec2(0.5f, 0.5f));
//    m_spGWSNode->setPosition(Vec2(winSize.width/2,winSize.height*3/4));
//    Size nodeSize = m_spGWSNode->getContentSize();
//    this->addChild(m_spGWSNode,1);
    
    m_spG = Sprite::createWithSpriteFrameName("loading_1.png");
    m_spG ->setAnchorPoint(Vec2(0, 0.5f));
    //winSize.height*3/4
    m_spG ->setPosition(Vec2(winSize.width/4,winSize.height*3/4));//+ m_spG->getContentSize().height
    //m_spG->setScale(1.5*kScaleNum);
    this->addChild(m_spG);
    
    
    Sprite* sp1 = Sprite::createWithSpriteFrameName("loading_0.png");
    sp1->setAnchorPoint(Vec2(1, 0.5f));
    sp1->setPosition(Vec2(winSize.width*3/8,m_spG->getPositionY()));
    this->addChild(sp1);
    
    m_spW = Sprite::createWithSpriteFrameName("loading_2.png");
    m_spW ->setAnchorPoint(Vec2(0.5f, 0.5f));
    m_spW ->setPosition(Vec2(winSize.width/2, winSize.height*3/4));//+ m_spW->getContentSize().height
    this->addChild(m_spW);
//    m_spW->setVisible(false);
//    m_spW->setScale(1.5*kScaleNum);
    Sprite* sp2 = Sprite::createWithSpriteFrameName("loading_0.png");
    sp2->setAnchorPoint(Vec2(1, 0.5f));
    sp2->setPosition(Vec2(winSize.width*5/8,m_spG->getPositionY()));
    this->addChild(sp2);
    
    
    m_spS = Sprite::createWithSpriteFrameName("loading_3.png");
    m_spS ->setAnchorPoint(Vec2(1, 0.5f));
    m_spS ->setPosition(Vec2(winSize.width*3/4,winSize.height*3/4));//+ m_spS->getContentSize().height
    this->addChild(m_spS);
//    m_spS->setVisible(false);
//    m_spS->setScale(1.5*kScaleNum);
    
    
}


void StartLayer::acGWSSp(){
    Size winSize = Director::getInstance()->getWinSize();
    MoveBy* moveBy1 = MoveBy::create(0.4, Vec2(0, winSize.height/4+m_spGWS->getContentSize().height/2));
    MoveBy* moveBY2 = MoveBy::create(0.4, Vec2(0, winSize.height/4+m_spGWS->getContentSize().height/4));
    Sequence* seq = Sequence::create(moveBy1,DelayTime::create(0.5), CallFunc::create(CC_CALLBACK_0(StartLayer::changeScene,this)), NULL);
    m_spGWS->runAction(seq);
    m_spHero->runAction(moveBY2);
}
void StartLayer::changeScene(){
    Size winSize = Director::getInstance()->getWinSize();
    Scene* sc = GameMainScene::createWithTag(Tag_GameStart);
    //TransitionSlideInT *transitionScene = TransitionSlideInT::create(0.25,sc);
    Director::getInstance()->replaceScene(sc);
}
void StartLayer::initHero(){
    Size winSize = Director::getInstance()->getWinSize();
    m_spHero = Sprite::createWithSpriteFrameName("loading_hero.png");
//    m_spHero ->setPosition(Vec2(winSize.width/2, winSize.height+m_spHero->getContentSize().height/2));
    m_spHero ->setPosition(Vec2(winSize.width/2, winSize.height/4+m_spGWS->getContentSize().height/4+m_spHero->getContentSize().height/2));
    
    addChild(m_spHero);
}
void StartLayer::initGWSBig(){
    Size winSize = Director::getInstance()->getWinSize();
    m_spGWS = Sprite::createWithSpriteFrameName("loading_word.png");
    m_spGWS ->setAnchorPoint(Vec2(0.5f, 1));
//    m_spGWS ->setPosition(Vec2(winSize.width/2, -m_spGWS->getContentSize().height));
    m_spGWS ->setPosition(Vec2(winSize.width/2, winSize.height/4-m_spGWS->getContentSize().height/2));
    
    addChild(m_spGWS);
    
}
