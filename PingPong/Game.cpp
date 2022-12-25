#include "Game.h"

#include <stdexcept>

using std::make_shared;

Game::Game(string const& cfgFileName, string const& logFileName) : GraphicBase(nullptr, 1)
{
	//log.Open(logFileName);
	//log.LogInfo("call Game()\n");

	try {
		ifstream cfgFile(cfgFileName);

		if (!cfgFile) {
			throw invalid_argument("Error in init from file: " + cfgFileName);
		}

		Init(cfgFile);;
	}
	catch (...) {
		throw;
	}
}

Game::~Game()
{
	//log.LogInfo("call ~Game()\n");
	//log.Close();
}

int Game::Run()
{
	Clock clock;
	float time = 0.0f;

	while (windowPtr->isOpen()) {
		Event event;

		time = float(clock.getElapsedTime().asSeconds());
		clock.restart();

		while (windowPtr->pollEvent(event)) {
			Control(event);
		}

		if (isActive) {
			Update(time);
		}

		windowPtr->clear();
		Draw();
		windowPtr->display();
	}

	return 0;
}

void Game::Control(Event const& event)
{
	Keyboard::Key key = event.key.code;

	switch (event.type) {
		case Event::Closed: {
			windowPtr->close();
			break;
		}
		case Event::KeyPressed: {
			if (key == Keyboard::Escape) {
				isActive = isActive ? false : true;
				break;
			}
			break;
		}
		case Event::KeyReleased: {
			break;
		}
		default:
			break;
	}

	ball->Control(event);
	player->Control(event);
}

void Game::Update(float time)
{
	float ballX = ball->GetPos().x;

	bool isNeedToInfoPanelUpdateFunction = false;
	
	if (ballX < 0) {
		ball->SetPos(centralPos);
		ball->SetDirs(1.0f, 1.0f);
		ball->ResetPoints();
		bot->IncPoints(dPoints);
		isNeedToInfoPanelUpdateFunction = true;
	}
	else if (ballX > windowPtr->getSize().x) {
		ball->SetPos(centralPos);
		ball->SetDirs(-1.0f, -1.0f);
		player->IncPoints(dPoints);
		isNeedToInfoPanelUpdateFunction = true;
	}
	else {
		if (player->Contain(ball->GetPos())) {
			ball->SetDirs(1.0f);
			ball->IncPoints(1);
			isNeedToInfoPanelUpdateFunction = true;
		}
		else if (bot->Contain(ball->GetPos())) {
			ball->SetDirs(-1.0f);
			ball->IncPoints(1);
			isNeedToInfoPanelUpdateFunction = true;
		}
	}

	ball     ->Update(time);
	player   ->Update(time);

	bot->SetBallPos(ball->GetPos());
	bot->Update(time);

	if (isNeedToInfoPanelUpdateFunction) {
		infoPanel->SetPlayerBotBallPoints(player->GetPoints(), bot->GetPoints(), ball->GetPoints());
		infoPanel->Update();
	}
}

void Game::Draw()
{
	// back
	windowPtr->draw(backGround);

	// graphic game objects
	ball  ->Draw();
	player->Draw();
	bot   ->Draw();

	if (isActive) {
		infoPanel->Draw();
	}
}


void Game::Init(ifstream& cfgFile)
{
	// window
	unsigned W, H; 
	string title;
	unsigned r, g, b, fLimit;

	if ( !(cfgFile >> W >> H >> title >> r >> g >> b >> fLimit
			>> dPoints >> maxPoints) ) {
		throw invalid_argument("Error of init Game class");
	}

	windowPtr = make_shared<RenderWindow>(VideoMode(W, H), title);
	windowPtr->setFramerateLimit(fLimit);
	centralPos = { windowPtr->getSize().x / 2.0f, windowPtr->getSize().y / 2.0f };

	// background
	backGround.setSize({ (float)W, (float)H });
	backGround.setFillColor(Color(r, g, b));

	// ball
	ball = make_shared<Ball>(windowPtr, 2);
	ball->Init(cfgFile);
	
	// player panel
	player = make_shared<PlayerPanel>(windowPtr, 3);
	player->Init(cfgFile);

	// bot panel
	bot = make_shared<BotPanel>(windowPtr, 4);
	bot->Init(cfgFile);

	// info panell
	infoPanel = make_shared<Info>(windowPtr, 5);
	infoPanel->Init(cfgFile);

	cfgFile.close();
}