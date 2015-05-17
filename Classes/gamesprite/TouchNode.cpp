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
void TouchNode::setPos(Point curP, float heroP){
    TouchType touchType_;
    SpriteFrame* frame = NULL;
    this->setPosition(curP);
    Size  size = Director::getInstance()->getWinSize();
    if (curP.y - heroP > size.height/8) {
        frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("touch_normal.png");
        touchType_ = TOUCH_Enable;
    }else{
     frame=SpriteFrameCache::getInstance()->getSpriteFrameByName("touch_unnormal.png");
    touchType_ = TOUCH_Disable;
    }
    
    if (m_type == touchType_)
        return;
    m_type = touchType_;
    this->setSpriteFrame(frame);
    
}
TouchType TouchNode::getCurType(){
    return m_type;
}







