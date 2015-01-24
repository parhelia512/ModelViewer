
#ifndef _MAIN_SCENE_H_
#define _MAIN_SCENE_H_

#include "cocos2d.h"
#include "LoadFile.h"

class Main : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update( float delta);
	CREATE_FUNC( Main);

	void menuMoveCallback( cocos2d::Ref* pSender);
	void menuRotationCallback( cocos2d::Ref* pSender);
	void menuScaleCallback( cocos2d::Ref* pSender);
	
	void menuXButtonCallback( cocos2d::Ref* pSender);
	void menuYButtonCallback( cocos2d::Ref* pSender);
	void menuZButtonCallback( cocos2d::Ref* pSender);

	void menuPlusButtonCallback( cocos2d::Ref* pSender);
	void menuMinusButtonCallback( cocos2d::Ref* pSender);

	void menuNextFileCallback( cocos2d::Ref* pSender);
	void menuPrevFileCallback( cocos2d::Ref* pSender);
	void menuModelReloadCallback( cocos2d::Ref* pSender);

	void menuModelAnimationCallback( cocos2d::Ref* pSender);

	bool onTouchBegan( cocos2d::Touch* touch,cocos2d::Event* event);
	void onTouchMoved( cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded( cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchCancelled( cocos2d::Touch* touch,cocos2d::Event* event);

private:
	enum MenuFlag
	{
		MoveFlag		= ( 1 << 0),
		RotationFlag	= ( 1 << 1),
		ScaleFlag		= ( 1 << 2),

		XFlag			= ( 1 << 3),
		YFlag			= ( 1 << 4),
		ZFlag			= ( 1 << 5),

		PlusFlag		= ( 1 << 6),
		MinusFlag		= ( 1 << 7),
		AnimeFlag		= ( 1 << 8),
	};

	unsigned short MenuFlags;
	LoadFile* fileInstance;

	cocos2d::Label* label;
	cocos2d::Sprite3D* sprite;
	cocos2d::Vec2 origin;
	cocos2d::Size visibleSize;
	cocos2d::Menu* menu;
	cocos2d::MenuItemImage* menuItem[12];

	bool checkFlag( unsigned short flag);
	void setFlag( unsigned short flag);
	void resetFlag( unsigned short flag);
	void setMenuSprite( void);
	void resetMenuSprite( int number);
	void setMenuItem( void);
};

#endif // _MAIN_SCENE_H_