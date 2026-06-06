#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include <string>
#include <vector>

bool save_game(const std::string& slot_name);
bool load_game(const std::string& slot_name);
void list_saves();
bool delete_save(const std::string& slot_name);

#endif
