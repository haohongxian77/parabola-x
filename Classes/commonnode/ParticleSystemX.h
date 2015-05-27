//
//  ParticleSystemX.h
//  GwsJump
//
//  Created by 易水流年 on 5/26/15.
//
//

#ifndef __GwsJump__ParticleSystemX__
#define __GwsJump__ParticleSystemX__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class ParticleSystemX :public Node{
    ParticleSystemX();
    ~ParticleSystemX();
public:
    CREATE_FUNC(ParticleSystemX);
    bool init();
    void showFristParticle();
    void restartParticle();
    
    void showSecParticle();
    void showTRParticle();
    
    ParticleSystemQuad* emitter1;
    ParticleSystemQuad* emitter2;
    ParticleSystemQuad* emitter3;
    
};

#endif /* defined(__GwsJump__ParticleSystemX__) */
