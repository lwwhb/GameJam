//
//  GameScene.cpp
//  MYLC
//
//  Created by wang haibo on 15/7/10.
//
//

#include "GameScene.h"
#include "GroundLayer.h"
#include "MenuScene.h"
#include "LevelSelectScene.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
GameScene::GameScene()
{
    m_pGroundLayer  = nullptr;
    m_pMainCamera   = nullptr;
    m_pWhiteLayer   = nullptr;
}
// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    m_nCurrentLevel = UserDefault::getInstance()->getIntegerForKey("CurrentLevel", 1);
    ParticleSystemQuad* starfield= ParticleSystemQuad::create("starfield.plist");
    if(!starfield)
    {
        CCLOG("Load explosion particle system failed! file: starfield.plist");
        return false;
    }
    starfield->setStartSize(5.0f);
    starfield->setStartSizeVar(3.0f);
    starfield->setGravity(Vec2(-40.0f, 0));
    addChild(starfield);
    
    m_pWhiteLayer = LayerColor::create(Color4B::WHITE);
    if(!m_pWhiteLayer)
        return false;
    addChild(m_pWhiteLayer);

    EaseExponentialIn* fadeOut = EaseExponentialIn::create(FadeOut::create(1.0f));
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(GameScene::gameStart, this));
    Sequence* sequence = Sequence::create( fadeOut,  callFunc, NULL);
    m_pWhiteLayer->runAction(sequence);
    return true;
}
void GameScene::gameWin()
{
    CCLOG("gameWin");
    m_nCurrentLevel++;
    UserDefault::getInstance()->setIntegerForKey("CurrentLevel", m_nCurrentLevel);
    gameEnd();
}
void GameScene::gameLose()
{
    CCLOG("gameLose");
    gameEnd();
}
void GameScene::gameStart()
{
    switch (m_nCurrentLevel) {
        case 1:
            m_pGroundLayer = GroundLayer::create("5x5-1.tmx");
            break;
        case 2:
            m_pGroundLayer = GroundLayer::create("5x5-2.tmx");
            break;
        case 3:
            m_pGroundLayer = GroundLayer::create("5x5-3.tmx");
            break;
        case 4:
            m_pGroundLayer = GroundLayer::create("5x5-4.tmx");
            break;
        case 5:
            m_pGroundLayer = GroundLayer::create("5x5-5.tmx");
            break;
        case 6:
            m_pGroundLayer = GroundLayer::create("5x5-6.tmx");
            break;
        default:
            break;
    }
    if(!m_pGroundLayer)
        return;
    m_pGroundLayer->setCameraMask((unsigned short)CameraFlag::USER1);
    ///focus
    m_pGroundLayer->setAnchorPoint(Vec2::ZERO);
    addChild(m_pGroundLayer);
    
    m_pMainCamera = Camera::create();
    if(!m_pMainCamera)
        return;
    m_pMainCamera->setPosition3D(Vec3(0,-m_pGroundLayer->getGroundRadius()*2.5f*cosf(M_PI),m_pGroundLayer->getGroundRadius()*2.5f*sinf(M_PI)) + m_pGroundLayer->getOffset() + Vec3(20,0,0));
    m_pMainCamera->lookAt(m_pGroundLayer->getPosition3D() + m_pGroundLayer->getOffset() + Vec3(20,0,0));
    addChild(m_pMainCamera);
    m_pMainCamera->setCameraFlag(CameraFlag::USER1);
    m_pGroundLayer->setCamera(m_pMainCamera);
    m_pGroundLayer->setGameScene(this);

}
void GameScene::gameEnd()
{
    if(m_pGroundLayer)
        m_pGroundLayer->setVisible(false);

    if(m_pWhiteLayer)
    {
        EaseExponentialOut* fadeIn = EaseExponentialOut::create(FadeIn::create(1.0f));
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(GameScene::jumpToLevelSelect, this));
        Sequence* sequence = Sequence::create( fadeIn, callFunc, NULL);
        m_pWhiteLayer->runAction(sequence);
    }
}
void GameScene::jumpToMenu()
{
    Director::getInstance()->replaceScene(MenuScene::createScene());
}
void GameScene::jumpToLevelSelect()
{
    Director::getInstance()->replaceScene(LevelSelectScene::createScene());
}