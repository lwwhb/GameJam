//
//  LogoScene.h
//  MYLC
//
//  Created by wang haibo on 15/7/10.
//
//

#ifndef __MYLC__LogoScene__
#define __MYLC__LogoScene__

#include "cocos2d.h"
class LogoScene : public cocos2d::Layer
{
    LogoScene();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LogoScene);
private:
    void precache();
    void endcache();
private:
    cocos2d::Sprite*    m_pLogoSprite;
};

#endif /* defined(__MYLC__LogoScene__) */
