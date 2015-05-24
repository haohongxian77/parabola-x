//
//  TouchNode.h
//  GWPJUMP
//
//  Created by 易水流年 on 3/25/15.
//
//

#ifndef __GWPJUMP__TouchNode__
#define __GWPJUMP__TouchNode__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
typedef enum {
    TOUCH_DISABLE = 0,
    TOUCH_ENABLE_UP ,
    TOUCH_DISABLE_UP ,
    TOUCH_ENALBE_DOWN , //没有碰撞
    TOUCH_DISABLE_DOWN,     //有效碰撞 hero站在上边
    
}TouchType;
#define TOUCH_DISABLE_DIS 50
class TouchNode :public Sprite{
private:
    TouchNode();
    ~TouchNode();
    TouchType m_type = TOUCH_ENABLE_UP;
    void initData();
public:
    static TouchNode* create();
    
    void setPos(Touch * curP,Point heroP);
    TouchType getCurType();
    
};

#endif /* defined(__GWPJUMP__TouchNode__) */
