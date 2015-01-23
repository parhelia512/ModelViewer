
#include <iostream>

sprite3d* sprite3d;
string modelpath;
vector< string> loadmodelpath;

void getmodelname( void)
{
    dir* dp;
    dirent* ent;
	auto file = fileutils::getinstance();
	string dir = file -> fullpathforfilename( "model");

	if(( dp = opendir( dir.c_str()), "r") == null)
	{
		// エラー処理
	}

	while(( ent = readdir( dp)) != null)
	{
		string str[2];
		for( auto &p : str) { p = ent -> d_name; }
		int point = str[0].rfind( '.', str.size());
		if( point == string::npos) return;
		str[0].erase( 0, str[0].size() - ( str[0].size() - point));
		if( str == ".fbx" || str == ".fbx")
		{
			modelpath = str[1];
			modelpath = modelpath;
		}
	};

	closedir( dp);
	return list;
}

void fbxfileconvert( void)
{
	auto file = fileutils::getinstance();
	string programpath = file -> fullpathforfilename( "program");
	if( modelpath.size() == 0) return;
	programpath = programpath + " -b " + modelpath;
	system( programpath.c_str());
}

void load3dmodel( void)
{

}
