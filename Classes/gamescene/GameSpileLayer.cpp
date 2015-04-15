//
//  GameSpileLayer.cpp
//  GWPJUMP
//
//  Created by ���姘存��骞� on 3/28/15.
//
//

#include "GameSpileLayer.h"
#include "helper/GameMainHelper.h"

GameSpileLayer::GameSpileLayer(){
}
GameSpileLayer::~GameSpileLayer(){
}
bool GameSpileLayer::init(){
    if (Layer::init()) {
        initHelper();
        return true;
    }
    return false;
}
void GameSpileLayer::initHelper(){
   // GameMainHelper::getInstance()->atachSpileLayer(this);
    GameMainHelper::getInstance()->initPosts();
}
void GameSpileLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    if(movingPoints.size() == 0)
        return;
    
    ccDrawColor4F(255,228,0,125);
    glLineWidth(5);
    for (int i=0; i<movingPoints.size()-1; i++) {
        if((i/10)%2==0)
            continue;
        Point p1= movingPoints[i];
        Point p2 = movingPoints[i+1];
        ccDrawLine(p1,p2);
    }
    
    
}
void GameSpileLayer::updatePostion(float dx, float dy){
    Point curPos = this->getPosition();
    this->setPositionX(curPos.x-dx);
}

