/*
	LucarIO - Un intento de Agar.IO para molestar a Fernando
	24/NOV/2019 - Copyright (C) 2019 Rodolfo Lam. All rights reserved.
*/
#pragma once

#include <string>
#include <unordered_map>

#include <allegro5/allegro_font.h>

#include <mathfu/vector.h>

namespace RL::Game {
	enum class lifetime
	{
		permanent, // Will remain indefinetly
		transient  // If not refreshed within n seconds, will be removed.
	};

	struct LogMessage
	{
		LogMessage(std::string msg, mathfu::Vector<float, 2> pos,lifetime = lifetime::transient);

		std::string data;
		mathfu::Vector<float, 2> position;

		void UpdateMessage(std::string msg); // Text changed.
		void Reposition(mathfu::Vector<float, 2> pos); // Updated when a message is removed.
		void Tick(); // decrease remaining decay time if transient.

		bool isActive() const; // Query lifetime without generating a tick.

	private:
		bool active{ false }; // Not decayed.
		int decay{ 10000 }; // How many milliseconds left to signal death.
	};

	class ScreenLogger
	{
	public:
		ScreenLogger();
		~ScreenLogger();

		void Draw() const; // Draws all messages stored.
		void Update(); // Produces ticks, then cleans deck by removing death messages.

		void SendNewMessage(std::string name, std::string msg, lifetime = lifetime::transient);
		void RemovePermanentMessage(std::string name);

	private:
		std::unordered_map<std::string, LogMessage> messageDeck;
		int lineCount{ 0 }; // How many lines of text we currently hold;

		ALLEGRO_FONT* font{ nullptr };
		float fontHeight{ 0.0f };
	};
}
