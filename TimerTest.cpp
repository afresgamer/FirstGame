#include "TimerTest.h"

USING_NS_CC;

CCScene* TimerScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	TimerScene *layer = TimerScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TimerScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
	//タイマー画像作成
	timer = 6;
	CCString* str = CCString::createWithFormat("%d", timer);
	CCLabelTTF* timerLabel = CCLabelTTF::create(str->getCString(), "arial", 48);
	timerLabel->setPosition(ccp(visibleSize.width * 0.9, visibleSize.height * 0.9));
	timerLabel->setTag(12);
	this->addChild(timerLabel);

	this->schedule(schedule_selector(TimerScene::countTimer), 1.0f);

    return true;
}

void TimerScene::countTimer(float time)
{
	//タイマーシステム作成
	timer--;
	if (timer < 0)
	{
		this->unschedule(schedule_selector(TimerScene::countTimer));
		return;
	}
	CCString* str = CCString::createWithFormat("%d", timer);
	CCLabelTTF* timerLabel = (CCLabelTTF*)this->getChildByTag(12);
	timerLabel->setString(str->getCString());

}

