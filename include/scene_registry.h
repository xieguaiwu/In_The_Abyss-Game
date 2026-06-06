#ifndef SCENE_REGISTRY_H
#define SCENE_REGISTRY_H

#include <string>
#include <vector>

struct SceneDef {
    std::string id;
    std::string label;
    std::string chapter;
    void (*func)();
    bool is_unlocked;
};

void register_scene(const SceneDef& scene);
bool execute_scene(const std::string& id);
void list_registered_scenes();
void empty_scene_placeholder();

// 章节预留入口（原 Abyss.cpp 中存在为空函数）
void b1();
void c1();

#endif
