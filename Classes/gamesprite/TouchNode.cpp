//
//  TouchNode.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 3/25/15.
//
//

#include "TouchNode.h"


TouchNode::TouchNode(){
}
TouchNode::~TouchNode(){
}
TouchNode* TouchNode::create(){
    TouchNode* touch = new TouchNode();
    touch->initWithSpriteFrameName("touch_normal.png");
    //touch->initWithFile("CloseNormal.png");
    return touch;
}
void TouchNode::setPos(Touch * touchPoint, Point heroP){
    TouchType touchType_;
    SpriteFrame* frame = NULL;
    Point curP = this->getParent()->convertTouchToNodeSpace(touchPoint);
    //Point wordP = touchPoint->getLocationInView();
    this->setPosition(curP);
    Size  size = Director::getInstance()->getWinSize();
    if(heroP.x-curP.x>0){
        frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("touch_unnormal.png");
        touchType_ = TOUCH_DISABLE;
        return;
    }
    if (curP.y-heroP.y> TOUCH_DISABLE_DIS) {
        frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("touch_normal.png");
        touchType_ = TOUCH_ENABLE_UP;
    }else if(curP.y-heroP.y>0){
     frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("touch_unnormal.png");
       touchType_ = TOUCH_DISABLE_UP;
    }else if(curP.y-heroP.y>-1*TOUCH_DISABLE_DIS){
        frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("touch_unnormal.png");
        touchType_ = TOUCH_DISABLE_DOWN;
    }else{
        frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("touch_normal.png");
        touchType_ = TOUCH_ENALBE_DOWN;
    }
    
    if (m_type == touchType_)
        return;
    m_type = touchType_;
    this->setSpriteFrame(frame);
    
}
TouchType TouchNode::getCurType(){
    return m_type;
}







