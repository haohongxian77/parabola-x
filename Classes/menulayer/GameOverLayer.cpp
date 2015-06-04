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
    std::string heroAniName = isNewHight?"hero_static_%d.png":"hero_cry_%d.png";
    Sprite* cryHero = Sprite::createWithSpriteFrameName(__String::createWithFormat(heroAniName.c_str(),0)->getCString());
    cryHero->setAnchorPoint(Vec2(0.5f,0.5f));
    cryHero->setPosition(Vec2(contentSize.width/4,contentSize.height*3/4-10));
    child->addChild(cryHero);
    auto animation = Animation::create();
    for( int i=1;i<8;i++)
    {
//        char szName[100] = {0};
//        sprintf(szName, "hero_cry_%d.png", i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat(heroAniName.c_str(),i)->getCString());
        animation->addSpriteFrame(frame);
    }
    // should last 2.8 seconds. And there are 14 frames.
    animation->setDelayPerUnit(2.1f / 14.0f);
    animation->setRestoreOriginalFrame(true);
    
    auto action = Animate::create(animation);
    cryHero->runAction(RepeatForever::create(action));
    
}
void GameOverLayer::initScore(){
    isNewHight = false;
    Sprite* child =dynamic_cast<Sprite*>(this->getChildByTag(101)) ;
    Size contentSize = child->getContentSize();
    
    
    int curScore = GameMainHelper::getInstance()->getCurScore();
    int highestScore = UserDefault::getInstance()->getIntegerForKey(Highest);
    
    if (curScore > highestScore) {
        if (GameMainHelper::getInstance()->getGoogleServer()) {
            HPlatformHelper::getInstance()->commitScore(curScore);
        }
        highestScore = curScore;
        isNewHight = true;
        
        UserDefault::getInstance()->setIntegerForKey(Highest, curScore);
    }
    GameMainHelper::getInstance()->setHighest(highestScore);
   std::string highFrontString = isNewHight?"fonts/game_frontoverhigh.png":"fonts/game_frontovercom.png";
   LabelAtlas* m_curscoreLabel = LabelAtlas::create(__String::createWithFormat("%d",curScore)->getCString(), highFrontString.c_str(),  23.4, 28, '0');
    m_curscoreLabel->setAnchorPoint(Vec2(0.5,0.5));
    m_curscoreLabel->setPosition(Vec2(contentSize.width*3/4+40,contentSize.height*3/4-15));
    child->addChild(m_curscoreLabel);
    
    LabelAtlas* m_higestscoreLabel = LabelAtlas::create(__String::createWithFormat("%d",highestScore)->getCString(), "fonts/game_frontoverhigh.png",  23.4, 28, '0');
    m_higestscoreLabel->setAnchorPoint(Vec2(0.5,0.5));
    m_higestscoreLabel->setPosition(Vec2(contentSize.width*3/4+40,contentSize.height/4-5));
    child->addChild(m_higestscoreLabel);
}
