#include <iostream>
#include <algorithm>
#include "dialogue_tree.h"
#include "platform.h"
#include "game_state.h"

DialogueTree::DialogueTree(const std::vector<DialogueNode>& nodes)
    : nodes_(nodes), current_node_(-1), active_(false) {}

void DialogueTree::load(const std::vector<DialogueNode>& nodes) {
    nodes_ = nodes;
    reset();
}

void DialogueTree::reset() {
    current_node_ = -1;
    active_ = false;
}

void DialogueTree::start(int root_node_id) {
    auto it = std::find_if(nodes_.begin(), nodes_.end(),
        [root_node_id](const DialogueNode& n) { return n.id == root_node_id; });
    if (it == nodes_.end()) return;

    current_node_ = std::distance(nodes_.begin(), it);
    active_ = true;

    while (active_ && current_node_ >= 0 && current_node_ < (int)nodes_.size()) {
        DialogueNode& node = nodes_[current_node_];

        if (!node.on_enter_flag.empty())
            GameState::instance().set_flag(node.on_enter_flag);

        if (!node.speaker.empty())
            std::cout << "【" << node.speaker << "】 ";
        std::cout << node.text << "\n";

        if (node.options.empty()) {
            std::cout << "（按任意键继续）\n";
            getch();
            break;
        }

        std::vector<DialogueOption> available;
        for (const auto& opt : node.options) {
            if (!opt.required_flag.empty() &&
                !GameState::instance().check_flag(opt.required_flag))
                continue;
            available.push_back(opt);
        }

        if (available.empty()) break;

        for (const auto& opt : available)
            std::cout << opt.key << "." << opt.label << "\n";

        char ch;
        bool chosen = false;
        while (!chosen) {
            ch = getch();
            for (const auto& opt : available) {
                if (ch == opt.key || ch == (opt.key - 'A' + 'a')) {
                    if (!opt.set_flag.empty())
                        GameState::instance().set_flag(opt.set_flag);
                    if (opt.next_node_id == -1) {
                        active_ = false;
                        chosen = true;
                        break;
                    }
                    auto next = std::find_if(nodes_.begin(), nodes_.end(),
                        [&](const DialogueNode& n) { return n.id == opt.next_node_id; });
                    if (next != nodes_.end())
                        current_node_ = std::distance(nodes_.begin(), next);
                    else
                        active_ = false;
                    chosen = true;
                    break;
                }
            }
        }
        if (!active_) break;
    }
}
