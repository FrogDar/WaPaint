#include "graphics.h"
#include "viewport.h"

int DevidingLine = 170;//左右视图分界线
extern PIMAGE qingwa;//青蛙图标

//重画菜单
void viewport_A() {
	int ImgHeight = 230 * DevidingLine / 500;
	
	//设置画图所需颜色等
	setfillcolor(WHITE); 
	setcolor(BLACK);
	setlinewidth(1);
	setlinestyle(SOLID_LINE);

	//基础底色
	bar(0, 0, DevidingLine, getheight());
	line(DevidingLine, 0, DevidingLine, getheight());	
	
	//自上而下依次画相关内容
	putimage(0, 0, DevidingLine, ImgHeight, qingwa, 0, 0, 500, 230);

	rectprintf(0, ImgHeight, DevidingLine, ImgHeight + 50, "    蛙板   ");

	int t = 230 * DevidingLine / 500 + 80;
	int tot = 6;
	char s[10][20] = { "  1.圆","  2.矩形","  3.多边形","  4.直线","  5.铅笔","  6.橡皮擦" };
	for (int i = 0; i < tot; i++)
		rectprintf(0, t + 50 * i, DevidingLine, t + 50 * (i + 1), s[i]);

	rectprintf(0, t + 300, DevidingLine, 370, "更多：回车!");

	char ss[10][20] = { "  C.清屏" ,"  O.打开","  S.保存","  Z.撤销","  E.退出" };
	for (int i = 0; i < 5; i++)
		rectprintf(0, 520 + 50 * i, DevidingLine, t + 50 * (i + 1), ss[i]);
}

//保留菜单地清屏
void viewport_clear() {
	cleardevice();
	viewport_A();
}

//为当前坐标所在按钮画虚线边框并返回命令代码
int kuang(int x, int y) {
	extern struct area tools[12];
	extern char Command;
	int t = 0;
	for (int i = 1; i < 12; i++)
		if (tools[i].check(x, y) == 1) {
			t = i;
			if (i + '0' != Command)tools[i].draw(CENTER_LINE);
		}
		else if (i + '0' != Command)tools[i].clear();
	return t;
}