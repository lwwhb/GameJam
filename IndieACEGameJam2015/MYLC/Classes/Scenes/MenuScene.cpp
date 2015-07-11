//
//  MenuScene.cpp
//  MYLC
//
//  Created by wang haibo on 15/7/10.
//
//

#include "MenuScene.h"
#include "LevelSelectScene.h"
USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
MenuScene::MenuScene()
{
    m_pMainCamera = nullptr;
    makeyourSprite = nullptr;
    colorfulSprite =nullptr;
    lifeSprite = nullptr;
    logoSprite = nullptr;
    isTouchState =false;
}
// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    m_nCurrentLevel = UserDefault::getInstance()->getIntegerForKey("CurrentLevel", 1);
    if(m_nCurrentLevel > 6)
    {
        m_nCurrentLevel = 1;
        UserDefault::getInstance()->setIntegerForKey("CurrentLevel", m_nCurrentLevel);
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
    
    size = Director::getInstance()->getVisibleSize();
    
    logoSprite = Sprite::create();
    logoSprite->setContentSize(size);
    logoSprite->setPosition(size.width/2,size.height/2);
    logoSprite->setAnchorPoint(Vec2(0.5, 0.5));
    addChild(logoSprite);
    
    makeyourSprite  = Sprite::create("makeyourim.png");
    makeyourSprite->setScale(0),
    makeyourSprite->setPosition(size.width/2,size.height*0.7);
    logoSprite->addChild(makeyourSprite);
    
    
    lifeSprite  = Sprite::create("life.png");
    lifeSprite->setScale(0.8);
    lifeSprite->setPosition(size.width/2,size.height*0.7 -70);
    lifeSprite->setOpacity(0);
    logoSprite->addChild(lifeSprite);
    
    
    colorfulSprite  = Sprite::create("colorful.png");
    colorfulSprite->setPosition(size.width/2+30,size.height*0.7-70);
    colorfulSprite->setScale(0.7);
    colorfulSprite->setOpacity(0);
    logoSprite->addChild(colorfulSprite);
    

    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MenuScene::makeyourEnd, this));
    auto  makeyouSeqAction = Sequence::create(Spawn::create(ScaleTo::create(0.6, 0.1),RotateBy::create(0.6, 120),NULL), Spawn::create(ScaleTo::create(0.6, 0.3),RotateBy::create(0.6, 240),NULL),
        Spawn::create(ScaleTo::create(0.6, 0.5),RotateBy::create(0.6, 360),NULL),
        Spawn::create(ScaleTo::create(0.6, 0.7),RotateBy::create(0.6, 240),NULL),
        Spawn::create(ScaleTo::create(0.6, 0.9),RotateBy::create(0.6, 120),NULL),
        Spawn::create(ScaleTo::create(0.6, 1),RotateBy::create(0.6, 0),NULL),callFunc, NULL);
    makeyourSprite->runAction(makeyouSeqAction);
    
    

    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MenuScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}
bool MenuScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    if (!isTouchState) {
        return false;
    }else{
        Director::getInstance()->replaceScene(LevelSelectScene::createScene());
    }
    
    
    return true;
}

void MenuScene::makeyourEnd()
{
     CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MenuScene::LifeEnd, this));
    auto lifeFadeAction = FadeIn::create(2);
    auto lifeMoveAction = MoveBy::create(0.4, Vec2(-150, 0));
    if (lifeSprite) {
        lifeSprite->runAction(Sequence::create(lifeFadeAction,lifeMoveAction,callFunc, NULL));
    }
    
}
void MenuScene::LifeEnd()
{
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MenuScene::colorfulEnd, this));
    auto colorfulFadeAction = FadeIn::create(2);
    auto colorfulMoveAction = MoveBy::create(0.4, Vec2(50, 0));
    if (colorfulSprite) {
        colorfulSprite->runAction(Sequence::create(colorfulFadeAction,colorfulMoveAction,callFunc, NULL));
    }
}
void MenuScene::colorfulEnd()
{
    auto logoScaleAction1 = ScaleTo::create(0.9, 1.0);
    auto logoScaleAction2 = ScaleTo::create(0.9, 0.9);
    
    if (logoSprite) {
        logoSprite->runAction(RepeatForever::create(Sequence::create(logoScaleAction1,logoScaleAction2, NULL)));
    }
    
//    auto touchLabel = Label::createWithTTF("请触摸开始游戏", "FZXIANGSU12.TTF", 20);
//    touchLabel->setPosition(size.width/2,100);
//    this->addChild(touchLabel);
//    auto touchFadeToaAction = FadeTo::create(0.7,10);
//    touchLabel->runAction(RepeatForever::create(Sequence::create(touchFadeToaAction,FadeIn::create(2), NULL)));
    
    isTouchState = true;
}