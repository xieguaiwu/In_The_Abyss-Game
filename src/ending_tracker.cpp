#include <iostream>
#include <algorithm>
#include "ending_tracker.h"

EndingTracker& EndingTracker::instance() {
    static EndingTracker et;
    return et;
}

void EndingTracker::register_ending(const EndingDef& ending) {
    endings_.push_back(ending);
}

void EndingTracker::check_all() {
    for (const auto& e : endings_) {
        if (std::find(unlocked_.begin(), unlocked_.end(), e.id) != unlocked_.end())
            continue;
        if (e.condition && e.condition()) {
            unlocked_.push_back(e.id);
            if (!e.hidden)
                std::cout << "解锁结局【" << e.title << "】\n";
        }
    }
}

bool EndingTracker::is_unlocked(const std::string& id) {
    return std::find(unlocked_.begin(), unlocked_.end(), id) != unlocked_.end();
}

void EndingTracker::list_unlocked() {
    if (unlocked_.empty()) {
        std::cout << "尚无已解锁结局\n";
        return;
    }
    std::cout << "已解锁结局/成就 (" << unlocked_.size() << "):\n";
    for (const auto& id : unlocked_) {
        for (const auto& e : endings_) {
            if (e.id == id) {
                std::cout << "  ✦ " << e.title;
                if (!e.description.empty())
                    std::cout << " — " << e.description;
                std::cout << "\n";
            }
        }
    }
}

int EndingTracker::total_unlocked() {
    return unlocked_.size();
}
