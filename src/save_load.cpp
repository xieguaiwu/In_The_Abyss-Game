#include "save_load.h"
#include "game_state.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>

namespace fs = std::filesystem;
static const char* SAVE_DIR = ".saves";

struct SaveHeader {
    std::string slot_name;
    std::string timestamp;
    int turn_count;
    std::map<std::string, int> visit_count;
    std::map<std::string, bool> flags;
    std::vector<std::string> inventory;
};

void to_json(nlohmann::json& j, const SaveHeader& s) {
    j = nlohmann::json{
        {"slot", s.slot_name},
        {"timestamp", s.timestamp},
        {"turn_count", s.turn_count},
        {"visit_count", s.visit_count},
        {"flags", s.flags},
        {"inventory", s.inventory}
    };
}

void from_json(const nlohmann::json& j, SaveHeader& s) {
    j.at("slot").get_to(s.slot_name);
    j.at("timestamp").get_to(s.timestamp);
    j.at("turn_count").get_to(s.turn_count);
    j.at("visit_count").get_to(s.visit_count);
    j.at("flags").get_to(s.flags);
    j.at("inventory").get_to(s.inventory);
}

bool save_game(const std::string& slot_name) {
    fs::create_directories(SAVE_DIR);
    auto& gs = GameState::instance();

    SaveHeader header;
    header.slot_name = slot_name;
    std::time_t t = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
    header.timestamp = buf;
    header.turn_count = gs.turn_count;
    header.visit_count = gs.visit_count;
    header.flags = gs.flags;
    header.inventory = gs.inventory;

    std::string path = std::string(SAVE_DIR) + "/" + slot_name + ".json";
    std::ofstream f(path);
    if (!f) return false;
    nlohmann::json j = header;
    f << j.dump(2);
    std::cout << "【存档】已保存至 " << slot_name << "\n";
    return true;
}

bool load_game(const std::string& slot_name) {
    std::string path = std::string(SAVE_DIR) + "/" + slot_name + ".json";
    std::ifstream f(path);
    if (!f) return false;
    try {
        nlohmann::json j;
        f >> j;
        SaveHeader header = j.get<SaveHeader>();
        auto& gs = GameState::instance();
        gs.visit_count = header.visit_count;
        gs.flags = header.flags;
        gs.inventory = header.inventory;
        gs.turn_count = header.turn_count;
        std::cout << "【读档】已读取 " << slot_name << "\n";
        return true;
    } catch (...) {
        return false;
    }
}

void list_saves() {
    fs::create_directories(SAVE_DIR);
    std::cout << "【存档列表】\n";
    for (auto& entry : fs::directory_iterator(SAVE_DIR)) {
        if (entry.path().extension() == ".json") {
            std::ifstream f(entry.path());
            if (f) {
                try {
                    nlohmann::json j;
                    f >> j;
                    std::cout << "  " << j["slot"].get<std::string>()
                              << " (" << j["timestamp"].get<std::string>() << ")"
                              << " [回合 " << j["turn_count"].get<int>() << "]\n";
                } catch (...) {}
            }
        }
    }
}

bool delete_save(const std::string& slot_name) {
    std::string path = std::string(SAVE_DIR) + "/" + slot_name + ".json";
    bool removed = fs::remove(path);
    if (removed)
        std::cout << "【存档】已删除 " << slot_name << "\n";
    return removed;
}
