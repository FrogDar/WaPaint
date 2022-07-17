
struct area {
	int x1, y1, x2, y2;
	void in(int a, int b, int c, int d) {
		x1 = a; y1 = b; x2 = c; y2 = d;
	}
	void draw(int style) {

		setlinestyle(style, NULL, 2);
		setlinestyle(style);
		setcolor(BLACK);
		rectangle(x1 + 3, y1 + 3, x2 - 3, y2 - 3);
	}
	int check(int x, int y) {
		if (x<x1 || y<y1 || x> x2 || y> y2)return -1;
		return 1;
	}
	void clear() {

		setlinestyle(SOLID_LINE, NULL, 2);
		setlinestyle(SOLID_LINE);
		setcolor(WHITE);
		rectangle(x1 + 3, y1 + 3, x2 - 3, y2 - 3);
	}
};

int kuang(int,int);
void viewport_A(void);//ªÊª≠◊Û ”Õº
void viewport_clear(void);//«Âø’”“ ”Õº


