#ifndef RANDOM_EVENT_H
#define RANDOM_EVENT_H

#include <string>
#include <vector>
#include <map>
#include <functional>

struct RandomEvent {
    std::string id;
    std::string description;
    float probability;
    std::function<bool()> condition;
    std::function<void()> effect;
    int cooldown;
};

class RandomEventSystem {
public:
    static RandomEventSystem& instance();

    void register_event(const RandomEvent& event);
    void try_trigger();
    void reset_cooldowns();

private:
    std::vector<RandomEvent> events_;
    std::map<std::string, int> last_trigger_turn_;
};

#endif
