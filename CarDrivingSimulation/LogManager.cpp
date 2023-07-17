#include "LogManager.h"
#include "FilesLibrary.h"

void CreateLogFolders() {
	//Create a new log folder.
	CreateDirectoryIfNotExists("Logs");

	//Create a new folder in the log folder for position logs.
	CreateDirectoryIfNotExists("Logs\\Position");
}
string GetLogsFolderPath() {
	return "Logs";
}