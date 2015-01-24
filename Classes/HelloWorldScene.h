
#ifndef _HELLOWORLD_SCENE_H_
#define _HELLOWORLD_SCENE_H_

#include "cocos2d.h"
#include "LoadFile.h"

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void menuMoveCallback( cocos2d::Ref* pSender);
	void menuRotationCallback( cocos2d::Ref* pSender);
	void menuScaleCallback( cocos2d::Ref* pSender);
	void menuXButtonCallback( cocos2d::Ref* pSender);
	void menuYButtonCallback( cocos2d::Ref* pSender);
	void menuZButtonCallback( cocos2d::Ref* pSender);

	void menuNextFileCallback( cocos2d::Ref* pSender);
	void menuPrevFileCallback( cocos2d::Ref* pSender);
	void menuModelReloadCallback( cocos2d::Ref* pSender);

	void menuModelAnimationCallback( cocos2d::Ref* pSender);

	void menuCloseCallback( cocos2d::Ref* pSender);
	CREATE_FUNC( HelloWorld);

private:
	LoadFile* fileInstance;
	cocos2d::Sprite3D* sprite;

	void setMenuSprite( void);
};

#endif // _HELLOWORLD_SCENE_H_
