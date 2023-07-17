#pragma once
#include <string>

using namespace std;

enum LogType {
	GeneralLog,
	LogTypeCount
};

enum CarLogType {
	CarPositionLog,
	CarLogTypeCount
};

void CreateLogFolders();

ofstream CreateOpenCarLog(const int carLogType, const string& carNameWithId);
ofstream CreateOpenLog(const int logType, bool reset = false);
void Log(ofstream& log, const string& text, bool newLine = true);
void Log(int logType, const string& text, bool newLine = true);
void CloseLog(ofstream& log);