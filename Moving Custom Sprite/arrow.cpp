#include "arrow.h"

// Define a bitmap structure for easy configuration
struct Bitmap {
	int x, y;
	ALLEGRO_COLOR color;
};

const int bmp_size = 64;

arrowClass::arrowClass()
{
	speed=0;
	x=100;
	y=100;
	dir=1;
	score = 0;
	for(int i=0; i<4; i++)
	{
		arrow_bmp[i]=NULL;
	}
}
arrowClass::~arrowClass()
{
	for(int i=0; i<4; i++)
	{
		al_destroy_bitmap(arrow_bmp[i]);
	}
}
void arrowClass::drawArrow()
{
	al_draw_bitmap(arrow_bmp[getDirection()], getX(), getY(), 0);
}

void arrowClass::create_arrow_bitmap(ALLEGRO_DISPLAY* display)
{
    // Bitmap imported was a 64x64 bitmap so
    const int bmp_w = bmp_size;
    const int bmp_h = 64;

    // Colors for ship parts
    ALLEGRO_COLOR colors[4] = {
        al_map_rgb(80, 180, 255),    // Body (light blue)
        al_map_rgb(200, 200, 255),   // Cockpit (light gray/blue)
        al_map_rgb(60, 60, 120),     // Wing (dark blue)
        al_map_rgb(50, 220, 80)      // Blaster (light green)
    };

    // Ship part definitions 
    Bitmap body    = { 32,  4,  colors[0] };
    Bitmap leftWing  = { 12, 32, colors[2] };
    Bitmap rightWing = { 52, 32, colors[2] };
    Bitmap cockpit = { 32, 24, colors[1] };
    Bitmap blaster = { 32,  8,  colors[3] };

    for (int i = 0; i < 4; i++) {
        arrow_bmp[i] = al_create_bitmap(bmp_w, bmp_h);
        al_set_target_bitmap(arrow_bmp[i]);
        al_clear_to_color(al_map_rgb(0, 0, 0));

        // Draw main body (facing upwards)
        al_draw_filled_triangle(body.x, body.y, 60, 56, 4, 56, body.color);

        // Draw left wing
        al_draw_filled_triangle(leftWing.x, leftWing.y, 4, 56, 24, 56, leftWing.color);

        // Draw right wing
        al_draw_filled_triangle(rightWing.x, rightWing.y, 60, 56, 40, 56, rightWing.color);

        // Draw cockpit
        al_draw_filled_ellipse(cockpit.x, cockpit.y, 8, 12, cockpit.color);

        // Draw blaster (small circle at tip)
        al_draw_filled_circle(blaster.x, blaster.y, 3, blaster.color);

        // If not in default position, rotate the bitmap to the correct direction
		// We can use ALLEGRO's PI constant to calculate this
		// We can ignore 360 angle change since that's redundant
        if (i != 0) {
            ALLEGRO_BITMAP* rotated = al_create_bitmap(bmp_w, bmp_h);
            al_set_target_bitmap(rotated);
            al_clear_to_color(al_map_rgb(0, 0, 0));
			// 90 degrees per direction (0, 90, 180, 270)
            float angle = ALLEGRO_PI * 0.5f * i;
			// Swap current bitmap with rotated version
            al_draw_rotated_bitmap(arrow_bmp[0], bmp_w / 2, bmp_h / 2, bmp_w / 2, bmp_h / 2, angle, 0);
            al_destroy_bitmap(arrow_bmp[i]);
            arrow_bmp[i] = rotated;
        }
    }
    al_set_target_backbuffer(display);
}

void arrowClass::erase_arrow()
{

	int left = x ;
	int top = y;
	int right = x + bmp_size;
	int bottom = y + bmp_size;

	al_draw_filled_rectangle(left, top, right, bottom, al_map_rgb(0, 0, 0));
}

void arrowClass::up()
{
	dir=0;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;
}

void arrowClass::down()
{
	dir=2;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;

}


void arrowClass::left()
{
	dir=3;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;

}

void arrowClass::right()
{
	dir=1;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;

}
int arrowClass::getDirection()
{
	return dir;
}
int arrowClass::getSpeed()
{
	return speed;
}
int arrowClass::getX()
{
	return x;
}
int arrowClass::getY()
{
	return y;
}
void arrowClass::move_arrow(int width, int height)
{

	//update arrow position based on direction
	switch(dir)
	{
	case 0:
		y -= speed;
		break;
	case 1:
		x += speed;
		break;
	case 2:
		y += speed;
		break;
	case 3:
		x -= speed;
	}

	//keep arrow inside the screen
	if (x > width- bmp_size)
	{
		x = width- bmp_size;
		speed = 0;
	}
	if (x < 0)
	{
		x = 0;
		speed = 0;
	}
	if (y > height- bmp_size)
	{
		y = height- bmp_size;
		speed = 0;
	}
	if (y < 0)
	{
		y = 0;
		speed = 0;
	}
}
