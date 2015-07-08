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
#include "commonnode/HMenu.h"
#define Gravity  1980//9.9
#define DPixelTo 28
#define MENUTAG 10001
#define ArrowTAG 10002

#define LAYERMOVESPEED 720
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
    //initGuildArrow();
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
    m_hero->setHeroStatus(frogStatic);
    addChild(m_hero,2);
    
  
    touNode = TouchNode::create();
    touNode->setVisible(false);
    addChild(touNode,3);
    
    drawNode = DrawNode::create();
    addChild(drawNode, 1);
}
void GameMainLayer::initGuildArrow(){
    Node* menu =  this->getChildByTag(MENUTAG);
    Node* arrow =  this->getChildByTag(ArrowTAG);
    if (menu) {
        menu->removeFromParentAndCleanup(true);
        menu = NULL;
    }
    if (arrow) {
        arrow->removeFromParentAndCleanup(true);
        arrow = NULL;
    }
    if (GameMainHelper::getInstance()->touchGuildPoints->size() == 0) {
        return;
    }
    
    std::vector<Point>* touchPoint  = GameMainHelper::getInstance()->touchGuildPoints;
    Point menuPoint = *(touchPoint->begin());
    touchPoint->erase(touchPoint->begin());
    
    HMenu* item1 = HMenu::create("guide_light_frame.png", "guide_light_frame.png",CC_CALLBACK_1(GameMainLayer::touchGuild, this));
    item1->getNormalImage()->setAnchorPoint(Vec2(0.5f, 0.5f));
    item1->setPosition(menuPoint);
    
    Node* m_menu = Menu::create(item1, nullptr);
    addChild(m_menu);
    m_menu->setTag(MENUTAG);
    m_menu->setAnchorPoint(Vec2(0, 0));
    m_menu->setPosition(Vec2(0,0));
    
    
    //箭头-----
    Sprite* m_arrow = Sprite::createWithSpriteFrameName("guide_hand.png");
    m_arrow ->setAnchorPoint(Vec2(1,1));
    m_arrow->setTag(ArrowTAG);
    m_arrow->setPosition(menuPoint.x+m_arrow->getContentSize().width/2+item1->getContentSize().width/2, menuPoint.y);
    this->addChild(m_arrow);
    m_arrow->setScale(0.8);
//    m_arrow->setScaleX(-1);
    
    

    ScaleTo *click_dwon = CCScaleTo::create(1, 1);
    ScaleTo *click_up = CCScaleTo::create(1, 0.8);
    FadeOut * ac = FadeOut::create(0.5);
    
    ActionInterval *result = (ActionInterval *)CCSequence::create(click_dwon,click_up,NULL);
    Repeat *repeat_ = Repeat::create(result,1);
    Sequence* seq = Sequence::create(repeat_,ac,CallFunc::create(CC_CALLBACK_0(GameMainLayer::removeArrow, this)), NULL);
    
    m_arrow->runAction(seq);
}
void GameMainLayer::removeArrow(){
    Node* arrow =  this->getChildByTag(ArrowTAG);
    if (arrow) {
        arrow->removeFromParentAndCleanup(true);
        arrow = NULL;
    }

}
void GameMainLayer::touchGuild(cocos2d::Ref *sender){
    Node* node = (Node*)sender;
    startJump(node->getPosition());
    std::vector<Point>* touchPoint  = GameMainHelper::getInstance()->touchGuildPoints;
    GameMainScene* scene = (GameMainScene*)this->getParent();
    if (touchPoint->size() == 0) {
        scene->showGuildPerfect();
    }else{
        scene->showGood();
    }
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
    initGuildArrow();
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
    //Node* menu = this->getChildByTag(MENUTAG);
    gameStatus status = GameMainHelper::getInstance()->getGameStaus();
    if ( status == Tag_GameOver || params.size()!=0||status == Tag_Guild) {
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
    startJump(this->convertTouchToNodeSpace(touch));
}
void GameMainLayer::startJump(Point touchPoint){
    Size winSize = Director::getInstance()->getWinSize();
    Point curPos = m_hero->getPosition();
    
    //touNode->setPos(touch, curPos);
    
    Point highPoint = touchPoint;
    highPoint = getTouchPoint(highPoint, touNode->getCurType());
    if (highPoint.x<=curPos.x) {
        m_hero->setHeroStatus(frogStatic);
        return;
    }
    
    float dtime = 0;
    float gravity ;
    float startSpeedY;
    FrogStatus heroStatus;
    switch (touNode->getCurType()) {
        case TOUCH_ENABLE_UP:
            dtime = curPos.distance(highPoint)/(winSize.width/2);
            gravity  = 2*(highPoint.y- curPos.y)/dtime/dtime;
            startSpeedY= gravity*dtime;
            speedX = (highPoint.x-curPos.x)/dtime;
            heroStatus = frogJumpUp;
            //m_hero->setHeroStatus();
            break;
        case TOUCH_DISABLE_UP:
            highPoint.y  = curPos.y+TOUCH_DISABLE_DIS;
            dtime = curPos.distance(highPoint)/(winSize.width/2);
            gravity  = 2*(highPoint.y- curPos.y)/dtime/dtime;
            startSpeedY= gravity*dtime;
            speedX = (highPoint.x-curPos.x)/dtime;
            heroStatus = frogJumpUp;
            // m_hero->setHeroStatus(frogJumpUp);
            break;
        case TOUCH_DISABLE_DOWN:
            highPoint.y  = curPos.y-TOUCH_DISABLE_DIS;
            dtime = curPos.distance(highPoint)/(winSize.width/2);
            gravity  = 2*(curPos.y-highPoint.y)/dtime/dtime;
            startSpeedY= 0;
            speedX = (highPoint.x-curPos.x)/dtime;
            heroStatus = frogJumpDown;
            //m_hero->setHeroStatus(frogJumpDown);
            highestPoint = curPos;
            break;
        case TOUCH_ENALBE_DOWN:
            dtime = curPos.distance(highPoint)/(winSize.width/2);
            gravity  = 2*(curPos.y-highPoint.y)/dtime/dtime;
            startSpeedY= 0;
            speedX = (highPoint.x-curPos.x)/dtime;
            heroStatus = frogJumpDown;
            //m_hero->setHeroStatus(frogJumpDown);
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
    m_hero->setHeroStatus(heroStatus);
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
        int w = Director::getInstance()->getOpenGLView()->getFrameSize().width;
        int winW = Director::getInstance()->getWinSize().height;
        drawNode->drawPoint(point1,(3.0f*w)/winW,Color4F(169,49,169,0.7));
    }
    
   
}
void GameMainLayer::setMoveXDistance(int distance,float speed){

    moveXDistance = MIN(distance,0);
    m_speedX = MAX(LAYERMOVESPEED, speed);
}
void GameMainLayer::updatePosition(float dt){
    
    float dis = m_speedX*dt;
    if (moveXDistance != 0 ) {
        dis = MIN(dis, -moveXDistance);
        moveXDistance += dis;
        
        this->setPositionX(this->getPositionX()-dis);
    }
    
    
}

void GameMainLayer::update(float dt){
    updatePosition(dt);
    m_hero->updateMusic(dt);
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



