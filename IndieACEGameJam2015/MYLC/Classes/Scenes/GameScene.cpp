//
//  GameScene.cpp
//  MYLC
//
//  Created by wang haibo on 15/7/10.
//
//

#include "GameScene.h"
#include "GroundLayer.h"
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
    m_pWhiteLayer = LayerColor::create(Color4B::WHITE);
    if(!m_pWhiteLayer)
        return false;
    addChild(m_pWhiteLayer);

    EaseExponentialIn* fadeOut = EaseExponentialIn::create(FadeOut::create(1.5f));
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(GameScene::gameStart, this));
    Sequence* sequence = Sequence::create( fadeOut,  callFunc, NULL);
    m_pWhiteLayer->runAction(sequence);
    return true;
}
void GameScene::gameWin()
{
    CCLOG("gameWin");
}
void GameScene::gameLose()
{
    CCLOG("gameLose");
}
void GameScene::gameStart()
{
    m_pGroundLayer = GroundLayer::create("5x5-6.tmx");
    if(!m_pGroundLayer)
        return;
    m_pGroundLayer->setCameraMask((unsigned short)CameraFlag::USER1);
    ///focus
    m_pGroundLayer->setAnchorPoint(Vec2::ZERO);
    addChild(m_pGroundLayer);
    
    m_pMainCamera = Camera::create();
    if(!m_pMainCamera)
        return;
    m_pMainCamera->setPosition3D(Vec3(0,-m_pGroundLayer->getGroundRadius()*2.5f*cosf(M_PI),m_pGroundLayer->getGroundRadius()*2.5f*sinf(M_PI)) + m_pGroundLayer->getOffset());
    m_pMainCamera->lookAt(m_pGroundLayer->getPosition3D() + m_pGroundLayer->getOffset());
    addChild(m_pMainCamera);
    m_pMainCamera->setCameraFlag(CameraFlag::USER1);
    m_pGroundLayer->setCamera(m_pMainCamera);
    m_pGroundLayer->setGameScene(this);

}
