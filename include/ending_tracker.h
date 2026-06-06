#ifndef ENDING_TRACKER_H
#define ENDING_TRACKER_H

#include <string>
#include <vector>

struct EndingDef {
    std::string id;
    std::string title;
    std::string description;
    bool hidden;
    bool (*condition)();
};

class EndingTracker {
public:
    static EndingTracker& instance();
    void register_ending(const EndingDef& ending);
    void check_all();
    bool is_unlocked(const std::string& id);
    void list_unlocked();
    int total_unlocked();

private:
    std::vector<EndingDef> endings_;
    std::vector<std::string> unlocked_;
};

#endif
