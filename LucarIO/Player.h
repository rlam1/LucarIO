/*
	LucarIO - Un intento de Agar.IO para molestar a Fernando
	16/NOV/2019 - Copyright (C) 2019 Rodolfo Lam. All rights reserved.
*/
#pragma once

#include <string>

#include <allegro5/allegro.h>

#include <mathfu/rect.h>
#include <mathfu/vector.h>

namespace RL::Game {
	class Player
	{
	public:
		Player(std::string pathToResource);
		~Player();

		void Update(mathfu::Vector<int, 2> mousePosition);
		void Draw() const;

		mathfu::Rect<double> getCollisionBox() const;

	private:
		mathfu::Vector<double, 2> position;
		mathfu::Rect<double> collisionBox;
		double size;
		double speed;

		ALLEGRO_BITMAP* img{ nullptr };
		mathfu::Vector<int, 2> imgSize;

		void moveCollisionBox();
	};
}

