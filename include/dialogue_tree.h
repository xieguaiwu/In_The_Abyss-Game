#ifndef DIALOGUE_TREE_H
#define DIALOGUE_TREE_H

#include <string>
#include <vector>

struct DialogueOption {
    char key;
    std::string label;
    int next_node_id;
    std::string set_flag;
    std::string required_flag;
};

struct DialogueNode {
    int id;
    std::string speaker;
    std::string text;
    std::vector<DialogueOption> options;
    std::string on_enter_flag;
};

class DialogueTree {
public:
    DialogueTree() : current_node_(-1), active_(false) {}
    explicit DialogueTree(const std::vector<DialogueNode>& nodes);

    void load(const std::vector<DialogueNode>& nodes);
    bool load_from_json(const std::string& path);
    void start(int root_node_id);
    void reset();
    bool is_active() const { return active_; }

private:
    std::vector<DialogueNode> nodes_;
    int current_node_;
    bool active_;
};

#endif
