//
//  GameScene.h
//  MYLC
//
//  Created by wang haibo on 15/7/10.
//
//

#ifndef __MYLC__GameScene__
#define __MYLC__GameScene__

#include "cocos2d.h"
class GroundLayer;
class GameScene : public cocos2d::Layer
{
    GameScene();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
    virtual void gameWin();
    virtual void gameLose();
    void gameStart();
    void gameEnd();
    void jumpToMenu();
    void jumpToLevelSelect();
private:
    GroundLayer*                m_pGroundLayer;
    cocos2d::Camera*            m_pMainCamera;
    cocos2d::LayerColor*         m_pWhiteLayer;
    int                         m_nCurrentLevel;
};

#endif /* defined(__MYLC__GameScene__) */
