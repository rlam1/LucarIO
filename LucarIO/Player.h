/*
	LucarIO - Un intento de Agar.IO para molestar a Fernando
	16/NOV/2019 - Copyright (C) 2019 Rodolfo Lam. All rights reserved.
*/
#pragma once

#include <string>
#include <stdexcept>

#include <allegro5/allegro.h>

#include "Rect.h"

namespace RL::Game {
	class Player
	{
	public:
		Player(std::string pathToResource);
		~Player();

		void Update(RL::Game::Math::Point<int> mousePosition);
		void Draw() const;

		RL::Game::Math::Rect<double> getCollisionBox() const;

	private:
		RL::Game::Math::Point<double> position;
		RL::Game::Math::Rect<double> collisionBox;
		double size;
		double speed;

		ALLEGRO_BITMAP* img{ nullptr };

		void moveCollisionBox();
	};
}

