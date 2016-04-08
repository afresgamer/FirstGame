#include "ScoreTest.h"

USING_NS_CC;

CCScene* ScoreTest::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ScoreTest *layer = ScoreTest::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ScoreTest::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize WinSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	//SCOREの表示 
	CCSprite* pSprite = CCSprite::create("Score.png");
	pSprite->setPosition(ccp(WinSize.width / 2, WinSize.height - pSprite->getContentSize().height / 2));
	pSprite->setTag(21);
	this->addChild(pSprite);

	//スコアポイント
	CCLabelTTF* gamePoint = CCLabelTTF::create("0", "Arial", 48);
	gamePoint->setPosition(ccp(WinSize.width / 2 + pSprite->getContentSize().width + 20,
								WinSize.height * 0.9 + 28));
	gamePoint->setTag(22);
	this->addChild(gamePoint);

    return true;
}

