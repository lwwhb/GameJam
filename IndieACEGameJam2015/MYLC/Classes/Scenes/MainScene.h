//
//  LogoScene.h
//  MYLC
//
//  Created by wang haibo on 15/7/10.
//
//

#ifndef __MYLC__MainScene__
#define __MYLC__MainScene__

#include "cocos2d.h"
class MainScene : public cocos2d::Layer
{
    MainScene();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
private:
    void precache();
    void endcache();
private:

};

#endif /* defined(__MYLC__MainScene__) */
