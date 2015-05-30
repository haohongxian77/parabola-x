//
//  GameOverLayer.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 4/12/15.
//
//

#include "GameOverLayer.h"
#include "helper/GameMainHelper.h"
#include "helper/HPlatformHelper.h"
bool GameOverLayer::init(){
    if (Layer::init()) {
        initBg();
        initScore();
        initHeroAni();
        return true;
    }
    return false;
}
void GameOverLayer::initBg(){
    Size size = Director::getInstance()->getWinSize();
    Sprite* spBg = Sprite::create("gameover_mainbg.png");
    spBg->setPosition(Vec2(size.width/2,size.height*3/4));
    spBg->setTag(101);
    addChild(spBg);
}
void GameOverLayer::initHeroAni(){
    Sprite* child =dynamic_cast<Sprite*>(this->getChildByTag(101)) ;
    Size contentSize = child->getContentSize();

    Sprite* cryHero = Sprite::createWithSpriteFrameName("hero_cry_0.png");
    cryHero->setAnchorPoint(Vec2(0.5f,0.5f));
    cryHero->setPosition(Vec2(contentSize.width/4,contentSize.height*3/4-10));
    child->addChild(cryHero);
    auto animation = Animation::create();
    for( int i=1;i<8;i++)
    {
        char szName[100] = {0};
        sprintf(szName, "hero_cry_%d.png", i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szName);
        animation->addSpriteFrame(frame);
    }
    // should last 2.8 seconds. And there are 14 frames.
    animation->setDelayPerUnit(2.1f / 14.0f);
    animation->setRestoreOriginalFrame(true);
    
    auto action = Animate::create(animation);
    cryHero->runAction(RepeatForever::create(action));
    
}
void GameOverLayer::initScore(){
    Sprite* child =dynamic_cast<Sprite*>(this->getChildByTag(101)) ;
    Size contentSize = child->getContentSize();
    
    
    int curScore = GameMainHelper::getInstance()->getCurScore();
    int highestScore = UserDefault::getInstance()->getIntegerForKey(Highest);
    
    if (curScore > highestScore) {
        if (GameMainHelper::getInstance()->getGoogleServer()) {
            //HPlatformHelper::getInstance()->commitScore(curScore);
        }
        highestScore = curScore;
        
        UserDefault::getInstance()->setIntegerForKey(Highest, curScore);
    }
    HPlatformHelper::getInstance()->commitScore(curScore);
    GameMainHelper::getInstance()->setHighest(highestScore);
     
   LabelAtlas* m_curscoreLabel = LabelAtlas::create(__String::createWithFormat("%d",curScore)->getCString(), "fonts/game_frontovercom.png",  23.4, 28, '0');
    m_curscoreLabel->setAnchorPoint(Vec2(0.5,0.5));
    m_curscoreLabel->setPosition(Vec2(contentSize.width*3/4+40,contentSize.height*3/4-15));
    child->addChild(m_curscoreLabel);
    
    LabelAtlas* m_higestscoreLabel = LabelAtlas::create(__String::createWithFormat("%d",highestScore)->getCString(), "fonts/game_frontoverhigh.png",  23.4, 28, '0');
    m_higestscoreLabel->setAnchorPoint(Vec2(0.5,0.5));
    m_higestscoreLabel->setPosition(Vec2(contentSize.width*3/4+40,contentSize.height/4-5));
    child->addChild(m_higestscoreLabel);
}
