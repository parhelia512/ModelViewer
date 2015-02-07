
#ifndef __UI_LAYER_H__
#define __UI_LAYER_H__

#include "cocos2d.h"

class UILayer : public cocos2d::Layer
{
public:
	virtual bool init();
	void update( float delta);
	void moveTime( float delta);
	CREATE_FUNC( UILayer);

	void onMouseDown( cocos2d::Event* event);
	void onMouseUp( cocos2d::Event* event);
	void onMouseMove( cocos2d::Event* event);
	void onMouseScroll( cocos2d::Event* event);

	void onKeyPressed( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	bool checkKeyboardState( cocos2d::EventKeyboard::KeyCode keyCode);

	void menuCloseCallback( cocos2d::Ref* pSender);

	void menuMoveCallback( cocos2d::Ref* pSender);
	void menuRotationCallback( cocos2d::Ref* pSender);
	void menuScaleCallback( cocos2d::Ref* pSender);
	
	void menuXButtonCallback( cocos2d::Ref* pSender);
	void menuYButtonCallback( cocos2d::Ref* pSender);
	void menuZButtonCallback( cocos2d::Ref* pSender);

	void menuPlusCallback( cocos2d::Ref* pSender);
	void menuMinusCallback( cocos2d::Ref* pSender);

	void menuNextFileCallback( cocos2d::Ref* pSender);
	void menuPrevFileCallback( cocos2d::Ref* pSender);
	void menuModelReloadCallback( cocos2d::Ref* pSender);

	void menuModelAnimationCallback( cocos2d::Ref* pSender);

private:
	enum MouseFlag
	{
		LeftButton			= 0,
		RightButton			= 1,
		CenterButton		= 2,

		PushFlag			= ( 1 << 0),

		LeftButtonFlag		= ( 1 << 1),
		RightButtonFlag		= ( 1 << 2),
		CenterButtonFlag	= ( 1 << 3),

		KeyboardPushFlag	= ( 1 << 4),
	};

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

		ParamX = 0,
		ParamY,
		ParamZ,

		Close = 0,
		
		Move,
		Rotation,
		Scale,

		PosX,
		PosY,
		PosZ,

		Plus,
		Minus,

		NextFile,
		PrevFile,
		Reload,

		Anime,

		MenuNum,
	};

	float modelScale;
	unsigned char inputFlag;
	cocos2d::Vec2 mouseStartPos;
	cocos2d::Vec2 mouseNowPos;
	cocos2d::Vec2 mouseMoveSize;
	cocos2d::EventKeyboard::KeyCode newKeyboardCode;

	char spriteState[256];
	unsigned short menuFlag;
	cocos2d::Label* pointStatus[3];
	cocos2d::Label* rotationStatus[3];
	cocos2d::Label* scaleStatus;
	cocos2d::Label* fileName;
	cocos2d::Menu* menu;
	cocos2d::MenuItemImage* menuItem[MenuNum];

	LoadFile* fileInstance;
	cocos2d::Sprite3D* sprite3D;

	void setInputEvent( void);
	void setLabel( void);
	void updateLabel( void);

	void setMenuUI( void);
	void setPositionUI( void);

	void menuAllReset( void);
};

#endif // __UI_LAYER_H__
