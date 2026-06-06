#ifndef PLATFORM_H
#define PLATFORM_H

// 跨平台支持头文件 - 支持Windows和Linux
// C++17标准

#include <iostream>
#include <string>
#include <cstdio>

// 平台检测
#if defined(_WIN32) || defined(_WIN64)
#define PLATFORM_WINDOWS
#include <windows.h>
#include <conio.h>
#else
#define PLATFORM_LINUX
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#endif

// ============ 控制台颜色定义 ============
// 前景色
#define COLOR_BLACK   30
#define COLOR_RED     31
#define COLOR_GREEN   32
#define COLOR_YELLOW  33
#define COLOR_BLUE    34
#define COLOR_MAGENTA 35
#define COLOR_CYAN    36
#define COLOR_WHITE   37

// 背景色 (+10)
#define BG_BLACK   40
#define BG_RED     41
#define BG_GREEN   42
#define BG_YELLOW  43
#define BG_BLUE    44
#define BG_MAGENTA 45
#define BG_CYAN    46
#define BG_WHITE   47

// ============ 跨平台函数实现 ============

namespace platform {

// 延时函数（毫秒）
inline void sleep_ms(int milliseconds) {
#ifdef PLATFORM_WINDOWS
	Sleep(milliseconds);
#else
	usleep(milliseconds * 1000);
#endif
}

// 清屏
inline void clear_screen() {
#ifdef PLATFORM_WINDOWS
	system("cls");
#else
	std::cout << "\033[2J\033[H";
	std::cout.flush();
#endif
}

// 设置光标位置（0-based）
inline void gotoxy(int x, int y) {
#ifdef PLATFORM_WINDOWS
	COORD coord;
	coord.X = static_cast<SHORT>(x);
	coord.Y = static_cast<SHORT>(y);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
	std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
	std::cout.flush();
#endif
}

// 设置控制台颜色（前景色和背景色）
inline void set_color(int foreground, int background = 0) {
#ifdef PLATFORM_WINDOWS
	// Windows颜色映射
	int win_fg = 0, win_bg = 0;

	switch (foreground) {
	case COLOR_BLACK:
		win_fg = 0;
		break;
	case COLOR_RED:
		win_fg = FOREGROUND_RED;
		break;
	case COLOR_GREEN:
		win_fg = FOREGROUND_GREEN;
		break;
	case COLOR_YELLOW:
		win_fg = FOREGROUND_RED | FOREGROUND_GREEN;
		break;
	case COLOR_BLUE:
		win_fg = FOREGROUND_BLUE;
		break;
	case COLOR_MAGENTA:
		win_fg = FOREGROUND_RED | FOREGROUND_BLUE;
		break;
	case COLOR_CYAN:
		win_fg = FOREGROUND_GREEN | FOREGROUND_BLUE;
		break;
	case COLOR_WHITE:
		win_fg = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		break;
	default:
		win_fg = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		break;
	}

	switch (background) {
	case BG_BLACK:
		win_bg = 0;
		break;
	case BG_RED:
		win_bg = BACKGROUND_RED;
		break;
	case BG_GREEN:
		win_bg = BACKGROUND_GREEN;
		break;
	case BG_YELLOW:
		win_bg = BACKGROUND_RED | BACKGROUND_GREEN;
		break;
	case BG_BLUE:
		win_bg = BACKGROUND_BLUE;
		break;
	case BG_MAGENTA:
		win_bg = BACKGROUND_RED | BACKGROUND_BLUE;
		break;
	case BG_CYAN:
		win_bg = BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;
	case BG_WHITE:
		win_bg = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;
	default:
		win_bg = 0;
		break;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
	                        FOREGROUND_INTENSITY | win_fg | win_bg);
#else
	// Linux使用ANSI转义序列
	std::cout << "\033[" << foreground << ";" << (background + 10) << "m";
	std::cout.flush();
#endif
}

// 重置颜色为默认
inline void reset_color() {
#ifdef PLATFORM_WINDOWS
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
	                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
	std::cout << "\033[0m";
	std::cout.flush();
#endif
}

// 兼容旧代码的color函数 (使用简单的颜色代码)
// 1=红 2=绿 3=蓝 4=黄 5=紫 6=青 7=白
inline void color(int colorCode) {
#ifdef PLATFORM_WINDOWS
	int attr = FOREGROUND_INTENSITY;
	switch (colorCode) {
	case 1:
		attr |= FOREGROUND_RED;
		break;
	case 2:
		attr |= FOREGROUND_GREEN;
		break;
	case 3:
		attr |= FOREGROUND_BLUE;
		break;
	case 4:
		attr |= FOREGROUND_RED | FOREGROUND_GREEN;
		break;
	case 5:
		attr |= FOREGROUND_RED | FOREGROUND_BLUE;
		break;
	case 6:
		attr |= FOREGROUND_GREEN | FOREGROUND_BLUE;
		break;
	case 7:
		attr |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		break;
	default:
		attr = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
#else
	int fg = 37;
	switch (colorCode) {
	case 1:
		fg = 31;
		break; // 红
	case 2:
		fg = 32;
		break; // 绿
	case 3:
		fg = 34;
		break; // 蓝
	case 4:
		fg = 33;
		break; // 黄
	case 5:
		fg = 35;
		break; // 紫
	case 6:
		fg = 36;
		break; // 青
	case 7:
		fg = 37;
		break; // 白
	default:
		fg = 37;
		break;
	}
	std::cout << "\033[1;" << fg << "m";
	std::cout.flush();
#endif
}

// 兼容system("color XX")的颜色设置
// 格式：第一个十六进制数字是背景色，第二个是前景色
inline void system_color(int code) {
#ifdef PLATFORM_WINDOWS
	char cmd[16];
	snprintf(cmd, sizeof(cmd), "color %02X", code);
	system(cmd);
#else
	int bg = (code >> 4) & 0x0F;
	int fg = code & 0x0F;

	// 映射到ANSI颜色
	auto mapColor = [](int c) -> int {
		switch (c) {
		case 0:
			return 30; // 黑
		case 1:
			return 34; // 蓝
		case 2:
			return 32; // 绿
		case 3:
			return 36; // 青
		case 4:
			return 31; // 红
		case 5:
			return 35; // 紫
		case 6:
			return 33; // 黄
		case 7:
			return 37; // 白
		case 8:
			return 37; // 灰(当作白)
		case 9:
			return 34; // 亮蓝
		case 10:
			return 32; // 亮绿
		case 11:
			return 36; // 亮青
		case 12:
			return 31; // 亮红
		case 13:
			return 35; // 亮紫
		case 14:
			return 33; // 亮黄
		case 15:
			return 37; // 亮白
		default:
			return 37;
		}
	};

	std::cout << "\033[" << mapColor(fg) << ";" << (mapColor(bg) + 10) << "m";
	std::cout.flush();
#endif
}

// 隐藏光标
inline void hide_cursor() {
#ifdef PLATFORM_WINDOWS
	CONSOLE_CURSOR_INFO ci;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleCursorInfo(hStdOut, &ci)) {
		ci.bVisible = FALSE;
		SetConsoleCursorInfo(hStdOut, &ci);
	}
#else
	std::cout << "\033[?25l";
	std::cout.flush();
#endif
}

// 显示光标
inline void show_cursor() {
#ifdef PLATFORM_WINDOWS
	CONSOLE_CURSOR_INFO ci;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleCursorInfo(hStdOut, &ci)) {
		ci.bVisible = TRUE;
		SetConsoleCursorInfo(hStdOut, &ci);
	}
#else
	std::cout << "\033[?25h";
	std::cout.flush();
#endif
}

// 获取终端大小
inline void get_terminal_size(int& width, int& height) {
#ifdef PLATFORM_WINDOWS
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	} else {
		width = 80;
		height = 24;
	}
#else
	struct winsize w;
	int result = ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (result == 0 && w.ws_col > 0 && w.ws_row > 0) {
		width = w.ws_col;
		height = w.ws_row;
	} else {
		// 无法获取终端大小时使用默认值
		// 尝试从环境变量获取
		const char* cols = std::getenv("COLUMNS");
		const char* lines = std::getenv("LINES");
		if (cols && lines) {
			width = std::atoi(cols);
			height = std::atoi(lines);
		} else {
			width = 80;
			height = 24;
		}
	}
#endif
	// 确保返回值在合理范围内
	if (width <= 0) width = 80;
	if (height <= 0) height = 24;
}

// 全屏（仅Windows有效，Linux下忽略）
inline void full_screen() {
#ifdef PLATFORM_WINDOWS
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);
	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
#endif
	// Linux下全屏需要终端支持，这里不做处理
}

} // namespace platform

// ============ getch() 实现 ============
#ifdef PLATFORM_LINUX
namespace {
// Linux下getch的实现
inline int getch_impl() {
	struct termios oldattr, newattr;
	int ch;

	// 获取当前终端设置
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	// 设置为非规范模式，禁用回显
	newattr.c_lflag &= ~(ICANON | ECHO);
	// 第一个字符阻塞等待
	newattr.c_cc[VMIN] = 1;
	newattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

	ch = getchar();

	// 检查方向键（Linux下方向键是3个字符的序列 ESC [ A/B/C/D）
	if (ch == 27) { // ESC
		// 切换到非阻塞模式读取后续字符
		newattr.c_cc[VMIN] = 0;
		newattr.c_cc[VTIME] = 1; // 0.1秒超时
		tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

		int ch2 = getchar();
		if (ch2 == '[') {
			int ch3 = getchar();
			switch (ch3) {
			case 'A':
				tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
				return 'H'; // 上 - 映射到原来的定义
			case 'B':
				tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
				return 'P'; // 下
			case 'C':
				tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
				return 'M'; // 右
			case 'D':
				tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
				return 'K'; // 左
			}
		}
		// 如果不是方向键序列，返回 ESC
	}

	// 恢复终端设置
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	return ch;
}
}
// 在Linux下重新定义getch
#define getch getch_impl
#endif

// ============ 兼容性宏定义 ============
// 方向键定义（与原代码保持一致）
#ifndef PLATFORM_WINDOWS
#undef left
#undef right
#undef up
#undef down
#endif

#define left 'K'
#define right 'M'
#define up 'H'
#define down 'P'

// Sleep兼容
#ifdef PLATFORM_LINUX
#define Sleep(ms) platform::sleep_ms(ms)
#endif

#endif // PLATFORM_H
