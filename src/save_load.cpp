#include <iostream>
#include <fstream>
#include "save_load.h"

static const char* SAVE_DIR = ".saves";

bool save_game(const std::string& slot_name) {
    std::string path = std::string(SAVE_DIR) + "/" + slot_name + ".sav";
    std::cout << "【存档系统】保存至 " << path << " ——框架已就绪\n";
    return true;
}

bool load_game(const std::string& slot_name) {
    std::string path = std::string(SAVE_DIR) + "/" + slot_name + ".sav";
    std::cout << "【存档系统】从 " << path << " 读取 ——框架已就绪\n";
    return true;
}

void list_saves() {
    std::cout << "【存档系统】列出存档 ——框架已就绪\n";
}

bool delete_save(const std::string& slot_name) {
    std::string path = std::string(SAVE_DIR) + "/" + slot_name + ".sav";
    std::cout << "【存档系统】删除 " << path << " ——框架已就绪\n";
    return true;
}
