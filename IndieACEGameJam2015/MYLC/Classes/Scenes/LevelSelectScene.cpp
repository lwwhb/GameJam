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
    m_bTouchEnable  = true;
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
    UserDefault::getInstance()->setIntegerForKey("CurrentLevel", 1);
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
    
    Sequence* sequence1 = Sequence::create(rotateBy1, rotateBy6, rotateBy3, rotateBy4, rotateBy5, rotateBy2, nullptr);
    RepeatForever* repeat = RepeatForever::create(sequence1);
    
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
    addChild(m_pWhiteLayer);
    m_pWhiteLayer->setCameraMask((unsigned short)CameraFlag::USER1);
    
    EaseExponentialIn* fadeOut = EaseExponentialIn::create(FadeOut::create(1.0f));
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::beginSelect, this));
    Sequence* sequence2 = Sequence::create( fadeOut,  callFunc, NULL);
    m_pWhiteLayer->runAction(sequence2);
    
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
    if(!m_bTouchEnable)
        return;
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
void LevelSelectScene::beginSelect()
{
    switch (m_nCurrentLevel) {
        case 1:
            enableTouch();
            break;
        case 2:
            {
                if(m_pFront)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, m_pFront->getRadius()*2+2, m_pFront->getRadius()*2));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pFront->runAction(sequnce);
                }
            }
            break;
        case 3:
            {
                if(m_pFront)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, m_pFront->getRadius()*2+2, m_pFront->getRadius()*2));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pFront->runAction(sequnce);
                }
                if(m_pTop)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, m_pTop->getRadius()*4+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pTop->runAction(sequnce);
                }
            }
            break;
        case 4:
            {
                if(m_pFront)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, m_pFront->getRadius()*2+2, m_pFront->getRadius()*2));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pFront->runAction(sequnce);
                }
                if(m_pTop)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, m_pTop->getRadius()*4+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pTop->runAction(sequnce);
                }
                if(m_pRight)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(0, 0, 180)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(m_pRight->getRadius()*24, m_pRight->getRadius()*24+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pRight->runAction(sequnce);
                }
            }
            break;
        case 5:
            {
                if(m_pFront)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, m_pFront->getRadius()*2+2, m_pFront->getRadius()*2));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pFront->runAction(sequnce);
                }
                if(m_pTop)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, m_pTop->getRadius()*4+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pTop->runAction(sequnce);
                }
                if(m_pRight)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(0, 0, 180)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(m_pRight->getRadius()*24, m_pRight->getRadius()*24+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pRight->runAction(sequnce);
                }
                if(m_pBack)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(-180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, m_pBack->getRadius()*2+2, -m_pBack->getRadius()*2));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pBack->runAction(sequnce);
                }
            }
            break;
        case 6:
            {
                if(m_pFront)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, m_pFront->getRadius()*2+2, m_pFront->getRadius()*2));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pFront->runAction(sequnce);
                }
                if(m_pTop)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, m_pTop->getRadius()*4+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pTop->runAction(sequnce);
                }
                if(m_pRight)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(0, 0, 180)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(m_pRight->getRadius()*24, m_pRight->getRadius()*24+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pRight->runAction(sequnce);
                }
                if(m_pBack)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(-180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, m_pBack->getRadius()*2+2, -m_pBack->getRadius()*2));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pBack->runAction(sequnce);
                }
                if(m_pLeft)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(0, 0, -180)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(-m_pRight->getRadius()*24, m_pRight->getRadius()*24+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pLeft->runAction(sequnce);
                }
            }
            break;
        default:
            {
                if(m_pFront)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, m_pFront->getRadius()*2+2, m_pFront->getRadius()*2));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pFront->runAction(sequnce);
                }
                if(m_pTop)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, m_pTop->getRadius()*4+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pTop->runAction(sequnce);
                }
                if(m_pRight)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(0, 0, 180)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(m_pRight->getRadius()*24, m_pRight->getRadius()*24+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pRight->runAction(sequnce);
                }
                if(m_pBack)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(-180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, m_pBack->getRadius()*2+2, -m_pBack->getRadius()*2));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pBack->runAction(sequnce);
                }
                if(m_pLeft)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(0, 0, -180)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(-m_pRight->getRadius()*24, m_pRight->getRadius()*24+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pLeft->runAction(sequnce);
                }
                
                if(m_pDown)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(-180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, 2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pDown->runAction(sequnce);
                }

            }
            break;
    }
}
void LevelSelectScene::beginGame()
{
    if(m_nCurrentLevel < 7)
    {
        if(m_pCube)
        {
            m_pCube->stopAllActions();
            RotateBy* rotateBy = RotateBy::create(1.5f, Vec3(0, 360, 0));
            EaseSineOut* moveTo = EaseSineOut::create(MoveTo::create(1.5f, m_pMainCamera->getPosition3D()-Vec3(0,m_pFront->getRadius()*2,m_pFront->getRadius()*3)));
            Spawn* spawn = Spawn::create(rotateBy, moveTo, NULL);
            RepeatForever* repeat = RepeatForever::create(spawn);
            m_pCube->runAction(repeat);
        }
        if(m_pWhiteLayer)
        {
            DelayTime* delay = DelayTime::create(0.5f);
            EaseExponentialOut* fadeIn = EaseExponentialOut::create(FadeIn::create(1.0f));
            CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::startGame, this));
            Sequence* sequence = Sequence::create(delay, fadeIn, callFunc, NULL);
            m_pWhiteLayer->runAction(sequence);
        }
    }
    else
    {
        if(m_pCube)
        {
            m_pCube->stopAllActions();
            
            EaseSineIn* rotateBy1 = EaseSineIn::create(RotateBy::create(0.1f, Vec3(2,-2,2)));
            EaseSineOut* rotateBy2 = EaseSineOut::create(RotateBy::create(0.1f, Vec3(-2,2,-2)));
            
            EaseSineIn* rotateBy3 = EaseSineIn::create((RotateBy::create(0.1f, Vec3(2,2,-2))));
            EaseSineOut* rotateBy4 = EaseSineOut::create(RotateBy::create(0.1f, Vec3(-2,-2,2)));
            
            EaseSineIn* rotateBy5 = EaseSineIn::create(RotateBy::create(0.1f, Vec3(-2,2,2)));
            EaseSineOut* rotateBy6 = EaseSineOut::create(RotateBy::create(0.1f, Vec3(2,-2,-2)));
            
            Sequence* sequence1 = Sequence::create(rotateBy1, rotateBy6, rotateBy3, rotateBy4, rotateBy5, rotateBy2, nullptr);
            //RotateBy* rotateBy = RotateBy::create(0.3f, Vec3(0, 180, 0));
            
            Spawn* spawn = Spawn::create(sequence1, NULL);
            RepeatForever* repeat = RepeatForever::create(spawn);
            m_pCube->runAction(repeat);
        }
        if(m_pWhiteLayer)
        {
            DelayTime* delay = DelayTime::create(5.0f);
            CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::girlDisplay, this));
            Sequence* sequence = Sequence::create(delay, callFunc, NULL);
            m_pWhiteLayer->runAction(sequence);
        }

    }
}
void LevelSelectScene::startGame()
{
    Director::getInstance()->replaceScene(GameScene::createScene());
}
void LevelSelectScene::enableTouch()
{
    m_bTouchEnable = true;
    switch (m_nCurrentLevel) {
        case 1:
            break;
        default:
            {
                if(m_pCube)
                {
                    EaseSineIn* rotateBy1 = EaseSineIn::create(RotateBy::create(1.0f, Vec3(2,-2,2)));
                    EaseSineOut* rotateBy2 = EaseSineOut::create(RotateBy::create(1.0f, Vec3(-2,2,-2)));
                    
                    EaseSineIn* rotateBy3 = EaseSineIn::create((RotateBy::create(1.0f, Vec3(2,2,-2))));
                    EaseSineOut* rotateBy4 = EaseSineOut::create(RotateBy::create(1.0f, Vec3(-2,-2,2)));
                    
                    EaseSineIn* rotateBy5 = EaseSineIn::create(RotateBy::create(1.0f, Vec3(-2,2,2)));
                    EaseSineOut* rotateBy6 = EaseSineOut::create(RotateBy::create(1.0f, Vec3(2,-2,-2)));
                    
                    Sequence* sequence1 = Sequence::create(rotateBy1, rotateBy6, rotateBy3, rotateBy4, rotateBy5, rotateBy2, nullptr);
                    RepeatForever* repeat = RepeatForever::create(sequence1);
                    m_pCube->runAction(repeat);
                }
            }
            break;
    }
}
void LevelSelectScene::girlDisplay()
{
    if(m_pFront)
    {
        m_bTouchEnable = false;
        EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(180, 0, 0)));
        MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, m_pFront->getRadius()*10+2, m_pFront->getRadius()*10));
        ScaleTo* scaleTo = ScaleTo::create(1.0f, 0.0f);
        Spawn* spawn = Spawn::create(moveTo, rotateTo, scaleTo, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
        Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
        m_pFront->runAction(sequnce);
    }
    if(m_pTop)
    {
        m_bTouchEnable = false;
        EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(180, 0, 0)));
        MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, m_pTop->getRadius()*20+2, 0));
        ScaleTo* scaleTo = ScaleTo::create(1.0f, 0.0f);
        Spawn* spawn = Spawn::create(moveTo, rotateTo, scaleTo, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
        Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
        m_pTop->runAction(sequnce);
    }
    if(m_pRight)
    {
        m_bTouchEnable = false;
        EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(0, 0, 180)));
        MoveTo* moveTo = MoveTo::create(1.0f, Vec3(m_pRight->getRadius()*140, m_pRight->getRadius()*140+2, 0));
        ScaleTo* scaleTo = ScaleTo::create(1.0f, 0.0f);
        Spawn* spawn = Spawn::create(moveTo, rotateTo, scaleTo, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
        Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
        m_pRight->runAction(sequnce);
    }
    if(m_pBack)
    {
        m_bTouchEnable = false;
        EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(-180, 0, 0)));
        MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, m_pBack->getRadius()*10+2, -m_pBack->getRadius()*10));
        ScaleTo* scaleTo = ScaleTo::create(1.0f, 0.0f);
        Spawn* spawn = Spawn::create(moveTo, rotateTo, scaleTo, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
        Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
        m_pBack->runAction(sequnce);
    }
    if(m_pLeft)
    {
        m_bTouchEnable = false;
        EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(0, 0, -180)));
        MoveTo* moveTo = MoveTo::create(1.0f, Vec3(-m_pRight->getRadius()*140, m_pRight->getRadius()*140+2, 0));
        ScaleTo* scaleTo = ScaleTo::create(1.0f, 0.0f);
        Spawn* spawn = Spawn::create(moveTo, rotateTo, scaleTo, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
        Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
        m_pLeft->runAction(sequnce);
    }
    
    if(m_pDown)
    {
        m_bTouchEnable = false;
        EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(1.0f, Vec3(-180, 0, 0)));
        MoveTo* moveTo = MoveTo::create(1.0f, Vec3(0, -m_pDown->getRadius()*10+2, 0));
        ScaleTo* scaleTo = ScaleTo::create(1.0f, 0.0f);
        Spawn* spawn = Spawn::create(moveTo, rotateTo, scaleTo, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
        Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
        m_pDown->runAction(sequnce);
    }

}