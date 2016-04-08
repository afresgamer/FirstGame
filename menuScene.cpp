#include "menuScene.h"
#include "Game.h"
#include "Gameclear.h"
#include "Game2.h"
#include "SimpleAudioEngine.h"
#include "Sound.h"

USING_NS_CC;
using namespace CocosDenshion;

CCScene* menuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    menuScene *layer = menuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool menuScene::init()
{
    //////////////////////////////
    // 1. super init first
	if (!CCLayer::init())
    {
        return false;
    }
	//サウンドプリロード
	//SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.1);
	//SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(TITLE_BGM);
	//サウンド再生
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic(TITLE_BGM, true);
	GameBackground();
	CCSize WinSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();	
	
	CCSprite* pSprite = CCSprite::create("title1.jpg");
	pSprite->setPosition(ccp(WinSize.width / 2, WinSize.height - pSprite->getContentSize().height / 2));
	pSprite->setTag(6);
	this->addChild(pSprite);
	
	//ボタンの配置
	char* name[] =
	{
		"Hard",
		"Easy"
	};
	for (int i = 0; i < 2; i++)
	{
		makeButton(i + 10, name[i], ccp(680 - 400 * i, WinSize.height / 4));
	}
	
	return true; 
}


void menuScene::makeButton(int tag, char* msg, CCPoint pos)
{
	//ボタン作成
	CCRect spriteRect = CCRectMake(0, 0, 80, 80);
	CCRect capInsents = CCRectMake(12, 12, 56, 56);
	CCScale9Sprite* pSprite =CCScale9Sprite::create("button9.png",spriteRect,capInsents);
	CCLabelTTF* label =CCLabelTTF::create(msg, "Arial", 30);
	CCControlButton* button =CCControlButton::create(label, pSprite);
	button->setPreferredSize(CCSizeMake(300, 50));
	button->setPosition(pos);
	button->setColor(ccc3(155,150,150));
	this->addChild(button, 1, tag);
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(menuScene::tapCallback), CCControlEventTouchUpInside);
	//SE3の再生
	//SimpleAudioEngine::sharedEngine()->playEffect(SE3);
}

void menuScene::tapCallback(CCObject* pSender, CCControlEvent event)
{
	//シーン切替作成
	CCSprite* btn = (CCSprite*)pSender;
	int tag = btn->getTag();
	CCScene* nextScene;
	CCScene* pScene;
	//ボタンの行先
	switch (tag)
	{
	case 10:		
		nextScene = GameScene::scene();
		//SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
		break;
	case 11: 
		nextScene = Game2Scene::scene();
		//SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
		break;
	default:
		return;
	}
	//画面切り替えの効果作成
	pScene = CCTransitionCrossFade::create(0.5f, nextScene);
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void menuScene::GameBackground()
{
	//ここで画面サイズを取得
	CCSize WinSize = CCDirector::sharedDirector()->getWinSize();
	//ここで画面を作成
	CCSprite* psprite = CCSprite::create("titleBackground.jpg");
	psprite->setPosition(ccp(WinSize.width*0.5, WinSize.height*0.5));
	this->addChild(psprite);

}