//
//  FinalScene.cpp
//  MYLC
//
//  Created by wang haibo on 15/7/12.
//
//

#include "FinalScene.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "TextDisplayer.h"
USING_NS_CC;
using namespace CocosDenshion;

Scene* FinalScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = FinalScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
FinalScene::FinalScene()
{
    m_pMainCamera       = nullptr;
    m_pWhiteLayer       = nullptr;
    
    m_pCloud1           = nullptr;
    m_pCloud2           = nullptr;
    
    m_pTree1            = nullptr;
    m_pTree2            = nullptr;
    m_pTree3            = nullptr;
    
    m_pFlower1          = nullptr;
    m_pFlower2          = nullptr;
    m_pFlower3          = nullptr;
    m_pFlower4          = nullptr;
    
    m_pBoy              = nullptr;
    m_pGirl             = nullptr;
    
    m_pSun = nullptr;
    
    m_pHeart    = nullptr;
}
// on "init" you need to initialize your instance
bool FinalScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::getInstance()->playBackgroundMusic("Horizon.mp3",true);
    
    auto la = Label::createWithTTF("", "FZXIANGSU12.TTF", 24);
    la->setString("");
    auto bill = BillBoard::create();
    bill->addChild(la);
    addChild(bill);
    bill->setPosition(570, 300);
    bill->setCameraMask((unsigned short)CameraFlag::USER1);
    
    std::vector<std::string> texts;
    
    texts.clear();
    texts.push_back("“你好……”");
    texts.push_back("“你好……你知道嘛，我发现了一个世界呢”");
    texts.push_back("“真的么？我也是”");
    texts.push_back("也许从这一刻开始");
    texts.push_back("两个世界才真正获得了色彩");
    texts.push_back("两个世界交织在一起");
    texts.push_back("变成了一个色彩斑斓的新世界");
    texts.push_back("男孩和女孩都没有再说话");
    texts.push_back("此刻两个人心里想的是");
    texts.push_back("“终于找到了”");
    
    
    
    auto text = TextDisplayer::create();
    addChild(text);
    text->setLabel(la);
    
    text->setTextToDisplay(texts);
    text->startTyping();
    
    auto size = Director::getInstance()->getVisibleSize();
    auto bgLayerColor =   LayerColor::create(Color4B(153, 204, 255, 255),size.width,size.height);
    addChild(bgLayerColor);
    
    m_pSun = EffectSprite3D::create("sun.obj", "IndexColor.png");
    if(!m_pSun)
        return false;
    addChild(m_pSun);
    m_pSun->setCameraMask((unsigned short)CameraFlag::USER1);
    
    m_pSun->setPosition(size.width*0.8f, size.height*0.8f);
    m_pSun->setScale(5);
    m_pSun->setRotation3D(Vec3(90,0,0));
    
    EaseSineIn* rotateBy1 = EaseSineIn::create(RotateBy::create(1.0f, Vec3(2,-2,0)));
    EaseSineOut* rotateBy2 = EaseSineOut::create(RotateBy::create(1.0f, Vec3(-2,2,-0)));
    
    EaseSineIn* rotateBy3 = EaseSineIn::create((RotateBy::create(1.0f, Vec3(2,2,-0))));
    EaseSineOut* rotateBy4 = EaseSineOut::create(RotateBy::create(1.0f, Vec3(-2,-2,0)));
    
    EaseSineIn* rotateBy5 = EaseSineIn::create(RotateBy::create(1.0f, Vec3(-2,2,0)));
    EaseSineOut* rotateBy6 = EaseSineOut::create(RotateBy::create(1.0f, Vec3(2,-2,-0)));
    
    Sequence* sequence = Sequence::create(rotateBy1, rotateBy6, rotateBy3, rotateBy4, rotateBy5, rotateBy2, NULL);
    RepeatForever* repeat = RepeatForever::create(sequence);
    m_pSun->runAction(repeat);
    
    
    m_pCloud1 = EffectSprite3D::create("cloud.obj", "IndexColor.png");
    if(!m_pCloud1)
        return false;
    addChild(m_pCloud1);
    m_pCloud1->setCameraMask((unsigned short)CameraFlag::USER1);
    
    m_pCloud1->setPosition(size.width*0.5f, size.height*0.7f);
    m_pCloud1->setScale(8);
    m_pCloud1->setRotation3D(Vec3(90,0,0));
    
    MoveTo* moveTo = MoveTo::create(15.0f, Vec2(size.width*0.6f, size.height*0.7f));
    FadeOut* fadeOut = FadeOut::create(1.0);
    MoveTo* moveTo2 = MoveTo::create(0.2f, Vec2(size.width*0.5f, size.height*0.7f));
    FadeIn* fadeIn = FadeIn::create(1.0f);
    sequence = Sequence::create(moveTo, fadeOut, moveTo2, fadeIn, NULL);
    repeat = RepeatForever::create(sequence);
    m_pCloud1->runAction(repeat);
    
    
    m_pCloud2 = EffectSprite3D::create("cloud.obj", "IndexColor.png");
    if(!m_pCloud2)
        return false;
    addChild(m_pCloud2);
    m_pCloud2->setCameraMask((unsigned short)CameraFlag::USER1);
    
    m_pCloud2->setPosition(size.width*0.2f, size.height*0.8f);
    m_pCloud2->setScale(5);
    m_pCloud2->setRotation3D(Vec3(90,0,0));
    
    moveTo = MoveTo::create(23.0f, Vec2(size.width*0.5f, size.height*0.8f));
    fadeOut = FadeOut::create(1.0);
    moveTo2 = MoveTo::create(0.2f, Vec2(size.width*0.2f, size.height*0.8f));
    fadeIn = FadeIn::create(1.0f);
    sequence = Sequence::create(moveTo, fadeOut, moveTo2, fadeIn, NULL);
    repeat = RepeatForever::create(sequence);
    m_pCloud2->runAction(repeat);
    
    
    m_pHouse = EffectSprite3D::create("house.obj", "IndexColor.png");
    if(!m_pHouse)
        return false;
    addChild(m_pHouse);
    m_pHouse->setCameraMask((unsigned short)CameraFlag::USER1);
    
    m_pHouse->setPosition3D(Vec3(size.width*0.2f, size.height*0.35f, 2));
    m_pHouse->setScale(10);
    m_pHouse->setRotation3D(Vec3(90,0,0));

    
    m_pTree1 = EffectSprite3D::create("tree.obj", "IndexColor.png");
    if(!m_pTree1)
        return false;
    addChild(m_pTree1);
    m_pTree1->setCameraMask((unsigned short)CameraFlag::USER1);
    
    m_pTree1->setPosition3D(Vec3(size.width*0.8f, size.height*0.315f, 8));
    m_pTree1->setScale(8);
    m_pTree1->setRotation3D(Vec3(90,0,0));
    
    sequence = Sequence::create(rotateBy3, rotateBy4, rotateBy1, rotateBy6, rotateBy5, rotateBy2, NULL);
    repeat = RepeatForever::create(sequence);
    m_pTree1->runAction(repeat);
    
    m_pTree2 = EffectSprite3D::create("tree.obj", "IndexColor.png");
    if(!m_pTree2)
        return false;
    addChild(m_pTree2);
    m_pTree2->setCameraMask((unsigned short)CameraFlag::USER1);
    
    m_pTree2->setPosition3D(Vec3(size.width*0.7f, size.height*0.3f, 2));
    m_pTree2->setScale(7);
    m_pTree2->setRotation3D(Vec3(90,0,0));
    
    
    sequence = Sequence::create(rotateBy3, rotateBy4, rotateBy1, rotateBy6, rotateBy5, rotateBy2, NULL);
    repeat = RepeatForever::create(sequence);
    m_pTree2->runAction(repeat);
    
    
    m_pTree3 = EffectSprite3D::create("tree.obj", "IndexColor.png");
    if(!m_pTree2)
        return false;
    addChild(m_pTree3);
    m_pTree3->setCameraMask((unsigned short)CameraFlag::USER1);
    
    m_pTree3->setPosition3D(Vec3(size.width*0.45f, size.height*0.3f, 2));
    m_pTree3->setScale(7);
    m_pTree3->setRotation3D(Vec3(90,0,0));
    
    
    sequence = Sequence::create(rotateBy3, rotateBy4, rotateBy5, rotateBy2, rotateBy1, rotateBy6, NULL);
    repeat = RepeatForever::create(sequence);
    m_pTree3->runAction(repeat);
    
    
    m_pFlower1 = EffectSprite3D::create("flower.obj", "IndexColor.png");
    if(!m_pFlower1)
        return false;
    addChild(m_pFlower1);
    m_pFlower1->setCameraMask((unsigned short)CameraFlag::USER1);
    
    m_pFlower1->setPosition3D(Vec3(size.width*0.5f, size.height*0.21f, 2));
    m_pFlower1->setScale(2);
    m_pFlower1->setRotation3D(Vec3(90,0,0));
    
    
    sequence = Sequence::create(rotateBy3, rotateBy4, rotateBy5, rotateBy2, rotateBy1, rotateBy6, NULL);
    repeat = RepeatForever::create(sequence);
    m_pFlower1->runAction(repeat);
    
    
    m_pFlower2 = EffectSprite3D::create("flower.obj", "IndexColor.png");
    if(!m_pFlower2)
        return false;
    addChild(m_pFlower2);
    m_pFlower2->setCameraMask((unsigned short)CameraFlag::USER1);
    
    m_pFlower2->setPosition3D(Vec3(size.width*0.6f, size.height*0.21f, 2));
    m_pFlower2->setScale(2);
    m_pFlower2->setRotation3D(Vec3(90,0,0));
    
    
    sequence = Sequence::create(rotateBy3, rotateBy4, rotateBy5, rotateBy2, rotateBy1, rotateBy6, NULL);
    repeat = RepeatForever::create(sequence);
    m_pFlower2->runAction(repeat);
    
    m_pFlower3 = EffectSprite3D::create("flower.obj", "IndexColor.png");
    if(!m_pFlower3)
        return false;
    addChild(m_pFlower3);
    m_pFlower3->setCameraMask((unsigned short)CameraFlag::USER1);
    
    m_pFlower3->setPosition3D(Vec3(size.width*0.3f, size.height*0.21f, 2));
    m_pFlower3->setScale(2);
    m_pFlower3->setRotation3D(Vec3(90,0,0));
    
    m_pFlower4 = EffectSprite3D::create("flower.obj", "IndexColor.png");
    if(!m_pFlower4)
        return false;
    addChild(m_pFlower4);
    m_pFlower4->setCameraMask((unsigned short)CameraFlag::USER1);
    
    m_pFlower4->setPosition3D(Vec3(size.width*0.9f, size.height*0.21f, 2));
    m_pFlower4->setScale(2);
    m_pFlower4->setRotation3D(Vec3(90,0,0));
    
    
    sequence = Sequence::create(rotateBy3, rotateBy4, rotateBy5, rotateBy2, rotateBy1, rotateBy6, NULL);
    repeat = RepeatForever::create(sequence);
    m_pFlower2->runAction(repeat);
    
    
    m_pBoy = EffectSprite3D::create("bboy.obj", "IndexColor.png");
    if(!m_pBoy)
        return false;
    addChild(m_pBoy);
    m_pBoy->setCameraMask((unsigned short)CameraFlag::USER1);
    
    m_pBoy->setPosition3D(Vec3(size.width*0.56f, size.height*0.15f, 8));
    m_pBoy->setScale(3);
    
    m_pGirl = EffectSprite3D::create("girl.obj", "IndexColor.png");
    if(!m_pGirl)
        return false;
    addChild(m_pGirl);
    m_pGirl->setCameraMask((unsigned short)CameraFlag::USER1);
    
    m_pGirl->setPosition3D(Vec3(size.width*0.62f, size.height*0.15f, 8));
    m_pGirl->setScale(3);
    
    m_pHeart = EffectSprite3D::create("heart.obj", "IndexColor.png");
    if(!m_pHeart)
        return false;
    addChild(m_pHeart);
    m_pHeart->setCameraMask((unsigned short)CameraFlag::USER1);
    
    m_pHeart->setPosition3D(Vec3(size.width*0.59f, size.height*0.33f, 8));
    m_pHeart->setScale(1.5);
    m_pHeart->setOpacity(0);
    m_pHeart->setRotation3D(Vec3(90,0,0));
    
    moveTo = MoveTo::create(2, Vec2(size.width*0.59f, size.height*0.37f));
    moveTo2 = MoveTo::create(0.2f, Vec2(size.width*0.59f, size.height*0.33f));
    fadeIn = FadeIn::create(0.2f);
    DelayTime* delay = DelayTime::create(1.8f);
    fadeOut = FadeOut::create(0.2f);
    sequence = Sequence::create(fadeIn, delay, fadeOut, NULL);
    Sequence* sequence2 = Sequence::createWithTwoActions(moveTo, moveTo2);
    Spawn* spawn = Spawn::create(sequence, sequence2, NULL);
    repeat = RepeatForever::create(spawn);
    m_pHeart->runAction(repeat);
    
    
    m_pMainCamera = Camera::create();
    if(!m_pMainCamera)
        return false;
    addChild(m_pMainCamera);
    m_pMainCamera->setCameraFlag(CameraFlag::USER1);
    
    AmbientLight* ambLight = AmbientLight::create(Color3B(200, 200, 200));
    if(!ambLight)
        return false;
    addChild(ambLight);
    DirectionLight* directionLight = DirectionLight::create(Vec3(-3, -4, -5), Color3B(128, 128, 128));
    if(!directionLight)
        return false;
    addChild(directionLight);
    
    m_pWhiteLayer = LayerColor::create(Color4B::WHITE);
    if(!m_pWhiteLayer)
        return false;
    addChild(m_pWhiteLayer);
    m_pWhiteLayer->setCameraMask((unsigned short)CameraFlag::USER1);
    
    EaseExponentialIn* fadeOut1 = EaseExponentialIn::create(FadeOut::create(1.0f));
    m_pWhiteLayer->runAction(fadeOut1);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(FinalScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}
bool FinalScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    //Director::getInstance()->replaceScene(MenuScene::createScene());
    return true;
}
