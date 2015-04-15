//
//  GameSpileLayer.h
//  GWPJUMP
//
//  Created by 易水流年 on 3/28/15.
//
//

#ifndef __GWPJUMP__GameSpileLayer__
#define __GWPJUMP__GameSpileLayer__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class GameSpileLayer : public Layer{
    GameSpileLayer();
    ~GameSpileLayer();
    virtual bool init();
private:
    void initHelper();
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
public:
    std::vector<Point>  movingPoints;   //移动的点；
    
    CREATE_FUNC(GameSpileLayer);
    void updatePostion(float dx,float dy);
};

#endif /* defined(__GWPJUMP__GameSpileLayer__) */
