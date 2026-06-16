#define _CRT_SECURE_NO_WARNINGS

#include"game.h"



void creatZM()
{
	static int zmFre = 500;//僵尸出现频率
	static int count = 0;//僵尸总数量
	count++;
	if (count > zmFre)
	{
		count = 0;
		zmFre = rand() % 200 + 300;
		int i;
		int zmMAX = sizeof(zms) / sizeof(zms[0]);
		for (i = 0; i < zmMAX && zms[i].used; i++);
		if (i < zmMAX)
		{
			zms[i].used = true;
			zms[i].x = WIN_WIDTH;
			zms[i].y = 17 + (1 + rand() % 3) * 100;
			zms[i].speed = 1;
		}
	}
}


void updateZM()
{
	int zmMax = sizeof(zms) / sizeof(zms[0]);

	//更新僵尸的位置
	for (int i = 0; i < zmMax; i++)
	{
		if (zms[i].used)
		{
			zms[i].x -= zms[i].speed;//僵尸快慢
			if (zms[i].x < 170)
			{
				printf("gameover\n");
				MessageBox(NULL, "over", "over", 0);//待优化
				exit(0);//待优化
			}
		}

	}

}

//渲染僵尸进场动作
void drawZM()
{
	int zmCount = sizeof(zms) / sizeof(zms[0]);
	for (int i = 0; i < zmCount; i++)
	{
		if (zms[i].used)
		{
			IMAGE* img = &imgZM[zms[i].frameIndex];
			putimagePNG(zms[i].x, zms[i].y - img->getheight(), img);
		}
	}
}