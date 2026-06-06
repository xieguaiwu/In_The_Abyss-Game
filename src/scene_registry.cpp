#include <iostream>
#include <algorithm>
#include "scene_registry.h"

static std::vector<SceneDef> g_scenes;

void register_scene(const SceneDef& scene) {
    g_scenes.push_back(scene);
}

bool execute_scene(const std::string& id) {
    for (const auto& s : g_scenes) {
        if (s.id == id) {
            if (s.func) s.func();
            return true;
        }
    }
    std::cout << "【场景 " << id << "】未注册\n";
    return false;
}

void list_registered_scenes() {
    std::cout << "已注册场景 (" << g_scenes.size() << "):\n";
    for (const auto& s : g_scenes) {
        std::cout << "  [" << s.chapter << "] " << s.id << " - " << s.label
                  << (s.is_unlocked ? " (已解锁)" : " (未解锁)") << "\n";
    }
}

void empty_scene_placeholder() {
    // 框架占位，无实际剧情内容
}

void b1() {
    // 第二章独立剧情——预留
}

void c1() {
    // 第三章独立剧情——预留
}
