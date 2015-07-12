//
//  FinalScene.h
//  MYLC
//
//  Created by wang haibo on 15/7/12.
//
//

#ifndef __MYLC__FinalScene__
#define __MYLC__FinalScene__

#include "cocos2d.h"

#include "EffectSprite3D.h"
#include "TextDisplayer.h"

class FinalScene : public cocos2d::Layer
{
    FinalScene();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(FinalScene);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *unused_event);
    void stuffText();
    
private:
    cocos2d::Camera*                m_pMainCamera;
    cocos2d::LayerColor*            m_pWhiteLayer;
    
    EffectSprite3D*                 m_pHouse;
    
    EffectSprite3D*                 m_pSun;
    EffectSprite3D*                 m_pTree1;
    EffectSprite3D*                 m_pTree2;
    EffectSprite3D*                 m_pTree3;
    
    EffectSprite3D*                 m_pFlower1;
    EffectSprite3D*                 m_pFlower2;
    EffectSprite3D*                 m_pFlower3;
    EffectSprite3D*                 m_pFlower4;
    
    EffectSprite3D*                 m_pCloud1;
    EffectSprite3D*                 m_pCloud2;
    
    EffectSprite3D*                 m_pBoy;
    EffectSprite3D*                 m_pGirl;

    EffectSprite3D*                 m_pHeart;
    TextDisplayer* text;
};

#endif /* defined(__MYLC__FinalScene__) */
