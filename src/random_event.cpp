#include <iostream>
#include <cstdlib>
#include "random_event.h"
#include "game_state.h"

RandomEventSystem& RandomEventSystem::instance() {
    static RandomEventSystem res;
    return res;
}

void RandomEventSystem::register_event(const RandomEvent& event) {
    events_.push_back(event);
}

void RandomEventSystem::try_trigger() {
    for (auto& e : events_) {
        auto it = last_trigger_turn_.find(e.id);
        if (it != last_trigger_turn_.end()) {
            int elapsed = GameState::instance().turn_count - it->second;
            if (elapsed < e.cooldown) continue;
        }
        if (e.condition && !e.condition()) continue;
        int roll = rand() % 100;
        if (roll < static_cast<int>(e.probability * 100)) {
            std::cout << "【随机事件】" << e.description << "\n";
            if (e.effect) e.effect();
            last_trigger_turn_[e.id] = GameState::instance().turn_count;
        }
    }
}

void RandomEventSystem::reset_cooldowns() {
    last_trigger_turn_.clear();
}
