/*
	LucarIO - Un intento de Agar.IO para molestar a Fernando
	23/NOV/2019 - Copyright (C) 2019 Rodolfo Lam. All rights reserved.
*/
#pragma once

#include <array>
#include <string>
#include <iostream>

#include <allegro5/allegro.h>

#include <mathfu/rect.h>
#include <mathfu/vector.h>

namespace RL::Game {
	class Screen
	{
	public:
		Screen();
		Screen(int w, int h);
		Screen(int w, int h, std::string name);

		~Screen();

		ALLEGRO_DISPLAY* display{ nullptr };
		ALLEGRO_EVENT_QUEUE* queue{ nullptr };
		ALLEGRO_TIMER* timer{ nullptr };

		bool hasValidState() const;
		void updateKeyboard(bool val, unsigned int keycode);
		void updateMousePosition(int x, int y);
		void updateMouseButtonUp(unsigned int val);
		void updateMouseButtonDown(unsigned int val);

		mathfu::Vector<int, 2> getMousePosition() const;
		unsigned int getMouseButtonState() const;

	private:
		const double TARGET_FRAME_SLICE{ 1.0 / 60.0 };
		bool stateOK{ true };

		std::array<bool, ALLEGRO_KEY_MAX> keyboardKeys;
		mathfu::Vector<int, 2> mouseCoordinates{ 0,0 };
		unsigned int mouseButtonState{ 0 };

		void InitializeScreen(int w = 1024, int h = 728, std::string name = "Game");
	};
}

