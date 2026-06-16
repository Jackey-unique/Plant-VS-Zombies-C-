#define _CRT_SECURE_NO_WARNINGS


#include"game.h"


IMAGE  imgBg;
IMAGE  imgBar;
IMAGE  imgCards[PLANT_COUNT];
IMAGE* imgPlant[PLANT_COUNT][20];
IMAGE imgSunshineBall[29];


int sunshine;

int curX, curY;//当前选中的植物，在移动过程中的位置
int curPlant;//0:没有选中，1：选中了第一种植物


struct plant map[5][9];



//池 10个阳光球，用一个拿一个，用完还回去
struct sunshineBall balls[10];




void gameInit()
{
	//加载有背景图片
	loadimage(&imgBg, "res/map0.jpg");
	//加载植物栏
	loadimage(&imgBar, "res/bar5.png");


	memset(imgPlant, 0, sizeof(imgPlant));//按字节赋值，初始化全赋为零
	memset(map, 0, sizeof(map));


	//初始化植物卡牌
	char name[64] = { 0 };
	for (int i = 0; i < PLANT_COUNT; i++)
	{
		//生成植物卡牌的文件名
		sprintf_s(name, sizeof(name), "res/Cards/card_%d.png", i + 1);

		loadimage(&imgCards[i], name);
		for (int j = 0; j < 20; j++)
		{
			sprintf_s(name, sizeof(name), "res/zhiwu/%d/%d.png",i,j+1);
			//先判断文件是否存在（意为有的植物的动态图片不够20张，那么就只加载存在的植物图片，不存在的不加载）
			if (fileExist(name))
			{
				imgPlant[i][j] = new IMAGE;//分配内存,如果没有这个，那么下面的loadimage时imgPlants里面全是空指针，无法实现，程序会崩溃。这个new没见过，先跳过（这里不能用malloc分配内存，因为这是c++）
				loadimage(imgPlant[i][j],name);
			}
			else
			{
				break;
			}
		}

	}

	curPlant = 0;
	sunshine = 50;

	memset(balls, 0, sizeof(balls));//阳光池，内存初始化全为零
	for (int i = 0; i < 29; i++)
	{
		sprintf_s(name, sizeof(name), "res/sunshine/%d.png", i + 1);
		loadimage(&imgSunshineBall[i], name);//加载图片到数组
	}

	//配置随机种子
	srand(time(NULL));



	//loadimage(&imgBulletNormal, "res/bullets/bullet_normal.png");//加载子弹
	/*memset(bullets, 0, sizeof(bullets));*/

	//创建游戏的图形窗口
	initgraph(WIN_WIDTH, WIN_HEIGHT, 1);

	//设置字体
	LOGFONT f;//定义字体文件
	gettextstyle(&f);
	f.lfHeight = 30;
	f.lfWeight = 15;
	strcpy(f.lfFaceName, "Segoe UI Black");//数字字体
	f.lfQuality = ANTIALIASED_QUALITY;//抗锯齿效果
	settextstyle(&f);//设置字体
	setbkmode(TRANSPARENT);//设置字体透明背景
	setcolor(BLACK);//设置字体颜色



	memset(zms, 0, sizeof(zms));
	for (int i = 0; i < 22; i++)
	{
		sprintf_s(name, sizeof(name), "res/zm/%d.png", i + 1);
		loadimage(&imgZM[i], name);
	}
}

void updateWindow()
{
	BeginBatchDraw();//开始缓冲

	putimage(0, 0, &imgBg);
	putimagePNG(250, 0, &imgBar);

	for (int i = 0; i < PLANT_COUNT; i++)
	{
		int x = 338 + i * 65;
		int y = 6;
		putimage(x, y, &imgCards[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (map[i][j].type > 0)
			{
				int x = 256 + j * 81;
				int y = 80 + i * 97+ 14;
				int PlantType = map[i][j].type - 1;
				int index = map[i][j].frameIndex;
				putimagePNG(x, y, imgPlant[PlantType][index]);
			}
		}
	}


	//渲染 拖动过程中的植物
	if (curPlant > 0)
	{
		IMAGE* img = imgPlant[curPlant - 1][0];
		putimagePNG(curX - img->getwidth() / 2, curY - img->getheight() / 2, img);//鼠标显示在植物图标中间
	}



	//渲染显示阳光
	int ballMax = sizeof(balls) / sizeof(balls[0]);
	for (int i = 0; i<ballMax;i++)
	{
		if (balls[i].used||balls[i].xoff)
		{
			static IMAGE* img = &imgSunshineBall[balls[i].frameIndex];
			putimagePNG(balls[i].x, balls[i].y, img);
		}
	}

	char scoretext[8];
	sprintf_s(scoretext, sizeof(scoretext), "%d", sunshine);//打印字符串
	outtextxy(283, 67, scoretext);//输出阳光值

	drawZM();

	EndBatchDraw();//结束双缓冲

	
}

void userClick()
{
	ExMessage msg;
	static int status = 0;
	if(peekmessage(&msg))//判断鼠标操作
	{
		if (msg.message == WM_LBUTTONDOWN)//鼠标长按拖拽
		{
			if (msg.x > 338 && msg.x < 338 + 65 * PLANT_COUNT && msg.y < 96)
			{
				int index = (msg.x - 338) / 65;
				status = 1;
				curPlant = index + 1;//选中植物
			}
			else
			{
				collectSunshine(&msg);
			}
		}
		else if (msg.message == WM_MOUSEMOVE && status == 1)//鼠标移动
		{
			curX = msg.x;
			curY = msg.y;
		}
		else if (msg.message == WM_LBUTTONUP)//松开鼠标放置
		{
			if (msg.x > 256 && msg.y > 80 && msg.y < 570)
			{
				int row = (msg.y - 80) / 97;
				int col = (msg.x - 256) / 81;
				
				if(map[row][col].type==0)
				{
					map[row][col].type = curPlant;
					map[row][col].frameIndex = 0;
				}
				
			}
			

			curPlant = 0;
			status = 0; 
		}
	}
}

bool fileExist(const char* name)
{
	FILE* fp = fopen(name, "r");//FILE* 文件指针
	if (fp == NULL)
	{
		return false;
	}
	else
	{
		fclose(fp);
		return true;
	}
}

void updateGame()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (map[i][j].type > 0)
			{
				map[i][j].frameIndex++;
				int PlantType = map[i][j].type - 1;
				int index = map[i][j].frameIndex;
				if (imgPlant[PlantType][index] == NULL)
				{
					map[i][j].frameIndex = 0;
				}
			}
		}
	}

	createSunshine();//创建阳光
	updateSunshine();//更新阳光状态


	creatZM();//创建僵尸
	updateZM();//更新僵尸状态
}

void startUI()
{
	IMAGE imgBg, imgMenu1, imgMenu2;
	loadimage(&imgBg, "res/Screen/MainMenu.png");
	loadimage(&imgMenu1, "res/menu1.png");
	loadimage(&imgMenu2, "res/menu2.png");
	int flag = 0;//未选中显示


		while (1)
		{
			BeginBatchDraw();
			putimage(0, 0, &imgBg);
			putimagePNG(474, 75, flag ? &imgMenu1 : &imgMenu2);//判断是否选中，选中前后图片不一致

			ExMessage msg;
			if (peekmessage(&msg))//判断鼠标操作
			{
				if (msg.message == WM_LBUTTONDOWN && msg.x > 474 && msg.x < 474 + 300 && msg.y > 75 && msg.y < 75 + 145)
				{
					flag = 1;
					//EndBatchDraw();
				}
				else if (msg.message == WM_LBUTTONUP && flag == 1)
				{
					return;
				}
			}
			EndBatchDraw();
		}
}

