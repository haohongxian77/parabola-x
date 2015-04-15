//
//  StartLayer.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 4/4/15.
//
//

#include "StartLayer.h"
#include "mainlayer/MainLayer.h"
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
        
        acFirstSp();
        return true;
    }
    return false;
}
void StartLayer::onEnter(){
    Layer::onEnter();
    
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
    m_spGWSNode = Sprite::createWithSpriteFrameName("loading_gwsk.png");
    m_spGWSNode->setAnchorPoint(Vec2(0.5f, 0.5f));
    m_spGWSNode->setPosition(Vec2(winSize.width/2,winSize.height*3/4));
    Size nodeSize = m_spGWSNode->getContentSize();
    this->addChild(m_spGWSNode,1);
    m_spG = Sprite::createWithSpriteFrameName("loading_1.png");
    m_spG ->setAnchorPoint(Vec2(1, 0.5f));
    //winSize.height*3/4
    m_spG ->setPosition(Vec2(nodeSize.width/4,m_spGWSNode->getContentSize().height/2));//+ m_spG->getContentSize().height
    m_spG->setScale(1.5*kScaleNum);
    m_spGWSNode->addChild(m_spG);
    
    m_spW = Sprite::createWithSpriteFrameName("loading_2.png");
    m_spW ->setAnchorPoint(Vec2(0.5f, 0.5f));
    m_spW ->setPosition(Vec2(nodeSize.width/2, m_spGWSNode->getContentSize().height/2));//+ m_spW->getContentSize().height
    m_spGWSNode->addChild(m_spW);
    m_spW->setVisible(false);
    m_spW->setScale(1.5*kScaleNum);
    
    m_spS = Sprite::createWithSpriteFrameName("loading_3.png");
    m_spS ->setAnchorPoint(Vec2(0, 0.5f));
    m_spS ->setPosition(Vec2(nodeSize.width*3/4,m_spGWSNode->getContentSize().height/2));//+ m_spS->getContentSize().height
    m_spGWSNode->addChild(m_spS);
    m_spS->setVisible(false);
    m_spS->setScale(1.5*kScaleNum);
    
    
}
void StartLayer::getShakeAction(){
    float rotateValue = 0.7;
    float scaleValue = 0.01;
    //RotateTo
    RotateTo *rotate = RotateTo::create(0.01, rotateValue);
    RotateTo *rotate1 = RotateTo::create(0.01, -rotateValue);
    RotateTo *rotate2 = RotateTo::create(0.01, 0);
    RotateTo *rotate3 = RotateTo::create(0.01, 0);
    
    ScaleTo *scale = ScaleTo::create(0.01, 1 + scaleValue);
    ScaleTo *scale1 = ScaleTo::create(0.01, 1 - scaleValue);
    ScaleTo *scale2 = ScaleTo::create(0.01, 1);
    ScaleTo *scale3 = ScaleTo::create(0.017, 1);
    
    Sequence *seq = Sequence::create(rotate,scale,rotate2,scale2, rotate1,scale1,rotate3,scale3,NULL);
    Repeat *repeat = Repeat::create(seq, 1);
    m_spGWSNode->runAction(repeat);
}
Action* StartLayer::getFallDownAC(Action* ac){
    ScaleTo *scaleTo1 = ScaleTo::create(0.3f, kScaleNum);
    ScaleTo *scaleTo2 = ScaleTo::create(0.03f, 1);
    Sequence* seq = Sequence::create(scaleTo1,scaleTo2,DelayTime::create(wordDelayTime), CallFunc::create(CC_CALLBACK_0(StartLayer::getShakeAction,this)),DelayTime::create(1), ac, NULL);
    return seq;
}
void StartLayer::acFirstSp(){
//    Size winSize = Director::getInstance()->getWinSize();
//    MoveTo* moveTo = MoveTo::create(speed, Point(m_spG->getPositionX(),winSize.height*3/4));
//    ScaleTo* scaleTo = ScaleTo::create(speed, 1);
//    Spawn* sp = Spawn::create(moveTo,scaleTo, NULL);
//    Sequence* seq = Sequence::create(sp,DelayTime::create(wordDelayTime), CallFunc::create(CC_CALLBACK_0(StartLayer::acSecondSp,this)), NULL);
    
    m_spG->runAction(getFallDownAC(CallFunc::create(CC_CALLBACK_0(StartLayer::acSecondSp,this))));
}
void StartLayer::acSecondSp(){
    Size nodeSize = m_spGWSNode->getContentSize();
    m_spW->setVisible(true);
    Sprite* sp = Sprite::createWithSpriteFrameName("loading_0.png");
    sp->setAnchorPoint(Vec2(1, 0.5f));
    sp->setPosition(Vec2(nodeSize.width*3/8,m_spG->getPositionY()));
    m_spGWSNode->addChild(sp);

//    MoveTo* moveTo = MoveTo::create(speed, Point(m_spW->getPositionX(),winSize.height*3/4));
//    ScaleTo* scaleTo = ScaleTo::create(speed, 1);
//    Spawn* spAc = Spawn::create(moveTo,scaleTo, NULL);
//    Sequence* seq = Sequence::create(spAc,DelayTime::create(wordDelayTime), CallFunc::create(CC_CALLBACK_0(StartLayer::acThirdSp,this)), NULL);
    m_spW->runAction(getFallDownAC(CallFunc::create(CC_CALLBACK_0(StartLayer::acThirdSp,this))));
}
void StartLayer::acThirdSp(){
    Size nodeSize = m_spGWSNode->getContentSize();
    m_spS->setVisible(true);
    Sprite* sp = Sprite::createWithSpriteFrameName("loading_0.png");
    sp->setAnchorPoint(Vec2(0, 0.5f));
    sp->setPosition(Vec2(nodeSize.width*5/8,m_spG->getPositionY()));
    m_spGWSNode->addChild(sp);
    //CallFunc::create(CC_CALLBACK_0(StartLayer::acHeroSp,this))
    Sequence* seq = Sequence::create(DelayTime::create(1),CallFunc::create(CC_CALLBACK_0(StartLayer::changeScene,this)), NULL);
    m_spS->runAction(getFallDownAC(seq));

}
void StartLayer::acHeroSp(){
    Size winSize = Director::getInstance()->getWinSize();
    MoveTo* moveTo = MoveTo::create(0.4f, Point(m_spGWSNode->getPositionX(),m_spHero->getContentSize().height/2));
   
    Sequence* seq = Sequence::create(moveTo, CallFunc::create(CC_CALLBACK_0(StartLayer::acGWSSp,this)), NULL);
    m_spHero->runAction(seq);

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
//    Scene* sc = MainLayer::createMainScene();
//    TransitionSlideInT *transitionScene = TransitionSlideInT::create(0.25,sc);
    MainLayer* mainLayer = MainLayer::create();
    Scene* sc = (Scene*)this->getParent();
    mainLayer->setPosition(Vec2(mainLayer->getPositionX(), mainLayer->getPositionY()+winSize.height));
   
    MoveTo* moveTo1 = MoveTo::create(0.5f,Point(0,winSize.height/4));
    MoveTo* moveTo12 = MoveTo::create(0.3f,Point(0,-winSize.height/8));
    //EaseSineOut* easeBack = EaseSineOut::create(moveTo1);
    MoveTo* moveTo2 = MoveTo::create(0.2f,Point(0,0));
    Sequence* seq = Sequence::create(moveTo1,moveTo12,moveTo2, NULL);
     sc->addChild(mainLayer);
    mainLayer->runAction(seq);
//    Director::getInstance()->pushScene(transitionScene);
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
