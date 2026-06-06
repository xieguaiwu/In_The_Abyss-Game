# In the Abyss

This game was wrote by me as a middle-school freshman, which was inspired by Kenzaburō Ōe's *The Silent Cry* (*万延元年のフットボール*). I was a big fan of text adventure games at that moment.

This is a text adventure game where players traverse between the city of the dead and hell, exploring the mysteries between life and death. The game is known for its unique narrative style and rich literary atmosphere.

## Game Overview

The game tells the story of an ordinary office worker who, after accidentally encountering the mysterious game "In the Abyss", begins to travel between the real world and hell. The game features multiple storylines and character-switching mechanics, allowing players to experience different perspectives.

## Project Structure

```
在深渊/
├── include/        # 头文件
│   ├── platform.h      # 跨平台支持（Windows/Linux）
│   ├── common_vars.h   # 公共变量声明
│   ├── functions.h     # 工具函数声明
│   ├── print.h         # ASCII 艺术打印
│   └── story.h         # 故事函数与全局变量声明
├── src/            # 源文件
│   ├── main.cpp        # 主函数、主菜单
│   ├── functions.cpp   # 工具函数实现
│   ├── globals.cpp     # 全局变量定义
│   ├── chapter1.cpp    # 第一章（死之人间·城市）
│   ├── chapter2.cpp    # 第二章（办公室·楼梯间）
│   └── chapter3.cpp    # 第三章（地狱探索）
├── Makefile
├── .gitignore
└── README.md
```

## Compilation and Running

### Linux (推荐)

```bash
make          # 编译
make run      # 编译并运行
make clean    # 清理编译产物
```

或直接编译：

```bash
g++ -o Abyss -Iinclude src/*.cpp -std=c++17
./Abyss
```

### Windows

Using MinGW/g++:
```cmd
g++ -o Abyss.exe -Iinclude src/*.cpp -std=c++17
Abyss.exe
```

Or using Visual Studio Developer Command Prompt:
```cmd
cl /Iinclude src/*.cpp
Abyss.exe
```

## Controls

| Key | Action |
|-----|--------|
| N | Move North |
| S | Move South |
| W | Move West |
| E | Move East |
| ↑ | Confirm / Continue waiting |
| ↓ | Cancel / Leave |
| Z | Switch character (in the Hell's Dull Fire) |
| A-E | Select menu options |

## License

MIT
