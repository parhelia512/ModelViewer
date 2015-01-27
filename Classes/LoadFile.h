
#ifndef  _LOAD_FILE_H_
#define  _LOAD_FILE_H_

#include "cocos2d.h"

class LoadFile
{
public:
	LoadFile( const LoadFile& p) = delete;
	LoadFile& operator=( const LoadFile& P) = delete;
	static LoadFile* getInstance( void);
	void load3DModel( void);
	void reload3DModel( void);
	cocos2d::Sprite3D* getModelData( int searchCount);
	std::string getModelName( void);
	void startModelAnime( void);
	void stopModelAnime( void);
	int getModelCount( void);

private:
	LoadFile();

	int loadFileCount;
	cocos2d::FileUtils* file;

	std::string programPath;
	std::string modelDirPath;
	std::string searchFilePath;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
#endif
	cocos2d::Animate3D* animate;

	std::vector <std::string> loadModelName;
	cocos2d::Map <std::string, cocos2d::Sprite3D*> loadModelData;
	cocos2d::Map <std::string, cocos2d::Animate3D*> loadModelAnimate;
};

#endif // _LOAD_FILE_H_