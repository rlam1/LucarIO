/*
	LucarIO - Un intento de Agar.IO para molestar a Fernando
	24/NOV/2019 - Copyright (C) 2019 Rodolfo Lam. All rights reserved.
*/
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>

#include <mathfu/constants.h>

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
	messageDeck.reserve(10);

	assert(al_is_system_installed());

	color = al_map_rgb(0, 0, 0);
	
	if (font = al_create_builtin_font()) {

		fontHeight = al_get_font_line_height(font);
	}
}

RL::Game::ScreenLogger::~ScreenLogger()
{
	al_destroy_font(font);
}

void RL::Game::ScreenLogger::Draw() const
{
	al_hold_bitmap_drawing(true);
	for (const auto& msg : messageDeck) {
		al_draw_text(font, color, msg.second.get()->position.x, msg.second.get()->position.y, NULL,
			msg.second.get()->data.c_str());
	}
	al_hold_bitmap_drawing(false);
}

void RL::Game::ScreenLogger::Update()
{
	bool needToReposition{ false };

	for (auto& msg : messageDeck) {
		msg.second.get()->Tick();

		if (false == msg.second.get()->isActive()) {
			needToReposition = true;
		}
	}

	if (needToReposition) {
		CalculateMessagePositions();
	}
}

void RL::Game::ScreenLogger::SendNewMessage(std::string name, std::string msg, lifetime tp)
{
	auto message = std::make_unique<LogMessage>(msg, mathfu::kZeros2f, tp);

	messageDeck.insert_or_assign(name, std::move(message));

	CalculateMessagePositions();
}

void RL::Game::ScreenLogger::RemovePermanentMessage(std::string name)
{
	auto message = messageDeck.find(name);

	if (messageDeck.end() != message) {
		messageDeck.erase(message);
	}

	CalculateMessagePositions();
}

void RL::Game::ScreenLogger::CalculateMessagePositions()
{
	int currentLine{ 0 };
	mathfu::Vector<float, 2> caret{ mathfu::kZeros2f };

	for (auto& msg : messageDeck) {
		msg.second.get()->position = caret;

		++currentLine;

		caret.x = currentLine * fontHeight;
	}
}
