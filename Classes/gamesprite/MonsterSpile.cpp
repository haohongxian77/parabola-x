//
//  MonsterSpile.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 3/22/15.
//
//

#include "MonsterSpile.h"

MonsterSpile::MonsterSpile(){
}
MonsterSpile::~MonsterSpile(){
}
std::string MonsterSpile::getspriteFileName(int type){
    return "spile.png";
}
MonsterSpile* MonsterSpile::create(int spileType){
    std::string fileName = getspriteFileName(spileType);
    MonsterSpile* sp = new MonsterSpile();
    
    //sp->initWithSpriteFrameName(fileName);
    sp->initWithFile(fileName);
    sp->setAnchorPoint(Vec2(0,1));
    return  sp;
}
CollisionType MonsterSpile::getValid(Rect heroRect){
    CollisionType _cType= Collision_None;
    Point _point = this->getPosition();
    Size  size = this->getContentSize();
    Rect rec = Rect(_point.x,_point.y-10,size.width,10);
    Rect recText = Rect(_point.x,_point.y-size.height,size.width,size.height);
//    CCLOG("英雄的位置======%f=====%f=====%f=====%f ",heroRect.origin.x,heroRect.origin.y,heroRect.size.width,heroRect.size.height);
//     CCLOG("可站立的位置======%f=====%f=====%f=====%f ",rec.origin.x,rec.origin.y,rec.size.width,rec.size.height);
//    CCLOG("柱子的位置======%f=====%f=====%f=====%f ",recText.origin.x,recText.origin.y,recText.size.width,recText.size.height);
    if (rec.intersectsRect(heroRect)) {
        return Collision_valid;
        
    }else if(recText.intersectsRect(heroRect)){
        return Collision_Dead;
        
    }else{
        return  Collision_None;
    }
    
    return _cType;
    
}