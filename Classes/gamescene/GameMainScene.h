#ifndef __GameMain_SCENE_H__
#define __GameMain_SCENE_H__

#include "cocos2d.h"

class GameMainScene : public cocos2d::Scene
{
public:
    bool init();
    void initLayer();
    
    // a selector callback
    CREATE_FUNC(GameMainScene);
};

#endif // __HELLOWORLD_SCENE_H__
