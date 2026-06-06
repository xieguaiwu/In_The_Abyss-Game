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
	register_scene({"ch1_city", "第一章·城市", "第一章", a1, true});
	register_scene({"ch2_office", "第二章·办公室", "第二章", a2, true});
	register_scene({"ch3_hell", "第三章·地狱", "第三章", a3, true});
	register_scene({"ch3_debug", "调试·地狱", "调试", debug, true});
	register_scene({"ch2_independent", "第二章·独立剧情", "第二章", b1, false});
	register_scene({"ch3_independent", "第三章·独立剧情", "第三章", c1, false});
}

void choice() {
	open();
	Alph(); Dire();
	platform::system_color(0xB1);
	pause_game(1);
	register_legacy_scenes();
	GameState::instance();
	EndingTracker::instance();
}

int main() {
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	while (true) {
		if (ingame == false) choice();
		platform::system_color(0xC7);
		std::cout << "第一章 " << Chap1 << "----";
		chap1 = true; std::cout << "已解锁\n";

		std::cout << "第二章 " << Chap2 << "----";
		if (chap2 == false) std::cout << "未解锁\n";
		else std::cout << "已解锁\n";

		std::cout << "第三章 " << Chap3 << "----";
		if (chap3 == false) std::cout << "未解锁\n";
		else std::cout << "已解锁\n";
		pause_game();
		std::cout << "\n玩哪一章？\nA.第一章\nB.第二章\nC.第三章\nD.退出游戏\n";
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
				return 0;
			}
		}
		if (!restart) break;
	}
	return 0;
}
