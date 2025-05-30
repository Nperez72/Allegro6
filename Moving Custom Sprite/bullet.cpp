#include "bullet.h"
bullet::bullet()
{
	alive = false;;
	bmp = nullptr;
	srand(time(0));
}

void bullet::init_bitmap()
{
    // Create a 16x16 bitmap for the bullet (slightly more detailed than previous one)
    bmp = al_create_bitmap(16, 16);
    al_set_target_bitmap(bmp);
    al_clear_to_color(al_map_rgba(0, 0, 0, 0)); 

    // Draw the base of bullet to mimic cylinder shape
    al_draw_filled_ellipse(8, 5, 3.5, 6, al_map_rgb(255, 255, 50));
    // Draw the tip (dark yellow circle) near the bottom
    al_draw_filled_circle(8, 12, 2, al_map_rgb(200, 180, 0));

    al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
}

bool bullet::getStatus()
{
	return alive;
}

void bullet::fire()
{
	x=rand()%615+10;
	y = 10;
	alive=true;

}
void bullet::erase_bullet()
{
    // Erase with a black ellipse covering the bullet area
    al_draw_filled_ellipse(x + 8, y + 8, 8, 8, al_map_rgb(0, 0, 0));
}
int bullet::move_bullet (int arrowX, int arrowY, int width, int length, int height)
{
	y++;
	// Draw the bullet bitmap
	if (bmp)
		al_draw_bitmap(bmp, x, y, 0);

	if (x > arrowX && x < arrowX+width && y > arrowY && y < arrowY+length) {
		erase_bullet();
		alive=false;
		return 1;
	}
	if (y> height)
		alive = false;
	return 0;


} 