#define _CRT_SECURE_NO_WARNINGS

/*
* 开发日志
* 2024.5.15
* 1.创建新项目
* 2.导入素材
* 3.创建游戏初始地图
* 
* 2024.5.19
* 4.创建植物卡槽（向日葵，豌豆射手）
* 5.种植植物，更改植物摇摆速度
* 6.优化游戏循环和游戏渲染顺序
* 7.制作启动菜单
* 
* 2024.5.23
* 8.生成随机阳光
*
* 2024.5.24
* 9.修复bug整合代码（修改全局变量的声明和定义，调整生成随机阳光的时间）
* 10.收集随机阳光
* 11.实现阳光球的飞跃
*/


#include"game.h"


int main()
{
	gameInit();

	startUI();

	int timer = 0;
	bool flag = true;
	while (1)
	{
		userClick();
		timer += getDelay();//获取延迟时间,判断更新游戏窗口
		if (timer > 80)//100接近原版，但是帧数太低
		{
			flag = true;
			timer = 0;
		}

		if (flag)
		{
			flag = false;
			updateWindow();
			updateGame();//每一帧更改游戏数据

		}

	}
	

	system("pause");
	return 0;
}

