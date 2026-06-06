#include "story.h"

// ============ 全局变量定义 ============
int random_val;
std::map<float, std::string> rooms;
std::map<int, char> alph;
std::map<int, std::string> dire;
float Prooms;

bool chap1 = true, chap2 = true, chap3 = true;
std::string Chap1 = "在起初，地狱乏火与死之人间";
std::string Chap2 = "";
std::string Chap3 = "";

bool ingame = false;
