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
    CollisionType getValid(Rect heroRect);
    static MonsterSpile* create(int spileType);
    
    
    
    
    
};

#endif /* defined(__GWPJUMP__MonsterSpile__) */
