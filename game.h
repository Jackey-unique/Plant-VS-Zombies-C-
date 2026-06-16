#pragma once


#include<stdio.h>
#include<graphics.h>
#include<time.h>
#include<math.h>

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define WIN_WIDTH 900
#define WIN_HEIGHT 600


enum { WAN_DOU, XIANG_RI_KUI_, PLANT_COUNT ,Cards};
enum { START, GOING, PAUSE, WIN, FAIL };//游戏的状态，用于判断胜利或者结束

extern IMAGE  imgBg;
extern IMAGE  imgBar;
extern IMAGE  imgCards[PLANT_COUNT];
extern IMAGE* imgPlant[PLANT_COUNT][20];
extern IMAGE imgSunshineBall[29];
extern IMAGE imgZM[22];



extern int sunshine;

extern int curX, curY;//当前选中的植物，在移动过程中的位置
extern int curPlant;//0:没有选中，1：选中了第一种植物

struct plant
{
	int type;       //0：没有植物    1：选择了第一种植物
	int frameIndex;//序列帧序号
};

extern struct plant map[5][9];

struct sunshineBall//定义阳光
{
	int x, y;//阳光球在飘落过程中的坐标位置（x不变）
	int frameIndex;//当前显示的图片帧的序号
	int destY;//飘落的目标位置的y坐标
	bool used;//是否在使用
	int timer;//计时器

	float xoff;
	float yoff;//飞跃过程中每一帧位置（偏移量）
};

struct zm   //定义僵尸
{
	int x, y;
	int frameIndex;
	bool used;
	int speed;
};
struct zm zms[10];


//池 10个阳光球，用一个拿一个，用完还回去
extern struct sunshineBall balls[10];

//判断铲子是否捡起来
extern bool judgeShovel;


//游戏目前状态（胜利或者结束）
extern int gameStatus;
//判断游戏是否重开
extern bool restart;
//判断游戏是否回到主页面
extern bool backToMenu;
//判断开场音效是否播放完毕
extern bool musicOver;







//extern struct bullet bullets[30];//创建子弹
//extern struct bullet
//{
//	int x, y;
//	bool used;
//	int speed;
//	int row;
//};










//游戏设置
void gameInit();
//更新窗口
void updateWindow();
//背景透明
void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);
int getDelay();
//用户点击
void userClick();
//判断文件是否存在
bool fileExist(const char* name);
//持续更新游戏画面
void updateGame();
//获取延迟时间，更新游戏窗口
int getDelay();
//游戏菜单
void startUI();
//创建阳光
void createSunshine();
//更新阳光状态
void updateSunshine();
//收集阳光
void collectSunshine(ExMessage* msg);
//创建僵尸
void creatZM();
//更新僵尸状态
void updateZM();
//渲染僵尸进场动作
void drawZM();