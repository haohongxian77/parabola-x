//
//  GameMainLayer.h
//  GWPJUMP
//
//  Created by 易水流年 on 3/20/15.
//
//

#ifndef __GWPJUMP__GameMainLayer__
#define __GWPJUMP__GameMainLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "gamesprite/TouchNode.h"
#include "gamesprite/HeroFrog.h"
#include "helper/CommomData.h"

using namespace cocos2d;
class GameMainLayer :public Layer{
    GameMainLayer();
    ~GameMainLayer();
private:
    bool init();
    
private:
    HeroFrog * m_hero;
    TouchNode * touNode;
    DrawNode* drawNode;
       
    double speedX = 0.0;          //水平速度
   
    std::vector<float> params;    //完美曲线参数
    std::vector<Point>  movingPoints;   //移动的点；
    Point highestPoint;
private:
    void initData();
    void inittestSp();
    void initHelper();
    float moveXDistance;
public:
    void setMoveXDistance(int distance);
    void reloadData();
    void startGame(float dx);
public:
    virtual void onEnter();
    void update(float dt);
    void updatePosition(float dt);
    CREATE_FUNC(GameMainLayer);
    void registerTouchDispatcher();
    bool onTouchBegan(Touch* touch, Event  *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(Touch* touch, Event  *event);
    void initHeroBeginPoint();
    void disPlayLine();
    void clearLine();
private:  //划线相关
    Point perPos;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
    
    
};

#endif /* defined(__GWPJUMP__GameMainLayer__) */
