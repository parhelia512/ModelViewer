
#include "AppDelegate.h"
#include "MainScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {}
AppDelegate::~AppDelegate() {}

void AppDelegate::initGLContextAttrs() 
{
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 16, 8 };
	GLView::setGLContextAttrs( glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() 
{
	auto director = Director::getInstance();
	auto glview = director -> getOpenGLView();

	if( !glview) 
	{
		glview = GLViewImpl::create( "ModelViewer");
		director -> setOpenGLView( glview);
	}

	glview -> setDesignResolutionSize( 640, 480, ResolutionPolicy::SHOW_ALL);
	glview -> setFrameSize( 640, 480);

	director -> setDisplayStats( true);
	director -> setAnimationInterval( 1.0 / 60);

	auto scene = MainScene::createScene();
	director -> runWithScene( scene);

	return true;
}

void AppDelegate::applicationDidEnterBackground() { Director::getInstance()->stopAnimation(); }
void AppDelegate::applicationWillEnterForeground() { Director::getInstance()->startAnimation(); }
