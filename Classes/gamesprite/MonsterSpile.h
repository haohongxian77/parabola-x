//
//  MonsterSpile.h
//  GWPJUMP
//
//  Created by 易水流年 on 3/22/15.
//
//

#ifndef __GWPJUMP__MonsterSpile__
#define __GWPJUMP__MonsterSpile__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
typedef enum {
    Collision_None =0, //没有碰撞
    Collision_valid,     //有效碰撞 hero站在上边
    Collision_Dead,      //无效碰撞 hero死亡
    
}CollisionType;
class MonsterSpile :public Sprite{
    MonsterSpile();
    ~MonsterSpile();
private:
    static std::string getspriteFileName(int type);
    Point m_curPoint;
public:
    CollisionType getValid(Rect heroFootRect,Rect heroBodyRect);
    void moveOver();
    void disapear();
    void changeSprite(int bgIndex);
    
    static MonsterSpile* create(int spileType);
private:
    void initDraw();
    DrawNode* drawNode;
//    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
    
    
    
    
};

#endif /* defined(__GWPJUMP__MonsterSpile__) */
