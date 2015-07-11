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
#include "TextDisplayer.h"
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
    
    //lixu add boy
    m_boy = Boy::create(m_nCurrentLevel);
    addChild(m_boy);
    m_boy->setPosition3D(Vec3(110,-50,-20));
    m_boy->setCameraMask((unsigned short)CameraFlag::USER1);
    m_boy->setRotation3D(Vec3(-90,180,-35));
    
    auto la = Label::createWithTTF("", "FZXIANGSU12.TTF", 24);
    la->setString("");
    auto bill = BillBoard::create();
    bill->addChild(la);
    addChild(bill);
    bill->setCameraMask((unsigned short)CameraFlag::USER1);
    bill->setPosition3D(Vec3(300,-500,100));
    std::vector<std::string> texts;
    
    switch (m_nCurrentLevel) {
        case 1:
            texts.clear();
            texts.push_back("选择了开始的格子");
            texts.push_back("选择了前进的方向");
            texts.push_back("接下来我能做的");
            texts.push_back("就是向着既定方向前进");
            texts.push_back("已经走过的路，不能再走");
            texts.push_back("前面是什么？");
            texts.push_back("我该做点什么？");
            texts.push_back("也许走遍所有的格子之后");
            texts.push_back("就会知道了吧");
            texts.push_back("第一章：初");
            break;
        case 2:
            texts.clear();
            texts.push_back("有些格子已经被探索过了");
            texts.push_back("走过的路是不能再走的");
            texts.push_back("“世界”也变化了");
            texts.push_back("难道……………………");
            texts.push_back("在“我“之前");
            texts.push_back("这个世界");
            texts.push_back("就已经");
            texts.push_back("存在了吗？");
            texts.push_back("第二章：领悟");
            break;
            
        case 3:
            texts.clear();
            texts.push_back("我现在很平静");
            texts.push_back("思维也很清晰“");
            texts.push_back("似乎这个世界的规则很简单");
            texts.push_back("…………我明白了…………");
            texts.push_back("“世界”诞生了");
            texts.push_back("“我”诞生了");
            texts.push_back("“世界”和“我”都需要“色彩”");
            texts.push_back("“我”要给“世界”找到“色彩“");
            texts.push_back("这就是我要做的");
            texts.push_back("第三章：梦");
            break;
        case 4:
            texts.clear();
            texts.push_back("“我”是唯一存在的么？");
            texts.push_back("如果“我是”唯一的");
            texts.push_back("那么究竟“我”是生");
            texts.push_back("还是死");
            texts.push_back("是创造者");
            texts.push_back("还是毁灭者");
            texts.push_back("到哪里去，到哪里去？");
            texts.push_back("寻找，寻找色彩");
            texts.push_back("第四章：唯一");
            break;
        case 5:
            texts.clear();
            texts.push_back("如果“世界”需要“色彩”");
            texts.push_back("那么色彩是均等的么");
            texts.push_back("也许有的色彩");
            texts.push_back("会比其他色彩更好");
            texts.push_back("我的心中充满困惑");
            texts.push_back("为什么？");
            texts.push_back("“我”拥有“世界”");
            texts.push_back("“世界”有了”色彩“");
            texts.push_back("一定还有什么，我没找到的");
            texts.push_back("然而我又是狂喜的");
            texts.push_back("因为今天，我会发现美");
            texts.push_back("第五章：美");
            break;
        case 6:
            texts.clear();
            texts.push_back("………………");
            texts.push_back("………………");
            texts.push_back("“我”很好");
            texts.push_back("………………");
            texts.push_back("“我”很好");
            texts.push_back("………………");
            texts.push_back("找到了……………");
            texts.push_back("改变了……………");
            texts.push_back("为什么？");
            texts.push_back("“我”还是“我”");
            texts.push_back("“世界”还是“世界”");
            texts.push_back("够了");
            texts.push_back("我累了");
            texts.push_back("第六章：无题");
            break;
            
        default:
            break;
    }
    
    auto text = TextDisplayer::create();
    addChild(text);
    text->setLabel(la);
    
    text->setTextToDisplay(texts);
    text->startTyping();
    
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