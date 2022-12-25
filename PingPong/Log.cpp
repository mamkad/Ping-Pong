#include "Log.h"

static constexpr auto INFOLINE = "-------------------------------------------------------------------------------------------\n";
static constexpr auto ERRORLINE = "*******************************************************************************************\n";

Log::Log(string const& path, bool viewMode)
{
	Open(path, viewMode);
}

Log::~Log()
{
	Close();
}

void Log::LogInfo(string const& msg)
{
	if (viewMode) {
		fileOut.write(INFOLINE, 93);
		fileOut.write(msg.data(), msg.size());
		fileOut.write(INFOLINE, 93);
	}
}

void Log::LogError(string const& msg)
{
	fileOut.write(ERRORLINE, 96);
	fileOut.write(msg.data(), msg.size());
	fileOut.write(ERRORLINE, 96);
}

void Log::Open(string const& path, bool viewMode)
{
	this->path = path;
	this->viewMode = viewMode;

	fileOut.open(path, std::ios::binary | std::ios_base::app);

	if (!fileOut.is_open()) {
		throw new std::logic_error("File: \"" + path + "\" not found");
	}
}

void Log::Close()
{
	fileOut.close();
}