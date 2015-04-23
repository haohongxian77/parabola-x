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
    bool updateHelper(float dt,Point ds);
    
    CollisionType isCollisionPosts();   //碰撞检测
    void initPosts();
    void managePost();
    int getEarthH();
    MonsterSpile* getCollectSp();
    void initJumpDate();
public:
    void share(ShareStatus status);
public:
    __Array* m_posts;
    //std::vector<Sprite*>  posts;   //存放所有的柱子
    GameMainLayer* m_Layer;
    Node* m_spilesNode;
    HeroFrog* m_Hero;
private:
    void initDate();
    
    Point addPosts(float perPointX);
    Point getTouchPoint(Point perPoint);
    float getNextPointX(Point touchPoint,Point perPoint);
    Point getNextPoint(Point perPoint);
    //Point getTouchPoint(Point beginPoint);
    //Point getCurSpilePoint(Point perPoint,std::vector<float> params);
    //float getDx(int dH,float spileW);
    //int getHregion();
    
    void movingLayer();
    
    
private:
    int m_unitH = 0;
    int m_unitW = 0;
    int m_EarthH = 0;
    int m_collectIndex = -1;
    int m_startIndex = -1;
    
    GameMainScene* m_mainScene = NULL;
    
    
};

#endif /* defined(__GWPJUMP__GameMainHelper__) */
