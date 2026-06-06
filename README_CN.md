# 在深渊 — In the Abyss

> [🇬🇧 English Version](README.md)

这款游戏是我初中一年级时写的，灵感来自大江健三郎的《万延元年的FOOTBALL》。那时我是文字冒险游戏的狂热爱好者。

这是一款终端文本冒险游戏，玩家在死之人间与地狱之间穿梭，探索生死之间的奥秘。游戏以其独特的叙事风格和浓厚的文学气息著称。

## 游戏概述

故事讲述了一位普通上班族在意外接触到神秘游戏《在深渊》后，开始在现实世界与地狱之间旅行的经历。游戏包含多线剧情和角色切换机制，玩家可以从不同视角体验故事共三章的内容，每一章都有独特的环境和氛围。叙事在平淡的办公室生活与超现实的地狱景观之间交替，逐渐揭示两个世界之间的联系。

## 故事流程

```
                    ┌──────────────┐
                    │   主菜单      │
                    │ A: 第一章    │
                    │ B: 第二章    │
                    │ C: 第三章    │
                    │ D: 退出      │
                    └──────┬───────┘
                           │
              ┌────────────┴────────────┐
              │  第一章                 │
              │  死之人间·城市           │
              │  街道漫步 / 写字楼办公   │
              └────────────┬────────────┘
                           │
              ┌────────────┴────────────┐
              │  第二章                 │
              │  办公室·楼梯间           │
              │  办公工作 / 楼梯小游戏   │
              └────────────┬────────────┘
                           │
              ┌────────────┴────────────┐
              │  第三章                 │
              │  地狱探索               │
              │  ┌─────────────────┐    │
              │  │ 按 Z 键在       │    │
              │  │ 两个世界之间切换  │    │
              │  └─────────────────┘    │
              │  探索地狱，揭露真相      │
              └─────────────────────────┘
```

## 项目结构

```
├── include/                # 头文件（12 个）
│   ├── platform.h          #   跨平台支持（Windows/Linux）
│   ├── common_vars.h       #   全局变量声明
│   ├── functions.h         #   工具函数声明
│   ├── print.h             #   ASCII 艺术打印
│   ├── story.h             #   故事函数与全局变量声明
│   ├── game_state.h        #   状态注册表
│   ├── room_registry.h     #   房间定义
│   ├── scene_registry.h    #   场景注册表
│   ├── dialogue_tree.h     #   对话树引擎
│   ├── ending_tracker.h    #   结局追踪
│   ├── save_load.h         #   存档/读档
│   └── random_event.h      #   随机事件系统
├── src/                    # 源文件（13 个）
│   ├── main.cpp            #   入口、主菜单
│   ├── globals.cpp         #   全局变量定义
│   ├── functions.cpp       #   工具函数实现
│   ├── chapter1.cpp        #   第一章（城市）
│   ├── chapter2.cpp        #   第二章（办公室）
│   ├── chapter3.cpp        #   第三章（地狱）
│   ├── game_state.cpp
│   ├── room_registry.cpp
│   ├── scene_registry.cpp
│   ├── dialogue_tree.cpp
│   ├── ending_tracker.cpp
│   ├── save_load.cpp
│   └── random_event.cpp
├── doc/                    # 本地文档
├── Makefile                # 构建系统
├── README.md               # 英文文档
└── README_CN.md            # 中文文档（本文件）
```

## 编译与运行

### Linux

```bash
make          # 编译（release）
make run      # 编译并运行
make debug    # 编译（debug，含调试符号）
make clean    # 清理编译产物
```

或直接编译：

```bash
g++ -o Abyss -Iinclude src/*.cpp -std=c++17
./Abyss
```

### Windows

使用 MinGW/g++：
```cmd
g++ -o Abyss.exe -Iinclude src/*.cpp -std=c++17
Abyss.exe
```

## 构建目标

| 目标 | 命令 | 说明 |
|------|------|------|
| Release | `make` | 优化编译（`-O2 -Wall -Wextra`） |
| Debug | `make debug` | 调试编译（`-O0 -g -DDEBUG`） |
| 运行 | `make run` | 编译并运行 release 版本 |
| 调试运行 | `make run-debug` | 编译并运行 debug 版本 |
| 清理 | `make clean` | 删除 obj/ 和二进制文件 |

## 操作控制

| 按键 | 功能 |
|------|------|
| N / S / W / E | 向北 / 南 / 西 / 东移动 |
| ↑ / ↓ | 确认 / 取消 |
| Z | 切换角色（第三章） |
| A-E | 选择菜单选项 |

## 扩展系统

项目包含可插拔的扩展框架，供未来剧情创作使用：

- **GameState（状态注册表）** — 集中式状态追踪，支持标记、访问计数和背包
- **RoomRegistry（房间注册）** — 房间图定义，含出口和场景挂钩
- **SceneRegistry（场景注册）** — 运行时场景注册与调度
- **DialogueTree（对话树）** — 分支对话引擎，支持条件和标记
- **EndingTracker（结局追踪）** — 多结局条件评估
- **Save/Load（存档系统）** — 序列化框架骨架
- **RandomEvent（随机事件）** — 概率触发事件，含冷却和条件

## 许可协议

MIT
