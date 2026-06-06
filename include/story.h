#ifndef STORY_H
#define STORY_H

#include <map>
#include <string>
#include <sstream>

// ============ 全局变量声明 ============
extern int random_val;
extern std::map<int, std::string> rooms;
extern std::map<int, char> alph;
extern std::map<int, std::string> dire;
extern int Prooms;

extern bool chap1, chap2, chap3;
extern std::string Chap1, Chap2, Chap3;

extern bool ingame;

// ============ 函数声明 ============
// 工具函数
int quit();
void Alph();
void Dire();
void checkpoint(int place = 0);

// 导航
void reborn();
void where();

// 第一章
void a1();
void a1a();
void a1aa();
void a1b();

// 第二章
void a2();
void a2_1();
void a2_2();

// 第三章（地狱）
void a3();
void a3_hell_define();
void a3_hell();
void sy();
void ba();
void qd();
void dd();
void hd();
void hh();
void fh();

// 章节预留入口（原 Abyss.cpp 中存在为空函数）
void b1();   // 第二章独立剧情
void c1();   // 第三章独立剧情

// 调试
void debug();

// 主菜单
void choice();

#endif // STORY_H
