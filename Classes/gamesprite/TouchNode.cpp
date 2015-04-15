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
    touch->initWithFile("CloseNormal.png");
    touch->initData();
    return touch;
}
void TouchNode::initData(){
        Director::getInstance()->getTextureCache()->addImage("CloseSelected.png");
        Director::getInstance()->getTextureCache()->addImage("CloseNormal.png");
}
void TouchNode::setPos(Point curP, float heroP){
    TouchType touchType_;
    Texture2D* tex = NULL;
    this->setPosition(curP);
    if (curP.y>heroP) {
        tex=Director::getInstance()->getTextureCache()->addImage("CloseNormal.png");
        touchType_ = TOUCH_Enable;
    }else{
     tex=Director::getInstance()->getTextureCache()->addImage("CloseSelected.png");
    touchType_ = TOUCH_Disable;
    }
    
    if (m_type == touchType_)
        return;
    m_type = touchType_;
    this->setTexture(tex);
    
}
TouchType TouchNode::getCurType(){
    return m_type;
}







