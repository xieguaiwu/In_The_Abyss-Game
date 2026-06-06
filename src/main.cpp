#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "platform.h"
#include "common_vars.h"
#include "functions.h"
#include "story.h"
#include "game_state.h"
#include "room_registry.h"
#include "scene_registry.h"
#include "ending_tracker.h"
#include "save_load.h"
#include "random_event.h"

char key;

int quit() {
	std::cout << "再见！"; pause_game(1);
	return 0;
}

void Alph() {
	alph[1] = 'A';
	alph[2] = 'B';
	alph[3] = 'C';
	alph[4] = 'D';
	alph[5] = 'E';
	alph[6] = 'F';
	alph[7] = 'G';
	alph[8] = 'H';
	alph[9] = 'I';
	alph[10] = 'J';
	alph[11] = 'K';
	alph[12] = 'L';
	alph[13] = 'M';
	alph[14] = 'N';
	alph[15] = 'O';
	alph[16] = 'P';
	alph[17] = 'Q';
	alph[18] = 'R';
	alph[19] = 'S';
	alph[20] = 'T';
	alph[21] = 'U';
	alph[22] = 'V';
	alph[23] = 'W';
	alph[24] = 'X';
	alph[25] = 'Y';
	alph[26] = 'Z';
}

void Dire() {
	dire[1] = "北";
	dire[2] = "南";
	dire[3] = "西";
	dire[4] = "东";
}

void debug() {
	a3_hell_define();
	a3_hell();
}

// 注册所有现有场景到场景注册表（供扩展系统发现）
static void register_legacy_scenes() {
	static bool registered = false;
	if (registered) return;  // 防止重复注册
	registered = true;
	register_scene({"ch1_city", "第一章·城市", "第一章", a1, true});
	register_scene({"ch2_office", "第二章·办公室", "第二章", a2, true});
	register_scene({"ch3_hell", "第三章·地狱", "第三章", a3, true});
	register_scene({"ch3_debug", "调试·地狱", "调试", debug, true});
	register_scene({"ch2_independent", "第二章·独立剧情", "第二章", b1, false});
	register_scene({"ch3_independent", "第三章·独立剧情", "第三章", c1, false});
}

// 一次性初始化（只在程序启动时执行一次）
static void init_game() {
	open();
	Alph(); Dire();
	platform::system_color(0x07);
	pause_game(1);
	register_legacy_scenes();

	// 注册示例随机事件，让随机系统有内容可触发
	RandomEventSystem::instance().register_event({
		"hell_whisper", "你听到远方传来低语……", 0.15f,
		[]{ return GameState::instance().visited("sy") > 0; },
		[]{ std::cout << "【低语】继续向前…不要回头…\n"; },
		5
	});

	// 注册示例结局
	EndingTracker::instance().register_ending({
		"abyss_gaze", "深渊凝视", "你在深渊中看到了自己的倒影",
		false,
		[]{ return GameState::instance().check_flag("look_clear"); }
	});

	GameState::instance();
	EndingTracker::instance();
}

// 使用 getch 读取一行输入（避免 std::cin 与 raw 模式冲突）
static std::string read_line_raw() {
	std::string result;
	char ch;
	while (true) {
		ch = getch();
		if (ch == '\r' || ch == '\n') {
			std::cout << '\n';
			break;
		}
		if (ch == 127 || ch == '\b') {
			if (!result.empty()) {
				result.pop_back();
				std::cout << "\b \b";
			}
		}
		else if (ch >= 32 && ch <= 126) {
			result += ch;
			std::cout << ch;
		}
	}
	return result;
}

// 存档管理子菜单
static void save_menu() {
	platform::clear_screen();
	platform::system_color(0x07);
	while (true) {
		std::cout << "=== 存档管理 ===\n";
		std::cout << "A.保存游戏\nB.读取存档\nC.查看存档列表\nD.删除存档\nE.返回主菜单\n";
		key = getch();
		if (key == 'A' || key == 'a') {
			std::cout << "请输入存档名称: ";
			std::string name = read_line_raw();
			save_game(name);
			pause_game();
			platform::clear_screen();
		}
		else if (key == 'B' || key == 'b') {
			list_saves();
			std::cout << "请输入要读取的存档名称: ";
			std::string name = read_line_raw();
			if (load_game(name)) {
				std::cout << "读取成功！请选择章节继续游戏。\n";
			}
			pause_game();
			platform::clear_screen();
		}
		else if (key == 'C' || key == 'c') {
			list_saves();
			pause_game();
			platform::clear_screen();
		}
		else if (key == 'D' || key == 'd') {
			list_saves();
			std::cout << "请输入要删除的存档名称: ";
			std::string name = read_line_raw();
			delete_save(name);
			pause_game();
			platform::clear_screen();
		}
		else if (key == 'E' || key == 'e') {
			break;  // 返回主菜单
		}
	}
}

int main() {
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	init_game();  // 只调用一次：开场动画 + 初始化

	while (true) {
		platform::system_color(0x06);
		std::cout << "第一章 " << Chap1 << "----";
		chap1 = true; std::cout << "已解锁\n";

		std::cout << "第二章 " << Chap2 << "----";
		if (chap2 == false) std::cout << "未解锁\n";
		else std::cout << "已解锁\n";

		std::cout << "第三章 " << Chap3 << "----";
		if (chap3 == false) std::cout << "未解锁\n";
		else std::cout << "已解锁\n";
		pause_game();
		std::cout << "\n玩哪一章？\nA.第一章\nB.第二章\nC.第三章\nD.存档管理\nE.退出游戏\n";
		bool restart = false;
		while (1) {
			key = getch();
			if (key == 'A' || key == 'a') {
				a1();
				checkpoint();
				if (key == 'B' || key == 'b') {
					restart = true;
					break;
				}
				else if (key == 'C' || key == 'c') break;
				hyphen();
				a2();
				if (ingame) {
					ingame = false;
					restart = true;
					break;
				}
				break;
			}
			else if (key == 'B' || key == 'b') {
				if (chap2 == false) {
					std::cout << "这一章尚未解锁，另选一个！\n"; hyphen();
				}
				else {
					b1();
					restart = true;
					break;
				}
			}
			else if (key == 'C' || key == 'c') {
				if (chap3 == false) {
					std::cout << "这一章尚未解锁，另选一个！\n"; hyphen();
				}
				else {
					c1();
					restart = true;
					break;
				}
			}
			else if (key == 'D' || key == 'd') {
				save_menu();
				restart = true;  // 存档结束后返回主菜单
				break;
			}
			else if (key == 'E' || key == 'e') {
				return 0;
			}
		}
		// restart=true → 继续循环显示菜单；restart=false → 退出程序
		if (!restart) break;
	}
	return 0;
}
