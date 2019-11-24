/*
	LucarIO - Un intento de Agar.IO para molestar a Fernando
	12/NOV/2019 - Copyright (C) 2019 Rodolfo Lam. All rights reserved.
*/
#pragma once

#include <array>
#include <iostream>
#include <string>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "Player.h"
#include "Screen.h"

bool redraw{ true };
bool quit{ false };

void Shutdown_System();