#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "arrow.h";
#include "bullet.h"

int main(void)
{
	arrowClass arrow;
	bullet mybullet[10];
	int score=0;
	bool redraw=true;
	const int FPS = 60;

	//variables
	int width = 640;
	// Object collision is restricted to a y value of 480
	int height = 520;
	bool done = false;

	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	// Separate timer for 30 second countdown
	ALLEGRO_TIMER* exit_timer = NULL;
	// A font object for exit timer and score
	ALLEGRO_FONT* font = NULL;
	

	//program init
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if(!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	// Load installed font
	font = al_load_font("16020_FUTURAM.ttf", 16, 0);
	//al
	arrow.create_arrow_bitmap(display);

	// Create a recyclable array of bullet bitmaps
	for (int i = 0; i < 10; i++) {
	    mybullet[i].init_bitmap();
	}

	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();

	// Register exit timer to the event queue
	exit_timer = al_create_timer(30.0);
	al_register_event_source(event_queue, al_get_timer_event_source(exit_timer));

	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_clear_to_color(al_map_rgb(0,0,0));
	arrow.drawArrow();
	al_flip_display();

	// Start both timers
	al_start_timer(timer);
	al_start_timer(exit_timer);

	double start_time = al_get_time(); // Clocks the time when program starts
	const double duration = 30.0; // Duration for timer

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);


		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			// When exit timer hits 0, the game loop will exit
			if (ev.timer.source == exit_timer) {
				done = true;
			}

			redraw = true;
			for(int i=0;i<10;i++)
			{
				if (!mybullet[i].getStatus()) {
					mybullet[i].fire();
				}
			}
		}


		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				arrow.up();
				break;
			case ALLEGRO_KEY_DOWN:
				arrow.down();
				break;
			case ALLEGRO_KEY_LEFT:
				arrow.left();
				break;
			case ALLEGRO_KEY_RIGHT:
				arrow.right();
				break;
			}
		}
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false; 

			// Clear the screen before drawing new time,score, and bitmaps
			al_clear_to_color(al_map_rgb(0, 0, 0));

			if (arrow.getSpeed()!=0){
				arrow.erase_arrow();
				arrow.move_arrow(width,height);
			}
			arrow.drawArrow();
			for(int i=0;i<10;i++)
			{
				mybullet[i].erase_bullet();
				// Collision height limit changed to 480
				score += mybullet[i].move_bullet(arrow.getX(), arrow.getY(), 32, 32, 480);
			}
		}

		// Calculate and display remaining seconds
		double elapsed = al_get_time() - start_time;
		int remaining = duration - static_cast<int>(elapsed);
		// No negative time allowed
		if (remaining < 0) remaining = 0;

		// Display timer and score at bottom left of display
		al_draw_textf(font, al_map_rgb(200, 200, 200), 16, 488, ALLEGRO_ALIGN_LEFT, "TIMER: %d", remaining);
		al_draw_textf(font, al_map_rgb(200, 200, 200), 200, 488, ALLEGRO_ALIGN_LEFT, "SCORE: %d", score);

		al_flip_display();
	}
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);						//destroy our display object
	system("pause");
	return 0;
}
