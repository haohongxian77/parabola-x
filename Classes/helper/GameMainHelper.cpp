//
//  GameMainHelper.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 3/22/15.
//
//

#include "GameMainHelper.h"
#include "gamelayer/GameMainLayer.h"
#include "helper/CalculateHelper.h"
#include "HPlatformHelper.h"
#include <stdlib.h>
#include <time.h>
#define minHei 2
#define maxHei 5
#define SCREEN_DE_COUNT 8   //屏幕划分的单位


#define MAX_TOUCH_W 5
#define MIN_TOUCH_W 2   //抛物线点击点和起始点最大具体和最小具体   以柱子宽为单位

#define MAX_TOUCH_H 7 //  抛物线点得最高点
#define MIN_TOUCH_H 0.5f  //  抛物线点 距离起始点 最小的距离差

GameMainHelper* GameMainHelper::mainHelper = NULL;

GameMainHelper::GameMainHelper():
m_gameStatus(Tag_None),
m_curHeroPost(NULL)
{
}

GameMainHelper::~GameMainHelper(){
    if (m_posts) {
        CC_SAFE_RELEASE_NULL(m_posts);
    }
}

GameMainHelper* GameMainHelper::getInstance(){
    if (!mainHelper) {
        mainHelper = new GameMainHelper();
        mainHelper->initDate();
        
    }
    return  mainHelper;
}

void GameMainHelper::initDate(){
    Size winSize = Director::getInstance()->getWinSize();
    srand((unsigned)time(NULL));
    
    m_spilesNode = Node::create();
    m_spilesNode->setAnchorPoint(Vec2(0,0));
    m_spilesNode->setPosition(Vec2(0, 0));
    
    m_unitH = winSize.height/SCREEN_DE_COUNT;
    Texture2D* tex = Director::getInstance()->getTextureCache()->addImage("spile.png");
    m_unitW = tex->getContentSize().width;
    
    m_posts = __Array::create();
    m_posts->retain();
    
}
void GameMainHelper::initJumpDate(){
    if (m_curHeroPost == NULL) {
        m_startIndex =0;
    }else{
        m_startIndex = (int)m_posts->getIndexOfObject(m_curHeroPost);
    }
}
void GameMainHelper::initPosts(){
    float posX = 0.0f;
    Size winSize = Director::getInstance()->getWinSize();
    if (m_posts->count() == 0) {
        posX = -1*m_Layer->getPositionX()+100;
    }else{
        Sprite* sp = (Sprite*)m_posts->getLastObject();
        posX = sp->getPositionX();
    }
    while (posX+m_Layer->getPositionX()<winSize.width*3) {
    //while (m_posts->count()<50) {
        Point curPos = addPosts(posX);
        posX = curPos.x;
        
    }
    m_curHeroPost =dynamic_cast<Sprite*>(m_posts->getObjectAtIndex(0));
    
}
Sprite* GameMainHelper::getCollectSp(){
        return m_curHeroPost;
}
Point GameMainHelper::addPosts(float perPointX){
    MonsterSpile* monspile = MonsterSpile::create(0);
  
    monspile->setAnchorPoint(Vec2(0,1));
    //m_Layer->addChild(monspile);
    Size spSize = monspile->getContentSize();

    Size winSize = Director::getInstance()->getWinSize();
    
    Point pos;

    
    if (m_posts->count()==0) {
        float x = winSize.width/5;
         int Hregion = rand()%(maxHei-minHei+1)+minHei;
        int randHeiInregion = rand()%((int)winSize.height/SCREEN_DE_COUNT); //
         pos= Point(x,randHeiInregion+Hregion*winSize.height/SCREEN_DE_COUNT);
       
    }else{
        Sprite* perSp = (Sprite*)m_posts->getObjectAtIndex(m_posts->count()-1);
        
        pos = getNextPoint(perSp->getPosition());
        
    }
//    int randY =rand();
//    float y = m_minHeight+randY%(m_maxHeight- m_minHeight+1);
//     //
//    Point pos = Vec2(perPointX+x, y- spSize.height);
    monspile->setPosition(pos);
    CCLOG("x ======%f   y =====%f",pos.x,pos.y);
    m_spilesNode->addChild(monspile);
    m_posts->addObject(monspile);
    return pos;
}

Point GameMainHelper::getNextPoint(Point perPoint){
    Point touPoint = getTouchPoint(perPoint);
    //获取抛物线参数
    std::vector<float> params = CalculateHelper::getPathParametersXABC(Vec2(0,0), Vec2(touPoint.x-perPoint.x,touPoint.y-perPoint.y));
    //下一个点的位置
    CCLOG("参数＝＝＝＝＝%f＝＝＝%f＝＝＝%f",params[0],params[1],params[2]);
    CCLOG("触摸点＝＝＝＝＝%f＝＝＝%f",touPoint.x,touPoint.y);
    CCLOG("前一个点＝＝＝＝＝%f＝＝＝%f",perPoint.x,perPoint.y);
    
    float x = getNextPointX(touPoint,perPoint);
    float dy = CalculateHelper::getPathABC(x-perPoint.x, params);
    float y = dy+perPoint.y;
    
    if (m_posts->count()>=2) {
        Sprite* perSp2 = (Sprite*)m_posts->getObjectAtIndex(m_posts->count()-2);
        if (perPoint.y == perSp2->getPositionY()) {
            while (perSp2->getPositionY() == y) {
                x = getNextPointX(touPoint, perPoint);
                dy = CalculateHelper::getPathABC(x-perPoint.x, params);
                y = dy+perPoint.y;
                CCLOG("前有两个相同高的点＝＝＝＝＝%f＝＝＝%f===%f",x,y,dy);
            }
        }
    }
    CCLOG("两个点＝＝＝%f＝＝＝%f",x,y);
    if (y>maxHei*m_unitH||y<minHei*m_unitH) {
        CCLOG("高出了范围＝＝＝＝＝%f＝＝＝%f",x,y);
        return getNextPoint(perPoint);
    }
    CCLOG("正常输出一个***************************%f***********************%f",x,y);
    return Point(x, y);
}
float GameMainHelper::getNextPointX(Point touchPoint, Point perPoint){
    int DW = (touchPoint.x-perPoint.x)/m_unitW+1;//距离起始点的单位宽
    int perRegion = MAX(perPoint.y/m_unitH+1,minHei);
    int touchRegion = MAX(touchPoint.y/m_unitH+1, minHei);
    
    
    int maxDw = (touchRegion-perRegion)+2*DW;
    
    float dx = rand()%(int)(maxDw*m_unitW-DW*m_unitW+1)+DW*m_unitW;
    CCLOG("dx====%f   maxDw===%d  DW====%d   m_unitW===%d  m_unitH=%d",dx,maxDw,DW,m_unitW,m_unitH);
    return perPoint.x+dx;
}
Point GameMainHelper::getTouchPoint(Point perPoint){
    float DX = rand()%((int)(MAX_TOUCH_W*m_unitW-MIN_TOUCH_W*m_unitW+1))+MIN_TOUCH_W*m_unitW;
    float y = rand()%(int)(MAX_TOUCH_H*m_unitH-(perPoint.y+MIN_TOUCH_H*m_unitH)+1)+perPoint.y+MIN_TOUCH_H*m_unitH;
    
    return Point(perPoint.x+DX, y);
    
    
}

void GameMainHelper::atachLayer(GameMainLayer *layer){
    m_Layer = layer;
    m_Layer->addChild(m_spilesNode);
}
CollisionType GameMainHelper::isCollisionPosts(Point curPoint){
    CollisionType c_Type = Collision_None;
    for (int i=0; i<m_posts->count(); i++) {
       
        CCLOG("=======================================%d",i);
        MonsterSpile* sp = (MonsterSpile*) m_posts->getObjectAtIndex(i);
        Size heroSize = m_Hero->getContentSize();
        //如果具体远不做碰撞检测
        if (i==m_startIndex||std::abs(sp->getPositionX()-m_Hero->getPositionX())>heroSize.width/2) {
            continue;
        }
        c_Type =  sp->getValid(m_Hero->getFootRect(curPoint),m_Hero->getBodyRect(curPoint));
        if(c_Type == Collision_None){
            
        }else {
            m_curHeroPost = sp;
            return c_Type;
        }
    }
                                             
    return c_Type;
}
void GameMainHelper::setHero(HeroFrog *hero){
    m_Hero = hero;
    Size s = Director::getInstance()->getWinSize();
    //m_spilesNode->runAction(Follow::create(hero,Rect(0, 0, 0, s.height)));
}
void GameMainHelper::updateHelper(float dt){
    Size s= Director::getInstance()->getWinSize();
    if (m_Hero->getHeroStatus() == frogStatic || m_Hero->getHeroStatus() == frogFall ||m_Hero->getHeroStatus() == frogDead1 ||
        m_Hero->getHeroStatus() == frogDead2) {
        return;
    }
    if (m_Hero->getPositionX()+m_Layer->getPositionX()>s.width*3/4&&m_Layer->getNumberOfRunningActions()==0) {
        movingLayer();
    }
    CollisionType m_Type = isCollisionPosts(m_Hero->getPosition());
    if (m_Type == Collision_valid) {
        m_Hero->setHeroStatus(frogFall);
        jumpOver();
        CCLOG("安全掉落");
        
    }else if(m_Type == Collision_Dead ){
        m_Hero->setHeroStatus(frogDead1);
        CCLOG("碰柱子死亡");
        gameOver();
    }else if(m_Hero->getPositionY()<m_earthH){
        m_Hero->setHeroStatus(frogDead2);
        CCLOG("落地死亡");
        
        gameOver();
    }
    
}
void GameMainHelper::jumpOver(){
     movingLayer();
     managePost();
    m_mainScene->changeScore();
}
void GameMainHelper::movingLayer(){
    Size size = Director::getInstance()->getWinSize();
    
    float dx = m_Hero->getPositionX()+m_Layer->getPositionX()-size.width/5;
    m_Layer->setMoveXDistance(-1*dx);
}
void GameMainHelper::managePost(){
    for (long int i=m_posts->count()-1; i>=0; i--) {
        MonsterSpile* curSp =(MonsterSpile*)m_posts->getObjectAtIndex(i);
        Point postPoint = curSp->getPosition();
        if (postPoint.x<m_curHeroPost->getPositionX()) {
            curSp->moveOver();
            m_posts->removeObject(curSp);
            m_curScore ++;
        }
        
    }
    initPosts();
}
void GameMainHelper::gameOver(){
    setGameStaus(Tag_GameOver);
    m_mainScene->gameOver();
    m_Layer->setMoveXDistance(0);
}
void GameMainHelper::startGame(){
    Size winSize  = Director::getInstance()->getWinSize();
    m_mainScene->startGame();
    m_Layer->reloadData();
    m_curHeroPost = dynamic_cast<Sprite*> (m_posts->getObjectAtIndex(0));
    int posX = m_curHeroPost->getPositionX()-winSize.width/5;
    m_Layer->setPositionX(-posX);
    m_curScore = 0;
    m_Layer->initHeroBeginPoint();
}
void GameMainHelper::atachScene(GameMainScene* scene){
    m_mainScene = scene;
}
void GameMainHelper::initPathPoints(std::vector<float> params, int SpeedX){
    Point startPoint = m_Hero->getPosition();
    Point curPoint = startPoint;
    
    while (isCollisionPosts(curPoint) == Collision_None) {
        float x = 0;
        if (m_heroPaths.size() == 0) {
            x = startPoint.x + SpeedX*1.0f/60;
        }else{
            Point endPoint = m_heroPaths.back();
            x = endPoint.x +SpeedX*1.0f/60;
        }
        
        float y = CalculateHelper::getPathABC(x, params);
        m_heroPaths.push_back(Point(x,y));
        curPoint = Point(x,y);
        
    }
}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void GameMainHelper::share(ShareStatus status){
    std::string fullpath = m_mainScene->cutOff(status);
    
}
#endif











