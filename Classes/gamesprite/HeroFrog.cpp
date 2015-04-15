//
//  HeroFrog.cpp
//  GWPJUMP
//
//  Created by 易水流年 on 3/21/15.
//
//

#include "HeroFrog.h"

HeroFrog::HeroFrog(){
}
HeroFrog::~HeroFrog(){
}
bool HeroFrog::init(){
    if (Sprite::init()) {
        this->initWithFile("dragon.png");
        return true;
    }
    return false;
    
}
void HeroFrog::setPos(Point pos){
 
}

