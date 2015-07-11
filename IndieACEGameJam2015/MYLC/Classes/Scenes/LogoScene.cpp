//
//  LogoScene.cpp
//  MYLC
//
//  Created by wang haibo on 15/7/10.
//
//

#include "LogoScene.h"
#include "GroundLayer.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* LogoScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LogoScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
LogoScene::LogoScene()
{
    tinyFlareSprite= nullptr;
    gamejamMarkSprite= nullptr;
    dateMarkSprite= nullptr;
    
    rowOne= nullptr;
    rowTwo= nullptr;
    colOne= nullptr;
    colTwo= nullptr;
    callbackIndex =0;
}
// on "init" you need to initialize your instance
bool LogoScene::init()
{

    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    size = Director::getInstance()->getVisibleSize();
    float scale = size.width / 960.0f;
    
    auto bgLayerColor =   LayerColor::create(Color4B::WHITE,size.width,size.height);
    addChild(bgLayerColor);
    
    
    rowOne  = LayerColor::create(Color4B::BLACK, size.width ,50);
    rowTwo  = LayerColor::create(Color4B::BLACK, size.width ,50);
    colOne  = LayerColor::create(Color4B::BLACK,50,size.height);
    colTwo = LayerColor::create(Color4B::BLACK,50,size.height);
    
    rowOne->setPosition(-size.height,size.height*0.7);
    rowTwo->setPosition(size.width,size.height*0.3);
    colOne->setPosition(size.width*0.3 ,-size.height);
    colTwo->setPosition(size.width * 0.6,size.height);


    rowOne->setScale(scale);
    rowTwo->setScale(scale);
    colOne->setScale(scale);
    colTwo->setScale(scale);
    
    addChild(rowOne);
    addChild(rowTwo);
    addChild(colOne);
    addChild(colTwo);
    
    tinyFlareSprite = Sprite::create("tinyflare.png");
    tinyFlareSprite->setPosition(size.width/2,size.height/2+50);
    addChild(tinyFlareSprite);
    tinyFlareSprite->setOpacity(0);
    
    gamejamMarkSprite = Sprite::create("indiace.png");
    gamejamMarkSprite->setPosition(size.width/2,size.height/2-tinyFlareSprite->getContentSize().height*0.5 );
    gamejamMarkSprite->setScale(scale);
    gamejamMarkSprite->setOpacity(0);
    addChild(gamejamMarkSprite);
    
    
    dateMarkSprite = Sprite::create("2015.png");
    dateMarkSprite->setPosition(size.width/2,size.height/2);
    dateMarkSprite->setScale(scale);
    dateMarkSprite->setOpacity(0);
    addChild(dateMarkSprite);
    
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LogoScene::rowOneEnd, this));
    auto rowOneMoveAction = MoveTo::create(0.4, Vec2(0,size.height*0.7));
    rowOne->runAction(Sequence::create(rowOneMoveAction,callFunc, NULL));
    
    return true;
}

void LogoScene::rowOneEnd()
{
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LogoScene::rowTwoEnd, this));
    auto rowTwoMoveAction = MoveTo::create(0.4, Vec2(0,size.height*0.3));
    if (rowTwo) {
        rowTwo->runAction(Sequence::create(rowTwoMoveAction,callFunc, NULL));
    }
    
}
void LogoScene::rowTwoEnd()
{

    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LogoScene::colOneEnd, this));
    auto colOneMoveAction = MoveTo::create(0.4, Vec2(size.width*0.3,0));
    if (colOne) {
        colOne->runAction(Sequence::create(colOneMoveAction,callFunc, NULL));
    }
}

void LogoScene::colOneEnd()
{
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LogoScene::colTwoEnd, this));
    auto colTwoMoveAction = MoveTo::create(0.4, Vec2(size.width * 0.6,0));
    if (colTwo) {
         colTwo->runAction(Sequence::create(colTwoMoveAction,callFunc, NULL));
    }
   
}
void LogoScene::colTwoEnd()
{
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LogoScene::precache, this));

    
   auto rowOneMoveAction = MoveTo::create(0.6, Vec2(0,size.height-50));
   auto rowTwoMoveAction = MoveTo::create(0.6, Vec2(0,0));
   auto colOneMoveAction = MoveTo::create(0.6, Vec2(0,0));
   auto colTwoMoveAction = MoveTo::create(0.6, Vec2(size.width-50 ,0));

    if (rowOne && rowTwo && colOne && colTwo) {
        rowOne->runAction(Sequence::create(rowOneMoveAction,callFunc, NULL));
        rowTwo->runAction(Sequence::create(rowTwoMoveAction,callFunc, NULL));
        colOne->runAction(Sequence::create(colOneMoveAction,callFunc, NULL));
        colTwo->runAction(Sequence::create(colTwoMoveAction,callFunc, NULL));
    }
   
    
}


void LogoScene::precache()
{
    callbackIndex++;
    if (callbackIndex==4)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("life.mp3");
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LogoScene::endcache, this));
        auto tinyFlareFadeInAction = FadeIn::create(2);
        auto tinyFlareMoveAction = MoveBy::create(0.5, Vec2(0, 50));
        if (tinyFlareSprite) {
            tinyFlareSprite->runAction(Sequence::create(tinyFlareFadeInAction,tinyFlareMoveAction,callFunc,NULL));

        }
          callbackIndex = 0;
    }
    
}
void LogoScene::endcache()
{
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LogoScene::logoActon, this));
    auto gamejamFadeInAction = FadeIn::create(2);
    auto gamejamMoveAction = MoveBy::create(0.5, Vec2(0,-50));
    if (gamejamMarkSprite) {
        gamejamMarkSprite->runAction(Sequence::create(gamejamFadeInAction,gamejamMoveAction,callFunc, NULL));
    }
    
    
}

void LogoScene::logoActon()
{
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(LogoScene::nextScene, this));
    auto dateMarkFadeInAction = FadeIn::create(2);
    if (dateMarkSprite) {
         dateMarkSprite->runAction(Sequence::create(dateMarkFadeInAction,callFunc, NULL));
    }
   
}

void LogoScene::nextScene()
{
    auto scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(scene);
}