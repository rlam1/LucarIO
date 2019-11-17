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

	display = al_create_display(1024, 768);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60.0);

	if (!display || !queue || !timer) {
		std::cerr << "Allegro fatal error!" << std::endl << "Data available: " << std::endl
			<< display << " | " << queue << " | " << timer << std::endl;
		Shutdown_System();
		return EXIT_FAILURE;
	}

	al_install_keyboard();
	al_install_mouse();

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));

	lucario = al_load_bitmap("res/lucario.jpg");
	std::cout << lucario << std::endl;

	al_start_timer(timer);

	while (!quit) {
		do {
			if (redraw) {
				al_clear_to_color(al_map_rgb(0, 0, 0));

				al_draw_scaled_bitmap(lucario, 0, 0, al_get_bitmap_width(lucario), al_get_bitmap_height(lucario),
					mouseX - 125, mouseY - 125, 250, 250, NULL);

				al_flip_display();
				redraw = false;
			}

			ALLEGRO_EVENT ev;
			al_wait_for_event(queue, &ev);

			switch (ev.type) {
			case ALLEGRO_EVENT_TIMER:
				// Drop next timer if previous render took too long.
				ALLEGRO_EVENT ev2;
				if (al_peek_next_event(queue, &ev2)) {
					if (ev.type == ALLEGRO_EVENT_TIMER) {
						al_drop_next_event(queue);
						break;
					}
				}
				redraw = true;
				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				quit = true;
				break;

			case ALLEGRO_EVENT_KEY_DOWN:
				if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					quit = true;
				}

				keys[ev.keyboard.keycode] = true;
				break;

			case ALLEGRO_EVENT_KEY_UP:
				keys[ev.keyboard.keycode] = false;
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				mouseBits |= (1 << ev.mouse.button);
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				mouseBits &= ~(1 << ev.mouse.button);
				break;

			case ALLEGRO_EVENT_MOUSE_AXES:
				mouseX = ev.mouse.x;
				mouseY = ev.mouse.y;
				break;

			default:
				break;
			}
		} while (!al_is_event_queue_empty(queue));
	}

	Shutdown_System();
	return EXIT_SUCCESS;
}

void Shutdown_System()
{
	std::cout << "Allegro is closing now..." << std::endl;

	al_destroy_bitmap(lucario);

	al_destroy_display(display);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);

	al_shutdown_font_addon();
	al_shutdown_image_addon();
	al_shutdown_primitives_addon();

	al_uninstall_system();
}
