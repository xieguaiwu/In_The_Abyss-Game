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
	platform::system_color(0x81);
}

void light() {
	platform::system_color(0x64);
}

void hell() {
	platform::system_color(0x47);
}

void light_hell() {
	platform::system_color(0x57);
}

void open() {
	platform::system_color(0x47);
	puts("[           -在深渊-           ]");
	Lwait();
	platform::system_color(0x74);
	Swait();
	platform::system_color(0x47);
	Mwait();
	platform::system_color(0x74);
	Swait();
	platform::system_color(0x47);
	Mwait();
	platform::clear_screen();
	puts("[         -In the Abyss-         ]");
	Lwait();
	platform::system_color(0x74);
	Swait();
	platform::system_color(0x47);
	Mwait();
	platform::system_color(0x74);
	Swait();
	platform::system_color(0x47);
	Mwait();
	platform::clear_screen();
	puts("[     Made By 齂怪物、地有小到中雨     ]");
	Lwait();
	platform::system_color(0x74);
	Swait();
	platform::system_color(0x47);
	Mwait();
	platform::system_color(0x74);
	Swait();
	platform::system_color(0x47);
	Mwait();
	platform::clear_screen();
}
