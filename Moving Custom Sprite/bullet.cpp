#include "bullet.h"
bullet::bullet()
{
	alive = false;;
	srand(time(0));
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
	al_draw_filled_rectangle(x,y,x+5,y+5,al_map_rgb(0,0,0)); //black color
}
int bullet::move_bullet (int arrowX, int arrowY, int width, int length, int height)
{
	y++;
	al_draw_filled_rectangle(x,y,x+5,y+5,al_map_rgb(255,255,0));//yellow color


	if (x > arrowX && x < arrowX+width && y > arrowY && y < arrowY+length) {
		al_draw_filled_rectangle(x,y,x+5,y+5,al_map_rgb(0,0,0)); //BLACK
		alive=false;
		return 1;
	}
	if (y> height)
		alive = false;
	return 0;


} 


