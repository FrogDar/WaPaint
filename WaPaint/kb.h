#include<graphics.h>

void kbwork(void);//¼üÅÌ²Ù×÷

//¼üÅÌ×÷»­Çø
void kb_circle();
void kb_rect();
void kb_poly();
void kb_line();
void kb_pix();
void kb_era();

//¼üÅÌÑ°ÕÒÒÑ»­Í¼ĞÎ
void kb_find();

//¸¨Öúº¯Êı
color_t choose_color();
int choose_linestyle();
int read(const char*, int, int);
	//readº¯Êı¸¨Öúº¯Êı
	int is_num(char* s);
	void getline(const char* s, char* in);
	void getnumber(const char* s, char* in);
