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
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#define minHei 3
#define maxHei 5
#define SCREEN_DE_COUNT 8   //屏幕划分的单位


#define MAX_TOUCH_W 5
#define MIN_TOUCH_W 2   //抛物线点击点和起始点最大具体和最小具体   以柱子宽为单位

#define MAX_TOUCH_H 7 //  抛物线点得最高点
#define MIN_TOUCH_H 0.5f  //  抛物线点 距离起始点 最小的距离差

//#define PLAYTIME "playGameTime"
#define SCOREADDTION  1.5
#define GUILDCount  4

GameMainHelper* GameMainHelper::mainHelper = NULL;

GameMainHelper::GameMainHelper():
m_gameStatus(Tag_None),
m_curHeroPost(NULL),
m_curScore(NULL),
touchGuildPoints(NULL),
m_curBgIndex(0),
m_isGoogle(true),
m_music(true),
m_sound(true)
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
    Sprite* sp = Sprite::createWithSpriteFrameName("game_column0.png");
    //Director::getInstance()->getTextureCache()->addImage("spile.png");
    m_unitW = sp->getContentSize().width*3/4;
    sp = NULL;
    
    m_posts = __Array::create();
    m_posts->retain();
    
    touchGuildPoints = new std::vector<Point>();
    m_playTimes = 0;
    m_HighstScore = UserDefault::getInstance()->getIntegerForKey(Highest);
    m_music = UserDefault::getInstance()->getBoolForKey(MUSICKEY, true);
    m_sound = UserDefault::getInstance()->getBoolForKey(SOUNDKEY, true);
    m_isGoogle = UserDefault::getInstance()->getBoolForKey(RANKKEY, true);
    bool isGuild = UserDefault::getInstance()->getBoolForKey(SHOWGUILD, true);
    if (isGuild) {
        m_gameStatus = Tag_Guild;
    }
    
    
}
void GameMainHelper::initJumpDate(std::vector<float> param,float SpeedX,float highY , float curY){
    if (m_curHeroPost == NULL) {
        m_startIndex =0;
    }else{
        m_startIndex = (int)m_posts->getIndexOfObject(m_curHeroPost);
    }
    initPathPoints(param, SpeedX,highY,curY);
}
void GameMainHelper::initPosts(){
    if (m_gameStatus == Tag_Guild&&m_posts->count()==0) {
            addGuildPost();
    }
    
    float posX = 0.0f;
    Size winSize = Director::getInstance()->getWinSize();
    if (m_posts->count() == 0) {
        posX = -1*m_Layer->getPositionX()+m_unitW;
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
    MonsterSpile* monspile = MonsterSpile::create(m_curBgIndex);
  
    monspile->setAnchorPoint(Vec2(0,1));
    //m_Layer->addChild(monspile);
    Size spSize = monspile->getContentSize();

    Size winSize = Director::getInstance()->getWinSize();
    
    Point pos;

    
    if (m_posts->count()==0) {
        float x = m_unitW;
         int Hregion = rand()%(maxHei-minHei+1)+minHei;
        int randHeiInregion = rand()%((int)winSize.height/SCREEN_DE_COUNT); //
         pos= Point(x,randHeiInregion+Hregion*winSize.height/SCREEN_DE_COUNT);
       
    }else{
        Sprite* perSp = (Sprite*)m_posts->getObjectAtIndex(m_posts->count()-1);
        
        pos = getNextPoint(perSp->getPosition());
        
    }
    monspile->setPosition(pos);
    m_spilesNode->addChild(monspile);
    m_posts->addObject(monspile);
    return pos;
}
void GameMainHelper::addGuildPost(){
   
    if (m_gameStatus == Tag_Guild) {
    Size winSize = Director::getInstance()->getWinSize();
        for (int i = 0; i<GUILDCount; i++) {
            MonsterSpile* monspile = MonsterSpile::create(m_curBgIndex);
            monspile->setAnchorPoint(Vec2(0,1));
            
            
            
            Point pos;
            
            
            if (m_posts->count()==0) {
                float x = m_unitW;
                pos= Point(x,winSize.height/2);
                
            }else{
                float x = m_unitW*2+m_unitW*3*m_posts->count();
                
                pos= Point(x,winSize.height/2);
                
            }
            monspile->setPosition(pos);
            m_spilesNode->addChild(monspile);
            m_posts->addObject(monspile);
        }
    touchGuildPoints->push_back(Vec2(m_unitW*4,winSize.height*3/4)) ;
    touchGuildPoints->push_back(Vec2(m_unitW*8.5,winSize.height*3/4))  ;
        
    }
    

}

Point GameMainHelper::getNextPoint(Point perPoint){
    Point touPoint = getTouchPoint(perPoint);
    //获取抛物线参数
    std::vector<float> params = CalculateHelper::getPathParametersXABC(Vec2(0,0), Vec2(touPoint.x-perPoint.x,touPoint.y-perPoint.y));
    
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
                //CCLOG("前有两个相同高的点＝＝＝＝＝%f＝＝＝%f===%f",x,y,dy);
            }
        }
    }
    //CCLOG("两个点＝＝＝%f＝＝＝%f",x,y);
    if (y>maxHei*m_unitH||y<minHei*m_unitH) {
        //CCLOG("高出了范围＝＝＝＝＝%f＝＝＝%f",x,y);
        return getNextPoint(perPoint);
    }
    //CCLOG("正常输出一个***************************%f***********************%f",x,y);
    return Point(x, y);
}
float GameMainHelper::getNextPointX(Point touchPoint, Point perPoint){
    int DW = (touchPoint.x-perPoint.x)/m_unitW+1;//距离起始点的单位宽
    int perRegion = MAX(perPoint.y/m_unitH+1,minHei);
    int touchRegion = MAX(touchPoint.y/m_unitH+1, minHei);
    
    
    int maxDw = (touchRegion-perRegion)+2*DW;
    
    float dx = rand()%(int)(maxDw*m_unitW-DW*m_unitW+1)+DW*m_unitW;
//    CCLOG("dx====%f   maxDw===%d  DW====%d   m_unitW===%d  m_unitH=%d",dx,maxDw,DW,m_unitW,m_unitH);
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
CollisionType GameMainHelper::isCollisionPosts(Point PreprePoint,Point prePoint,Point curPoint){
    CollisionType c_Type = Collision_None;
    for (int i=0; i<m_posts->count(); i++) {
       
//        CCLOG("=======================================%d",i);
        MonsterSpile* sp = (MonsterSpile*) m_posts->getObjectAtIndex(i);
        Size heroSize = m_Hero->getContentSize();
        //如果具体远不做碰撞检测
        if ((m_curHeroPost->getPositionX() == sp->getPositionX()
             && sp->getPositionY() == m_curHeroPost->getPositionY())) {
            continue;
        }
        if (std::abs(sp->getPositionX()-curPoint.x)>sp->getContentSize().width+10) {
            continue;
        }
        c_Type =  sp->getValid(prePoint,curPoint);
        if (c_Type == Collision_None) {
            c_Type =  sp->getValid(PreprePoint,curPoint);
        }
        if(c_Type == Collision_None){
            
        }else {
            m_curHeroPost = sp;
            return c_Type;
        }
    }
                                             
    return c_Type;
}
Node* GameMainHelper::getTouchPosts(Point touchPoint){
    
    for (int i=0; i<m_posts->count(); i++) {
        MonsterSpile* sp = (MonsterSpile*) m_posts->getObjectAtIndex(i);
        if(sp->isCollickPost(touchPoint))
        {
            return sp;
        }
    }
    
    return NULL;
}
void GameMainHelper::setHero(HeroFrog *hero){
    m_Hero = hero;
    Size s = Director::getInstance()->getWinSize();
    //m_spilesNode->runAction(Follow::create(hero,Rect(0, 0, 0, s.height)));
}
void GameMainHelper::updateHelper(float dt){
    Size s= Director::getInstance()->getWinSize();
    if (m_Hero->getHeroStatus() == frogStatic ||
        m_Hero->getHeroStatus() == frogFall ||
        m_Hero->getHeroStatus() == frogDead1 ||
        m_Hero->getHeroStatus() == frogDead2||
        m_Hero->getHeroStatus() == frogTakeoff) {
        return;
    }
    if (m_Hero->getPositionX()+m_Layer->getPositionX()>s.width*3/4&&m_Layer->getNumberOfRunningActions()==0) {
        float heroSpeed = 0;
        if (m_heroPathIndex>1) {
            heroSpeed = ( m_heroPaths[m_heroPathIndex].x-m_heroPaths[m_heroPathIndex-1].x)/dt;
        }
        
        movingLayer(heroSpeed);
    }
    if (m_heroPathIndex>=m_heroPaths.size()-2) {
        if (m_Hero->setHeroFall()) {
            m_heroPathIndex = m_heroPaths.size();
        }
    }
    if (m_heroPathIndex < m_heroPaths.size()) {
         m_Hero->setCurPosition(m_heroPaths[m_heroPathIndex]);
        m_heroPathIndex++;
    }else{
        //m_Hero->setCurPosition(m_heroPaths[m_heroPaths.size()-1]);
        m_Hero->setHeroMoveOver();
    }
}
Point GameMainHelper::getHeroPostPoint(){
    Size postSize = m_curHeroPost->getContentSize();
    Point postPoint = m_curHeroPost->getPosition();
    return Point(postPoint.x+postSize.width/2,postPoint.y);
}
void GameMainHelper::jumpOver(){
    
     movingLayer(0);
     managePost();
     m_mainScene->changeScore();
    m_heroPathIndex = 0;
    m_heroPaths.clear();
    GuildOver();
    
}
void GameMainHelper::GuildOver(){
    if (m_gameStatus == Tag_Guild) {
        if (touchGuildPoints->size() == 0) {
            UserDefault::getInstance()->setBoolForKey(SHOWGUILD, false);
            
            m_mainScene->showIsYouturn();
            m_Layer->setMoveXDistance(0,0);
            m_heroPaths.clear();
            m_heroPathIndex = 0;
            m_gameStatus = Tag_None;

        }
        m_Layer->initGuildArrow();
          
    }
}
void GameMainHelper::movingLayer(float speed){
    Size size = Director::getInstance()->getWinSize();
    
    float dx = m_Hero->getPositionX()+m_Layer->getPositionX()-size.width/20;
    m_Layer->setMoveXDistance(-1*dx,speed);
}
void GameMainHelper::managePost(){
    int score_ = 0;
    
    for (long int i=m_posts->count()-1; i>=0; i--) {
        MonsterSpile* curSp =(MonsterSpile*)m_posts->getObjectAtIndex(i);
        Point postPoint = curSp->getPosition();
        if (postPoint.x<m_curHeroPost->getPositionX()) {
            curSp->moveOver();
            m_posts->removeObject(curSp);
                score_ ++;
        }
        
    }
    if (m_gameStatus != Tag_Guild) {
        m_curScore = m_curScore+(int)(score_*SCOREADDTION);
        if (score_ >=2&&score_<=4) {
            m_mainScene->showGood();
        }else if(score_ >4){
            m_mainScene->showPerfect();
        }
    }
    
    
    initPosts();
}
void GameMainHelper::gameOver(){
    setGameStaus(Tag_GameOver);
    m_mainScene->gameOver();
    m_Layer->setMoveXDistance(0,0);
    m_heroPaths.clear();
    m_heroPathIndex = 0;
    m_playTimes ++;
    showFullAd();
}
void GameMainHelper::showFullAd(){
    
    int t= rand();
    int randNum ;
    if (m_playTimes < 4) {
        randNum = 1;
    }else{
        randNum = t%(3);
    }
    if (randNum == 1) {
    	CCLOG("显示全屏广告-----------------------");
        HPlatformHelper::getInstance()->showFullAd();
    }
}
void GameMainHelper::startGame(){
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    initGameStartData();
    Size winSize  = Director::getInstance()->getWinSize();
    m_mainScene->startGame();  //主scene准备开始游戏
    m_curHeroPost = dynamic_cast<Sprite*> (m_posts->getObjectAtIndex(0));
    m_Layer->startGame(m_curHeroPost->getPositionX()-m_unitW);
    if (m_gameStatus != Tag_None) {
         changePostsSprite();
    }
   
    if(m_gameStatus != Tag_Guild){
        setGameStaus(Tag_GameStart);
    }
    
    m_curScore = 0;
    m_mainScene->changeScore();

}
void GameMainHelper::initGameStartData(){
    if(m_gameStatus  != Tag_None){
        int nextBgIndex = m_curBgIndex;
        while (nextBgIndex == m_curBgIndex) {
            nextBgIndex = rand()%(5);
        }
        m_curBgIndex = nextBgIndex;
    }
    
}
void GameMainHelper::changePostsSprite(){
    for (int i=0; i<m_posts->count(); i++) {
        MonsterSpile* spile = dynamic_cast<MonsterSpile*> (m_posts->getObjectAtIndex(i));
        spile->changeSprite(m_curBgIndex);
    }
}
void GameMainHelper::atachScene(GameMainScene* scene){
    m_mainScene = scene;
}
void GameMainHelper::initPathPoints(std::vector<float> params, float SpeedX,float highY , float curY){
    Point startPoint = m_Hero->getPosition();
    //下落动画播放的开始位置
    Point downPoint ;
    float aniSpeed = 1.0f/60;
    //float dis = highY-curY;
    
    float sX = params[1];
    float gravity = params[0];
    float sY = params[2];
    
    Size winSize = Director::getInstance()->getWinSize();
    Point curPoint = startPoint;
    CollisionType curType = Collision_None;
    bool isFirstDown = true;
    float totalTime = 0.0;
    while (curType == Collision_None) {
        totalTime =totalTime+ (1.0f/60);
        float x = 0;
        if (m_heroPaths.size() == 0) {
            x = startPoint.x + SpeedX*totalTime;
        }else{
            
           
            x = startPoint.x +sX*totalTime;
        }
        
        float y = sY*totalTime-gravity*totalTime*totalTime/2;
        y = startPoint.y+y;
       
        //添加最高点的动画
        if (curPoint.y>y&&isFirstDown) {
            isFirstDown = false;
            if (m_heroPaths.size() >= 2) {
                downPoint = m_heroPaths[m_heroPaths.size() - 2];
                
            }else {
                downPoint = startPoint;
                aniSpeed = aniSpeed/2;
            }
            
            
        }
        curPoint = Point(x,y);
        if (m_heroPaths.size() >2 ) {
             curType=isCollisionPosts(m_heroPaths[m_heroPaths.size()-2],m_heroPaths[m_heroPaths.size()-1], curPoint);
        }
       
         m_heroPaths.push_back(curPoint);
        
        if(curPoint.y<m_earthH){
            break;
        }
    }
    
   
    
    FrogStatus overStatus = frogStatic;
    
    if (curType == Collision_valid) {
        overStatus = frogFall;
        //jumpOver();
        Point endPoint = getHeroPostPoint();
        float dx = endPoint.x - (curPoint.x);
        float dy = endPoint.y - curPoint.y;
        int totalCount = m_heroPaths.size();
        for (int i= m_heroPaths.size()-1; i> 0; i--) {
            float k = (i*1.0f)/(totalCount-1);
            m_heroPaths[i] = Point(m_heroPaths[i].x+(dx*k),m_heroPaths[i].y);
        }
        m_heroPaths[m_heroPaths.size()-1].y = m_heroPaths[m_heroPaths.size()-1].y+dy;
        CCLOG("安全掉落");
        
    }else if(curType == Collision_Dead ){
        overStatus =frogDead1;
        Size  postSize = m_curHeroPost->getContentSize();
        Point endPoint = getHeroPostPoint();
        float dx = (endPoint.x-postSize.width/2-m_Hero->getContentSize().width/4)-curPoint.x;

        int totalCount = m_heroPaths.size();
        
        for (int i= m_heroPaths.size()-1; i> 0; i--) {
            m_heroPaths[i] = Point(m_heroPaths[i].x+(dx*i*1.0f/(totalCount-1)),m_heroPaths[i].y);
           
        }
        CCLOG("碰柱子死亡");
    }else if(curPoint.y<m_earthH){
        overStatus = frogDead2;
        float dY = m_earthH-curPoint.y;
        int totalCount = m_heroPaths.size();
        for (int i= m_heroPaths.size()-1; i> totalCount/2; i--) {
            m_heroPaths[i] = Point(m_heroPaths[i].x,m_heroPaths[i].y);
        }
        m_heroPaths[m_heroPaths.size()-1].y = m_heroPaths[m_heroPaths.size()-1].y+dY;
        CCLOG("落地死亡");
    }
    if(m_heroPaths[m_heroPaths.size()-1].x  - startPoint.x >winSize.width/3){
       m_Hero->setIsLongJump(true);
    }else{
        m_Hero->setIsLongJump(false);
    }
    m_heroPathIndex = 0;
    m_Hero->setHeroMoveParam(downPoint, aniSpeed, overStatus);
    
}
float GameMainHelper::getCurSpeed(float speed,float totalDis, float curDis){
    if(curDis >= totalDis*3/4){
        return speed;
    }else if (curDis >= totalDis/2){
        return speed*7/8;
    }else{
        return speed*3/4;
    }
}
void GameMainHelper::playSound(std::string soundName){

    SimpleAudioEngine::getInstance()->playEffect(soundName.c_str(),false, 2, 1, 1);
}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void GameMainHelper::share(ShareStatus status){
    
    m_mainScene->gotoShare(status);
    
}
#endif











