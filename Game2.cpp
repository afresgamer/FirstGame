#include "Game2.h"
#include "GameClear.h"
#include "GameOver.h"
#include "SimpleAudioEngine.h"
#include "Sound.h"

USING_NS_CC;
using namespace CocosDenshion;

CCScene* Game2Scene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	Game2Scene *layer = Game2Scene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game2Scene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	//SE�̏���
	//SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0);
	//SimpleAudioEngine::sharedEngine()->preloadEffect(SE);
	//simpleAudioEngine::sharedEngine()->preloadEffect(SE2);
	//�T�E���h�v�����[�h
	//SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.1);
	//SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(SOUND_BGM);
	//�T�E���h�Đ�
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic(SOUND_BGM,true);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//�t�B�[���h�`��
	BattleField();
	///	�����̏�����
	srand((unsigned)time(NULL));
	//�^�b�`
	this->setTouchEnabled(true);
	this->setTouchMode(kCCTouchesAllAtOnce);
	//�G�l�~�[�������x
	this->schedule(schedule_selector(Game2Scene::makeEnemy), 0.2);
	//�^�C�}�[���x
	this->schedule(schedule_selector(Game2Scene::countTimer), 1.0);
	this->scheduleUpdate();
	///	�z�������������(�G�l�~�[�o���̏���)
	for (int i = 0; i < 100; i++){
		m_IsAlive[i] = false;
		m_EnemyMax = 0;
	}
		/*CCLabelTTF* label = CCLabelTTF::create("", "arial", 24);
		label->setColor(ccc3(255, 255, 255));
		label->setPosition(size / 2);
		label->setTag(1);
		this->addChild(label, 3);*/
	
    return true;
}

void Game2Scene::BattleField()
{
	//�v���C���[�쐬
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* player = CCSprite::create("monkey01.png", CCRectMake(0, 0, 100, 135));
	player->setPosition(ccp(player->getContentSize().width/2, winSize.height / 2));
	player->setTag(4);
	this->addChild(player, 5);
	//�J�E���g������
	//SCORE�̕\�� 
	CCSprite* pSprite = CCSprite::create("Score.png");
	pSprite->setPosition(ccp(winSize.width / 2, winSize.height - pSprite->getContentSize().height / 2));
	pSprite->setTag(21);
	this->addChild(pSprite, 3);
	//�X�R�A�|�C���g
	CCLabelTTF* gamePoint = CCLabelTTF::create("0", "Arial", 55);
	gamePoint->setPosition(ccp(winSize.width / 2 + pSprite->getContentSize().width /2,
		winSize.height * 0.9 + 20));
	gamePoint->setColor(ccc3(120, 120, 120));
	gamePoint->setTag(22);
	this->addChild(gamePoint, 3);
	//�^�C�}�[
	CCString* Count = CCString::createWithFormat("%d", m_timer);
	CCLabelTTF* timerLabel = CCLabelTTF::create(Count->getCString(), "arial", 55);
	timerLabel->setColor(ccc3(255,255,0));
	timerLabel->setPosition(ccp(winSize.width * 0.9, winSize.height * 0.9 + 20));
	timerLabel->setTag(12);
	this->addChild(timerLabel, 3);
	//�t�B�[���h�쐬
	CCSprite* Field = CCSprite::create("BattleField1.png");
	Field->setPosition(winSize / 2);
	Field->setTag(8);
	this->addChild(Field, 1);
	//�G�t�F�N�g�쐬
	for (int i = 0; i < 3; i++)
	{
		CCParticleGalaxy* p = CCParticleGalaxy::create();
		p->setStartColor(ccc4f(255, 255, 255, 0.7));
		p->setEndColor(ccc4f(255, 255, 119, 1.0));
		p->setZOrder(1);
		p->setSpeed(800);
		p->setStartSize(10);
		p->setEndSize(1000);
		p->setGravity(ccp(winSize.width/8, 0));
		int width1 = winSize.width - 660;
		int width2 = winSize.width - 160;
		int width3 = width2 - width1;
		int width = rand() % width3 + width1;
		p->setPosition(ccp(width, 320));
		this->addChild(p, 5);
	}
}

void Game2Scene::update(float dt)
{
	/*CCLabelTTF* label = (CCLabelTTF*)this->getChildByTag(1);
	CCString* str = CCString::createWithFormat("%d", this->m_EnemyMax);
	label->setString(str->getCString());
	*/
	///	�����蔻��̃`�F�b�N
	for (int i = 0; i < 100; i++)
	{
		CCSprite* spr = (CCSprite*)this->getChildByTag(i + 10);
		if (spr != nullptr)
		{		
			CCSprite* player = (CCSprite*)this->getChildByTag(4);
			//�v���C���[�̂�����͈�
			CCRect playerRect = CCRectMake(
				player->getPosition().x - (player->getContentSize().width / 2),
				player->getPosition().y - (player->getContentSize().height / 2),
				player->getContentSize().width,
				player->getContentSize().height);

			if (spr == NULL) return;
			//�G�̂�����͈�
			CCRect EnemyRect = CCRectMake(
				spr->getPosition().x - (spr->getContentSize().width ),
				spr->getPosition().y - (spr->getContentSize().height),
				spr->getContentSize().width,
				spr->getContentSize().height);
			//player��Enemy�̏Փ˔���łǂ�����
			if (playerRect.intersectsRect(EnemyRect))
			{
				this->removeChild(spr, true);
				player->setTexture(CCTextureCache::sharedTextureCache()->addImage("monkey02.png"));

				this->scheduleOnce(schedule_selector(Game2Scene::eat), 0.1f);
			}
		}
	}
}

void Game2Scene::eat(float dt)
{
	CCSprite* player = (CCSprite*)this->getChildByTag(4);
	player->setTexture(CCTextureCache::sharedTextureCache()->addImage("monkey01.png"));
	//SE�̍Đ�
	//SimpleAudioEngine::sharedEngine()->playEffect(SE);
	//�A�j���[�V����
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
	//�X�R�A�V�X�e���쐬
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* Label = (CCLabelTTF*)this->getChildByTag(22);
	this->m_Count += 1;
	CCString* gamePoints = CCString::createWithFormat("%d", this->m_Count);
	Label->setString(gamePoints->getCString());
}

/*
	�G�̐���
*/
void Game2Scene::makeEnemy(float dt)
{
	if (m_EnemyMax >= 100)	return;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCString* fname = CCString::createWithFormat("Enemy%d.png", rand()%2);
	CCSprite* Enemy = CCSprite::create(fname->getCString());
	float y = (rand() % (int)(size.height - Enemy->getContentSize().height)) + Enemy->getContentSize().height / 2;
	Enemy->setPosition(ccp(size.width + Enemy->getContentSize().width, y));
	int num = getEnableNumber();
	m_IsAlive[num] = true;
	m_EnemyMax++;
	Enemy->setTag(num + 10);
	this->addChild(Enemy,5);
	//SE2�̍Đ�
	//SimpleAudioEngine::sharedEngine()->playEffect(SE2);
	//�G�̏o���Ԋu
	int minDuration = (int)1.0;
	int middleDuration = (int)2.0;
	int maxDuration = (int)4.0;
	int rangeDuration1 = maxDuration - minDuration;
	int actualDuration = (rand() % rangeDuration1) + (rand()% minDuration);
	//�A�N�V�����̎��
	ccBezierConfig bezier;
	bezier.controlPoint_1 = ccp(rand()%(int)size.width, 650);
	bezier.controlPoint_2 = ccp(rand()%(int)size.width,y);
	bezier.endPosition = ccp(-Enemy->getContentSize().width, y);
	CCActionInterval* act = CCBezierTo::create(actualDuration, bezier);
	CCCallFuncO* func = CCCallFuncO::create(this, callfuncO_selector(Game2Scene::EndOfEnemyMoved), Enemy);
	Enemy->runAction(CCSequence::create(act, func, NULL));
}

void Game2Scene::EndOfEnemyMoved(CCObject* pSender)
{
	CCSprite* Enemy = (CCSprite*)pSender;
	int tag = Enemy->getTag();
	this->removeChild(Enemy);
	m_IsAlive[tag] = false;
	m_EnemyMax--;
}


/*
	�J���Ă���ꏊ������
*/
int Game2Scene::getEnableNumber()
{
	for (int i = 0; i < 100; i++)
	{
		if (m_IsAlive[i] == false)
		{
			return	i;
		}
	}
}

void Game2Scene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	if (!m_isMoving)
	{
		m_isMoving = true;
		//�^�b�`�����l
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCTouch *touch = (CCTouch *)pTouches->anyObject();
		CCPoint location = touch->getLocationInView();
		location = CCDirector::sharedDirector()->convertToGL(location);
		//�X�v���C�g�Ăяo��
		CCSprite *player = (CCSprite *)this->getChildByTag(4);
		//�v���C���[�̈ړ��͈�
		if (location.x  < 150 )
		{
			//�v���C���[�̏o��
			float Length = powf(location.x - player->getPositionX(), 2.0f) + powf(location.y - player->getPositionY(), 2.0f);
			float Duration = Length / winSize.width * 1.5f / speed;//�ړ��ɕK�v�Ȏ���
			//�^�b�`�C�x���g
			CCMoveTo* actionMove = CCMoveTo::create(Duration, location);
			actionMove->setTag(26);
			// actionMove�������~�߂�
			player->stopActionByTag(26);
			player->runAction(actionMove);
		}		
	}
}

void Game2Scene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	m_isMoving = false;
}

void Game2Scene::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{

}

void Game2Scene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{

}

void Game2Scene::countTimer(float dt)
{
	//���O
	CCLOG("kkkkk");
	//�^�C�}�[�V�X�e���쐬
	m_timer--;
	CCString* Count = CCString::createWithFormat("%d", m_timer);
	CCLabelTTF* timerLabel = (CCLabelTTF *)this->getChildByTag(12);
	timerLabel->setColor(ccc3(255,255,0));
	timerLabel->setString(Count->getCString());
	//�N���A����
	if (m_timer == 0 && m_Count < 10 || m_timer == 0 && m_Count < 15)
	{
		//�V�[���ړ�
		CCScene* GameOver = GameOver::scene();
		float duration = 0.5f;
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(duration, GameOver));
		//SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	}
	else if (m_timer > 0 && m_Count >= 10)
	{
		//�V�[���ړ�
		CCScene* GaveClear = GameClear::scene();
		float duration = 0.5f;
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(duration, GaveClear));
		//SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	}

}

