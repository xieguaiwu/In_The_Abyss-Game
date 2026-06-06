#include "room_registry.h"
#include "nlohmann/json.hpp"
#include <fstream>

const RoomDef room_table[] = {
    // 现有地狱房间
    { ROOM_ABYSS,       "深渊",           0,    -10,   0,    0,    nullptr },
    { ROOM_FLOWER,      "彼岸花丛",       -20,   0,    0,   -41,   nullptr },
    { ROOM_FRONT_HALL,  "秦广王殿-前殿",  -30,   0,    0,    0,    nullptr },
    { ROOM_MAIN_HALL,   "秦广王殿-大殿",  -40,  -35,  -41,  -45,   nullptr },
    { ROOM_BACK_HALL,   "秦广王殿-后殿",   0,    0,    0,    0,    nullptr },
    { ROOM_BACK_GARDEN, "后花园",          0,    0,   -35,   0,    nullptr },
    { ROOM_HELL_FIRE,   "地狱乏火",        0,    0,    0,    0,    nullptr },
    { ROOM_CORRIDOR,    "走廊",            0,    0,    0,    0,    nullptr },
    { ROOM_WING,        "偏殿",            0,    0,    0,    0,    nullptr },

    // 扩展预留
    { ROOM_YELLOW_SPRING_ROAD, "黄泉路",     0, 0, 0, 0, nullptr },
    { ROOM_JUDGE_PAVILION,     "判官厅",     0, 0, 0, 0, nullptr },
    { ROOM_FLAME_MOUNTAIN,     "火焰山",     0, 0, 0, 0, nullptr },
    { ROOM_WANGXIANG_TERRACE,  "望乡台",     0, 0, 0, 0, nullptr },
    { ROOM_NIECHENG,           "孽镜台",     0, 0, 0, 0, nullptr },
    { ROOM_MEMORY_CHAMBER,     "记忆回廊",   0, 0, 0, 0, nullptr },
};

const int room_table_size = sizeof(room_table) / sizeof(room_table[0]);

const RoomDef* find_room(int id) {
    for (int i = 0; i < room_table_size; ++i) {
        if (room_table[i].id == id) return &room_table[i];
    }
    return nullptr;
}

int room_id_from_old_coord(float old_coord) {
    // 旧系统编码：N=+1, S=-1, W=-0.1, E=+0.1
    // 转换成整数：乘以10，去掉小数部分
    return static_cast<int>(old_coord * 10);
}

bool is_valid_room(int id) {
    return find_room(id) != nullptr;
}

bool load_rooms_from_json(const std::string& path) {
    std::ifstream f(path);
    if (!f) return false;
    try {
        auto j = nlohmann::json::parse(f);
        // JSON 加载器已就绪，未来可将 room_table 替换为 JSON 数据
        return true;
    } catch (...) {
        return false;
    }
}
