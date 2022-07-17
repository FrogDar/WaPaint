#include"kb.h"
#include<graphics.h>
#include"viewport.h"
#include<string.h>
#include<stdlib.h>
#include"shape.h"
#include<stdio.h>

extern char Command;
extern int DevidingLine;
extern int picnow;
extern struct SHAPE pic[1111];
extern int Linecolor, Linestyle, Linewidth, Fillcolor;

//辅助函数区
color_t choose_color() {

	cleardevice();
	color_t t[] = { 0,0x0000A8,0x00A800,0x00A8A8,0xA80000,0xA800A8,0xA8A800,0xA8A8A8,0x545454,0x5454FC,0x54FC54,0x54FCFC,0xFC5454,0xFC54FC,0xFCFC54,0xFCFCFC };
	for (int i = 1; i <= 16; i++) {
		setfillcolor(t[i - 1]);
		xyprintf(40, i * 40, "编号%d", i);
		bar(150, i * 40, 220, (i + 1) * 40);
	}
	picnow++; Command = 'Z';
	return t[read("请输入颜色编号", 16, 1) - 1];
}
int choose_linestyle() {
	int t[] = { SOLID_LINE,CENTER_LINE,DOTTED_LINE,DASHED_LINE };
	int p = read("1   SOLID_LINE: 线形为实线。\n2   CENTER_LINE: 线形为：－－－－－－－－－－\n3   DOTTED_LINE: 线形为：●●●●●●●●●●●●\n4   DASHED_LINE: 线形为：－●－●－●－●－●－●\n", 4, 1);
	return t[p - 1];
}
int read(const char* s, int max = 1366 - DevidingLine, int min = 0)
{
	char in[10];
	getnumber(s, in);
	int x = atoi(in);
	while (x > max || x < min)
	{
		getnumber("输入不在合法范围！请重新输入！\n", in);
		x = atoi(in);
	}
	return x;
}
//read函数辅助函数
int is_num(char* s)
{
	if (strlen(s) == 0)return 0;
	for (int i = 0; i < strlen(s); i++)
		if (s[i]<'0' || s[i]>'9')return 0;
	return 1;
}
void getline(const char* s, char* in)
{
	inputbox_getline("WaPaint", s, in, 8);
}
void getnumber(const char* s, char* in)
{
	getline(s, in);
	while (is_num(in) == 0)
	{
		getline("输入非法字符！请重新输入！\n", in);
	}
}

//键盘操作主函数
void kbwork()
{
	char in[110];
	getline("请输入任务代码(左侧工具栏也是哦~)\n0：返回\t7：进入查询功能\nLC：设置颜色   LW：设置粗细   LS：设置样式\nF：设置填充颜色\tFN：不填充", in);
	switch (in[0])
	{
	case '0':
		if (in[1] == 0)Command = 0;
		break;
	case '1':
		if (in[1] == 0)kb_circle();
		break;
	case '2':
		if (in[1] == 0)kb_rect();
		break;
	case '3':
		if (in[1] == 0)kb_poly();
		break;
	case '4':
		if (in[1] == 0)kb_line();
		break;
	case '5':
		if (in[1] == 0)kb_pix();
		break;
	case '6':
		if (in[1] == 0)kb_era();
		break;
	case '7':
		if (in[1] == 0)kb_find();
		break;
	case 'L':case'l':
		if (in[2] == 0)
			switch (in[1]) {
			case 'C':case'c':
				Linecolor = choose_color();
				break;
			case 'W':case 'w':
				Linewidth = read("请设置线的粗度（1-50磅）", 50);
				Command = 0;
				break;
			case 'S':case 's':
				Linestyle = choose_linestyle();
				Command = 0;
				break;
			}
		break;
	case 'F':case 'f':
		if (in[1] == 0)Fillcolor = choose_color();
		else if (in[1] == 'n' || in[1] == 'N')Fillcolor = -1, Command = 0;
		break;
	case 'Z':case'z':
		if (in[1] == 0)Command = 'Z';
		break;
	case 'C':case'c':
		if (in[1] == 0)Command = 'C';
		break;
	case 'O':case 'o':
		if (in[1] == 0)Command = 'O';
		break;
	case 'S':case 's':
		if (in[1] == 0)Command = 'S';
		break;
	case 'E':case 'e':
		if (in[1] == 0)Command = 'e';
		break;
	}
}

void kb_find() {
	int k = read("你想查询的图形类型\n（用左侧数字表示）", 6);
	int cnt = 0;
	for (int i = 0; i < picnow; i++)
		if (pic[i].type == k)
		{
			cnt += (k == 5 || k == 6) ? pic[i].num : 1;
		}
	char word[110];
	sprintf(word, "你一共画了%d个这种图形~\n按回车键确认", cnt);
	inputbox_getline("消息栏", word, word, 1);
}

//键盘作画区
void kb_circle()
{
	struct SHAPE temp;
	temp.type = 1;
	temp.xy[0] = read("请输入圆心的横坐标x") + DevidingLine;
	temp.xy[1] = read("请输入圆心的纵坐标y", 768);
	temp.num = read("请输入圆的半径r");
	temp.pushin();
	Command = 0;
}
void kb_poly() {
	struct SHAPE temp;
	temp.type = 3;
	temp.num = read("多边形的边数(50以内)", 50);
	for (int i = 0; i < temp.num; i++)
	{
		temp.xy[i * 2] = read("一个顶点的横坐标x") + DevidingLine;
		temp.xy[i * 2 + 1] = read("同一个顶点的纵坐标y");
	}
	temp.pushin();
	Command = 0;
}
void kb_line() {
	struct SHAPE temp;
	temp.type = 4;
	temp.xy[0] = read("请输入一个端点的横坐标x") + DevidingLine;
	temp.xy[1] = read("请输入一个端点的纵坐标y", 768);
	temp.xy[2] = read("请输入另一个端点的横坐标x") + DevidingLine;
	temp.xy[3] = read("请输入另一个端点的纵坐标y", 768);
	temp.pushin();
	Command = 0;
}
void kb_pix() {
	struct SHAPE temp;
	temp.type = 4;
	temp.xy[0] = temp.xy[2] = read("请输入铅笔点的横坐标x") + DevidingLine;
	temp.xy[1] = temp.xy[3] = read("请输入铅笔点的纵坐标y", 768);
	temp.pushin();
	Command = 0;
}
void kb_era() {
	struct SHAPE temp;
	temp.type = 4;
	temp.linecolor = getbkcolor();
	temp.xy[0] = temp.xy[2] = read("请输入橡皮擦中心的横坐标x") + DevidingLine;
	temp.xy[1] = temp.xy[3] = read("请输入橡皮擦中心的纵坐标y", 768);
	temp.pushin();
	Command = 0;
}
void kb_rect() {
	struct SHAPE temp;
	temp.type = 2;
	temp.xy[0] = read("请输入一个端点的横坐标x") + DevidingLine;
	temp.xy[1] = read("请输入一个端点的纵坐标y", 768);
	temp.xy[2] = read("请输入另一个端点的横坐标x") + DevidingLine;
	temp.xy[3] = read("请输入另一个端点的纵坐标y", 768);
	temp.pushin();
	Command = 0;
}