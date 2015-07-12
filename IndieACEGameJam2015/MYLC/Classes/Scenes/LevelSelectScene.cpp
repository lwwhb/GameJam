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
#include "SimpleAudioEngine.h"
#include <vector>
#include "FinalScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* LevelSelectScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LevelSelectScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);

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
    //UserDefault::getInstance()->setIntegerForKey("CurrentLevel", 1);
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
    
    //lixu add boy
    boy = Boy::create(m_nCurrentLevel);
    addChild(boy);
    boy->setPosition3D(Vec3(-90,-100,-120));
    boy->setCameraMask((unsigned short)CameraFlag::USER1);
    

    
    
    auto la = Label::createWithTTF("", "FZXIANGSU12.TTF", 24);
    la->setString("");
    auto bill = BillBoard::create();
    bill->addChild(la);
    addChild(bill);
    bill->setPosition(300, 300);
    std::vector<std::string> texts;

    switch (m_nCurrentLevel) {
        case 1:
            texts.clear();
            texts.push_back("……………………");
            texts.push_back("…………我…………");
            texts.push_back("“我”诞生了");
            texts.push_back("……周围……是世界？");
            texts.push_back("“世界”诞生了");
            texts.push_back("前面是什么？");
            texts.push_back("我该做点什么？");
            texts.push_back("也许我该到那里去？");
            break;
        case 2:
            texts.clear();
            texts.push_back("……………………");
            texts.push_back("温暖的感觉");
            texts.push_back("“世界”也变化了");
            texts.push_back("这些……是“色彩”");
            texts.push_back("“我”……“世界……“色彩”");
            texts.push_back("也许这就是我该做的");
            texts.push_back("也许我该再到那里去");
            texts.push_back("会有新的“色彩”么？");
            break;

        case 3:
            texts.clear();
            texts.push_back("……………………");
            texts.push_back("我找到了新的”色彩“");
            texts.push_back("我感到……平静……");
            texts.push_back("…………我明白了…………");
            texts.push_back("“世界”诞生了");
            texts.push_back("“我”诞生了");
            texts.push_back("“世界”和“我”都需要“色彩”");
            texts.push_back("“我”要给“世界”找到“色彩“");
            texts.push_back("我要再到那里去");

            break;
        case 4:
            texts.clear();
            texts.push_back("哈哈哈");
            texts.push_back("果然，果然");
            texts.push_back("新的“色彩”！");
            texts.push_back("“我”活了");
            texts.push_back("“世界”活了");
            texts.push_back("活着真好");
            texts.push_back("到那里去，到那里去");
            texts.push_back("寻找，寻找色彩");
            break;
        case 5:
            texts.clear();
            texts.push_back("我又找到了一些");
            texts.push_back("很美");
            texts.push_back("…………很美…………");
            texts.push_back("然而为什么");
            texts.push_back("为什么我却感觉失落");
            texts.push_back("为什么？");
            texts.push_back("“我”拥有“世界”");
            texts.push_back("“世界”有了“色彩”");
            texts.push_back("一定还有什么，我没找到的");
            texts.push_back("我要再去那里寻找");
            texts.push_back("寻找，直到找到为止");
            break;
        case 6:
            texts.clear();
            texts.push_back("够了");
            texts.push_back("我累了");
            texts.push_back("“我”很好");
            texts.push_back("“我”很好");
            texts.push_back("我为什么还要去那儿");
            texts.push_back("一次又一次");
            texts.push_back("找到了“色彩”");
            texts.push_back("改变了“世界”");
            texts.push_back("为什么？");
            texts.push_back("“我”还是“我”");
            texts.push_back("“世界”还是“世界”");
            texts.push_back("还要再去那里吧");
            texts.push_back("还能去哪儿呢");
            break;
        case 7:
            texts.clear();
            texts.push_back("啊………………");
            texts.push_back("发生了了什么？");
            texts.push_back("另一个……“我”？");
            texts.push_back("不，是……“她”？");
            
        default:
            texts.clear();
            texts.push_back("啊………………");
            texts.push_back("发生了什么？");
            texts.push_back("虽然只是一瞬间");
            texts.push_back("但是“世界”除了表面");
            texts.push_back("似乎还有别的什么");
            texts.push_back("让我来看一看");
            break;
    }
    

    
    text = TextDisplayer::create();
    addChild(text);
    text->setLabel(la);

    text->setTextToDisplay(texts);
    text->startTyping();
    
    
    //+lixu
    
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
    boy->setRotation3D(Vec3(-10, 10, 5));
    
    EaseSineIn* rotateBy1 = EaseSineIn::create(RotateBy::create(1.0f, Vec3(2,-2,2)));
    EaseSineOut* rotateBy2 = EaseSineOut::create(RotateBy::create(1.0f, Vec3(-2,2,-2)));
    
    EaseSineIn* rotateBy3 = EaseSineIn::create((RotateBy::create(1.0f, Vec3(2,2,-2))));
    EaseSineOut* rotateBy4 = EaseSineOut::create(RotateBy::create(1.0f, Vec3(-2,-2,2)));
    
    EaseSineIn* rotateBy5 = EaseSineIn::create(RotateBy::create(1.0f, Vec3(-2,2,2)));
    EaseSineOut* rotateBy6 = EaseSineOut::create(RotateBy::create(1.0f, Vec3(2,-2,-2)));
    
    Sequence* sequence1 = Sequence::create(rotateBy1, rotateBy6, rotateBy3, rotateBy4, rotateBy5, rotateBy2, nullptr);
    RepeatForever* repeat = RepeatForever::create(sequence1);
    
    m_pCube->runAction(repeat);

    boy->runAction(repeat);



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
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(0, m_pFront->getRadius()*2+2, m_pFront->getRadius()*2));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pFront->runAction(sequnce);
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("stoneroll.wav");
                }
            }
            break;
        case 3:
            {
                if(m_pFront)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(0, m_pFront->getRadius()*2+2, m_pFront->getRadius()*2));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pFront->runAction(sequnce);
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("stoneroll.wav");
                }
                if(m_pTop)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(0, m_pTop->getRadius()*4+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pTop->runAction(sequnce);
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("stoneroll.wav");
                }
            }
            break;
        case 4:
            {
                if(m_pFront)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(0, m_pFront->getRadius()*2+2, m_pFront->getRadius()*2));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pFront->runAction(sequnce);
                }
                if(m_pTop)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(0, m_pTop->getRadius()*4+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pTop->runAction(sequnce);
                }
                if(m_pRight)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(0, 0, 180)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(m_pRight->getRadius()*24, m_pRight->getRadius()*24+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pRight->runAction(sequnce);
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("stoneroll.wav");
                }
            }
            break;
        case 5:
            {
                if(m_pFront)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(0, m_pFront->getRadius()*2+2, m_pFront->getRadius()*2));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pFront->runAction(sequnce);
                }
                if(m_pTop)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(0, m_pTop->getRadius()*4+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pTop->runAction(sequnce);
                }
                if(m_pRight)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(0, 0, 180)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(m_pRight->getRadius()*24, m_pRight->getRadius()*24+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pRight->runAction(sequnce);
                }
                if(m_pBack)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(-180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(0, m_pBack->getRadius()*2+2, -m_pBack->getRadius()*2));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pBack->runAction(sequnce);
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("stoneroll.wav");
                }
            }
            break;
        case 6:
            {
                if(m_pFront)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(0, m_pFront->getRadius()*2+2, m_pFront->getRadius()*2));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pFront->runAction(sequnce);
                }
                if(m_pTop)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(0, m_pTop->getRadius()*4+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pTop->runAction(sequnce);
                }
                if(m_pRight)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(0, 0, 180)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(m_pRight->getRadius()*24, m_pRight->getRadius()*24+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pRight->runAction(sequnce);
                }
                if(m_pBack)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(-180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(0, m_pBack->getRadius()*2+2, -m_pBack->getRadius()*2));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pBack->runAction(sequnce);
                }
                if(m_pLeft)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(0, 0, -180)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(-m_pRight->getRadius()*24, m_pRight->getRadius()*24+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pLeft->runAction(sequnce);
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("stoneroll.wav");
                }
            }
            break;
        default:
            {
                if(m_pFront)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(0, m_pFront->getRadius()*2+2, m_pFront->getRadius()*2));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pFront->runAction(sequnce);
                }
                if(m_pTop)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(0, m_pTop->getRadius()*4+2, 0));
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
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(-180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(0, m_pBack->getRadius()*2+2, -m_pBack->getRadius()*2));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pBack->runAction(sequnce);
                }
                if(m_pLeft)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(0, 0, -180)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(-m_pRight->getRadius()*24, m_pRight->getRadius()*24+2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pLeft->runAction(sequnce);
                }
                
                if(m_pDown)
                {
                    m_bTouchEnable = false;
                    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(2.0f, Vec3(-180, 0, 0)));
                    MoveTo* moveTo = MoveTo::create(2.0f, Vec3(0, 2, 0));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, rotateTo);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::enableTouch, this));
                    Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
                    m_pDown->runAction(sequnce);
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("stoneroll.wav");
                }

            }
            break;
    }
}
void LevelSelectScene::beginGame()
{
    if(m_nCurrentLevel < 7)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("stoneroll.wav");
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
    
    auto girl = EffectSprite3D::create("girl.obj", "IndexColor.png");
    if (!girl) {
        return;
    }
    addChild(girl);
    girl->setCameraMask((unsigned short)CameraFlag::USER1);
    girl->setPosition3D(Vec3(30,0,0));
    girl->setScale(0.4f);
    
    std::vector<std::string> texts;
    texts.push_back("哇…………");
    texts.push_back("这是……");
    texts.push_back("另一个……“我”？");
    texts.push_back("不，是……“她”？");
    texts.push_back("熟悉而亲切的感觉");
    texts.push_back("似乎是很久以前……");
    texts.push_back("先……打个招呼吧");
    text->setTextToDisplay(texts);
    text->startTyping();
    CallFunc* finalCall = CallFunc::create(CC_CALLBACK_0(LevelSelectScene::gotoFinal, this));
    DelayTime* delay = DelayTime::create(20.0f);
    Sequence* changeScene = Sequence::createWithTwoActions(delay, finalCall);
    this->runAction(changeScene);

}

void LevelSelectScene::gotoFinal()
{
    auto scene = FinalScene::createScene();
    Director::getInstance()->replaceScene(scene);
}