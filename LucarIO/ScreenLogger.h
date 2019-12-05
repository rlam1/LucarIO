/*
	LucarIO - Un intento de Agar.IO para molestar a Fernando
	24/NOV/2019 - Copyright (C) 2019 Rodolfo Lam. All rights reserved.
*/
#pragma once

#include <chrono>
#include <memory>
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
		LogMessage(std::string msg, mathfu::Vector<float, 2> pos, lifetime tp = lifetime::transient) :
			data{ msg },
			position{ pos },
			type{ tp }
		{};

		std::string data{ "" };
		mathfu::Vector<float, 2> position{ 0.0f,0.0f };

		void UpdateMessage(std::string msg); // Text changed.
		void Tick(); // decrease remaining decay time if transient.

		bool isActive() const; // Query lifetime without generating a tick.

	private:
		lifetime type{ lifetime::transient }; /* Only this type can auto signal its own death. */
											  /* Permanent messages are deleted upstream.      */
		bool active{ true }; // Not dead yet.

		const std::chrono::seconds timelimit{ 10 }; // How many seconds have to pass to kill message.
		std::chrono::system_clock::time_point timestamp{ std::chrono::system_clock::now() }; // Time of creation of message
	};

	class ScreenLogger
	{
	public:
		ScreenLogger();
		~ScreenLogger();

		void Draw() const; // Draws all messages stored.
		void Update(); // Produces ticks, then cleans deck by removing death messages.

		void SendNewMessage(std::string name, std::string msg, lifetime tp = lifetime::transient);
		void RemovePermanentMessage(std::string name);

	private:
		std::unordered_map<std::string, std::unique_ptr<LogMessage>> messageDeck;
		int lineCount{ 0 }; // How many lines of text we currently hold;

		ALLEGRO_FONT* font{ nullptr };
		ALLEGRO_COLOR color;
		int fontHeight{ 0 };

		void CalculateMessagePositions(); // Whenever a message is added/deleted, new positions are needed.
	};
}
