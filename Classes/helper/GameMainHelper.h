//
//  GameMainHelper.h
//  GWPJUMP
//
//  Created by 易水流年 on 3/22/15.
//
//

#ifndef __GWPJUMP__GameMainHelper__
#define __GWPJUMP__GameMainHelper__

#include <stdio.h>
#include "cocos2d.h"
#include "gamesprite/HeroFrog.h"
#include "gamesprite/MonsterSpile.h"
#include "gamescene/GameMainScene.h"

class GameMainLayer;
using namespace cocos2d;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/HHPlatform.h"
#endif
#define Highest "HIGHESTSCORE"
#define MUSICKEY "MUSICKEY"
#define SOUNDKEY "SOUNDKEY"
#define RANKKEY "RANKKEY"

#define BGMUSIC "sound/01.mp3"
#define NEWCAREAR "sound/02.wav"

#define BTNCLICK "sound/03.ogg"
#define JUMPSTART_0 "sound/04_0.mp3"
#define JUMPSTART_1 "sound/04_1.mp3"
#define JUMPOVER "sound/05.wav"
#define HEROOVER "sound/06.wav"
#define HEROSTATIC "sound/07.ogg"
#define GAMEOVER "sound/08.mp3"

class GameMainHelper :public Ref{
    GameMainHelper();
    ~GameMainHelper();
public:
    static GameMainHelper* mainHelper;
    static GameMainHelper* getInstance();
    
    void atachLayer(GameMainLayer* layer);
    void atachScene(GameMainScene* scene);
    void setHero(HeroFrog* hero);
    void updateHelper(float dt);
    
    CollisionType isCollisionPosts(Point PreprePoint,Point prePoint,Point curPoint);   //碰撞检测
    Node* getTouchPosts(Point touchPoint);
    void initPosts();
    void changePostsSprite();
    void managePost();
    Sprite* getCollectSp();
    void initJumpDate(std::vector<float> param,float SpeedX,float highY , float curY);
    
    Point getHeroPostPoint();
    void playSound(std::string soundName);
public:
    void gameOver();
    void startGame();
    void jumpOver();
    //void changeBgIndex();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void share(ShareStatus status);
#endif
   
public:
    CC_SYNTHESIZE(gameStatus, m_gameStatus, GameStaus);
    CC_SYNTHESIZE(int, m_earthH, EarthH);
    CC_SYNTHESIZE(int, m_curScore, CurScore);
    CC_SYNTHESIZE(int, m_HighstScore, Highest);
    CC_SYNTHESIZE(int, m_curBgIndex, CurBgIndex);
    CC_SYNTHESIZE(bool, m_isGoogle, GoogleServer);
    CC_SYNTHESIZE(int, m_music, Music);
    CC_SYNTHESIZE(int, m_sound, Sound);

    __Array* m_posts;
    Sprite* m_curHeroPost;
    GameMainLayer* m_Layer;
    Node* m_spilesNode;
    HeroFrog* m_Hero;
private:
    void initDate();
    void initGameStartData();
    
    
    Point addPosts(float perPointX);
    Point getTouchPoint(Point perPoint);
    float getNextPointX(Point touchPoint,Point perPoint);
    Point getNextPoint(Point perPoint);
    
    void movingLayer(float speed);
    void initPathPoints(std::vector<float> params,float SpeedX,float highY , float curY);
    
    float getCurSpeed(float speed,float totalDis,float curDis);
    void showFullAd();
    
    
    
private:
    int m_unitH = 0;
    int m_unitW = 0;
   // int m_collectIndex = -1;
    int m_startIndex = -1;
    
    
    
    GameMainScene* m_mainScene = NULL;
    //hero 路径
    std::vector<Point> m_heroPaths;
    int m_heroPathIndex = 0;
    int m_playTimes = -1;
    
    
    
};

#endif /* defined(__GWPJUMP__GameMainHelper__) */
