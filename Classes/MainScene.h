
#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "LoadFile.h"

class MainScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene( void);
	static cocos2d::Size getWindowSize( void);

	virtual bool init( void);
	CREATE_FUNC( MainScene);

	template<class P> static bool checkFlag( P* flag, const P number);
	template<class P> static void setFlag( P* flag, const P number);
	template<class P> static void resetFlag( P* flag, const P number);

private:
	static cocos2d::Size windowSize;

	LoadFile* fileInstance;
};

#endif // __MAIN_SCENE_H__
