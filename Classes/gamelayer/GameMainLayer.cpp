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
    if (GameMainHelper::getInstance()->getGameStaus() == Tag_GameOver) {
        return false;
    }
    movingPoints.clear();
    drawNode->clear();
    if (params.size()==0) {
        
        Point curP = this->convertTouchToNodeSpace(pTouch);
         Point heroP = m_hero->getPosition();
        //Vec2 heroWord = this->convertToWorldSpace(heroP);
       
        touNode->setPos(pTouch, heroP);
        touNode->setVisible(false);
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
    Size winSize = Director::getInstance()->getWinSize();
    Point curPos = m_hero->getPosition();
    //Point heroWord = convertToWorldSpace(curPos);
    
    touNode->setPos(touch, curPos);
    
    Point highPoint = this->convertTouchToNodeSpace(touch);
    highPoint = getTouchPoint(highPoint, touNode->getCurType());
    
    float dtime = 0;
    float gravity ;
    float startSpeedY;
    switch (touNode->getCurType()) {
        case TOUCH_ENABLE_UP:
            dtime = curPos.distance(highPoint)/(winSize.width/2);
            gravity  = 2*(highPoint.y- curPos.y)/dtime/dtime;
             startSpeedY= gravity*dtime;
            speedX = (highPoint.x-curPos.x)/dtime;
            m_hero->setHeroStatus(frogJumpUp);
            break;
        case TOUCH_DISABLE_UP:
            highPoint.y  = curPos.y+TOUCH_DISABLE_DIS;
            dtime = curPos.distance(highPoint)/(winSize.width/2);
            gravity  = 2*(highPoint.y- curPos.y)/dtime/dtime;
            startSpeedY= gravity*dtime;
            speedX = (highPoint.x-curPos.x)/dtime;
            m_hero->setHeroStatus(frogJumpUp);
            break;
        case TOUCH_DISABLE_DOWN:
            highPoint.y  = curPos.y-TOUCH_DISABLE_DIS;
            dtime = curPos.distance(highPoint)/(winSize.width/2);
            gravity  = 2*(curPos.y-highPoint.y)/dtime/dtime;
            startSpeedY= 0;
            speedX = (highPoint.x-curPos.x)/dtime;
            m_hero->setHeroStatus(frogJumpDown);
            highestPoint = curPos;
            break;
        case TOUCH_ENALBE_DOWN:
            dtime = curPos.distance(highPoint)/(winSize.width/2);
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
    
    
    GameMainHelper::getInstance()->initJumpDate(params,speedX,highPoint.y,curPos.y);
    
}
Point GameMainLayer::getTouchPoint(Point heightPoint,TouchType touchType){
    Node* sp = GameMainHelper::getInstance()->getTouchPosts(heightPoint);
    m_jumpOverType = frogFall;
    if ( sp== NULL) {
        return heightPoint;
    }
    Point heroPoint = m_hero->getPosition();
    if (touchType == TOUCH_ENABLE_UP|| touchType == TOUCH_DISABLE_UP) {
         heightPoint = Point(sp->getPositionX()+sp->getContentSize().width/2,heightPoint.y);
        float touchDH = (sp->getPositionY()-heroPoint.y)/(sp->getPositionX()-heroPoint.x)*(sp->getContentSize().width/2);
        if (heightPoint.y - sp->getPositionY()>= touchDH) {
            m_jumpOverType = frogStatic;
           
           
        }else {
            heightPoint = Point(sp->getPositionX()+sp->getContentSize().width/2,heightPoint.y);
            m_jumpOverType = frogDead1;
        }
         return heightPoint;
    }else{
        float touchDH = (heroPoint.y - sp->getPositionY())/(sp->getPositionX()+sp->getContentSize().width-heroPoint.x)*(sp->getPositionX()+ sp->getContentSize().width-heightPoint.x);
        if (heightPoint.y-sp->getPositionY() >= touchDH) {
            m_jumpOverType = frogStatic;
        }else{
            heightPoint = Point(sp->getPositionX(),sp->getPositionY()-1);
            m_jumpOverType = frogDead1;
        }
        
        
        
         return heightPoint;
        
    }
}
void GameMainLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    if(movingPoints.size() == 0)
        return;
    drawNode->clear();
    for (int i=0 ; i<movingPoints.size(); i++) {
        Point point1 = movingPoints[i-1];
        //Point point2 = movingPoints[i];
//        DrawPrimitives::drawCircle(point1, 2, 0, 10, false);
//        drawNode->drawCircle(point1,2, CC_DEGREES_TO_RADIANS(360), 100, true, Color4F(169,39,22,1));
        drawNode->drawPoint(point1,5,Color4F(169,49,169,0.7));
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
        if (m_hero->getHeroStatus() == frogStatic) {  //跳到柱子上
            params.clear();
            movingPoints.clear();
            disPlayLine();
            touNode->setVisible(false);

        }else if (m_hero->getHeroStatus() == frogDead1||m_hero->getHeroStatus() == frogDead2){   //游戏结束
            params.clear();
            movingPoints.clear();
            disPlayLine();
            touNode->setVisible(false);
        }
    }
}

void GameMainLayer::disPlayLine(){
    FadeOut* ac = FadeOut::create(0.8);
    Sequence* seq = Sequence::create(ac,CallFunc::create(CC_CALLBACK_0(GameMainLayer::clearLine, this)), NULL);
    drawNode->runAction(seq);
}
void GameMainLayer::clearLine(){
    drawNode->clear();
}



