# Plant VS Zombies / PVZ_2

这是一个基于 C++ 与 EasyX 图形库实现的《植物大战僵尸》风格小游戏工程。当前 `PVZ_2(2)` 文件夹保留了 Visual Studio 工程文件、源码文件、素材资源以及部分调试构建文件，是比精简提交目录更完整的工程版本。

## 完整性说明

- 包含 Visual Studio 解决方案文件 `PVZ_2.sln`，可以直接用 Visual Studio 打开。
- 包含项目配置文件 `PVZ_2.vcxproj`、`PVZ_2.vcxproj.filters`、`PVZ_2.vcxproj.user`。
- 包含主要源码文件：`game.cpp`、`game.h`、`test.cpp`、`bullet.cpp`、`sunshine.cpp`、`zombie.cpp`、`tools.cpp`、`tools.h`、`vector2.cpp`、`vector2.h`。
- 包含大量完整素材资源，位于 `PVZ_2/PVZ_2/res/`，包括植物、僵尸、子弹、地图、音效、菜单、胜负界面等素材。
- 包含 `植物大战僵尸-完整素材.zip`，可作为素材备份。
- 包含 `x64/Debug/` 与 `.vs/` 等 Visual Studio 生成文件，说明该工程曾被打开或编译过。

因此，建议以 `PVZ_2(2)` 作为完整工程版本进行保存、运行和后续维护。

## 目录结构

```text
PVZ_2(2)/
└─ PVZ_2/
   ├─ PVZ_2.sln                  # Visual Studio 解决方案
   ├─ PVZ_2/
   │  ├─ PVZ_2.vcxproj            # Visual Studio C++ 项目文件
   │  ├─ test.cpp                 # 程序入口 main
   │  ├─ game.h                   # 全局结构体、变量声明、函数声明
   │  ├─ game.cpp                 # 游戏初始化、主界面、渲染、流程控制
   │  ├─ bullet.cpp               # 子弹逻辑
   │  ├─ sunshine.cpp             # 阳光生成、移动、收集逻辑
   │  ├─ zombie.cpp               # 僵尸生成、移动、碰撞逻辑
   │  ├─ tools.cpp / tools.h       # 工具函数
   │  ├─ vector2.cpp / vector2.h   # 二维向量工具
   │  ├─ res/                      # 图片、音频、动画等资源
   │  └─ 植物大战僵尸-完整素材.zip  # 完整素材压缩包
   ├─ x64/Debug/                  # 编译生成的调试文件
   └─ .vs/                        # Visual Studio 缓存文件
```

## 运行环境

推荐环境：

- Windows 10 或 Windows 11
- Visual Studio 2022
- C++ 桌面开发组件
- EasyX 图形库

项目使用了以下 Windows / C++ 图形与多媒体相关内容：

- `graphics.h`：EasyX 图形库
- `mmsystem.h`：Windows 多媒体接口
- `winmm.lib`：音频播放相关库

## 打开方式

1. 安装 Visual Studio 2022，并勾选“使用 C++ 的桌面开发”。
2. 安装 EasyX 图形库。
3. 打开文件：

```text
C:\Users\Administrator\Desktop\植物大战僵尸项目\PVZ_2(2)\PVZ_2\PVZ_2.sln
```

4. 在 Visual Studio 中选择 `x64` 和 `Debug` 配置。
5. 设置 `PVZ_2` 为启动项目。
6. 编译并运行。

## 运行注意事项

- 程序依赖 `res/` 下的素材文件，运行时不要随意移动或删除 `res` 文件夹。
- 如果运行时报素材加载失败，请确认工作目录位于项目源码目录附近，即 `PVZ_2/PVZ_2/`。
- 如果提示找不到 `graphics.h`，说明 EasyX 没有安装或没有正确配置到 Visual Studio。
- 如果音频无法播放，检查 `winmm.lib` 是否正常链接；源码中已经包含 `#pragma comment(lib,"winmm.lib")`。
- `.vs/`、`x64/Debug/` 属于 IDE 缓存和编译产物，交作业或备份源码时可以不保留；但如果想保留当前完整现场，可以一起保留。

## 主要功能

- 游戏开始菜单
- 植物卡牌选择
- 阳光生成与收集
- 植物种植与动画渲染
- 僵尸生成、移动与进攻
- 豌豆子弹发射与碰撞检测
- 僵尸吃植物逻辑
- 胜利与失败状态判断
- 背景音乐和音效播放


