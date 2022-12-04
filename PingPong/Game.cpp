#include "Game.h"

#include <iostream>
#include <fstream>

Game::Game() : GraphicBase(nullptr)
{
	std::cout << "Game()\n";
}

Game::~Game()
{
	std::cout << "~Game()\n";
}

void Game::Update(float time)
{
	ball_->Update(time);
	player_->Update(time);
}

void Game::Draw()
{
	windowPtr_->draw(backGround_);
	ball_->Draw();
	player_->Draw();
}

int Game::Run()
{
	Clock clock;
	float time = 0.0f;

	bool isPause = true;

	while (windowPtr_->isOpen()) {
		Event event;

		time = float(clock.getElapsedTime().asSeconds());
		clock.restart();

		while (windowPtr_->pollEvent(event)) {
			switch (event.type) {
				case Event::Closed: {
					windowPtr_->close();
					break;
				}
				case Event::KeyPressed: {
					if (event.key.code == sf::Keyboard::Escape) {
						isPause = isPause == true ? false : true;
					}
					player_->OnControl(event);
					break;
				}
				default:
					break;
			}
		}

		if (!isPause) {
			Update(time);
		}

		windowPtr_->clear();
		Draw();
		windowPtr_->display();
	}

	return 0;
}

bool Game::Init(string const& cfgFileName)
{
	std::ifstream fIn(cfgFileName);

	// if file is not open
	if (!fIn) {
		//cout << "\n\tFile not found: " + fnamein + '\n';
		return false;
	}

	// window
	unsigned W, H; 
	string title;
	unsigned r, g, b, fLimit;

	if ( !(fIn >> W >> H >> title >> r >> g >> b >> fLimit) ) {
		//cout << "\n\tUnable to convert characters to rows and columns\n";
		return false;
	}

	windowPtr_ = std::make_shared<RenderWindow>(VideoMode(W, H), title);
	windowPtr_->setFramerateLimit(fLimit);

	// background
	backGround_.setSize({ (float)W, (float)H });
	backGround_.setFillColor(Color(r, g, b));

	// ball
	float radius, ballX, ballY;
	unsigned bR, bG, bB, bOR, bOG, bOB;
	float thicknes;

	if (!(fIn >> radius >> ballX >> ballY >> bR >> bG >> bB >> thicknes >> bOR >> bOG >> bOB)) {
		//cout << "\n\tUnable to convert characters to rows and columns\n";
		return false;
	}

	ball_ = std::make_shared<Ball>(windowPtr_);
	ball_->Setup(radius, Vector2f(ballX, ballY), Color(bR, bG, bB), thicknes, Color(bOR, bOG, bOB));

	// player panel
	player_ = std::make_shared<Panel>(windowPtr_);
	player_->Setup(Vector2f(20, 120), Vector2f(30, 250), Color(bR, bG, bB), 1.2f, Color(bOR, bOG, bOB));

	fIn.close();
	return true;
}