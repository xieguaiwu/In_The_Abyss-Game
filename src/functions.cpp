#include "functions.h"

void pause_game(int screen) {
	std::cout << "（按下任意键继续……）\n";
	getch();
	if (screen == 1) platform::clear_screen();
}

void text(const std::string& texttoprint, int Screen) {
	std::cout << texttoprint;
	getch();
	std::cout << "\n";
	if (Screen == 1) platform::clear_screen();
}

void Lwait() {
	platform::sleep_ms(500);
}

void Mwait() {
	platform::sleep_ms(300);
}

void Swait() {
	platform::sleep_ms(20);
}

void hyphen(int shan) {
	if (shan == 0) std::cout << "----------------------------------------\n";
	else if (shan == 1) std::cout << "****************************************\n";
	else if (shan == 2) std::cout << "++++++++++++++++++++++++++++++++++++++++\n";
	else if (shan == 3) std::cout << "========================================\n";
	else if (shan == 4) std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
	else if (shan == 5) std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
	else if (shan == 250) std::cout << "---Cheating Line-Cheating Line-Cheating Line-Cheating Line-Cheating Line---\n";
}

void colorc(int x) {
	platform::color(x);
}

int r(int min, int max) {
	if (max <= min) return min;
	return min + rand() % (max - min);
}

void city() {
	// 标准白字黑底，阅读清晰不刺眼
	platform::system_color(0x07);
}

void light() {
	platform::system_color(0x64);
}

void hell() {
	// 红底黑字：地狱氛围 + 高对比度可读
	platform::system_color(0x40);
}

void light_hell() {
	// 紫底黑字：地狱+微弱光线，仍保持清晰
	platform::system_color(0x50);
}

void open() {
	// 跳过检测辅助函数
	auto check_skip = []() -> bool {
		if (try_getch() != -1) {
			flush_input();
			platform::clear_screen();
			platform::system_color(0x07);
			return true;
		}
		return false;
	};

	std::cout << "（按任意键跳过开场动画）\n";

	// === 第一行 ===
	platform::system_color(0x06);
	puts("[           -在深渊-           ]");
	platform::sleep_ms(500); if (check_skip()) return;
	platform::system_color(0x07);
	platform::sleep_ms(20);  if (check_skip()) return;
	platform::system_color(0x06);
	platform::sleep_ms(300); if (check_skip()) return;
	platform::system_color(0x07);
	platform::sleep_ms(20);  if (check_skip()) return;
	platform::system_color(0x06);
	platform::sleep_ms(300); if (check_skip()) return;
	platform::clear_screen();

	// === 第二行 ===
	puts("[         -In the Abyss-         ]");
	platform::sleep_ms(500); if (check_skip()) return;
	platform::system_color(0x07);
	platform::sleep_ms(20);  if (check_skip()) return;
	platform::system_color(0x06);
	platform::sleep_ms(300); if (check_skip()) return;
	platform::system_color(0x07);
	platform::sleep_ms(20);  if (check_skip()) return;
	platform::system_color(0x06);
	platform::sleep_ms(300); if (check_skip()) return;
	platform::clear_screen();

	// === 第三行 ===
	puts("[     Made By 齂怪物、地有小到中雨     ]");
	platform::sleep_ms(500); if (check_skip()) return;
	platform::system_color(0x07);
	platform::sleep_ms(20);  if (check_skip()) return;
	platform::system_color(0x06);
	platform::sleep_ms(300); if (check_skip()) return;
	platform::system_color(0x07);
	platform::sleep_ms(20);  if (check_skip()) return;
	platform::system_color(0x06);
	platform::sleep_ms(300); if (check_skip()) return;
	platform::clear_screen();
}
