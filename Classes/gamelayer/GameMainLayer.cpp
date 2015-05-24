//
//  GameMainLayer.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 3/20/15.
//
//

#include "GameMainLayer.h"
//#include "helper/CalculateHelper.h"
#include "helper/GameMainHelper.h"
#include "gamesprite/MonsterSpile.h"
#define Gravity  1980//9.9
#define DPixelTo 28

#define LAYERMOVESPEED 480.0
GameMainLayer::GameMainLayer():
moveXDistance(0)
{
    registerTouchDispatcher();
}

GameMainLayer::~GameMainLayer(){
}
void GameMainLayer::onEnter(){
    Layer::onEnter();
    //scheduleUpdate();
}
void GameMainLayer::registerTouchDispatcher(){
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameMainLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameMainLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameMainLayer::onTouchEnded, this);
   // _eventDispatcher->addEventListenerWithFixedPriority(listener, TOUCHLEV_GAME);
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
void GameMainLayer::initData(){
     Size size = Director::getInstance()->getWinSize();
    moveXDistance = 0;
}
void GameMainLayer::inittestSp(){
    Size size = Director::getInstance()->getWinSize();
    
    m_hero = HeroFrog::create();
    m_hero ->setAnchorPoint(Vec2(0.5,0));
    m_hero->setPosition(Vec2(10,10));
    addChild(m_hero,2);
    
  
    touNode = TouchNode::create();
    touNode->setVisible(false);
    addChild(touNode,3);
    
    drawNode = DrawNode::create();
    addChild(drawNode, 10);
}
void GameMainLayer::reloadData(){
    params.clear();
}
void GameMainLayer::initHelper(){
    GameMainHelper::getInstance()->atachLayer(this);
    GameMainHelper::getInstance()->initPosts();
    GameMainHelper::getInstance()->setHero(m_hero);
    
}
void GameMainLayer::startGame(float dx){
    reloadData();
    setPositionX(-dx);
    initHeroBeginPoint();
}
void GameMainLayer::initHeroBeginPoint(){
    m_hero->setHeroStatus(frogStatic);
    if (GameMainHelper::getInstance()->m_posts->count()>0) {
        Sprite* firtPost= (Sprite*)GameMainHelper::getInstance()->m_posts->getObjectAtIndex(0);
        Point firstP = firtPost->getPosition();
        
        Point beginPoint =Vec2(firstP.x+firtPost->getContentSize().width/2,
                               firstP.y);
        m_hero->setPosition(beginPoint);
    }
}
bool GameMainLayer::onTouchBegan(Touch *pTouch, Event *pEvent){
    if (params.size()==0) {
        Point curP = this->convertTouchToNodeSpace(pTouch);
         Point heroP = m_hero->getPosition();
        //Vec2 heroWord = this->convertToWorldSpace(heroP);
       
        touNode->setPos(pTouch, heroP);
        touNode->setVisible(true);
        m_hero->setHeroStatus(frogTakeoff);
        return true;
    }else {
        return false;
    }

}
void GameMainLayer::onTouchMoved(Touch *touch, Event *event){
   // Point curP= this->convertTouchToNodeSpace(touch);
    Point heroP = m_hero->getPosition();
   // Point heroWord = convertToWorldSpace(heroP);
    
    touNode->setPos(touch, heroP);
    m_hero->setHeroStatus(frogTakeoff);
    
}
void GameMainLayer::onTouchEnded(Touch *touch, Event *unused_event){
//    if (touNode->getCurType() == TOUCH_Disable) {
//        m_hero->setHeroStatus(frogStatic);
//        return;
//    }
    
    
    Size winSize = Director::getInstance()->getWinSize();
    Point curPos = m_hero->getPosition();
    //Point heroWord = convertToWorldSpace(curPos);
    
    touNode->setPos(touch, curPos);
    
    Point highPoint = this->convertTouchToNodeSpace(touch);
    
    float dtime = 0;
    float gravity ;
    float startSpeedY;
    switch (touNode->getCurType()) {
        case TOUCH_ENABLE_UP:
            dtime = curPos.distance(highPoint)/600;
            gravity  = 2*(highPoint.y- curPos.y)/dtime/dtime;
             startSpeedY= gravity*dtime;
            speedX = (highPoint.x-curPos.x)/dtime;
            m_hero->setHeroStatus(frogJumpUp);
            break;
        case TOUCH_DISABLE_UP:
            highPoint.y  = curPos.y+TOUCH_DISABLE_DIS;
            dtime = curPos.distance(highPoint)/600;
            gravity  = 2*(highPoint.y- curPos.y)/dtime/dtime;
            startSpeedY= gravity*dtime;
            speedX = (highPoint.x-curPos.x)/dtime;
            m_hero->setHeroStatus(frogJumpUp);
            break;
        case TOUCH_DISABLE_DOWN:
            highPoint.y  = curPos.y-TOUCH_DISABLE_DIS;
            dtime = curPos.distance(highPoint)/600;
            gravity  = 2*(curPos.y-highPoint.y)/dtime/dtime;
            startSpeedY= 0;
            speedX = (highPoint.x-curPos.x)/dtime;
            m_hero->setHeroStatus(frogJumpDown);
            highestPoint = curPos;
            break;
        case TOUCH_ENALBE_DOWN:
            dtime = curPos.distance(highPoint)/600;
            gravity  = 2*(curPos.y-highPoint.y)/dtime/dtime;
            startSpeedY= 0;
            speedX = (highPoint.x-curPos.x)/dtime;
            m_hero->setHeroStatus(frogJumpDown);
            highestPoint = curPos;
            break;
            
        default:
            break;
    }
    if (params.size()!=0)
        return;
   // gravity = MIN(gravity,1400);
    params.push_back(gravity);
    params.push_back(speedX);
    params.push_back(startSpeedY);
    
    
//    params = CalculateHelper::getPathParametersXABC(curPos, highPoint);
//    double upTime = sqrt(2.0*dY/Gravity);
//    speedX = (highPoint.x-curPos.x)/upTime;//300;
//    speedX = MAX(300.0, speedX);
//    speedX = MIN(600.0,speedX);
    movingPoints.clear();
    
    GameMainHelper::getInstance()->initJumpDate(params,speedX,highPoint.y,curPos.y);
    
}
void GameMainLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    if(movingPoints.size() == 0)
        return;
    drawNode->clear();
    for (int i=1 ; i<movingPoints.size(); i+=2) {
        Point point1 = movingPoints[i-1];
        Point point2 = movingPoints[i];
        
        drawNode->drawSegment(point1, point2, 3,Color4F::ORANGE);
    }
    
   
}
void GameMainLayer::setMoveXDistance(int distance){

    moveXDistance = MIN(distance,0);
}
void GameMainLayer::updatePosition(float dt){
    
    float dis = LAYERMOVESPEED*dt;
    if (moveXDistance != 0 ) {
        dis = MIN(dis, -moveXDistance);
        moveXDistance += dis;
        
        this->setPositionX(this->getPositionX()-dis);
    }
    
    
}

void GameMainLayer::update(float dt){
    updatePosition(dt);
    if (params.size()==3) {
        perPos = m_hero->getPosition();
        movingPoints.push_back(perPos);
        
        
        
//        float curX = perPos.x+speedX*dt;//1;
//        float curY  = CalculateHelper::getPathABC(curX, params);
//        CCLOG("dx:%f=============dy:%f",curX-perPos.x,curY-perPos.y);
//        if(m_hero->getHeroStatus() == frogJumpUp||m_hero->getHeroStatus() == frogJumpDown){
//            m_hero->setPosition(Vec2(curX,curY));
//            if (curX>highestPoint.x) {
//                m_hero->setHeroStatus(frogJumpDown);
//            }
//        }
        if (m_hero->getHeroStatus() == frogStatic) {  //跳到柱子上
            params.clear();
            touNode->setVisible(false);

        }else if (m_hero->getHeroStatus() == frogDead1||m_hero->getHeroStatus() == frogDead2){   //游戏结束
            params.clear();
            touNode->setVisible(false);
        }
    }
}



