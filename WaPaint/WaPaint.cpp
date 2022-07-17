#include "graphics.h"
#include <math.h>
#include <string.h>
#include "drawfunction.h"
#include "viewport.h"
#include "kb.h"
#include <stdio.h>
#include "shape.h"

PIMAGE qingwa;//青蛙图标
struct area tools[12];//菜单按钮边框
extern int DevidingLine;//菜单分割线

int Linewidth = 1, Linecolor = 0, Linestyle = SOLID_LINE, Fillcolor = -1;
char smenu[] = { 'C','O','S','Z','E' };//小菜单按键
int checkchar(char*);//检验是否为小菜单按键

struct SHAPE pic[1111];//图形结构体
int picnow = 0, piclast = 0;//当前图形数量，上一次操作图形数量

char Command = 0;//当前的操作命令
void work();//主操作

void init();//启动前的初始化

int main() {
	//初始化
	init();

	//说明界面
	cleardevice();
	putimage(450, 10, qingwa);
	line(0, 240, 1366, 240);
	rectprintf(450, 270, 500, 500,
		"欢迎您进入蛙板！\n\n"
		"    ·支持  鼠标键盘混合操作！\n"
		"    ·纯键盘操作 请按  回车键\n"
		"   操作过程中若有延迟请稍等qwq");
	setfont(20, 0, "仿宋");
	rectprintf(450, 450, 500, 500, "部分鼠标操作提示：\n"
		"·圆    ：依次选取圆心和圆上一点\n"
		"·多边形：选取所有端点后按任意键或点击左侧工具栏中任意点，完成绘制\n"
		"·橡皮擦：尺寸修改同线条的粗细（回车->LW）\n"
	);
	setfont(30, 0, "仿宋");
	delay_ms(3000);
	
	//主操作
	viewport_clear();
	
	while (1)
		work();

	closegraph();
	return 0;
}

void work() {

	viewport_A();
	mouse_msg msg = { 0 };

	//判断用户的下一操作
	if (Command == 0)
		for (; is_run(); delay_fps(600))
		{
			if (kbhit()) {
				Command = getch();
				if (Command >= '1' && Command <= '6' || checkchar(&Command) == 1)break;
				if (Command == 10 || Command == 13)break;
			}
			if (mousemsg()) {
				msg = getmouse();
				Command = kuang(msg.x, msg.y);
				//绘制虚线边框并返回命令指令
				if ((int)msg.is_left() == 0)continue;
				if (Command >= 1 && Command <= 6) {
					Command += '0';
					break;
				}
				if (Command >= 7 && Command <= 11)
				{
					Command = smenu[Command - 7];
					break;
				}
				Command = 0;
			}
		}

	//为当前选中工具绘画边框
	if (Command >= '1' && Command <= '6')
		tools[Command - '0'].draw(SOLID_LINE);
	if (checkchar(&Command) == 1)
		for (int i = 0; i < 5; i++)
			if (smenu[i] == Command)
				tools[i + 7].draw(SOLID_LINE);

	switch (Command)
	{
	case '1':
		paint_circle();
		break;
	case '2':
		paint_rect();
		break;
	case '3':
		paint_poly();
		break;
	case '4':
		paint_line();
		break;
	case '5':
		paint_pixels(0);
		break;
	case '6':
		paint_pixels(-1);
		break;

	case 10:case 13:
		kbwork();
		break;

	case 'E':
		closegraph();
		exit(0);
		break;

	case 'C':
		piclast = picnow;
		picnow = 0;
		viewport_clear();
		Command = 0;
		break;	

	case 'S':
		fileout();
		Command = 0;
		break;

	case 'Z':
		if (picnow) picnow--;
		else if (piclast) {
			picnow = piclast;
			piclast = 0;
		}
		viewport_clear();
		for (int i = 0; i < picnow; i++)
			pic[i].paint();
		Command = 0;
		break;

	case 'O':
		if (filein() == 1) {
			viewport_clear();
			for (int i = 0; i < picnow; i++)
				pic[i].paint();
			piclast = 0;
		}		
		Command = 0;
		break;

	default:
		Command = 0;
		break;
	}
}

int checkchar(char* c)
{
	if (*c >= 'a' && *c <= 'z')
		* c = *c - 'a' + 'A';
	for (int i = 0; i < 5; i++)
		if (*c == smenu[i])return 1;
	return 0;
}

void init()
{
	//初始化窗口、字体、背景颜色
	initgraph(1366, 768);
	LOGFONTW f;
	getfont(&f);
	setfont(30, 0, "仿宋");
	f.lfWeight = 800;
	setcaption("蛙板");
	setbkcolor(WHITE);
	setcolor(BLACK);

	//初始化青蛙图标
	qingwa = newimage();
	rectprintf(200, 200, 500, 300,
		"．．．．．．╭╮╭╮．．．．．．\n"
		"．．．．．╭◆┴┴◆╮．．．．．\n"
		"．．．．．│）　　（│．．．．．\n"
		"★★★★★╰○－－○╯★★★★★\n"
		"╭☆ ╭╧╮╭╧╮╭╧╮╭╧╮╭☆\n"
		"╰╮ │※││蛙││板││※│╰╮\n"
		"☆╰ ╘∞╛╘∞╛╘∞╛╘∞╛☆╰");
	getimage(qingwa, 200, 200, 500, 230);

	//初始化工具栏按钮边界
	for (int i = 1; i <= 6; i++)
		tools[i].in(0, 100 + i * 50, DevidingLine, 150 + i * 50);
	for (int i = 0; i < 5; i++)
		tools[i + 7].in(0, 515 + i * 50, DevidingLine, 565 + i * 50);
	
	//开机广告进度条
	cleardevice();		
	for (int i = 4; i >= 0; i--) {
		putimage(450, 250, qingwa);
		bar(450, 500, 450 + 500 * (5 - i) / 5, 530);
		delay_ms(700);
	}
}