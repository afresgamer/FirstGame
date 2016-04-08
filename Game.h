#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public cocos2d::CCLayer
{
protected:
	int m_Count = 0;
	int m_timer = 5;
	int m_ActionType;
private:
	const float speed = 500;
	bool m_isMoving;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(GameScene);

	void BattleField();

	void Enemy();

	void Logic(float dt);

	void spriteMoveFinished(CCObject* sender);

	void update(float dt);

	void eat(float dt);

	void countTimer(float time);

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

};

#endif // __GAME_SCENE_H__

