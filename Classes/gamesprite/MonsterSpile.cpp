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
    __String* str = __String::createWithFormat("game_column%d.png",1);//bgIndex+1);
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
CollisionType MonsterSpile::getValid(Point prePoint,Point curPoint){
    CollisionType _cType= Collision_None;
    if (this->getPositionX()-curPoint.x<10) {
        
    }
    if (prePoint.y == this->getPositionY()) {
        prePoint.y = prePoint.y+1;
    }
    if (curPoint.y == this->getPositionY()) {
        curPoint.y = curPoint.y-1;
    }
    if (prePoint.x == this->getPositionX()) {
        prePoint.x = prePoint.x-1;
    }
    if (curPoint.x == this->getPositionX()) {
        curPoint.x = curPoint.x+1;
    }
    
    if (Vec2::isSegmentIntersect(prePoint, curPoint, this->getPosition(), Point(this->getPositionX(),this->getPositionY()-this->getContentSize().height)) ) {
        return Collision_Dead;
        
    }else if(Vec2::isSegmentIntersect(prePoint, curPoint, this->getPosition(), Point(this->getPositionX()+this->getContentSize().width,this->getPositionY())
        )
        ){
        return Collision_valid;
        
    }else{
        return  Collision_None;
    }
    
    return _cType;
    
}
bool MonsterSpile::isCollickPost(Point pos){
    Size  size = this->getContentSize();
     Point _point = this->getPosition();
    Rect recText = Rect(_point.x,_point.y-size.height,size.width,size.height);
    if (pos.x>_point.x&&pos.x<_point.x+size.width) {
        return true;
    }
    return false;
}





