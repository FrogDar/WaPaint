#include<graphics.h>

void kbwork(void);//���̲���

//����������
void kb_circle();
void kb_rect();
void kb_poly();
void kb_line();
void kb_pix();
void kb_era();

//����Ѱ���ѻ�ͼ��
void kb_find();

//��������
color_t choose_color();
int choose_linestyle();
int read(const char*, int, int);
	//read������������
	int is_num(char* s);
	void getline(const char* s, char* in);
	void getnumber(const char* s, char* in);
