/*
	LucarIO - Un intento de Agar.IO para molestar a Fernando
	12/NOV/2019 - Copyright (C) 2019 Rodolfo Lam. All rights reserved.
*/
#include "LucarIO.h"

int main(char argc, char* argv[])
{
	std::cout << "LucarIO is starting..." << std::endl;
	std::cout << std::to_string(argc) << " Started from: " << argv[0] << std::endl;

	if (!al_init()) {
		std::cerr << "Allegro could not be initialized!" << std::endl;
		Shutdown_System();
		return EXIT_FAILURE;
	}

	if (!al_init_image_addon()) {
		std::cerr << "Allegro could not initialize the image system!" << std::endl;
		Shutdown_System();
		return EXIT_FAILURE;
	}

	if (!al_init_primitives_addon()) {
		std::cerr << "Allegro could not initialize the primitives system!" << std::endl;
		Shutdown_System();
		return EXIT_FAILURE;
	}

	if (!al_init_font_addon()) {
		std::cerr << "Allegro could not initialize the font system!" << std::endl;
		Shutdown_System();
		return EXIT_FAILURE;
	}

	RL::Game::Screen screen(1024, 768, "Lucar.io | A Game of Nonsense");

	RL::Game::Player player("res/lucario.jpg");

	al_start_timer(screen.timer);

	while (!quit) {
		do {
			if (redraw && al_is_event_queue_empty(screen.queue)) {
				al_clear_to_color(al_map_rgb(0, 0, 0));

				player.Draw();

				al_flip_display();
				redraw = false;
			}

			ALLEGRO_EVENT ev;
			al_wait_for_event(screen.queue, &ev);

			switch (ev.type) {
			case ALLEGRO_EVENT_TIMER:
				redraw = true;

				player.Update(screen.getMousePosition());

				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				quit = true;
				break;

			case ALLEGRO_EVENT_KEY_DOWN:
				if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					quit = true;
				}

				screen.updateKeyboard(true, ev.keyboard.keycode);
				break;

			case ALLEGRO_EVENT_KEY_UP:

				screen.updateKeyboard(false, ev.keyboard.keycode);
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				screen.updateMouseButtonDown(ev.mouse.button);
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				screen.updateMouseButtonUp(ev.mouse.button);
				break;

			case ALLEGRO_EVENT_MOUSE_AXES:
				screen.updateMousePosition(ev.mouse.x, ev.mouse.y);
				break;

			default:
				break;
			}
		} while (!al_is_event_queue_empty(screen.queue));
	}

	Shutdown_System();
	return EXIT_SUCCESS;
}

void Shutdown_System()
{
	std::cout << "Allegro is closing now..." << std::endl;
}
