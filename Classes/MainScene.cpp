
#include "ErrorScene.h"
#include "MainScene.h"
#include "UILayer.h"

USING_NS_CC;

Size MainScene::windowSize;

Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	scene -> addChild( MainScene::create());
	return scene;
}

bool MainScene::init()
{
	if ( !Layer::init() ) { return false; }

	windowSize = Director::getInstance() -> getVisibleSize();
	fileInstance = LoadFile::getInstance();

	auto errorCode = fileInstance -> load3DModel();

	switch( errorCode)
	{
	case LoadFile::ErrorCode::No_Conv_exe:
	case LoadFile::ErrorCode::No_Model_Data:
		ErrorScene::setErrorCode( errorCode);
		Director::getInstance() -> replaceScene( ErrorScene::createScene());
		break;
	default:
		addChild( UILayer::create());
		break;
	}
	return true;
}

Size MainScene::getWindowSize( void) { return windowSize; }

template<class P> bool MainScene::checkFlag( P* flag, const P number) { return ( ( *flag & number) != 0); }

template<class P> void MainScene::setFlag( P* flag, const P number) { *flag |= number; }

template<class P> void MainScene::resetFlag( P* flag, const P number) { *flag &= ~number; }

template bool MainScene::checkFlag( unsigned char* a, const unsigned char b);
template void MainScene::setFlag( unsigned char* a, const unsigned char b);
template void MainScene::resetFlag( unsigned char* a, const unsigned char b);

template bool MainScene::checkFlag( unsigned short* a, const unsigned short b);
template void MainScene::setFlag( unsigned short* a, const unsigned short b);
template void MainScene::resetFlag( unsigned short* a, const unsigned short b);