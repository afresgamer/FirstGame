#include "Game.h"
#include "GameClear.h"
#include "GameOver.h"
#include "SimpleAudioEngine.h"
#include "Sound.h"

USING_NS_CC;
using namespace CocosDenshion;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	//SEの準備
	//SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0);
	//SimpleAudioEngine::sharedEngine()->preloadEffect(SE);
	//SimpleAudioEngine::sharedEngine()->preloadEffect(SE2);
	//サウンドプリロード
	//SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.1);
	//SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(SOUND_BGM);
	//サウンド再生
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic(SOUND_BGM,true);
	//変数の初期化
	srand((unsigned)time(NULL));
	//フィールド形成
	BattleField();
	//敵作成
	this->schedule(schedule_selector(GameScene::Logic), 0.3);
	//タイマー作成
	this->schedule(schedule_selector(GameScene::countTimer), 1.0);
	//タッチ取得
	this->setTouchEnabled(true);
	this->setTouchMode(kCCTouchesAllAtOnce);

	this->scheduleUpdate();
	
	return true;
}


void GameScene::BattleField()
{
	//プレイヤー作成
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* player = CCSprite::create("monkey01.png", CCRectMake(0, 0, 100, 135));
	player->setPosition(ccp(player->getContentSize().width / 2, winSize.height / 2));
	player->setTag(1);
	this->addChild(player, 5);
	//カウント初期化
	//SCOREの表示 
	CCSprite* pSprite = CCSprite::create("Score.png");
	pSprite->setPosition(ccp(winSize.width / 2, winSize.height - pSprite->getContentSize().height / 2));
	pSprite->setTag(21);
	this->addChild(pSprite, 3);
	//スコアポイント
	CCLabelTTF* gamePoint = CCLabelTTF::create("0", "Arial", 55);
	gamePoint->setPosition(ccp(winSize.width / 2 + pSprite->getContentSize().width/2+20 ,
		winSize.height * 0.9 + 20));
	gamePoint->setColor(ccc3(120, 120, 120));
	gamePoint->setTag(22);
	this->addChild(gamePoint, 3);
	//タイマー
	CCString* Count = CCString::createWithFormat("%d", m_timer);
	CCLabelTTF* timerLabel = CCLabelTTF::create(Count->getCString(), "arial", 55);
	timerLabel->setColor(ccc3(255,255,0));
	timerLabel->setPosition(ccp(winSize.width * 0.9, winSize.height * 0.9 +20));
	timerLabel->setTag(12);
	this->addChild(timerLabel, 3);
	//フィールド作成
	CCSprite* Field = CCSprite::create("BattleField1.png");
	Field->setPosition(winSize / 2);
	Field->setTag(8);
	this->addChild(Field, 1);
	//エフェクト作成
	for (int i = 0; i < 3; i++)
	{
		CCParticleGalaxy* p = CCParticleGalaxy::create();
		p->setStartColor(ccc4f(255, 255, 255, 0.7));
		p->setEndColor(ccc4f(255, 255, 119, 1.0));
		p->setZOrder(1);
		p->setSpeed(800);
		p->setStartSize(10);
		p->setEndSize(1000);
		p->setGravity(ccp(winSize.width / 8, 0));
		int width1 = winSize.width - 660;
		int width2 = winSize.width - 160;
		int width3 = width2 - width1;
		int width = rand() % width3 + width1;
		p->setPosition(ccp(width, 320));
		this->addChild(p, 5);
	}
	
}


void GameScene::spriteMoveFinished(CCObject* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
	bool iscleanUp = true;
	removeChild(sprite,iscleanUp);
}


void GameScene::Enemy()
{
	//敵作成(倒す=食べる)
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCString* fname = CCString::createWithFormat("Enemy%d.png", rand() % 2);
	CCSprite* Enemy = CCSprite::create(fname->getCString());
	//Y出現範囲
	int minY = Enemy->getContentSize().height / 2;
	int maxY = size.height - (Enemy->getContentSize().height / 2);
	int rangeY = maxY - minY;
	int height = (rand() % rangeY) + minY;

	Enemy->setPosition(ccp(size.width, height));
	Enemy->setTag(2);
	this->addChild(Enemy,5);
	//SE2の再生
	//SimpleAudioEngine::sharedEngine()->playEffect(SE2);
	//敵の出現ポイント
	int Ypoint1 = size.height - Enemy->getContentSize().height/2;
	int Ypoint2 = Enemy->getContentSize().height;
	int Ypoint3 = Ypoint1 - Ypoint2;
	int YPoint = rand() % Ypoint3 + Ypoint2;
	//敵の出現間隔
	int minDuration = (int)1.0;
	int maxDuration = (int)2.0;
	int rangeDuration1 = maxDuration - minDuration;
	int actualDuration = (rand() % rangeDuration1) +minDuration;
	//出現アクション
	//出現アクション
	CCMoveTo *actionMove = CCMoveTo::create(actualDuration, ccp(Enemy->getContentSize().width / 2, height));
	CCFiniteTimeAction* actionMoveDone = CCCallFuncO::create(this, callfuncO_selector(GameScene::spriteMoveFinished),Enemy);
	Enemy->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	ccBezierConfig bezier;
	bezier.controlPoint_1 = ccp(800,YPoint);
	bezier.controlPoint_2 = ccp(400,YPoint);
	bezier.endPosition = ccp(-Enemy->getContentSize().width,height);
	CCActionInterval* act;
	CCActionInterval* act1;
	CCPlace* place;
	CCCallFuncO* func;
	switch (this->m_ActionType)
	{
	case 1:
		act = CCBezierTo::create(actualDuration, bezier);
		func = CCCallFuncO::create(this, callfuncO_selector(GameScene::spriteMoveFinished), Enemy);
		Enemy->runAction(CCSequence::create(act, func, NULL));
		break;
	case 2:
		act = CCRotateBy::create(actualDuration, -360);
		place = CCPlace::create(ccp(rand()%400,YPoint));
		Enemy->runAction(act);
		act1 = CCRepeatForever::create(act);
		break;
	default:
		break;
	}
	this->m_ActionType += 1;
	this->m_ActionType = rand() % 3;
}


void GameScene::Logic(float dt)
{
	this->Enemy();
	
}


void GameScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	if (!m_isMoving)
	{
		m_isMoving = true;
		//タッチ初期値
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCTouch *touch = (CCTouch *)pTouches->anyObject();
		CCPoint location = touch->getLocationInView();
		location = CCDirector::sharedDirector()->convertToGL(location);
		//スプライト呼び出し
		CCSprite *player = (CCSprite *)this->getChildByTag(1);
		//プレイヤーの出現
		float Length = powf(location.x - player->getPositionX(), 2.0f) + powf(location.y - player->getPositionY(), 2.0f);
		float Duration = Length / winSize.width * 1.5f / speed;//移動に必要な時間
		//タッチイベント
		CCMoveTo* actionMove = CCMoveTo::create(Duration, location);
		actionMove->setTag(26);
		// actionMoveだけを止める
		player->stopActionByTag(26);
		player->runAction(actionMove);
	}
	
}


void GameScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	m_isMoving = false;
}


void GameScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{

}


void GameScene::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{

}


void GameScene::update(float dt)
{
	
	CCSprite* player = (CCSprite *)this->getChildByTag(1);
	//プレイヤーのあたり範囲
	CCRect playerRect = CCRectMake(
		player->getPosition().x - (player->getContentSize().width / 2),
		player->getPosition().y - (player->getContentSize().height / 2),
		player->getContentSize().width,
		player->getContentSize().height);

	CCSprite* Enemy = (CCSprite *)this->getChildByTag(2);
	if (Enemy == NULL) return;
	//敵のあたり範囲
	CCRect EnemyRect = CCRectMake(
		Enemy->getPosition().x - (Enemy->getContentSize().width),
		Enemy->getPosition().y - (Enemy->getContentSize().height),
		Enemy->getContentSize().width*2,
		Enemy->getContentSize().height*2);
	//playerとEnemyの衝突判定でどう動く
	if (playerRect.intersectsRect(EnemyRect))
	{
		this->removeChild(Enemy, true);
		player->setTexture(CCTextureCache::sharedTextureCache()->addImage("monkey02.png"));

		this->scheduleOnce(schedule_selector(GameScene::eat), 0.1f);
	}
	
}


void GameScene::eat(float dt)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* player = (CCSprite *)this->getChildByTag(1);
	player->setTexture(CCTextureCache::sharedTextureCache()->addImage("monkey01.png"));
	//SEの再生
	//SimpleAudioEngine::sharedEngine()->playEffect(SE);
	//アニメーション
	CCAnimation* ani = CCAnimation::create();
	for (int i = 3; i <= 5; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "monkey%02d.png", i);
		ani->addSpriteFrameWithFileName(szName);
	}
	ani->setDelayPerUnit(0.15 / 3);
	ani->setRestoreOriginalFrame(true);
	ani->setLoops(2);

	CCAnimate* act = CCAnimate::create(ani);
	player->runAction(act);
	//スコアシステム作成
	CCLabelTTF* Label = (CCLabelTTF *)this->getChildByTag(22);
	this->m_Count += 1;
	CCString* gamePoints = CCString::createWithFormat("%d", this->m_Count);
	Label->setString(gamePoints->getCString());
	
}


void GameScene::countTimer(float time)
{
	//ログ
	CCLOG("kkkkk");		
	//タイマーシステム作成
	m_timer--;
	CCString* Count = CCString::createWithFormat("%d", m_timer);
	CCLabelTTF* timerLabel = (CCLabelTTF *)this->getChildByTag(12);
	timerLabel->setColor(ccc3(255,255,0));
	timerLabel->setString(Count->getCString());
	
	//クリア条件
	if (m_timer == 0 && m_Count < 10 || m_timer == 0 && m_Count < 15)
	{
		//シーン移動
		CCScene* GameOver = GameOver::scene();
		float duration = 0.5f;
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(duration, GameOver));
		//SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	}
	else if (m_timer >= 0 && m_Count >= 10)
	{
		//シーン移動
		CCScene* GaveClear = GameClear::scene();
		float duration = 0.5f;
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(duration, GaveClear));
		//SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	}
}

