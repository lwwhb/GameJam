//
//  LevelSelectScene.cpp
//  MYLC
//
//  Created by wang haibo on 15/6/23.
//
//

#include "LevelSelectScene.h"
#include "CubeFace.h"
#include "UtilityHelper.h"
#include "GameScene.h"
USING_NS_CC;

Scene* LevelSelectScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LevelSelectScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
LevelSelectScene::LevelSelectScene()
{
    m_pMainCamera   = nullptr;
    m_pCube         = nullptr;
    m_pFront        = nullptr;
    m_pTop          = nullptr;
    m_pRight        = nullptr;
    m_pBack         = nullptr;
    m_pLeft         = nullptr;
    m_pDown         = nullptr;
    m_pWhiteLayer   = NULL;
    m_fRate = M_PI_2;
}
// on "init" you need to initialize your instance
bool LevelSelectScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
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
    
    m_pCube = Node::create();
    if(!m_pCube)
        return false;
    m_pFront = CubeFace::create(CubeFace::FT_FRONT);
    if(!m_pFront)
        return false;
    m_pCube->addChild(m_pFront);
        
    m_pTop = CubeFace::create(CubeFace::FT_TOP);
    if(!m_pTop)
        return false;
    m_pCube->addChild(m_pTop);
    
    m_pRight = CubeFace::create(CubeFace::FT_RIGHT);
    if(!m_pRight)
        return false;
    m_pCube->addChild(m_pRight);
    
    m_pBack = CubeFace::create(CubeFace::FT_BACK);
    if(!m_pBack)
        return false;
    m_pCube->addChild(m_pBack);
    
    m_pLeft = CubeFace::create(CubeFace::FT_LEFT);
    if(!m_pLeft)
        return false;
    m_pCube->addChild(m_pLeft);
    
    m_pDown = CubeFace::create(CubeFace::FT_DOWN);
    if(!m_pDown)
        return false;
    m_pCube->addChild(m_pDown);
    

    
    m_pCube->setCameraMask((unsigned short)CameraFlag::USER1);
    ///focus
    m_pCube->setAnchorPoint(Vec2::ZERO);
    addChild(m_pCube);
    m_pCube->setPosition3D(Vec3(30,0,0));
    m_pCube->setRotation3D(Vec3(0,20,0));
    
    EaseSineIn* rotateBy1 = EaseSineIn::create(RotateBy::create(1.0f, Vec3(2,-2,2)));
    EaseSineOut* rotateBy2 = EaseSineOut::create(RotateBy::create(1.0f, Vec3(-2,2,-2)));
    
    EaseSineIn* rotateBy3 = EaseSineIn::create((RotateBy::create(1.0f, Vec3(2,2,-2))));
    EaseSineOut* rotateBy4 = EaseSineOut::create(RotateBy::create(1.0f, Vec3(-2,-2,2)));
    
    EaseSineIn* rotateBy5 = EaseSineIn::create(RotateBy::create(1.0f, Vec3(-2,2,2)));
    EaseSineOut* rotateBy6 = EaseSineOut::create(RotateBy::create(1.0f, Vec3(2,-2,-2)));
    
    Sequence* sequence = Sequence::create(rotateBy1, rotateBy6, rotateBy3, rotateBy4, rotateBy5, rotateBy2, nullptr);
    RepeatForever* repeat = RepeatForever::create(sequence);
    
    m_pCube->runAction(repeat);
    
    
    m_pMainCamera = Camera::create();
    if(!m_pMainCamera)
        return false;
    m_pMainCamera->setPosition3D(Vec3(0, 40, 80));
    m_pMainCamera->lookAt(Vec3(0,15,0));
    addChild(m_pMainCamera);
    m_pMainCamera->setCameraFlag(CameraFlag::USER1);
    
    AmbientLight* ambLight = AmbientLight::create(Color3B(150, 150, 150));
    if(!ambLight)
        return false;
    addChild(ambLight);
    DirectionLight* directionLight = DirectionLight::create(Vec3(-3, -4, -2), Color3B(128, 128, 128));
    if(!directionLight)
        return false;
    addChild(directionLight);
    
    auto size = Director::getInstance()->getVisibleSize();
    m_pWhiteLayer = LayerColor::create(Color4B::WHITE);
    if(!m_pWhiteLayer)
        return false;
    m_pWhiteLayer->setPosition(-size.width*0.5f, -size.height*0.5f);
    m_pWhiteLayer->setOpacity(0);
    m_pWhiteLayer->setCameraMask((unsigned short)CameraFlag::USER1);
    addChild(m_pWhiteLayer);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchAllAtOnce::create();
    if(touchListener == nullptr)
        return false;
    touchListener->onTouchesBegan = CC_CALLBACK_2(LevelSelectScene::onTouchesBegan, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(LevelSelectScene::onTouchesMoved, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(LevelSelectScene::onTouchesEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}
void LevelSelectScene::onEnter()
{
    Layer::onEnter();
    scheduleUpdate();
}
void LevelSelectScene::onExit()
{
    unscheduleUpdate();
    Layer::onExit();
    
}
// 更新处理
void LevelSelectScene::update(float delta)
{
    if(m_pCube)
    {
        m_fRate += 0.01;
        m_pCube->setPosition3D(Vec3(m_pCube->getPositionX()+sin(1.05*m_fRate)*0.05f,m_pCube->getPositionY()-sin(1.05*m_fRate)*0.02f,m_pCube->getPositionZ()+sin(1.05*m_fRate)*0.01f));
    }
    Layer::update(delta);
    
}
// 处理输入
void LevelSelectScene::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
    if(touches.size() > 0)
    {
        Vec2 locationInNode = convertToNodeSpace(touches[0]->getLocation());
        Ray ray;
        UtilityHelper::getCameraToViewportRay(m_pMainCamera, locationInNode, &ray);
        if(m_pFront)
        {
            if(ray.intersects(m_pFront->getAABB()))
            {
                beginGame();
                return;
            }
        }
        if(m_pTop)
        {
            if(ray.intersects(m_pTop->getAABB()))
            {
                beginGame();
                return;
            }
        }
        if(m_pRight)
        {
            if(ray.intersects(m_pRight->getAABB()))
            {
                beginGame();
                return;
            }
        }
        if(m_pBack)
        {
            if(ray.intersects(m_pBack->getAABB()))
            {
                beginGame();
                return;
            }
        }
        if(m_pLeft)
        {
            if(ray.intersects(m_pLeft->getAABB()))
            {
                beginGame();
                return;
            }
        }
        if(m_pDown)
        {
            if(ray.intersects(m_pDown->getAABB()))
            {
                beginGame();
                return;
            }
        }
    }
}
void LevelSelectScene::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
}
void LevelSelectScene::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
}
void LevelSelectScene::beginGame()
{
    if(m_pCube)
    {
        m_pCube->stopAllActions();
        RotateBy* rotateBy = RotateBy::create(2.0f, Vec3(0, 360, 0));
        EaseSineOut* moveTo = EaseSineOut::create(MoveTo::create(2.0f, m_pMainCamera->getPosition3D()-Vec3(0,m_pFront->getRadius()*2,m_pFront->getRadius()*3)));
        Spawn* spawn = Spawn::create(rotateBy, moveTo, NULL);
        RepeatForever* repeate = RepeatForever::create(spawn);
        m_pCube->runAction(repeate);
    }
    if(m_pWhiteLayer)
    {
        EaseExponentialOut* fadeIn = EaseExponentialOut::create(FadeIn::create(1.5f));
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::startGame, this));
        Sequence* sequence = Sequence::create( fadeIn,  callFunc, NULL);
        m_pWhiteLayer->runAction(sequence);
    }
}
void LevelSelectScene::startGame()
{
    Director::getInstance()->replaceScene( GameScene::createScene());
}