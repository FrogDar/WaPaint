#include <graphics.h>
#include "shape.h"
#include <string.h>
#include <stdio.h>
extern struct SHAPE pic[1111];
extern int picnow;
extern int Linecolor, Linestyle, Linewidth, Fillcolor;



void fileout()
{
	//������ļ���
	char filename[110];
	inputbox_getline("�����ļ�", "�����뱣����ļ����������׺����", filename, 100);
	int n = strlen(filename);
	filename[n] = '.';
	filename[n + 1] = 'w';
	filename[n + 2] = 'a';
	filename[n + 3] = 'p';
	filename[n + 4] = '\0';

	//�������
	FILE* fp = fopen(filename, "w");
	fprintf(fp, "%d\n", picnow);
	for (int i = 0; i < picnow; i++)
	{
		fprintf(fp, "%d %d %d %d %d %d ",
			pic[i].type, pic[i].num, pic[i].fillcolor,
			pic[i].width, pic[i].linecolor, pic[i].linestyle);
		for (int j = 0; j < 100; j++)
			fprintf(fp, "%d ", pic[i].xy[j]);
		fprintf(fp, "\n");
	}
	fclose(fp);
}
int filein()
{
	//�򿪵��ļ���
	char filename[110];
	inputbox_getline("���ļ�", "������򿪵��ļ����������׺����", filename, 100);
	int n = strlen(filename);
	filename[n] = '.';
	filename[n + 1] = 'w';
	filename[n + 2] = 'a';
	filename[n + 3] = 'p';
	filename[n + 4] = '\0';
	FILE* fp = fopen(filename, "r");
	while (fp == NULL) {
		inputbox_getline("���ļ�", "�ļ�����������������\n�����س�ȡ�����룩", filename, 100);
		n = strlen(filename);
		if (n == 0)return 0;
		filename[n] = '.';
		filename[n + 1] = 'w';
		filename[n + 2] = 'a';
		filename[n + 3] = 'p';
		filename[n + 4] = '\0';
		fp = fopen(filename, "r");
	}

	//��ȡ����
	if (fscanf(fp, "%d", &picnow) != 1)return 0;
	for (int i = 0; i < picnow; i++)
	{
		if (fscanf(fp, "%d %d %d %d %d %d ",
			&pic[i].type, &pic[i].num, &pic[i].fillcolor,
			&pic[i].width, &pic[i].linecolor, &pic[i].linestyle) != 6)return 0;
		for (int j = 0; j < 100; j++)
			if (fscanf(fp, "%d ", &pic[i].xy[j]) != 1)return 0;
	}
	fclose(fp);
	return 1;
}