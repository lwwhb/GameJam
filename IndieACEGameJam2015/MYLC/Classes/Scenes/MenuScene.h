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
    
private:
    cocos2d::Camera*    m_pMainCamera;
    int                 m_nCurrentLevel;
};

#endif /* defined(__MYLC__MenuScene__) */
