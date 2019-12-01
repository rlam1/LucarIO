/*
	LucarIO - Un intento de Agar.IO para molestar a Fernando
	24/NOV/2019 - Copyright (C) 2019 Rodolfo Lam. All rights reserved.
*/
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>

#include "ScreenLogger.h"

void RL::Game::LogMessage::UpdateMessage(std::string msg)
{
	data = msg;

	active = true;

	timestamp = std::chrono::system_clock::now();
}

void RL::Game::LogMessage::Tick()
{
	if (lifetime::transient == type) {
		auto currentTime = std::chrono::system_clock::now();
		auto diff = currentTime - timestamp;

		if (diff >= timelimit) {
			active = false;
		}
	}
}

bool RL::Game::LogMessage::isActive() const
{
	return active;
}

RL::Game::ScreenLogger::ScreenLogger()
{
	assert(al_is_system_installed());

	color = al_map_rgb(0, 0, 0);
	
	if (font = al_create_builtin_font()) {
		messageDeck.reserve(10);

		fontHeight = al_get_font_line_height(font);
	}
}

RL::Game::ScreenLogger::~ScreenLogger()
{
	al_destroy_font(font);
}

void RL::Game::ScreenLogger::Draw() const
{
	for (auto& msg : messageDeck) {
		al_draw_text(font, color, msg.second.position.x, msg.second.position.y, NULL,
			msg.second.data.c_str());
	}
}

void RL::Game::ScreenLogger::Update()
{
}

void RL::Game::ScreenLogger::SendNewMessage(std::string name, std::string msg, lifetime)
{
}

void RL::Game::ScreenLogger::RemovePermanentMessage(std::string name)
{
}
