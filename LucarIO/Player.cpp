/*
	LucarIO - Un intento de Agar.IO para molestar a Fernando
	16/NOV/2019 - Copyright (C) 2019 Rodolfo Lam. All rights reserved.
*/
#include "Player.h"

RL::Game::Player::Player(std::string pathToResource)
{
	assert(al_is_system_installed());

	img = al_load_bitmap(pathToResource.c_str());
	if (!img) {
		throw std::invalid_argument::invalid_argument("The player image could not be found!\n");
	}

	position.x = 0.0;
	position.y = 0.0;

	collisionBox.xy.x = 0.0;
	collisionBox.xy.y = 0.0;
	collisionBox.wh.x = 0.0;
	collisionBox.wh.y = 0.0;

	size = 0.0;
	speed = 0.0;
}

RL::Game::Player::~Player()
{
	al_destroy_bitmap(img);
}

void RL::Game::Player::Update(RL::Game::Math::Point<int> mousePosition)
{

}

void RL::Game::Player::Draw() const
{
}

RL::Game::Math::Rect<double> RL::Game::Player::getCollisionBox() const
{
	return RL::Game::Math::Rect<double>();
}

void RL::Game::Player::moveCollisionBox()
{
}
