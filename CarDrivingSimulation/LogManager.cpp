#include "LogManager.h"
#include "FilesLibrary.h"
#include <map>
#include <fstream>

using namespace std;

map<int, string> carLogTypeNames = {
	{ CarPositionLog, "CarPosition" }
};

map<int, string> logTypeNames = {
	{ GeneralLog, "GeneralLog" }
};

#pragma region Private Functions

string GetLogsFolderPath() {
	return "Logs";
}
string GetLogFilePath(const int logType) {
	return GetLogsFolderPath() + "\\" + logTypeNames[logType] + ".txt";
}
string GetLogFolderPath(const int logType) {
	return GetLogsFolderPath() + "\\" + logTypeNames[logType];
}
string GetCarLogFolderPath(const int carLogType) {
	return GetLogsFolderPath() + "\\" + carLogTypeNames[carLogType];
}
string GetCarLogFilePath(const int carLogType, const string& carNameWithId) {
	return GetCarLogFolderPath(carLogType) + "\\" + carLogTypeNames[carLogType] + "_" + carNameWithId + ".txt";
}
ofstream CreateOpenLog(const string& logPath, bool reset = false) {
	ofstream log = ofstream(logPath, ios::out | (reset ? ios::trunc : ios::app));
	
	if (!log.is_open())
		throw runtime_error("Failed to create log file: " + logPath + ".");

	return log;
}

#pragma endregion

#pragma region Public Functions

ofstream CreateOpenCarLog(const int carLogType, const string& carNameWithId) {
	return CreateOpenLog(GetCarLogFilePath(carLogType, carNameWithId));
}
ofstream CreateOpenLog(const int logType, bool reset) {
	return CreateOpenLog(GetLogFilePath(logType), reset);
}
void Log(ofstream& log, const string& text, bool newLine) {
	if (!log.is_open())
		throw runtime_error("Log file is not open.");

	log << text;
	if (newLine)
		log << "\n";
}
void Log(int logType, const string& text, bool newLine) {
	ofstream log = CreateOpenLog(logType);
	Log(log, text, newLine);
	CloseLog(log);
}
void CloseLog(ofstream& log) {
	if (!log.is_open())
		return;

	log.close();
}
void CreateLogFolders() {
	//Create a new log folder.
	CreateDirectoryIfNotExists("Logs");

	for (int i = GeneralLog; i < LogTypeCount; i++) {
		//Create a new folder in the log folder for general logs.
		ofstream log = CreateOpenLog(i, true);
		CloseLog(log);
	}

	for (int i = CarPositionLog; i < CarLogTypeCount; i++) {
		//Create a new folder in the log folder for position logs.
		CreateDirectoryIfNotExists(GetCarLogFolderPath(i));
	}

	Log(GeneralLog, "Finished Creating Log Files and Folders.");
}

#pragma endregion