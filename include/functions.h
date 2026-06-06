#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <map>
#include <string>
#include <ctime>
#include <cstdlib>
#include "platform.h"
#include "common_vars.h"
#include "print.h"

// 颜色
#define red 1
#define green 2
#define blue 3
#define yellow 4
#define purple 5
#define lime 6
#define white 7

void pause_game(int screen = 0);
void text(const std::string& texttoprint, int Screen = 0);
void Lwait();
void Mwait();
void Swait();
void hyphen(int shan = 0);
void colorc(int x);
int r(int min, int max);
void city();
void light();
void hell();
void light_hell();
void open();

#endif // FUNCTIONS_H
