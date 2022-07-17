#include<graphics.h>

extern struct SHAPE pic[1111];
extern int picnow;
extern int Linecolor, Linestyle, Linewidth, Fillcolor;

void fileout();//�ļ����
int filein();//�ļ�����
struct SHAPE {
	int type = 0, num = 0;
	int xy[100] = { 0 };
	int fillcolor = 0;
	int width = 1, linecolor = 0, linestyle = SOLID_LINE;
	void paint() {
		//���õ�ǰͼ��������ɫ�������Ϣ
		if (fillcolor != -1)
			setfillcolor(fillcolor);
		setlinestyle(linestyle);
		setlinewidth(width);

		setcolor(linecolor);
		if (fillcolor == -1)//�����ͼ�λ���
			switch (type)
			{
			case 1://Բ��
				circle(xy[0], xy[1], num);
				break;
			case 2://����
				rectangle(xy[0], xy[1], xy[2], xy[3]);
				break;
			case 3://�����
				drawpoly(num, xy);
				break;
			case 4://ֱ��
				line(xy[0], xy[1], xy[2], xy[3]);
				break;
			case 5://���ص�
				for (int i = 1; i < num; i++)
					line(xy[i * 2], xy[i * 2 + 1], xy[i * 2 - 2], xy[i * 2 - 1]);
				break;
			}
		else//���ͼ�λ���
			switch (type)
			{
			case 1://Բ��
				fillellipse(xy[0], xy[1], num, num);
				break;
			case 2://����
				bar(xy[0], xy[1], xy[2], xy[3]);
				break;
			case 3://�����
				fillpoly(num, xy);
				break;
			case 4://ֱ��
				line(xy[0], xy[1], xy[2], xy[3]);
				break;
			case 5://���ص�
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