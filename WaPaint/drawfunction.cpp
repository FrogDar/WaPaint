#include "graphics.h"
#include <math.h>
#include "drawfunction.h"
#include "shape.h"
#include "viewport.h"

extern char Command;
extern int picnow;
extern struct SHAPE pic[1111];
extern int DevidingLine;
extern int Linecolor, Linestyle, Linewidth, Fillcolor;

int x[2], y[2];

int gettwopoints(int* xy)
{
	mouse_msg msg;
	int  t = 0;
	for (; t != 4; delay_fps(120))
	{
		if (kbhit())
		{
			Command = getch();
			return 1;
		}
		if (mousemsg()) {
			msg = getmouse();
			kuang(msg.x, msg.y);
			if ((int)msg.is_down() == 0)continue;
			if (msg.x <= DevidingLine)
			{
				Command = 0;
				return 1;
			}
			xy[t++] = msg.x; xy[t++] = msg.y;
		}
	}
	return 0;
}

void paint_line() {
	struct SHAPE temp; 
	temp.type = 4;
	if (gettwopoints(temp.xy))return;
	temp.pushin();
}
void paint_circle() {
	struct SHAPE temp; 
	temp.type = 1;
	if (gettwopoints(temp.xy))return;
	double d = sqrt((temp.xy[0] - temp.xy[2]) * (temp.xy[0] - temp.xy[2])
		+ (temp.xy[1] - temp.xy[3]) * (temp.xy[1] - temp.xy[3]));
	temp.num = (int)d;
	temp.pushin();
}
void paint_poly()
{
	struct SHAPE temp; 
	temp.type = 3; temp.num = 0;
	mouse_msg msg;
	int lx = 0, ly = 0;
	for (; is_run(); delay_fps(120))
	{
		if (kbhit()) {
			temp.pushin();
			picnow++;
			Command = 'Z';
			return;
		}
		if (mousemsg()) {
			msg = getmouse();
			kuang(msg.x, msg.y);
			if ((int)msg.is_down() == 0)continue;
			setcolor(temp.linecolor);
			if (msg.x <= DevidingLine)
			{
				temp.pushin();
				picnow++;
				Command = 'Z';
				return;
			}
			if (lx * ly != 0)
				line(lx, ly, msg.x, msg.y);
			lx = msg.x; ly = msg.y;
			temp.xy[temp.num * 2] = lx;
			temp.xy[temp.num * 2 + 1] = ly;
			temp.num++;
		}
	}
	return;
}
void paint_pixels(int x)
{
	struct SHAPE temp; 
	temp.type = 5; temp.num = 0;
	if (x == -1)temp.linecolor = getbkcolor();

	temp.fillcolor = temp.linecolor;

	int lx = -1, ly = 1;
	mouse_msg msg;
	for (; is_run(); delay_fps(120))
	{
		if (kbhit()) {
			Command = getch();
			return;
		}
		if (mousemsg()) {
			msg = getmouse();
			kuang(msg.x, msg.y);
			
			if ((int)msg.is_down() == 0)continue;
			setcolor(temp.linecolor);
			setfillcolor(temp.linecolor);
			setlinestyle(SOLID_LINE, NULL, Linewidth);

			for (; is_run(); delay_fps(1200)) {
				if (msg.x <= DevidingLine)
				{
					temp.pushin();
					Command = 0;
					return;
				}
				if (msg.x != lx || msg.y != ly) {
					temp.xy[temp.num * 2] = msg.x;
					temp.xy[temp.num * 2 + 1] = msg.y;
					if (lx * ly > 0)line(msg.x, msg.y, lx, ly);
					else line(msg.x, msg.y, msg.x, msg.y);

					lx = msg.x; ly = msg.y;
					temp.num++;
					if (temp.num == 49)
					{
						temp.pushin();
						temp.num = 0;
					}
				}
				if (mousemsg())
				{
					msg = getmouse();
					if ((int)msg.is_up() == 1) {
						temp.pushin();
						return;
					}
				}
			}
		}
	}
	temp.pushin();
	return;
}
void paint_rect()
{
	struct SHAPE temp; 
	temp.type = 2;
	if (gettwopoints(temp.xy))return;
	temp.pushin();
}
