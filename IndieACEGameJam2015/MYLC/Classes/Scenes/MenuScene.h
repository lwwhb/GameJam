//
//  MenuScene.h
//  MYLC
//
//  Created by wang haibo on 15/7/10.
//
//

#ifndef __MYLC__MenuScene__
#define __MYLC__MenuScene__

#include "cocos2d.h"
class MenuScene : public cocos2d::Layer
{
    MenuScene();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *unused_event);
    
private:
    cocos2d::Camera*    m_pMainCamera;
    cocos2d::Sprite*    makeyourSprite;
    cocos2d::Sprite*    lifeSprite;
    cocos2d::Sprite*    colorfulSprite;
    cocos2d::Sprite*    logoSprite;
    int                 m_nCurrentLevel;
    cocos2d::Size size;
private:
    
     void makeyourEnd();
     void LifeEnd();
     void colorfulEnd();
    bool isTouchState;
    
};

#endif /* defined(__MYLC__MenuScene__) */
