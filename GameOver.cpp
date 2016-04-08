#include "GameOver.h"
#include "menuScene.h"
#include "Game.h"
#include "Game2.h"
#include "SimpleAudioEngine.h"
#include "Sound.h"

USING_NS_CC;
using namespace CocosDenshion;

CCScene* GameOver::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameOver *layer = GameOver::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init())
    {
        return false;
    }
	//サウンドプリロード
	//SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.1);
	//SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(OVER_BGM);
	//サウンド再生
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic(OVER_BGM, true);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	//背景
	Background();
	//ゲームオーバー画像作成
	CCSprite* pSprite = CCSprite::create("GameOver2.png");
	pSprite->setPosition(winSize / 2);
	pSprite->setTag(3);
	this->addChild(pSprite);

	//メニューボタン作成
	CCMenuItemImage* pCloseItem = CCMenuItemImage::create("Exit.jpg", "Exit2.jpg",
															this, menu_selector(GameOver::menuCallback));
	pCloseItem->setPosition(ccp(winSize.width - pCloseItem->getContentSize().width, pCloseItem->getContentSize().height));

	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
	//SE3の再生
	//SimpleAudioEngine::sharedEngine()->playEffect(SE3);
	//ボタン配置
	char* Name[] = {
		"title",
		"Hard",
		"Easy"
	};
	for (int i = 0; i < 3; i++)
	{
		titleButton(i + 5, Name[i], ccp(800 - i * 300, winSize.height/3 - 20));
	}
    return true;
}

void GameOver::Background()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* p = CCSprite::create("OverBackground.jpg");
	p->setPosition(size/2);
	this->addChild(p);
}

void GameOver::titleButton(int tag, char* msg, CCPoint pos)
{
	CCRect spriteRect = CCRectMake(0, 0, 80, 20);
	CCRect capINsents = CCRectMake(12, 12, 46, 46);
	CCScale9Sprite* title = CCScale9Sprite::create("button9.png", spriteRect, capINsents);
	CCLabelTTF* TitleFont = CCLabelTTF::create(msg, "arial", 30);
	CCControlButton* tButton = CCControlButton::create(TitleFont, title);
	tButton->setPreferredSize(CCSizeMake(200, 50));
	tButton->setPosition(pos);
	tButton->setColor(ccc3(155, 150, 150));
	this->addChild(tButton, 1, tag);
	tButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameOver::tapCallback), CCControlEventTouchUpInside);
	//SE3の再生
	//SimpleAudioEngine::sharedEngine()->playEffect(SE3);
}

void GameOver::tapCallback(CCObject* pSender, CCControlEvent event)
{
	//シーン切替作成
	CCSprite* btn = (CCSprite*)pSender;
	int tag = btn->getTag();
	CCScene* nextScene;
	CCScene* pScene;
	//ボタンの行先
	switch (tag)
	{
	case 5:
		nextScene = menuScene::scene();
		//SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
		break;
	case 6:
		nextScene = GameScene::scene();
		//SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
		break;
	case 7:
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

void GameOver::menuCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

