/*
	LucarIO - Un intento de Agar.IO para molestar a Fernando
	12/NOV/2019 - Copyright (C) 2019 Rodolfo Lam. All rights reserved.
*/
#pragma once

#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"

#include "Player.h"

ALLEGRO_DISPLAY* display{ nullptr };
ALLEGRO_EVENT_QUEUE* queue{ nullptr };
ALLEGRO_TIMER* timer { nullptr };

ALLEGRO_BITMAP* lucario{ nullptr };

bool redraw{ true };
bool quit{ false };

// Mouse status variables
int mouseX{ 0 };
int mouseY{ 0 };
int mouseBits{ 0 };

// Keyboard state
bool keys[ALLEGRO_KEY_MAX] = { false };

void Shutdown_System();