#ifndef ROOM_REGISTRY_H
#define ROOM_REGISTRY_H

#include <string>
#include <vector>

// 房间 ID 枚举（兼容旧浮点坐标系统：原浮点值 ×10 取整）
enum RoomID {
    // 已有地狱房间
    ROOM_ABYSS       = 0,
    ROOM_FLOWER      = -10,
    ROOM_FRONT_HALL  = -20,
    ROOM_MAIN_HALL   = -30,
    ROOM_BACK_HALL   = -40,
    ROOM_BACK_GARDEN = -41,   // 旧坐标 -4.1
    ROOM_HELL_FIRE   = -51,   // 旧坐标 -5.1
    ROOM_CORRIDOR    = -35,   // 旧坐标 -3.5
    ROOM_WING        = -45,   // 旧坐标 -4.5

    // 扩展预留
    ROOM_YELLOW_SPRING_ROAD = 10,
    ROOM_JUDGE_PAVILION     = -22,
    ROOM_FLAME_MOUNTAIN     = -60,
    ROOM_WANGXIANG_TERRACE  = -55,
    ROOM_NIECHENG           = 20,
    ROOM_MEMORY_CHAMBER     = -70,
};

// 房间定义
struct RoomDef {
    int id;
    const char* name;
    int north, south, west, east;
    void (*on_enter)();     // nullptr = 暂无场景函数
};

// 房间注册表（C 数组，固定大小）
extern const RoomDef room_table[];
extern const int room_table_size;

const RoomDef* find_room(int id);
int room_id_from_old_coord(float old_coord);
bool is_valid_room(int id);
bool load_rooms_from_json(const std::string& path);

#endif
