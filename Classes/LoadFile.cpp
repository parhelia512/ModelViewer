
#include "LoadFile.h"

USING_NS_CC;
using namespace std;

LoadFile::LoadFile()
{ 
	loadFileCount = 0; 
	file = cocos2d::FileUtils::getInstance(); 
}

LoadFile* LoadFile::getInstance( void)
{
	static LoadFile* P;
	if( !P)	{ P = new LoadFile; }
	return P;
}

int LoadFile::load3DModel( void)
{
	programPath = file -> fullPathForFilename( "fbx-conv.exe");

	if( programPath == "") { return No_Conv_exe; }

	modelDirPath = programPath;
	int point = modelDirPath.rfind( '/', modelDirPath.size());
	modelDirPath.erase( modelDirPath.size() - ( modelDirPath.size() - point), modelDirPath.size());
	modelDirPath = modelDirPath + "/Model/";

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	searchFilePath = modelDirPath + "*.FBX";

	if(( hFind = FindFirstFile( searchFilePath.c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			string fileName = FindFileData.cFileName;
			string command = programPath + " -t " + modelDirPath + fileName;
			system( command.c_str());
			int point = fileName.rfind( '.', fileName.size());
			fileName.erase( fileName.size() - ( fileName.size() - point), fileName.size());
			fileName = fileName + ".c3t";
			string loadPath = "Model/" + fileName;
			auto sprite = Sprite3D::create( loadPath);
			if( sprite != nullptr) 
			{ 
				loadModelData.insert( fileName, sprite); 
				auto animation = Animation3D::create( loadPath);
				if( animation != nullptr)
				{
					animate = Animate3D::create( animation);
					loadModelAnimate.insert( fileName, animate);
				}
				string filePath = modelDirPath + fileName;
				DeleteFile( filePath.c_str());
			}
		} while( FindNextFile(hFind, &FindFileData));
		loadModelName = loadModelData.keys();
		FindClose(hFind);
		return 0;
	}
	searchFilePath = modelDirPath + "*.obj";
	loadCocosModel();

	searchFilePath = modelDirPath + "*.c3b";
	loadCocosModel();

	searchFilePath = modelDirPath + "*.c3t";
	loadCocosModel();

	if( loadModelData.size() == 0) { return No_Model_Data; }
#endif
}

void LoadFile::loadCocosModel( void)
{
	if(( hFind = FindFirstFile( searchFilePath.c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			string fileName = FindFileData.cFileName;
			string loadPath = "Model/" + fileName;
			auto sprite = Sprite3D::create( loadPath);
			if( sprite != nullptr) 
			{ 
				loadModelData.insert( fileName, sprite); 
				auto animation = Animation3D::create( loadPath);
				if( animation != nullptr)
				{
					animate = Animate3D::create( animation);
					loadModelAnimate.insert( fileName, animate);
				}
			}
		} while( FindNextFile(hFind, &FindFileData));
		loadModelName = loadModelData.keys();
		FindClose(hFind);
	}
}


void LoadFile::reload3DModel( void)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	searchFilePath = modelDirPath + "*.FBX";
	hFind = FindFirstFile( searchFilePath.c_str(), &FindFileData);
	do
	{
		string fileName = FindFileData.cFileName;
		string filePath = modelDirPath + fileName;
		string command = programPath + " -t " + filePath;
		int point = fileName.rfind( '.', fileName.size());
		fileName.erase( fileName.size() - ( fileName.size() - point), fileName.size());
		fileName = fileName + ".c3t";
		if( loadModelData.at( fileName) == nullptr)
		{
			system( command.c_str());
			string loadPath = "Model/" + fileName;
			auto sprite = Sprite3D::create( loadPath);
			loadModelData.insert( fileName, sprite);
			filePath = modelDirPath + fileName;
			DeleteFile( filePath.c_str());
		}
	} while( FindNextFile(hFind, &FindFileData));
	loadModelName = loadModelData.keys();
	FindClose(hFind);

	searchFilePath = modelDirPath + "*.obj";
	loadCocosModel();

	searchFilePath = modelDirPath + "*.c3b";
	loadCocosModel();

	searchFilePath = modelDirPath + "*.c3t";
	loadCocosModel();
#endif
}

Sprite3D* LoadFile::getModelData( int searchCount)
{
	loadFileCount += searchCount;
	if( loadFileCount < 0) { loadFileCount = loadModelName.size() - 1; }
	else if( loadFileCount == loadModelName.size()) { loadFileCount = 0; }

	auto sprite = loadModelData.at( loadModelName[loadFileCount]);
	sprite -> setPosition3D( Vec3( 320, 200, -5));
	sprite -> setRotation3D( Vec3( 0, 0, 0));
	sprite -> setScale( 100.0f);
	return sprite;
}

void LoadFile::startModelAnime( void)
{
	auto sprite = loadModelData.at( loadModelName[loadFileCount]);
	animate = loadModelAnimate.at( loadModelName[loadFileCount]);
	if( animate != nullptr) { sprite -> runAction( RepeatForever::create( animate)); }
}

void LoadFile::stopModelAnime( void)
{
	auto sprite = loadModelData.at( loadModelName[loadFileCount]);
	animate = loadModelAnimate.at( loadModelName[loadFileCount]);
	if( animate != nullptr) { sprite -> stopAllActions(); }
}

string LoadFile::getModelName( void)
{
	string fileName = loadModelName[loadFileCount];
	if( fileName == "") { return nullptr; }
	int point = fileName.rfind( '.', fileName.size());
	fileName.erase( fileName.size() - ( fileName.size() - point), fileName.size());
	return fileName;
}