#include "graphics.h"
#include "viewport.h"

int DevidingLine = 170;//������ͼ�ֽ���
extern PIMAGE qingwa;//����ͼ��

//�ػ��˵�
void viewport_A() {
	int ImgHeight = 230 * DevidingLine / 500;
	
	//���û�ͼ������ɫ��
	setfillcolor(WHITE); 
	setcolor(BLACK);
	setlinewidth(1);
	setlinestyle(SOLID_LINE);

	//������ɫ
	bar(0, 0, DevidingLine, getheight());
	line(DevidingLine, 0, DevidingLine, getheight());	
	
	//���϶������λ��������
	putimage(0, 0, DevidingLine, ImgHeight, qingwa, 0, 0, 500, 230);

	rectprintf(0, ImgHeight, DevidingLine, ImgHeight + 50, "    �ܰ�   ");

	int t = 230 * DevidingLine / 500 + 80;
	int tot = 6;
	char s[10][20] = { "  1.Բ","  2.����","  3.�����","  4.ֱ��","  5.Ǧ��","  6.��Ƥ��" };
	for (int i = 0; i < tot; i++)
		rectprintf(0, t + 50 * i, DevidingLine, t + 50 * (i + 1), s[i]);

	rectprintf(0, t + 300, DevidingLine, 370, "���ࣺ�س�!");

	char ss[10][20] = { "  C.����" ,"  O.��","  S.����","  Z.����","  E.�˳�" };
	for (int i = 0; i < 5; i++)
		rectprintf(0, 520 + 50 * i, DevidingLine, t + 50 * (i + 1), ss[i]);
}

//�����˵�������
void viewport_clear() {
	cleardevice();
	viewport_A();
}

//Ϊ��ǰ�������ڰ�ť�����߱߿򲢷����������
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