
#include "MainScene.h"

USING_NS_CC;

Scene* Main::createScene()
{
	auto scene = Scene::create();
	auto layer = Main::create();
	scene -> addChild( layer);
	return scene;
}

bool Main::init()
{
	if ( !Layer::init()) { return false; }

	MenuFlags = 0;
	fileInstance = LoadFile::getInstance();
	visibleSize = Director::getInstance() -> getVisibleSize();
	origin = Director::getInstance() -> getVisibleOrigin();

	setMenuItem();
	setMenuSprite();

	fileInstance -> load3DModel();

	sprite = fileInstance -> getModelData( 0);
	addChild( sprite);
	label = Label::createWithTTF( fileInstance -> getModelName(), "fonts/arial.ttf", 24);
	label -> setPosition( Vec2( origin.x + visibleSize.width / 2,
							origin.y + visibleSize.height - label -> getContentSize().height));
	addChild( label); 

	for( auto &p : pointStatus) { p = Label::create(); addChild( p); }
	for( auto &p : rotationStatus) { p = Label::create(); addChild( p); }
	scaleStatus = Label::create(); addChild( scaleStatus);

	auto listener = EventListenerTouchOneByOne::create();
	listener -> setSwallowTouches( true);

	listener -> onTouchBegan = CC_CALLBACK_2( Main::onTouchBegan, this);
	listener -> onTouchMoved = CC_CALLBACK_2( Main::onTouchMoved, this);
	listener -> onTouchEnded = CC_CALLBACK_2( Main::onTouchEnded, this);
	listener -> onTouchCancelled = CC_CALLBACK_2( Main::onTouchCancelled, this);

	auto dip = Director::getInstance() -> getEventDispatcher();
	dip -> addEventListenerWithSceneGraphPriority( listener, this);

	auto s = Director::getInstance() -> getWinSize();
	auto camera = Camera::createOrthographic( s.width, s.height, 1, 1000);
	camera -> setPosition3D( Vec3( 0, 0, 500));
	camera -> lookAt( Vec3( 0, 0, 0), Vec3( 0, 0, -1));

	addChild( camera);

	scheduleUpdate();

	return true;
}

void Main::update( float delta)
{
	float scale;
	Vec3 velocity;
	Vec3 Angle;

	if( checkFlag( PushFlag) && checkFlag( MoveFlag))
	{
		if( checkFlag( PlusFlag))
		{
			if( checkFlag( XFlag)) { velocity.x = 1; }
			if( checkFlag( YFlag)) { velocity.y = 1; }
			if( checkFlag( ZFlag)) { velocity.z = 1; }
		}
		else if( checkFlag( MinusFlag))
		{
			if( checkFlag( XFlag)) { velocity.x = -1; }
			if( checkFlag( YFlag)) { velocity.y = -1; }
			if( checkFlag( ZFlag)) { velocity.z = -1; }
		}
		velocity = sprite -> getPosition3D() + velocity;
		sprite -> setPosition3D( velocity);
	}

	if( checkFlag( PushFlag) && checkFlag( RotationFlag))
	{
		if( checkFlag( PlusFlag))
		{
			if( checkFlag( XFlag)) { Angle.x = 1; }
			if( checkFlag( YFlag)) { Angle.y = 1; }
			if( checkFlag( ZFlag)) { Angle.z = 1; }
		}
		else if( checkFlag( MinusFlag))
		{
			if( checkFlag( XFlag)) { Angle.x = -1; }
			if( checkFlag( YFlag)) { Angle.y = -1; }
			if( checkFlag( ZFlag)) { Angle.z = -1; }
		}
		Angle = sprite -> getRotation3D() + Angle;
		sprite -> setRotation3D( Angle);
	}

	if( checkFlag( PushFlag) && checkFlag( ScaleFlag))
	{
		if( checkFlag( PlusFlag)) { scale = 1.0f; }
		else if( checkFlag( MinusFlag)) { scale = -1.0f; }
		scale = sprite -> getScale() + scale;
		sprite -> setScale( scale);
	}
	updateLabel();
}

void Main::updateLabel( void)
{
	const int fontSize = 18;
	removeChild( pointStatus[ParamX]);
	sprintf( spriteState, "Pos X:%3.1f", sprite -> getPositionX());
	pointStatus[ParamX] = Label::createWithTTF( spriteState, "fonts/arial.ttf", fontSize);
	pointStatus[ParamX] -> setPosition( Vec2( origin.x + visibleSize.width - pointStatus[ParamX] -> getContentSize().width / 2,
							origin.y + visibleSize.height - pointStatus[ParamX] -> getContentSize().height));
	addChild( pointStatus[ParamX]);

	removeChild( pointStatus[ParamY]);
	sprintf( spriteState, "Y:%3.1f", sprite -> getPositionY());
	pointStatus[ParamY] = Label::createWithTTF( spriteState, "fonts/arial.ttf", fontSize);
	pointStatus[ParamY] -> setPosition( Vec2( origin.x + visibleSize.width - pointStatus[ParamY] -> getContentSize().width / 2,
							origin.y + visibleSize.height - pointStatus[ParamY] -> getContentSize().height * 2));
	addChild( pointStatus[ParamY]);

	removeChild( pointStatus[ParamZ]);
	sprintf( spriteState, "Z:%3.1f", sprite -> getPositionZ());
	pointStatus[ParamZ] = Label::createWithTTF( spriteState, "fonts/arial.ttf", fontSize);
	pointStatus[ParamZ] -> setPosition( Vec2( origin.x + visibleSize.width - pointStatus[ParamZ] -> getContentSize().width / 2,
							origin.y + visibleSize.height - pointStatus[ParamZ] -> getContentSize().height * 3));
	addChild( pointStatus[ParamZ]);

	removeChild( rotationStatus[ParamX]);
	sprintf( spriteState, "Rot X:%3.1f", sprite -> getRotation3D().x);
	rotationStatus[ParamX] = Label::createWithTTF( spriteState, "fonts/arial.ttf", fontSize);
	rotationStatus[ParamX] -> setPosition( Vec2( origin.x + visibleSize.width - rotationStatus[ParamX] -> getContentSize().width / 2,
							origin.y + visibleSize.height - rotationStatus[ParamX] -> getContentSize().height * 4));
	addChild( rotationStatus[ParamX]);

	removeChild( rotationStatus[ParamY]);
	sprintf( spriteState, "Y:%3.1f", sprite -> getRotation3D().y);
	rotationStatus[ParamY] = Label::createWithTTF( spriteState, "fonts/arial.ttf", fontSize);
	rotationStatus[ParamY] -> setPosition( Vec2( origin.x + visibleSize.width - rotationStatus[ParamY] -> getContentSize().width / 2,
							origin.y + visibleSize.height - rotationStatus[ParamY] -> getContentSize().height * 5));
	addChild( rotationStatus[ParamY]);

	removeChild( rotationStatus[ParamZ]);
	sprintf( spriteState, "Z:%3.1f", sprite -> getRotation3D().z);
	rotationStatus[ParamZ] = Label::createWithTTF( spriteState, "fonts/arial.ttf", fontSize);
	rotationStatus[ParamZ] -> setPosition( Vec2( origin.x + visibleSize.width - rotationStatus[ParamZ] -> getContentSize().width / 2,
							origin.y + visibleSize.height - rotationStatus[ParamZ] -> getContentSize().height * 6));
	addChild( rotationStatus[ParamZ]);

	removeChild( scaleStatus);
	sprintf( spriteState, "Sca :%3.1f", sprite -> getScale());
	scaleStatus = Label::createWithTTF( spriteState, "fonts/arial.ttf", fontSize);
	scaleStatus -> setPosition( Vec2( origin.x + visibleSize.width - scaleStatus -> getContentSize().width / 2,
							origin.y + visibleSize.height - scaleStatus -> getContentSize().height * 7));
	addChild( scaleStatus);
}

bool Main::onTouchBegan( Touch* touch,Event* event)
{
	touchStart = touch -> getLocation();
	setFlag( PushFlag);
	return true;
}

void Main::onTouchMoved( Touch* touch, Event* event)
{
	nowPoint = touch -> getLocation();
}

void Main::onTouchEnded( Touch* touch, Event* event)
{
	resetFlag( PushFlag);
}

void Main::onTouchCancelled( Touch* touch, Event* event)
{

}

void Main::setMenuSprite( void)
{
	for( auto &p : menuItem)
	{
		menu = Menu::create( p, NULL);
		menu -> setPosition( Vec2::ZERO);
		addChild( menu);
	}
}

void Main::resetMenuSprite( int number)
{
	removeChild( menuItem[number]);
	menu = Menu::create( menuItem[number], NULL);
	menu -> setPosition( Vec2::ZERO);
	addChild( menu);
}

void Main::setMenuItem( void)
{
	menuItem[0] = MenuItemImage::create( "Picture/MoveIdleNormal.png", "Picture/MoveIdleSelected.png",
											CC_CALLBACK_1( Main::menuMoveCallback, this));
	menuItem[0] -> setPosition( Vec2( 30, 450));

	menuItem[1] = MenuItemImage::create( "Picture/RotationIdleNormal.png", "Picture/RotationIdleSelected.png",
											CC_CALLBACK_1( Main::menuRotationCallback, this));
	menuItem[1] -> setPosition( Vec2( 80, 450));

	menuItem[2] = MenuItemImage::create( "Picture/ScaleIdleNormal.png", "Picture/ScaleIdleSelected.png",
												CC_CALLBACK_1( Main::menuScaleCallback, this));
	menuItem[2] -> setPosition( Vec2( 130, 450));

	menuItem[3] = MenuItemImage::create( "Picture/X_IdleNormal.png", "Picture/X_IdleSelected.png",
												CC_CALLBACK_1( Main::menuXButtonCallback, this));
	menuItem[3] -> setPosition( Vec2( 22, 405));

	menuItem[4] = MenuItemImage::create( "Picture/Y_IdleNormal.png", "Picture/Y_IdleSelected.png",
												CC_CALLBACK_1( Main::menuYButtonCallback, this));
	menuItem[4] -> setPosition( Vec2( 52, 405));

	menuItem[5] = MenuItemImage::create( "Picture/Z_IdleNormal.png", "Picture/Z_IdleSelected.png",
												CC_CALLBACK_1( Main::menuZButtonCallback, this));
	menuItem[5] -> setPosition( Vec2( 82, 405));

	menuItem[6] = MenuItemImage::create( "Picture/PlusIdleNormal.png", "Picture/PlusIdleSelected.png",
												CC_CALLBACK_1( Main::menuPlusButtonCallback, this));
	menuItem[6] -> setPosition( Vec2( 65, 368));

	menuItem[7] = MenuItemImage::create( "Picture/MinusIdleNormal.png", "Picture/MinusIdleSelected.png",
												CC_CALLBACK_1( Main::menuMinusButtonCallback, this));
	menuItem[7] -> setPosition( Vec2( 25, 368));

	menuItem[8] = MenuItemImage::create( "Picture/AnimeStartNormal.png", "Picture/AnimeStartSelected.png",
												CC_CALLBACK_1( Main::menuModelAnimationCallback, this));
	menuItem[8] -> setPosition( Vec2( 560, 38));

	menuItem[9] = MenuItemImage::create( "Picture/FileReloadNormal.png", "Picture/FileReloadSelected.png",
												CC_CALLBACK_1( Main::menuModelReloadCallback, this));
	menuItem[9] -> setPosition( Vec2( 320, 38));

	menuItem[10] = MenuItemImage::create( "Picture/NextFileNormal.png", "Picture/NextFileSelected.png",
												CC_CALLBACK_1( Main::menuNextFileCallback, this));
	menuItem[10] -> setPosition( Vec2( 370, 38));

	menuItem[11] = MenuItemImage::create( "Picture/PrevFileNormal.png", "Picture/PrevFileSelected.png",
												CC_CALLBACK_1( Main::menuPrevFileCallback, this));
	menuItem[11] -> setPosition( Vec2( 270, 38));
}

void Main::menuMoveCallback( Ref* pSender)
{
	if( checkFlag( MoveFlag))
	{
		menuItem[0] = MenuItemImage::create( "Picture/MoveIdleNormal.png", "Picture/MoveIdleSelected.png",
												CC_CALLBACK_1( Main::menuMoveCallback, this));
		menuItem[0] -> setPosition( Vec2( 30, 450));
		resetMenuSprite( 0);
		resetFlag( MoveFlag);
	}
	else
	{
		menuItem[0] = MenuItemImage::create( "Picture/MoveActiveNormal.png", "Picture/MoveActiveSelected.png",
												CC_CALLBACK_1( Main::menuMoveCallback, this));
		menuItem[0] -> setPosition( Vec2( 30, 450));
		resetMenuSprite( 0);
		setFlag( MoveFlag);
	}

	menuItem[1] = MenuItemImage::create( "Picture/RotationIdleNormal.png", "Picture/RotationIdleSelected.png",
											CC_CALLBACK_1( Main::menuRotationCallback, this));
	menuItem[1] -> setPosition( Vec2( 80, 450));
	resetMenuSprite( 1);
	resetFlag( RotationFlag);

	menuItem[2] = MenuItemImage::create( "Picture/ScaleIdleNormal.png", "Picture/ScaleIdleSelected.png",
												CC_CALLBACK_1( Main::menuScaleCallback, this));
	menuItem[2] -> setPosition( Vec2( 130, 450));
	resetMenuSprite( 2);
	resetFlag( ScaleFlag);
}

void Main::menuRotationCallback( Ref* pSender)
{
	if( checkFlag( RotationFlag))
	{
		menuItem[1] = MenuItemImage::create( "Picture/RotationIdleNormal.png", "Picture/RotationIdleSelected.png",
												CC_CALLBACK_1( Main::menuRotationCallback, this));
		menuItem[1] -> setPosition( Vec2( 80, 450));
		resetMenuSprite( 1);
		resetFlag( RotationFlag);
	}
	else
	{
		menuItem[1] = MenuItemImage::create( "Picture/RotationActiveNormal.png", "Picture/RotationActiveSelected.png",
												CC_CALLBACK_1( Main::menuRotationCallback, this));
		menuItem[1] -> setPosition( Vec2( 80, 450));
		resetMenuSprite( 1);
		setFlag( RotationFlag);
	}

	menuItem[0] = MenuItemImage::create( "Picture/MoveIdleNormal.png", "Picture/MoveIdleSelected.png",
											CC_CALLBACK_1( Main::menuMoveCallback, this));
	menuItem[0] -> setPosition( Vec2( 30, 450));
	resetMenuSprite( 0);
	resetFlag( MoveFlag);

	menuItem[2] = MenuItemImage::create( "Picture/ScaleIdleNormal.png", "Picture/ScaleIdleSelected.png",
												CC_CALLBACK_1( Main::menuScaleCallback, this));
	menuItem[2] -> setPosition( Vec2( 130, 450));
	resetMenuSprite( 2);
	resetFlag( ScaleFlag);
}

void Main::menuScaleCallback( Ref* pSender)
{
	if( checkFlag( ScaleFlag))
	{
		menuItem[2] = MenuItemImage::create( "Picture/ScaleIdleNormal.png", "Picture/ScaleIdleSelected.png",
												CC_CALLBACK_1( Main::menuScaleCallback, this));
		menuItem[2] -> setPosition( Vec2( 130, 450));
		resetMenuSprite( 2);
		resetFlag( ScaleFlag);
	}
	else
	{
		menuItem[2] = MenuItemImage::create( "Picture/ScaleActiveNormal.png", "Picture/ScaleActiveSelected.png",
												CC_CALLBACK_1( Main::menuScaleCallback, this));
		menuItem[2] -> setPosition( Vec2( 130, 450));
		resetMenuSprite( 2);
		setFlag( ScaleFlag);
	}


	menuItem[0] = MenuItemImage::create( "Picture/MoveIdleNormal.png", "Picture/MoveIdleSelected.png",
											CC_CALLBACK_1( Main::menuMoveCallback, this));
	menuItem[0] -> setPosition( Vec2( 30, 450));
	resetMenuSprite( 0);
	resetFlag( MoveFlag);

	menuItem[1] = MenuItemImage::create( "Picture/RotationIdleNormal.png", "Picture/RotationIdleSelected.png",
												CC_CALLBACK_1( Main::menuRotationCallback, this));
	menuItem[1] -> setPosition( Vec2( 80, 450));
	resetMenuSprite( 1);
	resetFlag( RotationFlag);
}

void Main::menuXButtonCallback( Ref* pSender)
{
	if( checkFlag( XFlag))
	{
		menuItem[3] = MenuItemImage::create( "Picture/X_IdleNormal.png", "Picture/X_IdleSelected.png",
												CC_CALLBACK_1( Main::menuXButtonCallback, this));
		menuItem[3] -> setPosition( Vec2( 22, 405));
		resetMenuSprite( 3);
		resetFlag( XFlag);
	}
	else
	{
		menuItem[3] = MenuItemImage::create( "Picture/X_ActiveNormal.png", "Picture/X_ActiveSelected.png",
												CC_CALLBACK_1( Main::menuXButtonCallback, this));
		menuItem[3] -> setPosition( Vec2( 22, 405));
		resetMenuSprite( 3);
		setFlag( XFlag);
	}
}

void Main::menuYButtonCallback( Ref* pSender)
{
	if( checkFlag( YFlag))
	{
		menuItem[4] = MenuItemImage::create( "Picture/Y_IdleNormal.png", "Picture/Y_IdleSelected.png",
												CC_CALLBACK_1( Main::menuYButtonCallback, this));
		menuItem[4] -> setPosition( Vec2( 52, 405));
		resetMenuSprite( 4);
		resetFlag( YFlag);
	}
	else
	{
		menuItem[4] = MenuItemImage::create( "Picture/Y_ActiveNormal.png", "Picture/Y_ActiveSelected.png",
												CC_CALLBACK_1( Main::menuYButtonCallback, this));
		menuItem[4] -> setPosition( Vec2( 52, 405));
		resetMenuSprite( 4);
		setFlag( YFlag);
	}
}

void Main::menuZButtonCallback( Ref* pSender)
{
	if( checkFlag( ZFlag))
	{
		menuItem[5] = MenuItemImage::create( "Picture/Z_IdleNormal.png", "Picture/Z_IdleSelected.png",
												CC_CALLBACK_1( Main::menuZButtonCallback, this));
		menuItem[5] -> setPosition( Vec2( 82, 405));
		resetMenuSprite( 5);
		resetFlag( ZFlag);
	}
	else
	{
		menuItem[5] = MenuItemImage::create( "Picture/Z_ActiveNormal.png", "Picture/Z_ActiveSelected.png",
												CC_CALLBACK_1( Main::menuZButtonCallback, this));
		menuItem[5] -> setPosition( Vec2( 82, 405));
		resetMenuSprite( 5);
		setFlag( ZFlag);
	}
}

void Main::menuPlusButtonCallback( Ref* pSender)
{
	if( checkFlag( PlusFlag))
	{
		menuItem[6] = MenuItemImage::create( "Picture/PlusIdleNormal.png", "Picture/PlusIdleSelected.png",
												CC_CALLBACK_1( Main::menuPlusButtonCallback, this));
		menuItem[6] -> setPosition( Vec2( 65, 368));
		resetMenuSprite( 6);
		resetFlag( PlusFlag);
	}
	else
	{
		menuItem[6] = MenuItemImage::create( "Picture/PlusActiveNormal.png", "Picture/PlusActiveSelected.png",
												CC_CALLBACK_1( Main::menuPlusButtonCallback, this));
		menuItem[6] -> setPosition( Vec2( 65, 368));
		resetMenuSprite( 6);
		setFlag( PlusFlag);
	}

	menuItem[7] = MenuItemImage::create( "Picture/MinusIdleNormal.png", "Picture/MinusIdleSelected.png",
											CC_CALLBACK_1( Main::menuMinusButtonCallback, this));
	menuItem[7] -> setPosition( Vec2( 25, 368));
	resetMenuSprite( 7);
	resetFlag( MinusFlag);
}

void Main::menuMinusButtonCallback( Ref* pSender)
{
	if( checkFlag( MinusFlag))
	{
		menuItem[7] = MenuItemImage::create( "Picture/MinusIdleNormal.png", "Picture/MinusIdleSelected.png",
												CC_CALLBACK_1( Main::menuMinusButtonCallback, this));
		menuItem[7] -> setPosition( Vec2( 25, 368));
		resetMenuSprite( 7);
		resetFlag( MinusFlag);
	}
	else
	{
		menuItem[7] = MenuItemImage::create( "Picture/MinusActiveNormal.png", "Picture/MinusActiveSelected.png",
												CC_CALLBACK_1( Main::menuMinusButtonCallback, this));
		menuItem[7] -> setPosition( Vec2( 25, 368));
		resetMenuSprite( 7);
		setFlag( MinusFlag);
	}

	menuItem[6] = MenuItemImage::create( "Picture/PlusIdleNormal.png", "Picture/PlusIdleSelected.png",
											CC_CALLBACK_1( Main::menuPlusButtonCallback, this));
	menuItem[6] -> setPosition( Vec2( 65, 368));
	resetMenuSprite( 6);
	resetFlag( PlusFlag);
}

void Main::menuNextFileCallback( Ref* pSender)
{
	removeChild( sprite);
	sprite = fileInstance -> getModelData( 1);
	addChild( sprite);
	MenuFlags = 0;
	removeChild( label);
	label = Label::createWithTTF( fileInstance -> getModelName(), "fonts/arial.ttf", 24);
	label -> setPosition( Vec2( origin.x + visibleSize.width/2,
							origin.y + visibleSize.height - label->getContentSize().height));
	addChild( label);
	menuAllReset();
}

void Main::menuPrevFileCallback( Ref* pSender)
{
	removeChild( sprite);
	sprite = fileInstance -> getModelData( -1);
	addChild( sprite);
	MenuFlags = 0;
	removeChild( label);
	label = Label::createWithTTF( fileInstance -> getModelName(), "fonts/arial.ttf", 24);
	label -> setPosition( Vec2( origin.x + visibleSize.width/2,
							origin.y + visibleSize.height - label->getContentSize().height));
	addChild( label);
	menuAllReset();
}

void Main::menuModelReloadCallback( Ref* pSender)
{
	fileInstance -> reload3DModel();
}

void Main::menuModelAnimationCallback( Ref* pSender)
{
	if( checkFlag( AnimeFlag))
	{
		menuItem[8] = MenuItemImage::create( "Picture/AnimeStartNormal.png", "Picture/AnimeStartSelected.png",
												CC_CALLBACK_1( Main::menuModelAnimationCallback, this));
		menuItem[8] -> setPosition( Vec2( 560, 38));
		resetMenuSprite( 8);
		fileInstance -> stopModelAnime();
		resetFlag( AnimeFlag);
	}
	else
	{
		menuItem[8] = MenuItemImage::create( "Picture/AnimeStopNormal.png", "Picture/AnimeStopSelected.png",
												CC_CALLBACK_1( Main::menuModelAnimationCallback, this));
		menuItem[8] -> setPosition( Vec2( 560, 38));
		resetMenuSprite( 8);
		fileInstance -> startModelAnime();
		setFlag( AnimeFlag);
	}
}

bool Main::checkFlag( unsigned short flag)
{
	return ( ( MenuFlags & flag) != 0);
}

void Main::setFlag( unsigned short flag)
{
	MenuFlags |= flag;
}

void Main::resetFlag( unsigned short flag)
{
	MenuFlags &= ~flag;
}

void Main::menuAllReset( void)
{
	menuItem[0] = MenuItemImage::create( "Picture/MoveIdleNormal.png", "Picture/MoveIdleSelected.png",
											CC_CALLBACK_1( Main::menuMoveCallback, this));
	menuItem[0] -> setPosition( Vec2( 30, 450));
	resetMenuSprite( 0);
	resetFlag( MoveFlag);

	menuItem[1] = MenuItemImage::create( "Picture/RotationIdleNormal.png", "Picture/RotationIdleSelected.png",
											CC_CALLBACK_1( Main::menuRotationCallback, this));
	menuItem[1] -> setPosition( Vec2( 80, 450));
	resetMenuSprite( 1);
	resetFlag( RotationFlag);

	menuItem[2] = MenuItemImage::create( "Picture/ScaleIdleNormal.png", "Picture/ScaleIdleSelected.png",
												CC_CALLBACK_1( Main::menuScaleCallback, this));
	menuItem[2] -> setPosition( Vec2( 130, 450));
	resetMenuSprite( 2);
	resetFlag( ScaleFlag);

	menuItem[3] = MenuItemImage::create( "Picture/X_IdleNormal.png", "Picture/X_IdleSelected.png",
												CC_CALLBACK_1( Main::menuXButtonCallback, this));
	menuItem[3] -> setPosition( Vec2( 22, 405));
	resetMenuSprite( 3);
	resetFlag( XFlag);

	menuItem[4] = MenuItemImage::create( "Picture/Y_IdleNormal.png", "Picture/Y_IdleSelected.png",
	CC_CALLBACK_1( Main::menuYButtonCallback, this));
	menuItem[4] -> setPosition( Vec2( 52, 405));
	resetMenuSprite( 4);
	resetFlag( YFlag);

	menuItem[5] = MenuItemImage::create( "Picture/Z_IdleNormal.png", "Picture/Z_IdleSelected.png",
	CC_CALLBACK_1( Main::menuZButtonCallback, this));
	menuItem[5] -> setPosition( Vec2( 82, 405));
	resetMenuSprite( 5);
	resetFlag( ZFlag);

	menuItem[6] = MenuItemImage::create( "Picture/PlusIdleNormal.png", "Picture/PlusIdleSelected.png",
	CC_CALLBACK_1( Main::menuPlusButtonCallback, this));
	menuItem[6] -> setPosition( Vec2( 65, 368));
	resetMenuSprite( 6);
	resetFlag( PlusFlag);

	menuItem[7] = MenuItemImage::create( "Picture/MinusIdleNormal.png", "Picture/MinusIdleSelected.png",
	CC_CALLBACK_1( Main::menuMinusButtonCallback, this));
	menuItem[7] -> setPosition( Vec2( 25, 368));
	resetMenuSprite( 7);
	resetFlag( MinusFlag);

	menuItem[8] = MenuItemImage::create( "Picture/AnimeStartNormal.png", "Picture/AnimeStartSelected.png",
												CC_CALLBACK_1( Main::menuModelAnimationCallback, this));
	menuItem[8] -> setPosition( Vec2( 560, 38));
	resetMenuSprite( 8);
	fileInstance -> stopModelAnime();
	resetFlag( AnimeFlag);
}
