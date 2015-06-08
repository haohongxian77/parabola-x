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
#include "helper/CommomData.h"
#define speed 0.05f
#define wordDelayTime 0.1
#define kScaleNum 2

StartLayer::StartLayer(){
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("loadinglayer.plist", "loadinglayer.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("load_hero.plist", "load_hero.png");
     
}
StartLayer::~StartLayer(){
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("load_hero.plist");
    
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
    Sequence* seq = Sequence::create(DelayTime::create(2.5),CallFunc::create(CC_CALLBACK_0(StartLayer::changeScene, this)), NULL);
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
    Sequence* seq = Sequence::create(moveBy1,DelayTime::create(1.2), CallFunc::create(CC_CALLBACK_0(StartLayer::changeScene,this)), NULL);
    m_spGWS->runAction(seq);
    m_spHero->runAction(moveBY2);
}
void StartLayer::changeScene(){
    Size winSize = Director::getInstance()->getWinSize();
    Scene* sc = GameMainScene::create();
    //TransitionSlideInT *transitionScene = TransitionSlideInT::create(0.25,sc);
    Director::getInstance()->replaceScene(sc);
}
void StartLayer::initHero(){
    Size winSize = Director::getInstance()->getWinSize();
    m_spHero = Sprite::createWithSpriteFrameName("hero_load_0.png");
    
    auto animation = Animation::create();
    for( int i=0;i<8;i++)
    {
        char szName[100] = {0};
        sprintf(szName, "hero_load_%d.png", i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szName);
        animation->addSpriteFrame(frame);
    }
    // should last 2.8 seconds. And there are 14 frames.
    animation->setDelayPerUnit(2.8f / 14.0f);
    animation->setRestoreOriginalFrame(false);
    
    auto action = Animate::create(animation);
    m_spHero->runAction(RepeatForever::create(action));

    m_spHero ->setPosition(Vec2(winSize.width/2, winSize.height/4+m_spGWS->getContentSize().height/2+m_spHero->getContentSize().height*4/10));
    
    addChild(m_spHero);
}
void StartLayer::initGWSBig(){
    Size winSize = Director::getInstance()->getWinSize();
    m_spGWS = Sprite::create("GWS_1.png");
    m_spGWS ->setAnchorPoint(Vec2(0.5f, 1));

    m_spGWS ->setPosition(Vec2(winSize.width/2, winSize.height/4-m_spGWS->getContentSize().height/2));
    
    addChild(m_spGWS);
    
    m_spG->runAction(Sequence::create(DelayTime::create(0.3),CallFunc::create(CC_CALLBACK_0(StartLayer::showBackWordPro, this)), NULL));
    
    auto s = Director::getInstance()->getWinSize();
    
    auto to1 = Sequence::createWithTwoActions(ProgressTo::create(1.8, 100), ProgressTo::create(0, 0));
    
    auto left = ProgressTimer::create(Sprite::create("GWS_2.png"));
    left->setType(ProgressTimer::Type::BAR);
    left->setMidpoint(Vec2(0,0));
    left->setBarChangeRate(Vec2(1, 0));
    addChild(left);
    left->setPosition(Vec2(winSize.width/2, winSize.height/4-m_spGWS->getContentSize().height));
    left->runAction( RepeatForever::create(to1));
    
}
void StartLayer::showBackWordPro(){
    Size winSize = Director::getInstance()->getWinSize();
    auto to2 = Sequence::createWithTwoActions(ProgressTo::create(1.8, 100), ProgressTo::create(0, 0));
    auto right = ProgressTimer::create(Sprite::create("GWS_1.png"));
    right->setType(ProgressTimer::Type::BAR);
    
    right->setMidpoint(Vec2(0, 0));
    
    right->setBarChangeRate(Vec2(1, 0));
    addChild(right);
    right->setPosition(Vec2(winSize.width/2, winSize.height/4-m_spGWS->getContentSize().height));
    right->runAction(  RepeatForever::create(to2));
}
