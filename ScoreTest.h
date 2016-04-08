#ifndef __SCORETEST_SCENE_H__
#define __SCORETEST_SCENE_H__

#include "cocos2d.h"

class ScoreTest : public cocos2d::CCLayer
{
protected:
	int m_points;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(ScoreTest);	

};

#endif // __SCORETEST_SCENE_H__
