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
    TOUCH_Enable =0, //没有碰撞
    TOUCH_Disable     //有效碰撞 hero站在上边
    
}TouchType;
class TouchNode :public Sprite{
private:
    TouchNode();
    ~TouchNode();
    TouchType m_type = TOUCH_Enable;
    void initData();
public:
    static TouchNode* create();
    
    void setPos(Point curP,float heroP);
    TouchType getCurType();
    
};

#endif /* defined(__GWPJUMP__TouchNode__) */
