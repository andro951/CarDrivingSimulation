#include "FilesLibrary.h"
#include <stdexcept>

using namespace std;

void CreateDirectoryIfNotExists(const string& directoryPath) {
	wstring wideString(directoryPath.begin(), directoryPath.end());
	if (CreateDirectory(wideString.c_str(), NULL))
		return;

	DWORD errorCode = GetLastError();
	if (errorCode == ERROR_ALREADY_EXISTS)
		return;

	throw runtime_error("Failed to create directory: " + directoryPath + ".");
}