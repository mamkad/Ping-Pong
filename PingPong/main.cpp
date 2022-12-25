#include "Game.h"
#include "Log.h"

static constexpr auto stdCfgFileName = "init.txt";
static constexpr auto stdLogFileName = "log.txt";

int main(int argc, char** argv)
{
	// init log
	Log log(stdLogFileName);

	shared_ptr<Game> pingPong = nullptr;

	try {
		string cfgFileName;

		switch (argc) {
			case 1: {
				cfgFileName = stdCfgFileName;
				break;
			}
			case 2: {
				cfgFileName = argv[1];
				break;
			}
			default:
				log.LogError("Wrong count of argument: " + std::to_string(argc) + "\n");
				return -1;
		}

		pingPong = std::make_shared<Game>(cfgFileName, stdLogFileName);
	}
	catch (std::exception const& e) {
		log.LogError("Error of start game: " + string(e.what()) + "\n");

		return -1;
	}

	return pingPong->Run();
}