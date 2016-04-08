#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class menuScene : public cocos2d::CCLayer
{
private:
	void GameBackground();
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

	void makeButton(int tag, char* msg, CCPoint pos);

	void tapCallback(CCObject* pSender, CCControlEvent event);
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
	CREATE_FUNC(menuScene);
};

#endif // __MENU_SCENE_H__
