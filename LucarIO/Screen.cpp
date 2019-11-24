/*
	LucarIO - Un intento de Agar.IO para molestar a Fernando
	23/NOV/2019 - Copyright (C) 2019 Rodolfo Lam. All rights reserved.
*/
#include "Screen.h"

RL::Game::Screen::Screen()
{
	InitializeScreen();
}

RL::Game::Screen::Screen(int w, int h)
{
	InitializeScreen(w, h);
}

RL::Game::Screen::Screen(int w, int h, std::string name)
{
	InitializeScreen(w, h, name);
}

RL::Game::Screen::~Screen()
{
	al_destroy_display(display);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
}

bool RL::Game::Screen::hasValidState() const
{
	return stateOK;
}

void RL::Game::Screen::updateKeyboard(bool val, unsigned int keycode)
{
	keyboardKeys.at(keycode) = val;
}

void RL::Game::Screen::updateMousePosition(int x, int y)
{
	mouseCoordinates.x = x;
	mouseCoordinates.y = y;
}

void RL::Game::Screen::updateMouseButtonUp(unsigned int val)
{
	mouseButtonState &= ~(1 << val);
}

void RL::Game::Screen::updateMouseButtonDown(unsigned int val)
{
	mouseButtonState |= (1 << val);
}

RL::Game::Math::Point<int> RL::Game::Screen::getMousePosition() const
{
	return mouseCoordinates;
}

unsigned int RL::Game::Screen::getMouseButtonState() const
{
	return mouseButtonState;
}

void RL::Game::Screen::InitializeScreen(int w, int h, std::string name)
{
	if (al_is_system_installed()) {
		al_set_new_window_title(name.c_str());

		display = al_create_display(w, h);
		queue = al_create_event_queue();
		timer = al_create_timer(TARGET_FRAME_SLICE);

		if (!display || !queue || !timer) {
			std::cerr << "Allegro fatal error!" << std::endl << "Data available: " << std::endl
				<< display << " | " << queue << " | " << timer << std::endl;

			stateOK = false;
		}

		al_install_keyboard();
		al_install_mouse();

		al_register_event_source(queue, al_get_display_event_source(display));
		al_register_event_source(queue, al_get_keyboard_event_source());
		al_register_event_source(queue, al_get_mouse_event_source());
		al_register_event_source(queue, al_get_timer_event_source(timer));
	}
}
