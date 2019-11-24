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

	imgSize.x = al_get_bitmap_width(img);
	imgSize.y = al_get_bitmap_height(img);

	position.x = 512.0;
	position.y = 384.0;

	collisionBox.pos = mathfu::kZeros2d;
	collisionBox.size = mathfu::kZeros2d;

	size = 0.25;
	speed = 1.0;
}

RL::Game::Player::~Player()
{
	al_destroy_bitmap(img);
}

void RL::Game::Player::Update(mathfu::Vector<int, 2> mousePosition)
{
	/* Posible implementation:
			Do the Lerp
			Normalize the vector  (make it lenght 1)
			Multiply this vector by the current speed factor
			Profit
	*/

	mathfu::Vector<double, 2> mouseD{ 
		static_cast<double>(mousePosition.x), 
		static_cast<double>(mousePosition.y) 
	};

	mathfu::Vector<double, 2> a = mathfu::Vector<double, 2>::Lerp
		(mouseD, position, 0.5);
	a.Normalize();
	a *= speed;

	position += a;

	moveCollisionBox();
}

void RL::Game::Player::Draw() const
{
	al_draw_scaled_bitmap(img, 0, 0, imgSize.x, imgSize.y,
		collisionBox.pos.x, collisionBox.pos.y,
		collisionBox.size.x, collisionBox.size.y, NULL);
}

mathfu::Rect<double> RL::Game::Player::getCollisionBox() const
{
	return collisionBox;
}

void RL::Game::Player::moveCollisionBox()
{
	collisionBox.pos.x = (position.x - (imgSize.x / 2.0)) * size;
	collisionBox.pos.y = (position.y - (imgSize.y / 2.0)) * size;

	collisionBox.size.x = (position.x + (imgSize.x / 2.0)) * size;
	collisionBox.size.y = (position.y + (imgSize.y / 2.0)) * size;
}
