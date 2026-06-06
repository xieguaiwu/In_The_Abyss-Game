#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

// 统一状态注册表，替代散落的全局变量
struct GameState {
    std::map<std::string, int> visit_count;
    std::map<std::string, bool> flags;
    std::vector<std::string> inventory;
    int turn_count = 0;

    static GameState& instance() {
        static GameState gs;
        return gs;
    }

    int visit(const std::string& key) { return ++visit_count[key]; }
    int visited(const std::string& key) const {
        auto it = visit_count.find(key);
        return (it != visit_count.end()) ? it->second : 0;
    }

    void set_flag(const std::string& key, bool val = true) { flags[key] = val; }
    bool check_flag(const std::string& key) const {
        auto it = flags.find(key);
        return it != flags.end() && it->second;
    }

    void add_item(const std::string& item) { inventory.push_back(item); }
    bool has_item(const std::string& item) {
        return std::find(inventory.begin(), inventory.end(), item) != inventory.end();
    }
    void remove_item(const std::string& item) {
        auto it = std::find(inventory.begin(), inventory.end(), item);
        if (it != inventory.end()) inventory.erase(it);
    }

    // ===== 任务系统 =====
    struct QuestCondition {
        std::string flag;
        bool expected = true;
    };

    struct QuestDef {
        std::string id;
        std::string title;
        std::vector<QuestCondition> conditions;
        std::string completion_flag;
    };

    void register_quest(const QuestDef& quest) {
        quest_defs_.push_back(quest);
    }

    void check_quests() {
        for (auto& qd : quest_defs_) {
            if (check_flag(qd.completion_flag)) continue;
            bool all_met = true;
            for (auto& c : qd.conditions) {
                if (check_flag(c.flag) != c.expected) {
                    all_met = false;
                    break;
                }
            }
            if (all_met) {
                set_flag(qd.completion_flag);
                std::cout << "✅ 任务完成：【" << qd.title << "】\n";
            }
        }
    }

private:
    std::vector<QuestDef> quest_defs_;
};

#endif
