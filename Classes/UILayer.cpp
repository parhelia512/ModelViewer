
#include "MainScene.h"
#include "LoadFile.h"
#include "UILayer.h"

#define LITELAL_POS

USING_NS_CC;
using namespace std;

bool UILayer::init( void)
{
	if ( !Layer::init() ) { return false; }

	fileInstance = LoadFile::getInstance();

	sprite3D = Sprite3D::create();
	sprite3D -> setPosition3D( Vec3( 0, 0, -200));
	auto bg = LayerColor::create( Color4B( 120, 120, 120, 255), MainScene::getWindowSize().width, MainScene::getWindowSize().height);
	sprite3D -> addChild( bg);
	addChild( sprite3D);

	auto camera = Camera::createOrthographic( MainScene::getWindowSize().width, MainScene::getWindowSize().height, 1, 1000);
	camera -> setPosition3D( Vec3( 0, 0, 500));
	camera -> lookAt( Vec3( 0, 0, 0), Vec3( 0, 0, -1));
	addChild( camera);

	sprite3D = fileInstance -> getModelData( 0);
	modelScale = 0;
	addChild( sprite3D);

	inputFlag = 0;
	setInputEvent();
	setLabel();

	menuFlag = 0;
	setMenuUI();
	setPositionUI();

	scheduleUpdate();
//	schedule( schedule_selector( UILayer::moveTime), 1);
	return true;
}

void UILayer::update( float delta)
{
	float scale = 0;
	Vec3 velocity = Vec3( 0, 0, 0);
	Vec3 Angle = Vec3( 0, 0, 0);

	if( MainScene::checkFlag( &inputFlag, (unsigned char)PushFlag) && MainScene::checkFlag( &menuFlag, (unsigned short)MoveFlag))
	{
		if( MainScene::checkFlag( &menuFlag, (unsigned short)PlusFlag))
		{
			if( MainScene::checkFlag( &menuFlag, (unsigned short)XFlag)) { velocity.x = 1; }
			if( MainScene::checkFlag( &menuFlag, (unsigned short)YFlag)) { velocity.y = 1; }
			if( MainScene::checkFlag( &menuFlag, (unsigned short)ZFlag)) { velocity.z = 1; }
		}
		else if( MainScene::checkFlag( &menuFlag, (unsigned short)MinusFlag))
		{
			if( MainScene::checkFlag( &menuFlag, (unsigned short)XFlag)) { velocity.x = -1; }
			if( MainScene::checkFlag( &menuFlag, (unsigned short)YFlag)) { velocity.y = -1; }
			if( MainScene::checkFlag( &menuFlag, (unsigned short)ZFlag)) { velocity.z = -1; }
		}
		sprite3D -> setPosition3D( sprite3D -> getPosition3D() + velocity);
	}

	if( MainScene::checkFlag( &inputFlag, (unsigned char)PushFlag) && MainScene::checkFlag( &menuFlag, (unsigned short)RotationFlag))
	{
		if( MainScene::checkFlag( &menuFlag, (unsigned short)PlusFlag))
		{
			if( MainScene::checkFlag( &menuFlag, (unsigned short)XFlag)) { Angle.x = 1; }
			if( MainScene::checkFlag( &menuFlag, (unsigned short)YFlag)) { Angle.y = 1; }
			if( MainScene::checkFlag( &menuFlag, (unsigned short)ZFlag)) { Angle.z = 1; }
		}
		else if( MainScene::checkFlag( &menuFlag, (unsigned short)MinusFlag))
		{
			if( MainScene::checkFlag( &menuFlag, (unsigned short)XFlag)) { Angle.x = -1; }
			if( MainScene::checkFlag( &menuFlag, (unsigned short)YFlag)) { Angle.y = -1; }
			if( MainScene::checkFlag( &menuFlag, (unsigned short)ZFlag)) { Angle.z = -1; }
		}
		sprite3D -> setRotation3D( sprite3D -> getRotation3D() + Angle);
	}

	if( MainScene::checkFlag( &inputFlag, (unsigned char)PushFlag) && MainScene::checkFlag( &menuFlag, (unsigned short)ScaleFlag))
	{
		if( MainScene::checkFlag( &menuFlag, (unsigned short)PlusFlag)) { scale = 1.0f; }
		else if( MainScene::checkFlag( &menuFlag, (unsigned short)MinusFlag)) { scale = -1.0f; }
		sprite3D -> setScale( sprite3D -> getScale() + scale);
	}
	updateLabel();
}

void UILayer::moveTime( float delta)
{
	if( modelScale == sprite3D -> getScale())
	{
		menuItem[Scale] -> setNormalImage( Sprite::create( "Picture/ScaleIdleNormal.png"));
		menuItem[Scale] -> setSelectedImage( Sprite::create( "Picture/ScaleIdleSelected.png"));
		MainScene::resetFlag( &menuFlag, (unsigned short)ScaleFlag);

		menuItem[Plus] -> setNormalImage( Sprite::create( "Picture/PlusIdleNormal.png"));
		menuItem[Plus] -> setSelectedImage( Sprite::create( "Picture/PlusIdleSelected.png"));
		MainScene::resetFlag( &menuFlag, (unsigned short)PlusFlag);

		menuItem[Minus] -> setNormalImage( Sprite::create( "Picture/MinusIdleNormal.png"));
		menuItem[Minus] -> setSelectedImage( Sprite::create( "Picture/MinusIdleSelected.png"));
		MainScene::resetFlag( &menuFlag, (unsigned short)MinusFlag);
	}
	modelScale = sprite3D -> getScale();
}

void UILayer::setInputEvent( void)
{
	auto dip = Director::getInstance() -> getEventDispatcher();

	auto mouseListener = EventListenerMouse::create();
	mouseListener -> onMouseMove = CC_CALLBACK_1( UILayer::onMouseMove, this);
	mouseListener -> onMouseUp = CC_CALLBACK_1( UILayer::onMouseUp, this);
	mouseListener -> onMouseDown = CC_CALLBACK_1( UILayer::onMouseDown, this);
	mouseListener -> onMouseScroll = CC_CALLBACK_1( UILayer::onMouseScroll, this);
	dip -> addEventListenerWithSceneGraphPriority( mouseListener, this);

	auto listener = EventListenerKeyboard::create();
	listener -> onKeyPressed = CC_CALLBACK_2( UILayer::onKeyPressed, this);
	listener -> onKeyReleased = CC_CALLBACK_2( UILayer::onKeyReleased, this);
	dip -> addEventListenerWithSceneGraphPriority( listener, this);
}

void UILayer::onMouseDown( Event* event)
{
	auto e = ( EventMouse*)event;
	MainScene::setFlag( &inputFlag, (unsigned char)PushFlag);
	switch( e -> getMouseButton())
	{
	case LeftButton:
		MainScene::setFlag( &inputFlag, (unsigned char)LeftButtonFlag);
		break;
	case RightButton:
		MainScene::setFlag( &inputFlag, (unsigned char)RightButtonFlag);
		break;
	case CenterButton:
		MainScene::setFlag( &inputFlag, (unsigned char)CenterButtonFlag);
		break;
	default:
		break;
	}
	mouseMoveSize = Vec2( 0, 0);
}

void UILayer::onMouseUp( Event* event)
{
	MainScene::resetFlag( &inputFlag, (unsigned char)PushFlag);
	MainScene::resetFlag( &inputFlag, (unsigned char)LeftButtonFlag);
	MainScene::resetFlag( &inputFlag, (unsigned char)RightButtonFlag);
	MainScene::resetFlag( &inputFlag, (unsigned char)CenterButtonFlag);
}

void UILayer::onMouseMove( Event* event)
{
	auto e = (EventMouse*)event;
	Vec3 vector = Vec3( 0, 0, 0);

	mouseMoveSize = Vec2( e -> getCursorX() - mouseStartPos.x, e -> getCursorY() - mouseStartPos.y);

	if( MainScene::checkFlag( &inputFlag, (unsigned char)LeftButtonFlag))
	{
		vector.x = mouseMoveSize.x * 2;
		vector.y = mouseMoveSize.y * 2;
		sprite3D -> setPosition3D( sprite3D -> getPosition3D() + vector);
	}
	
	if( MainScene::checkFlag( &inputFlag, (unsigned char)RightButtonFlag))
	{
		if( MainScene::checkFlag( &inputFlag, (unsigned char)CenterButtonFlag))
		{
			vector.z = mouseMoveSize.x * 2;
			sprite3D -> setRotation3D( sprite3D -> getRotation3D() + vector);
		}
		else
		{
			vector.x = mouseMoveSize.x * 2;
			sprite3D -> setRotation3D( sprite3D -> getRotation3D() + vector);
		}
	}
	else if( MainScene::checkFlag( &inputFlag, (unsigned char)CenterButtonFlag))
	{
		vector.y = mouseMoveSize.x * 2;
		sprite3D -> setRotation3D( sprite3D -> getRotation3D() + vector);
	}

	mouseStartPos.x = e -> getCursorX();
	mouseStartPos.y = e -> getCursorY();
}

void UILayer::onMouseScroll( Event* event)
{
	auto e = (EventMouse*)event;
	modelScale = sprite3D -> getScale() + ( ( e -> getScrollY() * 10) * -1);
	sprite3D -> setScale( modelScale);

	menuItem[Scale] -> setNormalImage( Sprite::create( "Picture/ScaleActiveNormal.png"));
	menuItem[Scale] -> setSelectedImage( Sprite::create( "Picture/ScaleActiveSelected.png"));
	MainScene::setFlag( &menuFlag, (unsigned short)ScaleFlag);

	if( e -> getScrollY() > 0)
	{
		menuItem[Minus] -> setNormalImage( Sprite::create( "Picture/MinusActiveNormal.png"));
		menuItem[Minus] -> setSelectedImage( Sprite::create( "Picture/MinusActiveSelected.png"));
		MainScene::setFlag( &menuFlag, (unsigned short)MinusFlag);
	}
	else if( e -> getScrollY() < 0)
	{
		menuItem[Plus] -> setNormalImage( Sprite::create( "Picture/PlusActiveNormal.png"));
		menuItem[Plus] -> setSelectedImage( Sprite::create( "Picture/PlusActiveSelected.png"));
		MainScene::setFlag( &menuFlag, (unsigned short)PlusFlag);
	}
}

void UILayer::onKeyPressed( EventKeyboard::KeyCode keyCode, Event* event)
{
	MainScene::setFlag( &inputFlag, (unsigned char)KeyboardPushFlag);
	newKeyboardCode = keyCode;
}

void UILayer::onKeyReleased( EventKeyboard::KeyCode keyCode, Event* event)
{
	MainScene::resetFlag( &inputFlag, (unsigned char)KeyboardPushFlag);
}

bool UILayer::checkKeyboardState( EventKeyboard::KeyCode keyCode)
{
	if( MainScene::checkFlag( &inputFlag, (unsigned char)KeyboardPushFlag))
	{
		if( newKeyboardCode == keyCode) { return true; }
	}
	return false;
}

void UILayer::setLabel( void)
{
	fileName = Label::createWithTTF( LoadFile::getInstance() -> getModelName(), "fonts/arial.ttf", 24);
	fileName -> setPosition( Vec2( MainScene::getWindowSize().width / 2, MainScene::getWindowSize().height - fileName -> getContentSize().height));
	addChild( fileName); 

	for( auto &p : pointStatus) 
	{ 
		p = Label::create();
		addChild( p);
	}
	for( auto &p : rotationStatus)
	{
		p = Label::create();
		addChild( p);
	}
	scaleStatus = Label::create();
	addChild( scaleStatus);
}

void UILayer::updateLabel( void)
{
	const int fontSize = 18;
	removeChild( pointStatus[ParamX]);
	sprintf( spriteState, "Pos X:%3.1f", sprite3D -> getPositionX());
	pointStatus[ParamX] = Label::createWithTTF( spriteState, "fonts/arial.ttf", fontSize);
	pointStatus[ParamX] -> setPosition( Vec2( MainScene::getWindowSize().width - pointStatus[ParamX] -> getContentSize().width / 2,
							MainScene::getWindowSize().height - pointStatus[ParamX] -> getContentSize().height));
	addChild( pointStatus[ParamX]);

	removeChild( pointStatus[ParamY]);
	sprintf( spriteState, "Y:%3.1f", sprite3D -> getPositionY());
	pointStatus[ParamY] = Label::createWithTTF( spriteState, "fonts/arial.ttf", fontSize);
	pointStatus[ParamY] -> setPosition( Vec2( MainScene::getWindowSize().width - pointStatus[ParamY] -> getContentSize().width / 2,
							MainScene::getWindowSize().height - pointStatus[ParamY] -> getContentSize().height * 2));
	addChild( pointStatus[ParamY]);

	removeChild( pointStatus[ParamZ]);
	sprintf( spriteState, "Z:%3.1f", sprite3D -> getPositionZ());
	pointStatus[ParamZ] = Label::createWithTTF( spriteState, "fonts/arial.ttf", fontSize);
	pointStatus[ParamZ] -> setPosition( Vec2( MainScene::getWindowSize().width - pointStatus[ParamZ] -> getContentSize().width / 2,
							MainScene::getWindowSize().height - pointStatus[ParamZ] -> getContentSize().height * 3));
	addChild( pointStatus[ParamZ]);

	removeChild( rotationStatus[ParamX]);
	sprintf( spriteState, "Rot X:%3.1f", sprite3D -> getRotation3D().x);
	rotationStatus[ParamX] = Label::createWithTTF( spriteState, "fonts/arial.ttf", fontSize);
	rotationStatus[ParamX] -> setPosition( Vec2( MainScene::getWindowSize().width - rotationStatus[ParamX] -> getContentSize().width / 2,
							MainScene::getWindowSize().height - rotationStatus[ParamX] -> getContentSize().height * 4));
	addChild( rotationStatus[ParamX]);

	removeChild( rotationStatus[ParamY]);
	sprintf( spriteState, "Y:%3.1f", sprite3D -> getRotation3D().y);
	rotationStatus[ParamY] = Label::createWithTTF( spriteState, "fonts/arial.ttf", fontSize);
	rotationStatus[ParamY] -> setPosition( Vec2( MainScene::getWindowSize().width - rotationStatus[ParamY] -> getContentSize().width / 2,
							MainScene::getWindowSize().height - rotationStatus[ParamY] -> getContentSize().height * 5));
	addChild( rotationStatus[ParamY]);

	removeChild( rotationStatus[ParamZ]);
	sprintf( spriteState, "Z:%3.1f", sprite3D -> getRotation3D().z);
	rotationStatus[ParamZ] = Label::createWithTTF( spriteState, "fonts/arial.ttf", fontSize);
	rotationStatus[ParamZ] -> setPosition( Vec2( MainScene::getWindowSize().width - rotationStatus[ParamZ] -> getContentSize().width / 2,
							MainScene::getWindowSize().height - rotationStatus[ParamZ] -> getContentSize().height * 6));
	addChild( rotationStatus[ParamZ]);

	removeChild( scaleStatus);
	sprintf( spriteState, "Sca :%3.1f", sprite3D -> getScale());
	scaleStatus = Label::createWithTTF( spriteState, "fonts/arial.ttf", fontSize);
	scaleStatus -> setPosition( Vec2( MainScene::getWindowSize().width - scaleStatus -> getContentSize().width / 2,
							MainScene::getWindowSize().height - scaleStatus -> getContentSize().height * 7));
	addChild( scaleStatus);
}

void UILayer::setMenuUI( void)
{
	menuItem[Close] = MenuItemImage::create( "Picture/CloseNormal.png", "Picture/CloseSelected.png", CC_CALLBACK_1( UILayer::menuCloseCallback, this));
	menu = Menu::create( menuItem[Close], NULL);
	menu -> setPosition( Vec2( MainScene::getWindowSize().width - menuItem[Close] -> getContentSize().width / 2, menuItem[Close] -> getContentSize().height / 2));
	addChild( menu);
}

void UILayer::menuCloseCallback( Ref* pSender) { Director::getInstance() -> end(); }

void UILayer::setPositionUI( void)
{
	menuItem[Move] = MenuItemImage::create( "Picture/MoveIdleNormal.png", "Picture/MoveIdleSelected.png", CC_CALLBACK_1( UILayer::menuMoveCallback, this));
	menu = Menu::create( menuItem[Move], NULL);
#ifdef LITELAL_POS
	menu -> setPosition( Vec2( 30, 450));
#else
	menu -> setPosition( Vec2( menuItem[Move] -> getContentSize().width, MainScene::getWindowSize().height - menuItem[Move] -> getContentSize().height));
#endif
	addChild( menu);

	menuItem[Rotation] = MenuItemImage::create( "Picture/RotationIdleNormal.png", "Picture/RotationIdleSelected.png", CC_CALLBACK_1( UILayer::menuRotationCallback, this));
	menu = Menu::create( menuItem[Rotation], NULL);
#ifdef LITELAL_POS
	menu -> setPosition( Vec2( 80, 450));
#else
	menu -> setPosition( Vec2( menuItem[Rotation] -> getContentSize().width * 2 + 5, MainScene::getWindowSize().height - menuItem[Rotation] -> getContentSize().height));
#endif
	addChild( menu);

	menuItem[Scale] = MenuItemImage::create( "Picture/ScaleIdleNormal.png", "Picture/ScaleIdleSelected.png", CC_CALLBACK_1( UILayer::menuScaleCallback, this));
	menu = Menu::create( menuItem[Scale], NULL);
#ifdef LITELAL_POS
	menu -> setPosition( Vec2( 130, 450));
#else
	menu -> setPosition( Vec2( menuItem[Scale] -> getContentSize().width * 3 + 10, MainScene::getWindowSize().height - menuItem[Scale] -> getContentSize().height));
#endif	
	addChild( menu);

	menuItem[PosX] = MenuItemImage::create( "Picture/X_IdleNormal.png", "Picture/X_IdleSelected.png", CC_CALLBACK_1( UILayer::menuXButtonCallback, this));
	menu = Menu::create( menuItem[PosX], NULL);
#ifdef LITELAL_POS
	menu -> setPosition( Vec2( 22, 405));
#else
	menu -> setPosition( Vec2( menuItem[PosX] -> getContentSize().width, MainScene::getWindowSize().height - menuItem[PosX] -> getContentSize().height * 2));	
#endif	
	addChild( menu);

	menuItem[PosY] = MenuItemImage::create( "Picture/Y_IdleNormal.png", "Picture/Y_IdleSelected.png", CC_CALLBACK_1( UILayer::menuYButtonCallback, this));
	menu = Menu::create( menuItem[PosY], NULL);
#ifdef LITELAL_POS
	menu -> setPosition( Vec2( 52, 405));
#else
	menu -> setPosition( Vec2( menuItem[PosY] -> getContentSize().width * 2 + 5, MainScene::getWindowSize().height - menuItem[PosY] -> getContentSize().height * 2));
#endif
	addChild( menu);

	menuItem[PosZ] = MenuItemImage::create( "Picture/Z_IdleNormal.png", "Picture/Z_IdleSelected.png", CC_CALLBACK_1( UILayer::menuZButtonCallback, this));
	menu = Menu::create( menuItem[PosZ], NULL);
#ifdef LITELAL_POS
	menu -> setPosition( Vec2( 82, 405));
#else
	menu -> setPosition( Vec2( menuItem[PosZ] -> getContentSize().width * 3 + 10, MainScene::getWindowSize().height - menuItem[PosZ] -> getContentSize().height * 2));
#endif
	addChild( menu);

	menuItem[Plus] = MenuItemImage::create( "Picture/PlusIdleNormal.png", "Picture/PlusIdleSelected.png", CC_CALLBACK_1( UILayer::menuPlusCallback, this));
	menu = Menu::create( menuItem[Plus], NULL);
#ifdef LITELAL_POS
	menu -> setPosition( Vec2( 65, 368));
#else
	// menu -> setPosition( Vec2( menuItem[Plus] -> getContentSize().width * 3 + 10, MainScene::getWindowSize().height - menuItem[Plus] -> getContentSize().height * 2));
#endif
	addChild( menu);

	menuItem[Minus] = MenuItemImage::create( "Picture/MinusIdleNormal.png", "Picture/MinusIdleSelected.png", CC_CALLBACK_1( UILayer::menuMinusCallback, this));
	menu = Menu::create( menuItem[Minus], NULL);
#ifdef LITELAL_POS
	menu -> setPosition( Vec2( 25, 368));
#else
	// menu -> setPosition( Vec2( menuItem[Minus] -> getContentSize().width * 3 + 10, MainScene::getWindowSize().height - menuItem[Minus] -> getContentSize().height));
#endif	
	addChild( menu);

	menuItem[NextFile] = MenuItemImage::create( "Picture/NextFileNormal.png", "Picture/NextFileSelected.png", CC_CALLBACK_1( UILayer::menuNextFileCallback, this));
	menu = Menu::create( menuItem[NextFile], NULL);
#ifdef LITELAL_POS
	menu -> setPosition( Vec2( 370, 38));
#else
	// menu -> setPosition( Vec2( menuItem[NextFile] -> getContentSize().width * 3 + 10, MainScene::getWindowSize().height - menuItem[NextFile] -> getContentSize().height));
#endif	
	addChild( menu);

	menuItem[PrevFile] = MenuItemImage::create( "Picture/PrevFileNormal.png", "Picture/PrevFileSelected.png", CC_CALLBACK_1( UILayer::menuPrevFileCallback, this));
	menu = Menu::create( menuItem[PrevFile], NULL);
#ifdef LITELAL_POS
	menu -> setPosition( Vec2( 270, 38));
#else
	menu -> setPosition( Vec2( menuItem[PrevFile] -> getContentSize().width * 3 + 10, MainScene::getWindowSize().height - menuItem[PrevFile] -> getContentSize().height));
#endif	
	addChild( menu);

	menuItem[Reload] = MenuItemImage::create( "Picture/FileReloadNormal.png", "Picture/FileReloadSelected.png", CC_CALLBACK_1( UILayer::menuModelReloadCallback, this));
	menu = Menu::create( menuItem[Reload], NULL);
#ifdef LITELAL_POS
	menu -> setPosition( Vec2( 320, 38));
#else
	menu -> setPosition( Vec2( menuItem[Reload] -> getContentSize().width * 3 + 10, MainScene::getWindowSize().height - menuItem[Reload] -> getContentSize().height));
#endif	
	addChild( menu);

	menuItem[Anime] = MenuItemImage::create( "Picture/AnimeStartNormal.png", "Picture/AnimeStartSelected.png", CC_CALLBACK_1( UILayer::menuModelAnimationCallback, this));
	menu = Menu::create( menuItem[Anime], NULL);
#ifdef LITELAL_POS
	menu -> setPosition( Vec2( 560, 38));
#else
	// menu -> setPosition( Vec2( menuItem[Anime] -> getContentSize().width * 3 + 10, MainScene::getWindowSize().height - menuItem[Anime] -> getContentSize().height));
#endif	
	addChild( menu);
}

void UILayer::menuMoveCallback( Ref* pSender)
{
	if( MainScene::checkFlag( &menuFlag, (unsigned short)MoveFlag))
	{
		menuItem[Move] -> setNormalImage( Sprite::create( "Picture/MoveIdleNormal.png"));
		menuItem[Move] -> setSelectedImage( Sprite::create( "Picture/MoveIdleSelected.png"));
		MainScene::resetFlag( &menuFlag, (unsigned short)MoveFlag);
	}
	else
	{
		menuItem[Move] -> setNormalImage( Sprite::create( "Picture/MoveActiveNormal.png"));
		menuItem[Move] -> setSelectedImage( Sprite::create( "Picture/MoveActiveSelected.png"));
		MainScene::setFlag( &menuFlag, (unsigned short)MoveFlag);
	}
	menuItem[Rotation] -> setNormalImage( Sprite::create( "Picture/RotationIdleNormal.png"));
	menuItem[Rotation] -> setSelectedImage( Sprite::create( "Picture/RotationIdleSelected.png"));
	MainScene::resetFlag( &menuFlag, (unsigned short)RotationFlag);

	menuItem[Scale] -> setNormalImage( Sprite::create( "Picture/ScaleIdleNormal.png"));
	menuItem[Scale] -> setSelectedImage( Sprite::create( "Picture/ScaleIdleSelected.png"));
	MainScene::resetFlag( &menuFlag, (unsigned short)ScaleFlag);
}

void UILayer::menuRotationCallback( Ref* pSender)
{
	if( MainScene::checkFlag( &menuFlag, (unsigned short)RotationFlag))
	{
		menuItem[Rotation] -> setNormalImage( Sprite::create( "Picture/RotationIdleNormal.png"));
		menuItem[Rotation] -> setSelectedImage( Sprite::create( "Picture/RotationIdleSelected.png"));
		MainScene::resetFlag( &menuFlag, (unsigned short)RotationFlag);
	}
	else
	{
		menuItem[Rotation] -> setNormalImage( Sprite::create( "Picture/RotationActiveNormal.png"));
		menuItem[Rotation] -> setSelectedImage( Sprite::create( "Picture/RotationActiveSelected.png"));
		MainScene::setFlag( &menuFlag, (unsigned short)RotationFlag);
	}
	menuItem[Move] -> setNormalImage( Sprite::create( "Picture/MoveIdleNormal.png"));
	menuItem[Move] -> setSelectedImage( Sprite::create( "Picture/MoveIdleSelected.png"));
	MainScene::resetFlag( &menuFlag, (unsigned short)MoveFlag);

	menuItem[Scale] -> setNormalImage( Sprite::create( "Picture/ScaleIdleNormal.png"));
	menuItem[Scale] -> setSelectedImage( Sprite::create( "Picture/ScaleIdleSelected.png"));
	MainScene::resetFlag( &menuFlag, (unsigned short)ScaleFlag);
}

void UILayer::menuScaleCallback( Ref* pSender)
{
	if( MainScene::checkFlag( &menuFlag, (unsigned short)ScaleFlag))
	{
		menuItem[Scale] -> setNormalImage( Sprite::create( "Picture/ScaleIdleNormal.png"));
		menuItem[Scale] -> setSelectedImage( Sprite::create( "Picture/ScaleIdleSelected.png"));
		MainScene::resetFlag( &menuFlag, (unsigned short)ScaleFlag);
	}
	else
	{
		menuItem[Scale] -> setNormalImage( Sprite::create( "Picture/ScaleActiveNormal.png"));
		menuItem[Scale] -> setSelectedImage( Sprite::create( "Picture/ScaleActiveSelected.png"));
		MainScene::setFlag( &menuFlag, (unsigned short)ScaleFlag);
	}
	menuItem[Move] -> setNormalImage( Sprite::create( "Picture/MoveIdleNormal.png"));
	menuItem[Move] -> setSelectedImage( Sprite::create( "Picture/MoveIdleSelected.png"));
	MainScene::resetFlag( &menuFlag, (unsigned short)MoveFlag);

	menuItem[Rotation] -> setNormalImage( Sprite::create( "Picture/RotationIdleNormal.png"));
	menuItem[Rotation] -> setSelectedImage( Sprite::create( "Picture/RotationIdleSelected.png"));
	MainScene::resetFlag( &menuFlag, (unsigned short)RotationFlag);
}

void UILayer::menuXButtonCallback( Ref* pSender)
{
	if( MainScene::checkFlag( &menuFlag, (unsigned short)XFlag))
	{
		menuItem[PosX] -> setNormalImage( Sprite::create( "Picture/X_IdleNormal.png"));
		menuItem[PosX] -> setSelectedImage( Sprite::create( "Picture/X_IdleSelected.png"));
		MainScene::resetFlag( &menuFlag, (unsigned short)XFlag);
	}
	else
	{
		menuItem[PosX] -> setNormalImage( Sprite::create( "Picture/X_ActiveNormal.png"));
		menuItem[PosX] -> setSelectedImage( Sprite::create( "Picture/X_ActiveSelected.png"));
		MainScene::setFlag( &menuFlag, (unsigned short)XFlag);
	}
}

void UILayer::menuYButtonCallback( Ref* pSender)
{
	if( MainScene::checkFlag( &menuFlag, (unsigned short)YFlag))
	{
		menuItem[PosY] -> setNormalImage( Sprite::create( "Picture/Y_IdleNormal.png"));
		menuItem[PosY] -> setSelectedImage( Sprite::create( "Picture/Y_IdleSelected.png"));
		MainScene::resetFlag( &menuFlag, (unsigned short)YFlag);
	}
	else
	{
		menuItem[PosY] -> setNormalImage( Sprite::create( "Picture/Y_ActiveNormal.png"));
		menuItem[PosY] -> setSelectedImage( Sprite::create( "Picture/Y_ActiveSelected.png"));
		MainScene::setFlag( &menuFlag, (unsigned short)YFlag);
	}
}

void UILayer::menuZButtonCallback( Ref* pSender)
{
	if( MainScene::checkFlag( &menuFlag, (unsigned short)ZFlag))
	{
		menuItem[PosZ] -> setNormalImage( Sprite::create( "Picture/Z_IdleNormal.png"));
		menuItem[PosZ] -> setSelectedImage( Sprite::create( "Picture/Z_IdleSelected.png"));
		MainScene::resetFlag( &menuFlag, (unsigned short)ZFlag);
	}
	else
	{
		menuItem[PosZ] -> setNormalImage( Sprite::create( "Picture/Z_ActiveNormal.png"));
		menuItem[PosZ] -> setSelectedImage( Sprite::create( "Picture/Z_ActiveSelected.png"));
		MainScene::setFlag( &menuFlag, (unsigned short)ZFlag);
	}
}

void UILayer::menuPlusCallback( Ref* pSender)
{
	if( MainScene::checkFlag( &menuFlag, (unsigned short)PlusFlag))
	{
		menuItem[Plus] -> setNormalImage( Sprite::create( "Picture/PlusIdleNormal.png"));
		menuItem[Plus] -> setSelectedImage( Sprite::create( "Picture/PlusIdleSelected.png"));
		MainScene::resetFlag( &menuFlag, (unsigned short)PlusFlag);
	}
	else
	{
		menuItem[Plus] -> setNormalImage( Sprite::create( "Picture/PlusActiveNormal.png"));
		menuItem[Plus] -> setSelectedImage( Sprite::create( "Picture/PlusActiveSelected.png"));
		MainScene::setFlag( &menuFlag, (unsigned short)PlusFlag);
	}
	menuItem[Minus] -> setNormalImage( Sprite::create( "Picture/MinusIdleNormal.png"));
	menuItem[Minus] -> setSelectedImage( Sprite::create( "Picture/MinusIdleSelected.png"));
	MainScene::resetFlag( &menuFlag, (unsigned short)MinusFlag);
}

void UILayer::menuMinusCallback( Ref* pSender)
{
	if( MainScene::checkFlag( &menuFlag, (unsigned short)MinusFlag))
	{
		menuItem[Minus] -> setNormalImage( Sprite::create( "Picture/MinusIdleNormal.png"));
		menuItem[Minus] -> setSelectedImage( Sprite::create( "Picture/MinusIdleSelected.png"));
		MainScene::resetFlag( &menuFlag, (unsigned short)MinusFlag);
	}
	else
	{
		menuItem[Minus] -> setNormalImage( Sprite::create( "Picture/MinusActiveNormal.png"));
		menuItem[Minus] -> setSelectedImage( Sprite::create( "Picture/MinusActiveSelected.png"));
		MainScene::setFlag( &menuFlag, (unsigned short)MinusFlag);
	}
	menuItem[Plus] -> setNormalImage( Sprite::create( "Picture/PlusIdleNormal.png"));
	menuItem[Plus] -> setSelectedImage( Sprite::create( "Picture/PlusIdleSelected.png"));
	MainScene::resetFlag( &menuFlag, (unsigned short)PlusFlag);
}

void UILayer::menuNextFileCallback( Ref* pSender)
{
	removeChild( sprite3D);
	sprite3D = fileInstance -> getModelData( 1);
	addChild( sprite3D);
	menuFlag = 0;
	removeChild( fileName);
	fileName = Label::createWithTTF( fileInstance -> getModelName(), "fonts/arial.ttf", 24);
	fileName -> setPosition( Vec2( MainScene::getWindowSize().width / 2, MainScene::getWindowSize().height - fileName -> getContentSize().height));
	addChild( fileName);
	menuAllReset();
}

void UILayer::menuPrevFileCallback( Ref* pSender)
{
	removeChild( sprite3D);
	sprite3D = fileInstance -> getModelData( -1);
	addChild( sprite3D);
	menuFlag = 0;
	removeChild( fileName);
	fileName = Label::createWithTTF( fileInstance -> getModelName(), "fonts/arial.ttf", 24);
	fileName -> setPosition( Vec2( MainScene::getWindowSize().width / 2, MainScene::getWindowSize().height - fileName -> getContentSize().height));
	addChild( fileName);
	menuAllReset();
}

void UILayer::menuModelReloadCallback( Ref* pSender)
{
	fileInstance -> reload3DModel();
}

void UILayer::menuModelAnimationCallback( Ref* pSender)
{
	if( MainScene::checkFlag( &menuFlag, (unsigned short)AnimeFlag))
	{
		menuItem[Anime] -> setNormalImage( Sprite::create( "Picture/AnimeStartNormal.png"));
		menuItem[Anime] -> setSelectedImage( Sprite::create( "Picture/AnimeStartSelected.png"));
		fileInstance -> stopModelAnime();
		MainScene::resetFlag( &menuFlag, (unsigned short)AnimeFlag);
	}
	else
	{
		menuItem[Anime] -> setNormalImage( Sprite::create( "Picture/AnimeStopNormal.png"));
		menuItem[Anime] -> setSelectedImage( Sprite::create( "Picture/AnimeStopSelected.png"));
		fileInstance -> startModelAnime();
		MainScene::setFlag( &menuFlag, (unsigned short)AnimeFlag);
	}
}

void UILayer::menuAllReset( void)
{
	menuFlag = 0;
	setPositionUI();
}