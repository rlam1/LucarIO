/*
	LucarIO - Un intento de Agar.IO para molestar a Fernando
	16/NOV/2019 - Copyright (C) 2019 Rodolfo Lam. All rights reserved.
*/
#pragma once

#include <string>
#include <stdexcept>

#include <allegro5/allegro.h>

#include "Rect.h"

class Player
{
public:
	Player(std::string pathToResource);
	~Player();

	void Update(Point<int> mousePosition);
	void Draw() const;

private:
	Point<double> position;
	Rect<double> collisionBox;
	double size;
	double speed;

	ALLEGRO_BITMAP* img{ nullptr };

	void moveCollisionBox();
};

