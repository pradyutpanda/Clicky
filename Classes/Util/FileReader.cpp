

#include "FileReader.h"
#include <fstream>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;


FileReader::FileReader( string fileName ) {
   // Initialize variables needed
   long fileSize = 0;
   unsigned char * fileContents = NULL;
   string thisLine, result, fullPath, contents;

   addSearchPaths();

   // Get absolute path of file
   fullPath = FileUtils::getInstance()->fullPathForFilename( fileName.c_str( ) );

   // Get data of file
   fileContents = FileUtils::getInstance()->getFileData( fullPath.c_str( ) , "r", &fileSize );
   contents.append( ( char * ) fileContents );

   // Create a string stream so that we can use getline( ) on it
   istringstream fileStringStream( contents );

   // Get file contents line by line
   while ( getline( fileStringStream, thisLine ) ) {
      // Put all lines in vector
      _fileContents.push_back( thisLine );
   }

   // After this, mFileContents will have an extra entry and will have the value '\x04'.
   // We should remove this by popping it out the vector.
   _fileContents.pop_back( );

   // Delete buffer created by fileContents. This part is required.
   if ( fileContents ) {
      delete[ ] fileContents;
      fileContents = NULL;
   }

   // For testing purposes
    CCLOG( "[ NOTICE ] Finished opening file: %s ", fileName.c_str() );
}

const vector<string>& FileReader::getFileContents() const
{
   return _fileContents;
}

void FileReader::addSearchPaths()
{
   string resourcePath("/Users/pradyut.panda/develop/code/cocosx/clicky/Resources");
   FileUtils::getInstance()->addSearchPath(resourcePath);
}


/*void FileReader::writeFile() 
{
   // Load the JSON document
   //const char* fullpath = NULL;
    long filesize;
   unsigned char* data;
   int flags = 0;
   //json_error_t error;

   string path = cocos2d::FileUtils::getInstance()->getWritablePath();
   string gameSaveFolder = "clickydata/";
   string fullpath = path + gameSaveFolder + "level1.json";
   data = CCFileUtils::sharedFileUtils()->getFileData(fullpath.c_str(), "r", &filesize);
   //root = json_loadb((char*)data, filesize, flags, &error);
   //if( root == NULL ) {
     //dbg_parser_error("Error parsing the json document on line %d: %s %s", error.line, error.text);
     //return false;
   //}
}*/
