
#ifndef  _ERROR_SCENE_H_
#define  _ERROR_SCENE_H_

#include "cocos2d.h"

class ErrorScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene( void);
	static void setErrorCode( int errorCode);

	virtual bool init( void);
	CREATE_FUNC( ErrorScene);

	void menuResetCallback( cocos2d::Ref* pSender);

private:
	static int errorCode;
};

#endif