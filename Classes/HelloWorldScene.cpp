
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene -> addChild( layer);
	return scene;
}

bool HelloWorld::init()
{
	if ( !Layer::init()) { return false; }
	
	Size visibleSize = Director::getInstance() -> getVisibleSize();
	Vec2 origin = Director::getInstance() -> getVisibleOrigin();

	auto closeItem = MenuItemImage::create( "Picture/CloseNormal.png", "Picture/CloseSelected.png",
										   CC_CALLBACK_1( HelloWorld::menuCloseCallback, this));
	
	closeItem -> setPosition( Vec2( origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
								origin.y + closeItem->getContentSize().height/2));

	auto menu = Menu::create( closeItem, NULL);
	menu->setPosition( Vec2::ZERO);
	this -> addChild( menu, 100);

	auto label = Label::createWithTTF( "Hello World", "fonts/arial.ttf", 24);
	
	label -> setPosition( Vec2( origin.x + visibleSize.width/2,
							origin.y + visibleSize.height - label->getContentSize().height));
	this -> addChild( label, 100);

	fileInstance = LoadFile::getInstance();
	fileInstance -> load3DModel();
	sprite = fileInstance -> getModelData( 0);
	addChild( sprite, 0);
	
//	removeChild( sprite);
	return true;
}

void HelloWorld::setMenuSprite( void)
{

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	removeChild( sprite);
	fileInstance -> reload3DModel();
	sprite = fileInstance -> getModelData( 1);
	addChild( sprite, 0);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	//Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void menuMoveCallback( cocos2d::Ref* pSender)
{

}

void menuRotationCallback( cocos2d::Ref* pSender)
{

}

void menuScaleCallback( cocos2d::Ref* pSender)
{

}

void menuXButtonCallback( cocos2d::Ref* pSender)
{

}

void menuYButtonCallback( cocos2d::Ref* pSender)
{

}

void menuZButtonCallback( cocos2d::Ref* pSender)
{

}

void menuNextFileCallback( cocos2d::Ref* pSender)
{

}

void menuPrevFileCallback( cocos2d::Ref* pSender)
{

}

void menuModelReloadCallback( cocos2d::Ref* pSender)
{

}

void menuModelAnimationCallback( cocos2d::Ref* pSender)
{

}

void menuCloseCallback( cocos2d::Ref* pSender)
{

}

