//
//  LevelSelectScene.h
//  MYLC
//
//  Created by wang haibo on 15/7/10.
//
//

#ifndef __MYLC__LevelSelectScene__
#define __MYLC__LevelSelectScene__

#include "cocos2d.h"
#include "CubeFace.h"
class LevelSelectScene : public cocos2d::Layer
{
    LevelSelectScene();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LevelSelectScene);
    
    virtual void onEnter();
    virtual void onExit();
    // 更新处理
    virtual void update(float delta);
protected:
    // 处理输入
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
private:
    void beginSelect();
    void beginGame();
    void startGame();
private:
    cocos2d::Camera*    m_pMainCamera;
    cocos2d::Node*      m_pCube;
    CubeFace*           m_pFront;
    CubeFace*           m_pTop;
    CubeFace*           m_pRight;
    CubeFace*           m_pBack;
    CubeFace*           m_pLeft;
    CubeFace*           m_pDown;
    float               m_fRate;
    cocos2d::LayerColor*         m_pWhiteLayer;
    int                 m_nCurrentLevel;
};

#endif /* defined(__MYLC__LevelSelectScene__) */
