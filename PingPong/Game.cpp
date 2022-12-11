#include "Game.h"

#include <stdexcept>

using std::make_shared;

Game::Game(string const& cfgFileName) : GraphicBase(nullptr, 1)
{
	std::cout << "Game()\n";

	try {
		ifstream cfgFile(cfgFileName);

		if (!cfgFile) {
			throw invalid_argument("Error in init from file: " + cfgFileName);
		}

		Init(cfgFile);
	}
	catch (...) {
		throw;
	}
}

Game::~Game()
{
	std::cout << "~Game()\n";
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
	
	if (ballX < 0) {
		ball->SetPos(centralPos);
		ball->SetDirs(1.0f, 1.0f);
		player->AddPoints();
		std::cout << player->Points() << '\n';
	}
	else if (ballX > windowPtr->getSize().x) {
		ball->SetPos(centralPos);
		ball->SetDirs(-1.0f, -1.0f);
		bot->AddPoints();
	}
	else {
		if (player->Contain(ball->GetPos())) {
			ball->SetDirs(1.0f);
		}
		else if (bot->Contain(ball->GetPos())) {
			ball->SetDirs(-1.0f);
		}
	}

	ball->Update(time);
	player->Update(time);
	bot->Update(time);
}

void Game::Draw()
{
	// back
	windowPtr->draw(backGround);
	// graphic objects
	ball->Draw();
	player->Draw();
	bot->Draw();
}


void Game::Init(ifstream& cfgFile)
{
	// window
	unsigned W, H; 
	string title;
	unsigned r, g, b, fLimit;

	if ( !(cfgFile >> W >> H >> title >> r >> g >> b >> fLimit) ) {
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

	cfgFile.close();
}