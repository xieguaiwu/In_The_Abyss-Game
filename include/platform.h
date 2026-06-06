#ifndef PLATFORM_H
#define PLATFORM_H

// ============================================================================
// 跨平台支持头文件 — 支持 Windows / macOS / Linux
// C++17 标准，零外部依赖
// ============================================================================

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>   // std::atoi, std::getenv
#include <thread>    // std::this_thread::sleep_for
#include <chrono>    // std::chrono::milliseconds
#include <functional>

// ============ 平台检测 ============
#if defined(_WIN32) || defined(_WIN64)
  #define PLATFORM_WINDOWS
  #include <windows.h>
  #include <conio.h>       // Windows 原生 _getch()
#elif defined(__APPLE__)
  #define PLATFORM_MAC
  #define PLATFORM_POSIX
  // macOS: 需要 _DARWIN_C_SOURCE 获取 TIOCGWINSZ 等 POSIX 扩展
  #ifndef _DARWIN_C_SOURCE
    #define _DARWIN_C_SOURCE
  #endif
  #include <termios.h>
  #include <unistd.h>
  #include <sys/ioctl.h>   // TIOCGWINSZ
  #include <fcntl.h>
#else
  #define PLATFORM_LINUX
  #define PLATFORM_POSIX
  #include <termios.h>
  #include <unistd.h>
  #include <sys/ioctl.h>
  #include <fcntl.h>
#endif

// ============ 控制台颜色定义（ANSI 标准） ============
#define COLOR_BLACK   30
#define COLOR_RED     31
#define COLOR_GREEN   32
#define COLOR_YELLOW  33
#define COLOR_BLUE    34
#define COLOR_MAGENTA 35
#define COLOR_CYAN    36
#define COLOR_WHITE   37

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

// 延时函数（毫秒）— 跨平台，无弃用警告
inline void sleep_ms(int milliseconds) {
#ifdef PLATFORM_WINDOWS
	Sleep(milliseconds);
#else
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
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

// 设置控制台颜色（前景色 + 背景色）
inline void set_color(int foreground, int background = 0) {
#ifdef PLATFORM_WINDOWS
	int win_fg = 0, win_bg = 0;
	switch (foreground) {
	case COLOR_BLACK:   win_fg = 0;                                  break;
	case COLOR_RED:     win_fg = FOREGROUND_RED;                    break;
	case COLOR_GREEN:   win_fg = FOREGROUND_GREEN;                  break;
	case COLOR_YELLOW:  win_fg = FOREGROUND_RED | FOREGROUND_GREEN; break;
	case COLOR_BLUE:    win_fg = FOREGROUND_BLUE;                   break;
	case COLOR_MAGENTA: win_fg = FOREGROUND_RED | FOREGROUND_BLUE;  break;
	case COLOR_CYAN:    win_fg = FOREGROUND_GREEN | FOREGROUND_BLUE;break;
	case COLOR_WHITE:   win_fg = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
	default:            win_fg = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
	}
	switch (background) {
	case BG_BLACK:   win_bg = 0;                                           break;
	case BG_RED:     win_bg = BACKGROUND_RED;                              break;
	case BG_GREEN:   win_bg = BACKGROUND_GREEN;                            break;
	case BG_YELLOW:  win_bg = BACKGROUND_RED | BACKGROUND_GREEN;           break;
	case BG_BLUE:    win_bg = BACKGROUND_BLUE;                             break;
	case BG_MAGENTA: win_bg = BACKGROUND_RED | BACKGROUND_BLUE;            break;
	case BG_CYAN:    win_bg = BACKGROUND_GREEN | BACKGROUND_BLUE;          break;
	case BG_WHITE:   win_bg = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; break;
	default:         win_bg = 0;                                           break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
	                        FOREGROUND_INTENSITY | win_fg | win_bg);
#else
	std::cout << "\033[" << foreground << ";" << (background + 10) << "m";
	std::cout.flush();
#endif
}

// 重置颜色
inline void reset_color() {
#ifdef PLATFORM_WINDOWS
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
	                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
	std::cout << "\033[0m";
	std::cout.flush();
#endif
}

// 兼容旧代码：1=红 2=绿 3=蓝 4=黄 5=紫 6=青 7=白
inline void color(int colorCode) {
#ifdef PLATFORM_WINDOWS
	int attr = FOREGROUND_INTENSITY;
	switch (colorCode) {
	case 1:  attr |= FOREGROUND_RED;                                    break;
	case 2:  attr |= FOREGROUND_GREEN;                                  break;
	case 3:  attr |= FOREGROUND_BLUE;                                   break;
	case 4:  attr |= FOREGROUND_RED | FOREGROUND_GREEN;                 break;
	case 5:  attr |= FOREGROUND_RED | FOREGROUND_BLUE;                  break;
	case 6:  attr |= FOREGROUND_GREEN | FOREGROUND_BLUE;                break;
	case 7:  attr |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
	default: attr  = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
#else
	static constexpr int ansi_map[8] = {37, 31, 32, 34, 33, 35, 36, 37};
	int fg = (colorCode >= 0 && colorCode <= 7) ? ansi_map[colorCode] : 37;
	std::cout << "\033[1;" << fg << "m";
	std::cout.flush();
#endif
}

// 兼容 system("color XX") — 两个十六进制数字，第一个背景，第二个前景
inline void system_color(int code) {
#ifdef PLATFORM_WINDOWS
	char cmd[16];
	snprintf(cmd, sizeof(cmd), "color %02X", code);
	system(cmd);
#else
	int bg = (code >> 4) & 0x0F;
	int fg = code & 0x0F;

	std::function<int(int)> map_color = [&map_color](int c) -> int {
		if (c <= 7) {
			static constexpr int ansi[8] = {30, 34, 32, 36, 31, 35, 33, 37};
			return ansi[c];
		}
		return map_color(c - 8);
	};

	std::cout << "\033[" << map_color(fg) << ";" << (map_color(bg) + 10) << "m";
	std::cout.flush();
#endif
}

// 光标控制
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

// 获取终端窗口大小
inline void get_terminal_size(int& width, int& height) {
#ifdef PLATFORM_WINDOWS
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		width  = csbi.srWindow.Right  - csbi.srWindow.Left + 1;
		height = csbi.srWindow.Bottom - csbi.srWindow.Top  + 1;
	} else {
		width = 80; height = 24;
	}
#else
	struct winsize w;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0 && w.ws_col > 0 && w.ws_row > 0) {
		width  = w.ws_col;
		height = w.ws_row;
	} else {
		const char* cols = std::getenv("COLUMNS");
		const char* lines = std::getenv("LINES");
		if (cols && lines) {
			width  = std::atoi(cols);
			height = std::atoi(lines);
		} else {
			width = 80; height = 24;
		}
	}
#endif
	if (width  <= 0) width  = 80;
	if (height <= 0) height = 24;
}

// 全屏 — 仅 Windows 有控制台 API 支持
inline void full_screen() {
#ifdef PLATFORM_WINDOWS
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
#endif
}

} // namespace platform

// ============ getch() 键盘输入（跨平台） ============

#ifdef PLATFORM_POSIX
namespace {

inline int getch_impl() {
	struct termios oldattr, newattr;
	int ch;

	// 保存当前终端属性，设为原始模式
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);  // 非行缓冲，无回显
	newattr.c_cc[VMIN]  = 1;              // 至少读 1 字节
	newattr.c_cc[VTIME] = 0;              // 无限等待
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

	ch = getchar();

	// 检查方向键序列: ESC [ A/B/C/D (3 字节)
	if (ch == 27) {  // ESC
		newattr.c_cc[VMIN]  = 0;
		newattr.c_cc[VTIME] = 1;  // 0.1 秒超时
		tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

		int ch2 = getchar();
		if (ch2 == '[') {
			int ch3 = getchar();
			tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
			switch (ch3) {
			case 'A': return 'H';  // 上
			case 'B': return 'P';  // 下
			case 'C': return 'M';  // 右
			case 'D': return 'K';  // 左
			default:  return 27;
			}
		}
	}

	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	return ch;
}

} // anonymous namespace

#define getch getch_impl

#endif // PLATFORM_POSIX

// ============ 方向键映射 ============
constexpr char KEY_LEFT  = 'K';
constexpr char KEY_RIGHT = 'M';
constexpr char KEY_UP    = 'H';
constexpr char KEY_DOWN  = 'P';

// ============ Sleep 兼容宏 ============
#ifdef PLATFORM_POSIX
#define Sleep(ms) platform::sleep_ms(ms)
#endif

#endif // PLATFORM_H
