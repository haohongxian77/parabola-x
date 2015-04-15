//
//  GameMainLayer.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 3/20/15.
//
//

#include "GameMainLayer.h"
#include "helper/CalculateHelper.h"
#include "helper/GameMainHelper.h"
#include "gamesprite/MonsterSpile.h"
#define Gravity  100//9.9
#define DPixelTo 28

GameMainLayer::GameMainLayer(){
    registerTouchDispatcher();
}

GameMainLayer::~GameMainLayer(){
}
void GameMainLayer::onEnter(){
    Layer::onEnter();
    scheduleUpdate();
}
void GameMainLayer::registerTouchDispatcher(){
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameMainLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameMainLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameMainLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//事件调度器
    
}
bool GameMainLayer::init(){
    if( !cocos2d::Layer::init() ){
        return false;
    }
    inittestSp();
    initHelper();
    initHeroBeginPoint();
    return true;
}
void GameMainLayer::inittestSp(){
    Size size = Director::getInstance()->getWinSize();
    
    m_hero = HeroFrog::create();
    m_hero ->setAnchorPoint(Vec2(0.5,0.5f));
    m_hero->setPosition(Vec2(10,10));
    addChild(m_hero);
    
  
    touNode = TouchNode::create();
    touNode->setVisible(false);
    addChild(touNode);
}
void GameMainLayer::initHelper(){
    m_helper=GameMainHelper::getInstance();
    m_helper->atachLayer(this);
    m_helper->initPosts();
    m_helper->setHero(m_hero);
    
}
void GameMainLayer::initHeroBeginPoint(){
    if (m_helper->m_posts->count()>0) {
        Sprite* firtPost= (Sprite*)m_helper->m_posts->getObjectAtIndex(0);
        Point firstP = firtPost->getPosition();
        
        Point beginPoint =Vec2(firstP.x+firtPost->getContentSize().width/2,
                               firstP.y+m_hero->getContentSize().height/2);
        m_hero->setPosition(beginPoint);
    }
}
bool GameMainLayer::onTouchBegan(Touch *pTouch, Event *pEvent){
    if (params.size()==0) {
        Point curP = this->convertTouchToNodeSpace(pTouch);
        Point heroP = m_hero->getPosition();
        touNode->setPos(curP, heroP.y);
        touNode->setVisible(true);
        m_hero->setHeroStatus(frogTakeoff);
        return true;
    }else {
        return false;
    }

}
void GameMainLayer::onTouchMoved(Touch *touch, Event *event){
    Point curP= this->convertTouchToNodeSpace(touch);
    Point heroP = m_hero->getPosition();
    touNode->setPos(curP, heroP.y);
    if (touNode->getCurType() == TOUCH_Enable) {
        m_hero->setHeroStatus(frogTakeoff);
    }else{
        m_hero->setHeroStatus(frogStatic);
    }
    
    
}
void GameMainLayer::onTouchEnded(Touch *touch, Event *unused_event){
    if (touNode->getCurType() == TOUCH_Disable) {
        return;
    }
    Point curPos = m_hero->getPosition();
    Point highPoint = this->convertTouchToNodeSpace(touch);
    float dY = highPoint.y- curPos.y;
    
    params = CalculateHelper::getPathParametersXABC(curPos, highPoint);
    double upTime = sqrt(2.0*dY/Gravity);
    speedX = (highPoint.x-curPos.x)/upTime;
    m_hero->setHeroStatus(frogJumpUp);
    movingPoints.clear();
    highestPoint = highPoint;
    m_helper->initJumpDate();
    
}
void GameMainLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    if(movingPoints.size() == 0)
        return;

    DrawPrimitives::setDrawColor4F(255,228,0,125);
    glLineWidth(5);
    for (int i=0; i<movingPoints.size()-1; i++) {
        if((i/10)%2==0)
            continue;
        Point p1= movingPoints[i];
        Point p2 = movingPoints[i+1];
        ccDrawLine(p1,p2);
    }
    
   
}

void GameMainLayer::update(float dt){
    if (params.size()==3) {
        perPos = m_hero->getPosition();
        movingPoints.push_back(perPos);
        
        float curX = perPos.x+speedX*dt;//1;
        float curY  = CalculateHelper::getPathABC(curX, params);
        CCLOG("dx:%f=============dy:%f",curX-perPos.x,curY-perPos.y);
        
        if(m_helper->updateHelper(dt, Vec2(curX,curY))){
            m_hero->setPosition(Vec2(curX,curY));
            if (curX>highestPoint.x) {
                m_hero->setHeroStatus(frogJumpDown);
            }
        }
        if (m_hero->getHeroStatus() == frogFall) {  //跳到柱子上
            params.clear();
            touNode->setVisible(false);
            m_helper->managePost();

        }else if (m_hero->getHeroStatus() == frogDead1||m_hero->getHeroStatus() == frogDead2){   //游戏结束
            params.clear();
            touNode->setVisible(false);
            m_helper->managePost();
            unscheduleUpdate();
        }
    }
}



