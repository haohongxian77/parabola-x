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

class GameMainLayer;
using namespace cocos2d;

class GameMainHelper :public Ref{
    GameMainHelper();
    ~GameMainHelper();
public:
    static GameMainHelper* mainHelper;
    static GameMainHelper* getInstance();
    
    void atachLayer(GameMainLayer* layer);
    void setHero(HeroFrog* hero);
    bool updateHelper(float dt,Point ds);
    
    CollisionType isCollisionPosts();
    void initPosts();
    void managePost();
    int getEarthH();
    MonsterSpile* getCollectSp();
    void initJumpDate();
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
    
    
};

#endif /* defined(__GWPJUMP__GameMainHelper__) */
