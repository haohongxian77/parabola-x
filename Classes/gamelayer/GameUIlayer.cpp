//
//  GameUIlayer.cpp
//  GwsJump
//
//  Created by 易水流年 on 5/9/15.
//
//

#include "GameUIlayer.h"
GameUIlayer::GameUIlayer():
m_scoreBg(NULL),
m_scoreLabel(NULL)
{
}
GameUIlayer::~GameUIlayer(){
}
bool GameUIlayer::init(){
    if (Node::init()) {
        Size size = Director::getInstance()->getWinSize();
        m_scoreBg = Sprite::createWithSpriteFrameName("game_scorebg.png");
        m_scoreBg->setAnchorPoint(Vec2(0.5,1));
        m_scoreBg->setPosition(Vec2(size.width/2,size.height-10));
        this->addChild(m_scoreBg);
        
        
        Size contentSize = m_scoreBg->getContentSize();
         m_scoreLabel = LabelAtlas::create("9876543210", "fonts/game_frontovercom.png",  23.4, 28, '0');
        m_scoreLabel->setAnchorPoint(Vec2(0.5,0.5));
        m_scoreLabel->setPosition(Vec2(contentSize.width/2,contentSize.height/2-10));
        m_scoreBg->addChild(m_scoreLabel);
        
        return true;
    }
    return false;
}
void GameUIlayer::changeScore(int curScore){
    m_scoreLabel->setString(__String::createWithFormat("%d",curScore)->getCString());
//    m_scoreLabel->setString("9876543210");
}
void GameUIlayer::changeScoreBg(){
    std::string str =  m_scoreLabel->getString();
    m_scoreLabel->removeFromParentAndCleanup(true);
    
    Size contentSize = m_scoreBg->getContentSize();
    m_scoreLabel = LabelAtlas::create(str, "fonts/game_frontoverhigh.png",  23.4, 28, '0');
    m_scoreLabel->setAnchorPoint(Vec2(0.5,0.5));
    m_scoreLabel->setPosition(Vec2(contentSize.width/2,contentSize.height/2-10));
    m_scoreBg->addChild(m_scoreLabel);
}




