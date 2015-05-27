//
//  MonsterSpile.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 3/22/15.
//
//

#include "MonsterSpile.h"

MonsterSpile::MonsterSpile():drawNode(NULL){
}
MonsterSpile::~MonsterSpile(){
}
std::string MonsterSpile::getspriteFileName(int type){
    
    return "game_column1.png";
}
MonsterSpile* MonsterSpile::create(int spileType){
    std::string fileName = getspriteFileName(spileType);
    MonsterSpile* sp = new MonsterSpile();
    
    sp->initWithSpriteFrameName(fileName);
   // sp->initWithFile(fileName);
    sp->setAnchorPoint(Vec2(0,1));
    sp->initDraw();
    
    
    return  sp;
}
void MonsterSpile::changeSprite(int bgIndex){
    __String* str = __String::createWithFormat("game_column%d.png",bgIndex+1);
    SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
    setDisplayFrame(frame);
}
void MonsterSpile::moveOver(){
    Size size = this->getContentSize();
    MoveBy* moBy = MoveBy::create(1, Point(0,-size.height));
    Sequence* seq = Sequence::create(moBy,CCCallFunc::create(CC_CALLBACK_0(MonsterSpile::disapear, this)), NULL);
    this->runAction(seq);
    
}
void MonsterSpile::disapear(){
    this->removeFromParentAndCleanup(true);
}
void MonsterSpile::initDraw(){
    drawNode = DrawNode::create();
    this->addChild(drawNode,100);
}
void MonsterSpile::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags){
    Sprite::draw(renderer,transform,flags);
    if (!drawNode) {
        return;
    }
    drawNode->clear();
    
    Size  size = this->getContentSize();
    drawNode->drawRect(Vec2(0,-10), Vec2(size.width,0), Color4F(255, 0, 255, 1));
    drawNode->drawRect(Vec2(0, -size.height), Vec2(size.width,0), Color4F(0, 255, 255, 1));
}
CollisionType MonsterSpile::getValid(Rect heroFootRect,Rect heroBodyRect){
    CollisionType _cType= Collision_None;
    Point _point = this->getPosition();
    Size  size = this->getContentSize();
    Rect rec = Rect(_point.x,_point.y,size.width,10);
    Rect recText = Rect(_point.x,_point.y-size.height,size.width,size.height);
//    CCLOG("英雄的位置======%f=====%f=====%f=====%f ",heroRect.origin.x,heroRect.origin.y,heroRect.size.width,heroRect.size.height);
//     CCLOG("可站立的位置======%f=====%f=====%f=====%f ",rec.origin.x,rec.origin.y,rec.size.width,rec.size.height);
    CCLOG("柱子的位置======%f=====%f=====%f=====%f ",recText.origin.x,recText.origin.y,recText.size.width,recText.size.height);
    if (rec.intersectsRect(heroFootRect)) {
        return Collision_valid;
        
    }else if(recText.intersectsRect(heroBodyRect)){
        return Collision_Dead;
        
    }else{
        return  Collision_None;
    }
    
    return _cType;
    
}