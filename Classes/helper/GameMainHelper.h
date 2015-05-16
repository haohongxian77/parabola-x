//
//  GameMainHelper.h
//  GWPJUMP
//
//  Created by 易水流年 on 3/22/15.
//
//

#ifndef __GWPJUMP__GameMainHelper__
#define __GWPJUMP__GameMainHelper__

#include <stdio.h>
#include "cocos2d.h"
#include "gamesprite/HeroFrog.h"
#include "gamesprite/MonsterSpile.h"
#include "gamescene/GameMainScene.h"

class GameMainLayer;
using namespace cocos2d;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/HHPlatform.h"
#endif
class GameMainHelper :public Ref{
    GameMainHelper();
    ~GameMainHelper();
public:
    static GameMainHelper* mainHelper;
    static GameMainHelper* getInstance();
    
    void atachLayer(GameMainLayer* layer);
    void atachScene(GameMainScene* scene);
    void setHero(HeroFrog* hero);
    void updateHelper(float dt);
    
    CollisionType isCollisionPosts();   //碰撞检测
    void initPosts();
    void managePost();
    Sprite* getCollectSp();
    void initJumpDate();
public:
    void gameOver();
    void startGame();
    void jumpOver();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void share(ShareStatus status);
#endif
   
public:
    CC_SYNTHESIZE(gameStatus, m_gameStatus, GameStaus);
    CC_SYNTHESIZE(int, m_earthH, EarthH);
    CC_SYNTHESIZE(int, m_curScore, CurScore);
    __Array* m_posts;
    Sprite* m_curHeroPost;
    GameMainLayer* m_Layer;
    Node* m_spilesNode;
    HeroFrog* m_Hero;
private:
    void initDate();
    
    
    Point addPosts(float perPointX);
    Point getTouchPoint(Point perPoint);
    float getNextPointX(Point touchPoint,Point perPoint);
    Point getNextPoint(Point perPoint);
    
    void movingLayer();
    void initPathPoints(std::vector<float> params,int SpeedX);
   
    
    
    
private:
    int m_unitH = 0;
    int m_unitW = 0;
   // int m_collectIndex = -1;
    int m_startIndex = -1;
    
    
    GameMainScene* m_mainScene = NULL;
    std::list<Point> m_heroPaths;
    
    
};

#endif /* defined(__GWPJUMP__GameMainHelper__) */
