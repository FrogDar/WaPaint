#include<graphics.h>

extern struct SHAPE pic[1111];
extern int picnow;
extern int Linecolor, Linestyle, Linewidth, Fillcolor;

void fileout();//文件输出
int filein();//文件读入
struct SHAPE {
	int type = 0, num = 0;
	int xy[100] = { 0 };
	int fillcolor = 0;
	int width = 1, linecolor = 0, linestyle = SOLID_LINE;
	void paint() {
		//设置当前图案所需颜色、宽度信息
		if (fillcolor != -1)
			setfillcolor(fillcolor);
		setlinestyle(linestyle);
		setlinewidth(width);

		setcolor(linecolor);
		if (fillcolor == -1)//非填充图形画法
			switch (type)
			{
			case 1://圆形
				circle(xy[0], xy[1], num);
				break;
			case 2://矩形
				rectangle(xy[0], xy[1], xy[2], xy[3]);
				break;
			case 3://多边形
				drawpoly(num, xy);
				break;
			case 4://直线
				line(xy[0], xy[1], xy[2], xy[3]);
				break;
			case 5://像素点
				for (int i = 1; i < num; i++)
					line(xy[i * 2], xy[i * 2 + 1], xy[i * 2 - 2], xy[i * 2 - 1]);
				break;
			}
		else//填充图形画法
			switch (type)
			{
			case 1://圆形
				fillellipse(xy[0], xy[1], num, num);
				break;
			case 2://矩形
				bar(xy[0], xy[1], xy[2], xy[3]);
				break;
			case 3://多边形
				fillpoly(num, xy);
				break;
			case 4://直线
				line(xy[0], xy[1], xy[2], xy[3]);
				break;
			case 5://像素点
				for (int i = 1; i < num; i++)
					line(xy[i * 2], xy[i * 2 + 1], xy[i * 2 - 2], xy[i * 2 - 1]);
				break;
			}
	}
	SHAPE() {
		linecolor = Linecolor;
		linestyle = Linestyle;
		width = Linewidth;
		fillcolor = Fillcolor;
	}
	void pushin()
	{
		pic[picnow] = *this;
		picnow++;
		paint();
	}
};