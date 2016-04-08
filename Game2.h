#ifndef __GAME2_SCENE_H__
#define __GAME2_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Game2Scene : public cocos2d::CCLayer
{
protected:
	int m_Count = 0;
	int m_timer = 10;
private:
	bool m_IsAlive[100];
	int	m_EnemyMax;
	bool m_isMoving;
	const float speed = 400;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
	CREATE_FUNC(Game2Scene);

	void BattleField();

	void makeEnemy(float dt);

	int getEnableNumber();

	void EndOfEnemyMoved(CCObject* pSender);

	void update(float dt);

	void countTimer(float dt);

	void eat(float dt);

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
	
};

#endif // __GAME2_SCENE_H__
