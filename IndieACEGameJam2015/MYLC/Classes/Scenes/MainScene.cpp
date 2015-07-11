//
//  MainScene.cpp
//  MYLC
//
//  Created by wang haibo on 15/7/10.
//
//

#include "MainScene.h"
#include "GroundLayer.h"
#include "GameScene.h"
USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
MainScene::MainScene()
{


}
// on "init" you need to initialize your instance
bool MainScene::init()
{

    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width / 960.0f;
    
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
    
    
    return true;
}
void MainScene::precache()
{
    
}
void MainScene::endcache()
{
    
}