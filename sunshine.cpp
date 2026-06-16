#define _CRT_SECURE_NO_WARNINGS

#include"game.h"

void createSunshine()
{
	static int count = 0;//声明静态变量，生成阳光数量
	static int fre = 200;
	count++;

	if (count >= fre)//每fre帧创建一个掉落阳光
	{
		fre = 200 + rand() % 200;
		count = 0;
		//从阳光池中取一个可以使用的
		int ballMax = sizeof(balls) / sizeof(balls[0]);//计算个数

		int i;
		for (i = 0; i < ballMax && balls[i].used; i++);//空循环寻找能用的阳光球
		if (i >= ballMax)
			return;//阳光球全用完

		balls[i].used = true;
		balls[i].frameIndex = 0;
		balls[i].x = 260 + rand() % (900 - 260);//阳光掉落范围：草坪最左端->窗口宽度260-900   x随机值
		balls[i].y = 50;
		balls[i].destY = 90 + (rand() % 5) * 90;//阳光掉落范围：植物卡槽->第五行草坪   阳光球竖直掉落
		balls[i].timer = 0;//初始化计时器
		balls[i].xoff = 0;
		balls[i].yoff = 0;//初始化偏移量

	}

}

void updateSunshine()
{
	int ballMax = sizeof(balls) / sizeof(balls[0]);//阳光球数量
	for (int i = 0; i < ballMax; i++)
	{
		if (balls[i].used)//使用了才更新
		{
			balls[i].frameIndex = (balls[i].frameIndex + 1) % 29;//帧序号
			if (balls[i].timer == 0)
			{
				balls[i].y += 2;
			}

			if (balls[i].y >= balls[i].destY)//降落到底
			{
				balls[i].timer++;
				if (balls[i].timer > 100)
				{
					balls[i].used = false;//到指定位置，指定时间消失
				}
			}
		}
		else if (balls[i].xoff)
		{
			float destY = 0;
			float destX = 262;//最终偏移位置
			float angle = atan((balls[i].y - destY) / (balls[i].x - destX));
			balls[i].xoff = 4 * cos(angle);
			balls[i].yoff = 4 * sin(angle);

			balls[i].x -= balls[i].xoff;
			balls[i].y -= balls[i].yoff;//飞
			if (balls[i].y < 0 || balls[i].x < 262)
			{
				balls[i].xoff = 0;
				balls[i].yoff = 0;
				sunshine += 25;//飞到了
			}
		}
	}
}

void collectSunshine(ExMessage* msg)
{
	int count = sizeof(balls) / sizeof(balls[0]);//阳光球个数
	int w = imgSunshineBall[0].getwidth();
	int h = imgSunshineBall[0].getheight();//阳光球的宽和高
	for (int i = 0; i < count; i++)
	{
		if (balls[i].used)
		{
			int x = balls[i].x;//阳光球距离窗口左侧的距离
			int y = balls[i].y;//阳光球距离窗口右侧的距离
			if (msg->x > x && msg->x<x + w && msg->y>y && msg->y < y + h)//判断点击范围，阳光球的外接矩形
			{
				balls[i].used = false;//阳光球被点击消失
				//sunshine += 25;
				mciSendString("play res/sunshine.mp3",0,0,0);
				//设置阳光球的偏移量（数学计算角度arctan,x=rcos,y=rsin）
				float destY = 0;
				float destX = 262;//最终偏移位置
				float angle = atan((y - destY) / (x - destX));
				balls[i].xoff = 4 * cos(angle);
				balls[i].yoff = 4 * sin(angle);
			}
		}
	}
}

