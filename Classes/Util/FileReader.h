

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;


class FileReader 
{

public:
	FileReader( string fileName );

	const vector<string> &getFileContents() const;

private:
	void addSearchPaths();

	vector< string > 	_fileContents;
};
