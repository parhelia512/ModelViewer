
#include "ErrorScene.h"
#include "LoadFile.h"
#include "MainScene.h"

USING_NS_CC;

int ErrorScene::errorCode;

Scene* ErrorScene::createScene( void)
{
	auto scene = Scene::create();
	auto layer = ErrorScene::create();
	scene -> addChild( layer);
	return scene;
}

bool ErrorScene::init()
{
	if ( !Layer::init() ) { return false; }

	auto closeItem = MenuItemImage::create( "Picture/FileReloadNormal.png", "Picture/FileReloadSelected.png", CC_CALLBACK_1( ErrorScene::menuResetCallback, this));
	closeItem -> setPosition( Vec2( MainScene::getWindowSize().width / 2 , MainScene::getWindowSize().width / 10));
	auto menu = Menu::create( closeItem, NULL);
	addChild( menu);

	switch( errorCode)
	{
	case LoadFile::ErrorCode::No_Conv_exe:
		MessageBox( "/ ��fbx-conv.exe������܂���", "�G���[ code 1");
		break;
	case LoadFile::ErrorCode::No_Model_Data:
		MessageBox( "/Model �ɓǂݍ��݉\�ȃ��f���f�[�^������܂���", "�G���[ code 2");
		break;
	default:
		MessageBox( "�s���ȃG���[���������܂���", "�G���[ code 0");
		break;
	}

	return true;
}

void ErrorScene::menuResetCallback( Ref* pSender) { Director::getInstance() -> replaceScene( MainScene::createScene()); }
	
void ErrorScene::setErrorCode( int errorCode) { ErrorScene::errorCode = errorCode; }
