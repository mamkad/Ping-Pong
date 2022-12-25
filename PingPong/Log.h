#pragma once

#include <fstream>

using std::ofstream;
using std::string;

class Log final
{
private:
	string path;
	bool viewMode = true;
	ofstream fileOut;

public:
	Log(string const& path, bool viewMode = true);
	Log() = default;
	~Log();

	void LogInfo(string const& msg);
	void LogError(string const& msg);

	void Open(string const& path, bool viewMode = true);
	void Close();
};