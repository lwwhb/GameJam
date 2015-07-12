//
//  MenuScene.cpp
//  MYLC
//
//  Created by wang haibo on 15/7/10.
//
//

#include "MenuScene.h"
#include "LevelSelectScene.h"
#include "SimpleAudioEngine.h"
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
    makeyourlifeSprite = nullptr;
    colorfulSprite =nullptr;
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
    
    
    makeyourlifeSprite  = Sprite::create("makeyourlife.png");
    makeyourlifeSprite->setPosition(size.width/2-100,size.height);
    makeyourlifeSprite->setScale(1.2);
    this->addChild(makeyourlifeSprite);
    
    
    colorfulSprite  = Sprite::create("colorful.png");
    colorfulSprite->setPosition(size.width+colorfulSprite->getContentSize().width,size.height*0.7-100);
    colorfulSprite->setScale(1.6);
    this->addChild(colorfulSprite);
    
    
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MenuScene::makeyourEnd, this));
   
    makeyourlifeSprite->runAction(Sequence::create(MoveTo::create(0.5, Vec2(size.width/2-100,size.height*0.7)),JumpBy::create(0.3,Point::ZERO, 30, 1), callFunc,NULL));
    
    
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
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("start.mp3");
        Director::getInstance()->replaceScene(LevelSelectScene::createScene());
    }
    
    
    return true;
}

void MenuScene::makeyourEnd()
{
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MenuScene::colorfulEnd, this));
     colorfulSprite->runAction(Sequence::create(MoveTo::create(0.7, Vec2(size.width/2+100,size.height*0.7-100)), callFunc,NULL));
    
}

void MenuScene::colorfulEnd()
{
    
    auto touchLabel = Label::createWithTTF("请点击开始游戏", "FZXIANGSU12.TTF", 20);
    touchLabel->setPosition(size.width/2,100);
    this->addChild(touchLabel);
    auto touchFadeToaAction = FadeTo::create(0.7,10);
    touchLabel->runAction(RepeatForever::create(Sequence::create(touchFadeToaAction,FadeIn::create(2), NULL)));
    
    isTouchState = true;
}